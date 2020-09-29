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
    connect(ui->loadDirBtn,&QPushButton::clicked,this,&MainWindow::slot_loadAPKDir);
    connect(ui->outputDirBtn,&QPushButton::clicked,this,&MainWindow::slot_outputDir);
    connect(ui->desktopBtn,&QPushButton::clicked,this,&MainWindow::slot_desktopDir);
    connect(ui->apkDirBtn,&QPushButton::clicked,this,&MainWindow::slot_appDir);
    connect(ui->addApksBtn,&QPushButton::clicked,this,&MainWindow::slot_addApkInfo);
    connect(ui->actionBtn,&QPushButton::clicked,this,&MainWindow::slot_createDirAndDeb);
    connect(ui->apkManagerBtn,&QPushButton::clicked,this,&MainWindow::slot_showApkManager);
}

MainWindow::~MainWindow()
{
    writeConfig();
    delete ui;
}
/********************************deb槽函数*************************************/
//加载文件夹
void MainWindow::slot_loadAPKDir()
{
    getDirPath(ui->loadLine);
}
//选择输出文件夹
void MainWindow::slot_outputDir()
{
    getDirPath(ui->outLine);
}
//选择图标文件夹
void MainWindow::slot_desktopDir()
{
    getDirPath(ui->desktoLine);
}
//选择app文件夹
void MainWindow::slot_appDir()
{
    getDirPath(ui->apkDirLine);
}
//创建deb及文件
void MainWindow::slot_createDirAndDeb()
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
    bool debFlag = ui->checkBox->checkState()==Qt::CheckState::Checked;
    bool iconFlag = ui->iconCheckBox->checkState()==Qt::CheckState::Checked;

    QDir dir(m_loadDir);
    //获取文件夹内所有apk文件
    foreach(QString appName,getDirFileNames(m_loadDir,QDir::NoDotAndDotDot | QDir::AllEntries,QStringList()<<"*.apk"))
    {
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

/********************************deb相关内部调用*************************************/
//获取文件夹路径
void MainWindow::getDirPath(QLineEdit *line)
{
    QString filepath = QFileDialog::getExistingDirectory();
    if(!filepath.isEmpty())
        line->setText(filepath);
}
//替换字符
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
//修改icon内容
void MainWindow::iconChanged(const ApkInfo &apk, const QString filePath)
{
    QStringList list =readFile(filePath).split("\n");
    QString text;
    for(QStringList::iterator str = list.begin();str!=list.end();++str)
    {
        if((*str).startsWith("Icon="))
            text += "Icon="+this->m_desktopDir+"/"+apk.appIcon;
        else
            text += (*str+"\n");

    }
    createFile(filePath,text);
}
//创建deb
void MainWindow::createDeb(QString debPath, QString debName)
{
    QString str =QString("dpkg  -b  %1  %2\n").arg(debPath).arg(debName);
    m_proces_bash->write(str.toLocal8Bit());
}
/********************************apkinfo属性相关*************************************/
//读取apk属性
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
//写入apkinfo
void MainWindow::writeAppPackageNames()
{
    //对比 m_apppAckageNames是否有变化，无变化不写入
}



/********************************apkinfo管理*************************************/
//添加apkinfo
void MainWindow::slot_addApkInfo()
{
    getDirPath(ui->addApksLine);

    //弹出apk添加窗口

}

void MainWindow::slot_showApkManager()
{
    if(!m_apkManager)
        m_apkManager =new ApkInfoManager(&m_apppAckageNames,NULL);
    m_apkManager->show();
}

/********************************外部程序输出*************************************/
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


/********************************读写配置文件*************************************/
void MainWindow::readConfig()
{
    QSettings configIni("config.ini", QSettings::IniFormat);
    ui->loadLine->setText(configIni.value( "mainWindwos/loadLine").toString());
    ui->outLine->setText(configIni.value( "mainWindwos/outLine").toString());
    ui->desktoLine->setText(configIni.value( "settings/desktoLine").toString());
    ui->apkDirLine->setText(configIni.value( "settings/apkDirLine").toString());
    ui->checkBox->setChecked(configIni.value("mainWindwos/debCheckBox").toBool());
    ui->iconCheckBox->setChecked(configIni.value("settings/iconCheckBox").toBool());
}

void MainWindow::writeConfig()
{
    QSettings configIni("config.ini", QSettings::IniFormat);
    configIni.setValue( "mainWindwos/loadLine" ,ui->loadLine->text());
    configIni.setValue( "mainWindwos/outLine" ,ui->outLine->text());
    configIni.setValue( "mainWindwos/debCheckBox" ,ui->checkBox->checkState()==Qt::CheckState::Checked);
    configIni.setValue( "settings/desktoLine" ,ui->desktoLine->text());
    configIni.setValue( "settings/apkDirLine" ,ui->apkDirLine->text());
    configIni.setValue( "settings/iconCheckBox" ,ui->iconCheckBox->checkState()==Qt::CheckState::Checked);
}




