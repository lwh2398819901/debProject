#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "publisherfunc.h"
#include <QDebug>
#include <QFileDialog>
#include <QJsonObject>
#include <QProcess>
#include <thread>
using namespace publisherFunc;
QString curPath = QDir::currentPath();

/*
package:com.android.calendar
package:com.android.contacts
package:com.android.deskclock
package:com.android.dialer
package:com.android.documentsui
package:com.android.gallery3d
package:com.android.quicksearchbox
package:com.android.settings
package:com.android.traceur
package:org.chromium.webview_shell
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::onStart()
{
    QDir dir(curPath);
    dir.remove(curPath+"/desktopTmp");
    dir.mkpath(curPath+"/desktopTmp/icons");

    ui->startBtn->setEnabled(false);
    ui->outText->clear();
    ui->listWidget->clear();
    apkList.clear();
    bool selectDir=(ui->scmdCbox->currentIndex()==0);
    QString path = ui->pathLine->text();
    QStringList list;
    if(selectDir){
        list = publisherFunc::getDirFileNames(path,QDir::Files,QStringList()<<"*.apk");
        QStringList list2;
        foreach(QString it ,list){
            list2.push_back(path+"/"+it);
        }
        list.swap(list2);
    }else {
        list << path;
    }
    qDebug()<<list;
    foreach(QString apkFile,list){
        if(QFile::exists(apkFile)){
            auto it = getApkInfo(apkFile);
            while(it.debVersion.isEmpty())
                it = getApkInfo(apkFile);
            apkList.insert(it.apkName,it);
            ui->listWidget->addItem(it.apkName);
        }
    }
    ui->startBtn->setEnabled(true);
}

void MainWindow::onCreateDir()
{
    QDir dir(curPath);
    dir.mkpath(curPath+"/test");
    QString cmd =QString("cp -r %1/desktopTmp  %1/test/anbox_app").arg(curPath).arg(curPath);
    threadCallDbus(cmd,false);
}

void MainWindow::onCreateJson()
{
    QDir dir(curPath);
    dir.mkpath(curPath+"/test");
    QJsonObject rootObj;

    foreach(QString key,apkList.keys()){
        QJsonObject info;
        ApkInfo apk = apkList.value(key);
        info.insert("debName",apk.debName);
        info.insert("debVersion",apk.debVersion);
        info.insert("platform",apk.platform);
        info.insert("appDesktop",apk.appDesktop);
        info.insert("appIcon",apk.appIcon);
        info.insert("androidName",apk.androidName);
        info.insert("zhName",apk.zhName);
        info.insert("description",apk.description);
        rootObj.insert(key,info);
    }

    QJsonDocument doc(rootObj);
    publisherFunc::createFile(curPath+"/test/android_app.json",doc.toJson());
}

void MainWindow::onOpenDir()
{
    // /usr/bin/dde-file-manager -n file:///home/uos/Desktop/pure-bash-bible
    QString path = curPath+"/test/anbox_app";
    QProcess().startDetached(QString("dde-file-manager -n %1").arg(path));
}

void MainWindow::onShowJson()
{
    QString cmd = QString("deepin-editor %1/test/android_app.json").arg(curPath);
     QProcess().startDetached(cmd);
}

void MainWindow::onAllCreate()
{
    onCreateDir();
    onCreateJson();
}

void MainWindow::onSelectListItem()
{
    QString str = ui->listWidget->currentItem()->text();
    auto it = apkList.find(str);
    if(it!=apkList.end())
    {
        ui->apkText->setText(it.value().toString());
    }

}

void MainWindow::onSelectPath()
{
    QString path;
    if(ui->scmdCbox->currentIndex()==0){
        path = QFileDialog::getExistingDirectory(this, tr("Open File"),
                                                         "/home");
    }else
    {
        path = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("*.apk"));
    }
    if(!path.isEmpty()){
        ui->pathLine->setText(path);
    }

}

void MainWindow::initConnect()
{
   connect(ui->startBtn,&QPushButton::clicked,this,&MainWindow::onStart);
   connect(ui->showJsonBtn,&QPushButton::clicked,this,&MainWindow::onShowJson);
   connect(ui->openDirBtn,&QPushButton::clicked,this,&MainWindow::onOpenDir);
   connect(ui->allCreateBtn,&QPushButton::clicked,this,&MainWindow::onAllCreate);
   connect(ui->createJsonBtn,&QPushButton::clicked,this,&MainWindow::onCreateJson);
   connect(ui->createDirBtn,&QPushButton::clicked,this,&MainWindow::onCreateDir);
   connect(ui->selectPathBtn,&QPushButton::clicked,this,&MainWindow::onSelectPath);
   connect(ui->listWidget,&QListWidget::itemClicked,this,&MainWindow::onSelectListItem);
}

ApkInfo MainWindow::getApkInfo(QString filePath)
{
    ApkInfo apk;
    apk.apkName = QFileInfo(filePath).fileName();
    apk.platform = "arm64";

    QSet<QString> beforeInstall = getApkList();
    installApk(filePath);
    QSet<QString> afterInstall = getApkList();
    int num =0;
    while(beforeInstall==afterInstall&&num<5){
        afterInstall = getApkList();
        num++;
        pause(3000);
    }

    if(beforeInstall==afterInstall){
        //卸载apk
        QString uninstall =QString("/usr/bin/android-appmgr.sh uninstall %1").arg(apk.androidName);
        QPair<int,QString> res5=threadCallDbus(uninstall);
        ui->outText->append("ERROR: 安装后列表查询失败！！");
        return apk;
    }else {
        foreach(QString str,afterInstall){
            if(beforeInstall.find(str)==beforeInstall.end()){
                QString android = str.split("package:")[1];
                apk.debName = android;
                apk.androidName =android;
                apk.appIcon = android+".png";
                apk.appDesktop = android+".desktop";
                ui->outText->append(str);
            }
        }
    }
    //查看版本
    QString showApkInfo =QString("/usr/bin/android-appmgr.sh package-version %1").arg(apk.androidName);
    QPair<int,QString> res4=threadCallDbus(showApkInfo);
    int a = res4.second.indexOf("title:");
    QStringList temp3 = res4.second.mid(a).split("\n");
    qDebug()<<res4.second;
    foreach(QString str,temp3){
        qDebug()<<str;
        if(str.startsWith("title:")){
            apk.zhName = str.split("title:")[1];
        }

        if(str.indexOf("version:")!=-1){
            apk.debVersion = str.split("version:")[1];
        }
    }

    ui->outText->append(res4.second);

    //创建desktop文件
    QString createDesktop =QString("/usr/bin/android-appmgr.sh creat %1 %2/desktopTmp/").arg(apk.androidName).arg(curPath);
    QPair<int,QString> res=threadCallDbus(createDesktop);
    ui->outText->append(res.second);
    //复制icon
    QDir dir(curPath);
    dir.mkpath(QString("%1/desktopTmp/icons/%2").arg(curPath).arg(apk.apkName));
    QFile::copy(QString("/home/Kbox/icons/%1").arg(apk.appIcon),QString("%1/desktopTmp/icons/%2").arg(curPath).arg(apk.appIcon));


    //卸载apk
    QString uninstall =QString("/usr/bin/android-appmgr.sh uninstall %1").arg(apk.androidName);
    QPair<int,QString> res5=threadCallDbus(uninstall);
    ui->outText->append(res5.second);
    return apk;
}

QSet<QString> MainWindow::getApkList()
{
    QString showList =QString("/usr/bin/android-appmgr.sh package-list"); //查看列表
    //查看列表
    QPair<int,QString> res1=threadCallDbus(showList);

    int a = res1.second.indexOf("package:");
    QStringList temp = res1.second.mid(a).split("\n");
    QSet<QString>set;
    foreach(QString str,temp){
        set.insert(str);
    }
    ui->outText->append(res1.second);
    return  set;
}

void MainWindow::installApk(QString filePath)
{
      QString install =QString("/usr/bin/android-appmgr.sh install %1").arg(filePath); //安装
      //安装apk
      QPair<int,QString> res2=threadCallDbus(install);
      ui->outText->append(res2.second);
      pause(10000);
}



QPair<int,QString> MainWindow::threadCallDbus(const QString &cmd,bool isQProcess,int msec)
{
    QPair<int,QString>res{-1,"ERROR"};
    bool threadEixt = false;
    std::thread t([&]() {
        if(isQProcess){//使用QProcess
            QStringList list = cmd.split(" ");
            if(list.count()){
                QProcess p(nullptr);
                QString _cmd = list[0];
                list.removeAt(0);
                p.start(_cmd,list);
                p.waitForFinished();
                res.first = p.exitCode();
                res.second = p.readAllStandardOutput();
                res.second = p.readAllStandardError();
            }
        }else {
            res = publisherFunc::startPopen(cmd);
        }
        threadEixt = true;
    });
    t.detach();
    while (!threadEixt&&msec>0) {
       publisherFunc::pause(200);
       msec -= 200;
    }
    return  res;
}

















