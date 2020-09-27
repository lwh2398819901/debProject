#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QProcess>
#include <sys/types.h>
#include <sys/stat.h>
#include "publisherfunc.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QSettings>

using namespace publisherFunc;

#define SHELLSCRICPT "/usr/bin/anbox-appmgr-demo.sh"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //获取apk属性
    readAppPackageNames();
    //读取配置文件
    readConfig();
    //
    m_apkManager=NULL;
    //外部命令调用及信号连接
    m_proces_bash = new QProcess;
    m_proces_bash->start("bash");
    m_proces_bash->waitForStarted();
    connect(m_proces_bash,SIGNAL(readyReadStandardOutput()),this,SLOT(readBashStandardOutputInfo()));
    connect(m_proces_bash,SIGNAL(readyReadStandardError()),this,SLOT(readBashStandardErrorInfo()));
    //获取模板文件内容
    model_control = readFile("./model/control");
    model_postinst = readFile("./model/postinst");
    model_prerm = readFile("./model/prerm");

    //信按钮号连接
    connect(ui->loadDirBtn,&QPushButton::clicked,this,&MainWindow::loadDir);
    connect(ui->outputDirBtn,&QPushButton::clicked,this,&MainWindow::outputDir);
    connect(ui->desktopBtn,&QPushButton::clicked,this,&MainWindow::desktopDir);
    connect(ui->apkDirBtn,&QPushButton::clicked,this,&MainWindow::appDir);
    connect(ui->addApksBtn,&QPushButton::clicked,this,&MainWindow::addApks);
    connect(ui->actionBtn,&QPushButton::clicked,this,&MainWindow::createDirAndDeb);
    connect(ui->apkManagerBtn,&QPushButton::clicked,this,&MainWindow::showApkManager);
}

MainWindow::~MainWindow()
{
    writeConfig();
    delete ui;
}

/********************************外部调用slot函数*************************************/
//加载文件夹
void MainWindow::loadDir()
{
    getDirPath(ui->loadLine);
}

//选择输出文件夹
void MainWindow::outputDir()
{
    getDirPath(ui->outLine);
}

//选择图标文件夹
void MainWindow::desktopDir()
{
    getDirPath(ui->desktoLine);
}

//选择app文件夹
void MainWindow::appDir()
{
    getDirPath(ui->apkDirLine);
}

//添加apk
void MainWindow::addApks()
{
    getDirPath(ui->addApksLine);

    //弹出apk添加窗口


}

void MainWindow::showApkManager()
{
    if(!m_apkManager)
        m_apkManager =new ApkInfoManager(&m_apppAckageNames,NULL);
    m_apkManager->show();
}

//标准输出
void MainWindow::readBashStandardOutputInfo()
{
    QByteArray cmdout = m_proces_bash->readAllStandardOutput();
    ui->textEdit->append(cmdout);
}

//标准错误
void MainWindow::readBashStandardErrorInfo()
{
    QByteArray cmdout = m_proces_bash->readAllStandardError();
    ui->textEdit->append(cmdout);
}

//创建deb
void MainWindow::createDeb(QString debPath, QString debName)
{
    QString str =QString("dpkg  -b  %1  %2\n").arg(debPath).arg(debName);
    m_proces_bash->write(str.toLocal8Bit());
}


/********************************内部调用函数*************************************/
//获取文件夹路径
void MainWindow::getDirPath(QLineEdit *line)
{
    QString filepath = QFileDialog::getExistingDirectory();
    if(!filepath.isEmpty())
        line->setText(filepath);
}

//创建deb及文件
void MainWindow::createDirAndDeb()
{
    m_loadDir = ui->loadLine->text();
    m_outputDir=ui->outLine->text();
    m_desktopDir=ui->desktoLine->text();
    m_apkDir=ui->apkDirLine->text();
    //执行
    if(m_loadDir.isEmpty()||m_outputDir.isEmpty()||m_desktopDir.isEmpty()||m_apkDir.isEmpty())
    {
        QMessageBox::warning(NULL,"错误","目录不能为空");
        return ;
    }
    //获取加载文件夹内所有文件名
    QDir dir(m_loadDir);
    if (dir.exists())
    {
        dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
        bool debFlag = ui->checkBox->checkState()==Qt::CheckState::Checked;
        bool iconFlag = ui->iconCheckBox->checkState()==Qt::CheckState::Checked;

        //在输出目录创建文件夹
        foreach(QString appName,dir.entryList())
        {  

            if(!appName.endsWith(".apk"))
                continue;

            QMap<QString,ApkInfo>::iterator it= m_apppAckageNames.find(appName);
            if(it!=m_apppAckageNames.end())
            {
                ApkInfo apk =it.value();            
                //创建apk debian opt 目录结构
                QString appDir = m_outputDir+"/"+appName.left(appName.size()-4);
                QString DebianDir=appDir+"/DEBIAN/";
                QString optDir=appDir+m_apkDir+"/";
                QString desktopDir=appDir+m_desktopDir+"/";

                dir.mkpath(DebianDir); //递归创建目录结构，appdir目录通过递归创建出来
                dir.mkpath(optDir);
                dir.mkpath(desktopDir);

                //拷贝文件 app icon desktop
                QFile::copy(m_loadDir+"/"+appName,optDir+appName);
                QFile::copy("./anbox_app/"+apk.appIcon,desktopDir+apk.appIcon);
                QFile::copy("./anbox_app/"+apk.appDesktop,desktopDir+apk.appDesktop);

                //创建control postinst prer
                createFile(DebianDir+"control",replaceString(model_control,apk));
                createFile(DebianDir+"postinst",replaceString(model_postinst,apk));
                createFile(DebianDir+"prerm",replaceString(model_prerm,apk));

                //更改权限0755
                chmod((DebianDir+"control").toLocal8Bit().data(),0755);
                chmod((DebianDir+"postinst").toLocal8Bit().data(),0755);
                chmod((DebianDir+"prerm").toLocal8Bit().data(),0755);

                //修改icon文件
                if(iconFlag)
                    iconChanged(apk,desktopDir+apk.appDesktop);
                //创建deb
                if(debFlag)
                    createDeb(appDir,m_outputDir+"/"+apk.debName+"_"+apk.debVersion+"_"+apk.platform+".deb");
            }
            else {
               //弹出错误提示
               QMessageBox::warning(NULL,"错误",QString("error:%1 属性查找不存在  跳过该deb创建").arg(appName));
            }
        }
    }
}

void MainWindow::readAppPackageNames()
{
    //创建json对象，读取json文件
    QByteArray allData = readFile("./android_app.json").toLocal8Bit();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));

    if(json_error.error != QJsonParseError::NoError)
    {
        QMessageBox::warning(NULL,"错误","读取android_app.json文件失败,程序退出");
        exit(1);
    }

    QJsonObject rootObj = jsonDoc.object();

    foreach(QString key,rootObj.keys())
    {
        if(rootObj[key].isObject())
        {
            ApkInfo apk;
            QJsonObject obj= rootObj[key].toObject();
            apk.apkName = key;
            apk.debName=obj.value("debName").toString();
            apk.debVersion=obj.value("debVersion").toString();
            apk.platform=obj.value("platform").toString();
            apk.appDesktop=obj.value("appDesktop").toString();
            apk.appIcon=obj.value("appIcon").toString();
            apk.androidName=obj.value("androidName").toString();
            m_apppAckageNames.insert(key,apk);
        }
    }
}

void MainWindow::writeAppPackageNames()
{
    //对比 m_apppAckageNames是否有变化，无变化不写入
}

QString MainWindow::replaceString(QString src, const ApkInfo &apk)
{
    src.replace("#apkDir#",m_apkDir);
    src.replace("#desktopDir#",m_desktopDir);
    src.replace("#apkName#",apk.apkName);
    src.replace("#debName#",apk.debName.toLower());
    src.replace("#debVersion#",apk.debVersion);
    src.replace("#platform#",apk.platform);
    src.replace("#appDesktop#",apk.appDesktop);
    src.replace("#appIcon#",apk.appIcon);
    src.replace("#androidName#",apk.androidName);
    return src;
}

void MainWindow::iconChanged(const ApkInfo &apk, const QString filePath)
{
    QStringList list =readFile(filePath).split("\n");
    for(QStringList::iterator str = list.begin();str!=list.end();++str)
    {
        if((*str).startsWith("Icon="))
            (*str)="Icon="+this->m_desktopDir+"/"+apk.appIcon;
    }

    QFile f2(filePath);
    if(f2.open(QIODevice::WriteOnly))
    {
        foreach(QString str,list)
            f2.write(str.toLocal8Bit()+"\n");
    }
    f2.close();
}

void MainWindow::readConfig()
{
    QSettings configIni("config.ini", QSettings::IniFormat);
    QString str1 = configIni.value( "mainWindwos/loadLine").toString();
    QString str2 = configIni.value( "mainWindwos/outLine").toString();
    QString str3 = configIni.value( "settings/desktoLine").toString();
    QString str4 = configIni.value( "settings/apkDirLine").toString();

    ui->loadLine->setText(str1);
    ui->outLine->setText(str2);
    ui->desktoLine->setText(str3);
    ui->apkDirLine->setText(str4);

    bool flag1=configIni.value("mainWindwos/debCheckBox").toBool();
    bool flag2=configIni.value("settings/iconCheckBox").toBool();

    ui->checkBox->setChecked(flag1);
    ui->iconCheckBox->setChecked(flag2);
}

void MainWindow::writeConfig()
{

    QString str1=ui->loadLine->text();
    QString str2=ui->outLine->text();
    QString str3=ui->desktoLine->text();
    QString str4=ui->apkDirLine->text();

    bool flag1 = ui->checkBox->checkState()==Qt::CheckState::Checked;
    bool flag2 = ui->iconCheckBox->checkState()==Qt::CheckState::Checked;

    QSettings configIni("config.ini", QSettings::IniFormat);

    configIni.setValue( "mainWindwos/loadLine" ,str1);
    configIni.setValue( "mainWindwos/outLine" ,str2);
    configIni.setValue( "mainWindwos/debCheckBox" ,flag1);

    configIni.setValue( "settings/desktoLine" ,str3);
    configIni.setValue( "settings/apkDirLine" ,str4);
    configIni.setValue( "settings/iconCheckBox" ,flag2);
}




