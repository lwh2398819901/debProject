#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include "apkinfowindow.h"

using namespace publisherFunc;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    isAddApk(false)
{
    ui->setupUi(this);
    //获取apk属性
    readAppPackageNames();
    //读取配置文件
    readConfig();
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
    connect(ui->editApkBtn,&QPushButton::clicked,[=](){
        QMessageBox::warning(nullptr,"警告","修改此文件可能会造成错误，建议修改后重启软件");
        QProcess().startDetached("deepin-editor ./android_app.json");
    });
    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    writeConfig();
    writeAppPackageNames();
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
        QMessageBox::warning(nullptr,"错误","目录不能为空");
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

            bool flag1=dir.mkpath(DebianDir); //递归创建目录结构，appdir目录通过递归创建出来
            bool flag2=dir.mkpath(optDir);
            bool flag3=dir.mkpath(desktopDir);

            if(!flag1||!flag2||!flag3)
            {
                QString str;
                if(!flag1)
                    str += "debianDir\t";
                if(!flag2)
                    str += "optDir\t";
                if(!flag3)
                    str += "desktopDir\t";
                str+= "目录创建失败";
                QMessageBox::warning(nullptr,"错误",str);
                return ;
            }

            //拷贝文件 app icon desktop
            flag1=QFile::copy(m_loadDir+"/"+appName,optDir+appName);
            flag2=QFile::copy("./anbox_app/"+apk.appIcon,desktopDir+apk.appIcon);
            flag3=QFile::copy("./anbox_app/"+apk.appDesktop,desktopDir+apk.appDesktop);

            if(!flag1||!flag2||!flag3)
            {
                QString str;
                if(!flag1)
                    str += "app\t";
                if(!flag2)
                    str += "icon\t";
                if(!flag3)
                    str += "desktop\t";
                str+= "文件拷贝失败";
                QMessageBox::warning(nullptr,"错误",str);
                return ;
            }

            //创建control postinst prer
            flag1=createFile(DebianDir+"control",replaceString(model_control,apk));
            flag2=createFile(DebianDir+"postinst",replaceString(model_postinst,apk));
            flag3=createFile(DebianDir+"prerm",replaceString(model_prerm,apk));

            if(!flag1||!flag2||!flag3)
            {
                QString str;
                if(!flag1)
                    str += "control\t";
                if(!flag2)
                    str += "postinst\t";
                if(!flag3)
                    str += "prerm\t";
                str+= "模板文件创建失败";
                QMessageBox::warning(nullptr,"错误",str);
                return ;
            }

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
           QMessageBox::warning(nullptr,"错误",QString("error:%1 属性查找不存在  跳过该deb创建").arg(appName));
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
    foreach(const QString &str, list)
    {
        if(str.startsWith("Icon="))
            text += "Icon="+this->m_desktopDir+"/"+apk.appIcon;
        else
            text += (str+"\n");
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
        QMessageBox::warning(nullptr,"错误","读取android_app.json文件失败,程序退出");
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
    if(!isAddApk)
        return ;

    QJsonObject rootObj;

    foreach(QString key,m_apppAckageNames.keys())
    {
        QJsonObject info;
        ApkInfo apk = m_apppAckageNames.value(key);
        info.insert("debName",apk.debName);
        info.insert("debVersion",apk.debVersion);
        info.insert("platform",apk.platform);
        info.insert("appDesktop",apk.appDesktop);
        info.insert("appIcon",apk.appIcon);
        info.insert("androidName",apk.androidName);
        rootObj.insert(key,info);
    }

    QJsonDocument doc(rootObj);
    createFile("./android_app.json",doc.toJson());
    isAddApk=false;
}

/********************************apkinfo管理*************************************/
//添加apkinfo
void MainWindow::slot_addApkInfo()
{
    QString filepath = QFileDialog::getOpenFileName(nullptr,"","","*.apk");
    if(!filepath.isEmpty())
    {
        addApkInfo(filepath);
    }
}

void MainWindow::addApkInfo(QString filePath)
{
    QFileInfo fileINfo(filePath);
    ApkInfo *apk;
    auto it = m_apppAckageNames.find(fileINfo.fileName());
    if(it!=m_apppAckageNames.end())
    {
        apk = new ApkInfo(it.value());
    }
    else {
        apk = new ApkInfo();
        apk->apkName = fileINfo.fileName();
        apk->platform ="all";
    }

    ApkInfoWindow*w =new ApkInfoWindow(apk,nullptr);
    connect(w,&ApkInfoWindow::sig_save,[=](){
        m_apppAckageNames.insert(apk->apkName,*apk);
        delete apk;
        isAddApk=true;
        writeAppPackageNames();
    });
    connect(w,&ApkInfoWindow::sig_cancel,[=](){
        delete apk;
    });

    w->show();
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





