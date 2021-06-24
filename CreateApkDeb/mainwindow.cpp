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
    curRowlabel.setText("当前 0 行");
    countRowlabel.setText("总 0 行");
    ui->statusBar->addPermanentWidget(&curRowlabel);
    ui->statusBar->addWidget(&countRowlabel);
    initConnect();
    ui->stopBtn->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::onStart()
{
    QString path = ui->pathLine->text();
    if (path.isEmpty()) {
        showTextBox("路径为空，请选择路径");
    }

    isStop =false;
    QDir dir(curPath);
    dir.remove(curPath + "/desktopTmp");
    dir.mkpath(curPath + "/desktopTmp/icons");

    auto chBtnStatus = [=](bool flag ){
        ui->startBtn->setEnabled(!flag);
        ui->selectPathBtn->setEnabled(!flag);
        ui->scmdCbox->setEnabled(!flag);
        ui->pathLine->setReadOnly(flag);
        ui->createDirBtn->setEnabled(!flag);
        ui->createJsonBtn->setEnabled(!flag);
        ui->allCreateBtn->setEnabled(!flag);
        ui->stopBtn->setEnabled(flag);
    };

    chBtnStatus(true);

    ui->outText->clear();
    ui->listWidget->clear();
    apkList.clear();

    QStringList list;
    if (ui->scmdCbox->currentIndex() == 0) {
        list = publisherFunc::getDirFileNames(path, QDir::Files, QStringList() << "*.apk");
        QStringList list2;
        foreach (QString it, list) {
            list2.push_back(path + "/" + it);
        }
        list.swap(list2);
    } else {
        list << path;
    }
    qDebug() << list;
    kbox_init = getApkList();
    foreach (QString apkFile, list) {
        if(isStop)
            break;
        if (QFile::exists(apkFile)) {
            auto it = getApkInfo(apkFile);
            while (it.debVersion.isEmpty()) {
                it = getApkInfo(apkFile);
            }

            apkList.insert(it.apkName, it);
            apkList[it.apkName].description = ApkDescription(it.zhName);
            ui->listWidget->addItem(it.apkName);
            int countRow = ui->listWidget->count();
            countRowlabel.setText(QString("总 %1 行").arg(countRow));
        }
    }
    chBtnStatus(false);

    createJson(curPath+"/desktopTmp/android_app.json");
}

void MainWindow::onCreateDir()
{
    if (apkList.empty()) {
        showTextBox("当前apk属性列表为空，请点击启动按钮获取apk属性");
        return ;
    }

    QDir dir(curPath);
    dir.mkpath(curPath + "/test");
    QString cmd = QString("rm -rf %1/test/anbox_app;cp -r -f %1/desktopTmp  %1/test/anbox_app").arg(curPath).arg(curPath).arg(curPath);
    threadCallDbus(cmd, false);
}


void MainWindow::onCreateJson()
{
   createJson();
}

void MainWindow::onOpenDir()
{
    // /usr/bin/dde-file-manager -n file:///home/uos/Desktop/pure-bash-bible
    QString path = curPath + "/test/anbox_app";
    QProcess().startDetached(QString("dde-file-manager -n %1").arg(path));
}

void MainWindow::onShowJson()
{
    QString cmd = QString("deepin-editor %1/test/android_app.json").arg(curPath);
    QProcess().startDetached(cmd);
}

void MainWindow::onAllCreate()
{
    if (apkList.empty()) {
        showTextBox("当前apk属性列表为空，请点击启动按钮获取apk属性");
        return ;
    }
    onCreateDir();
    onCreateJson();
}

void MainWindow::onSelectListItem()
{
    QString str = ui->listWidget->currentItem()->text();
    auto it = apkList.find(str);
    if (it != apkList.end()) {
        ui->apkText->setText(it.value().toString());
    }

    int curRow = ui->listWidget->currentRow()+1;
    curRowlabel.setText(QString("当前 %1 行").arg(curRow));
}

void MainWindow::onSelectPath()
{
    QString path;
    if (ui->scmdCbox->currentIndex() == 0) {
        path = QFileDialog::getExistingDirectory(this, tr("Open File"),
                                                 "/home");
    } else {
        path = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("*.apk"));
    }
    if (!path.isEmpty()) {
        ui->pathLine->setText(path);
    }

}

void MainWindow::onStop()
{
    isStop=true;
}

void MainWindow::initConnect()
{
    connect(ui->startBtn, &QPushButton::clicked, this, &MainWindow::onStart);
    connect(ui->showJsonBtn, &QPushButton::clicked, this, &MainWindow::onShowJson);
    connect(ui->openDirBtn, &QPushButton::clicked, this, &MainWindow::onOpenDir);
    connect(ui->allCreateBtn, &QPushButton::clicked, this, &MainWindow::onAllCreate);
    connect(ui->createJsonBtn, &QPushButton::clicked, this, &MainWindow::onCreateJson);
    connect(ui->createDirBtn, &QPushButton::clicked, this, &MainWindow::onCreateDir);
    connect(ui->selectPathBtn, &QPushButton::clicked, this, &MainWindow::onSelectPath);
    connect(ui->stopBtn, &QPushButton::clicked, this, &MainWindow::onStop);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::onSelectListItem);
    connect(ui->listWidget, &QListWidget::currentItemChanged, this, &MainWindow::onSelectListItem);
}

ApkInfo MainWindow::getApkInfo(QString filePath)
{
    ApkInfo apk;
    apk.apkName = QFileInfo(filePath).fileName();
    apk.platform = "arm64";

    if(!setApkInfo(apk,filePath))
        return apk;

    //查看版本
    QString showApkInfo = QString("/usr/bin/android-appmgr.sh package-version %1").arg(apk.androidName);
    QPair<int, QString> res4 = threadCallDbus(showApkInfo);
    int a = res4.second.indexOf("title:");
    QStringList temp3 = res4.second.mid(a).split("\n");
    foreach (QString str, temp3) {
        if (str.startsWith("title:")) {
            apk.zhName = str.split("title:")[1];
        }

        if (str.indexOf("version:") != -1) {
            apk.debVersion = str.split("version:")[1];
        }
    }

    bool isInsert = true;
    foreach(QString key,apkList.keys()) {
        if(apkList[key].debName == apk.debName ){
            QString str = QString("dpkg --compare-versions %1 lt %2 ").arg(apkList[key].debVersion).arg(apk.debVersion);
            auto result = startPopen(str);
            isInsert =  (result.first == 0);
        }
    }

    if(isInsert) {
        ui->outText->append(res4.second);
        //创建desktop文件
        QString createDesktop = QString("/usr/bin/android-appmgr.sh creat %1 %2/desktopTmp/").arg(apk.androidName).arg(curPath);
        QPair<int, QString> res = threadCallDbus(createDesktop);
        ui->outText->append(res.second);
        //复制icon
        QDir dir(curPath);
        QString iconDir = QString("%1/desktopTmp/icons/%2").arg(curPath).arg(apk.apkName.left(apk.apkName.size()-4));
        QString cp_iconPath = QString("%1/desktopTmp/icons/%2").arg(curPath).arg(apk.appIcon);
        QString iconPath = QString("/home/Kbox/icons/%2").arg(apk.appIcon);
        dir.mkpath(iconDir);
        QFile::copy(iconPath, cp_iconPath);

        //创建不同像素icon
        QStringList iconPixList{"16x16", "24x24", "32x32", "48x48", "128x128", "256x256", "512x512"};
        foreach (QString tmp, iconPixList) {
            QString str = QString("convert -resize %1 %2 %3/%4.png").arg(tmp).arg(cp_iconPath).arg(iconDir).arg(tmp);
            publisherFunc::startPopen(str);
        }
    }

    //卸载apk
    QString uninstall = QString("/usr/bin/android-appmgr.sh uninstall %1").arg(apk.androidName);
    QPair<int, QString> res5 = threadCallDbus(uninstall);
    ui->outText->append(res5.second);

    return apk;
}

QSet<QString> MainWindow::getApkList()
{
    QString showList = QString("/usr/bin/android-appmgr.sh package-list"); //查看列表
    //查看列表
    QPair<int, QString> res1 = threadCallDbus(showList);

    int a = res1.second.indexOf("package:");
    QStringList temp = res1.second.mid(a).split("\n");
    QSet<QString>set;
    foreach (QString str, temp) {
        set.insert(str);
    }
    ui->outText->append(res1.second);
    return  set;
}

void MainWindow::installApk(QString filePath)
{
    QString install = QString("/usr/bin/android-appmgr.sh install %1").arg(filePath); //安装
    //安装apk
    QPair<int, QString> res2 = threadCallDbus(install);
    ui->outText->append(res2.second);
    pause(100);
}

QString MainWindow::ApkDescription(QString title)
{
    QString str;
    QXlsx::Document xlsx("app_list.xlsx");
    if (QFile::exists("app_list.xlsx")) {
        int i = 1, j = 1;
        while (true) {
            QString tmp = xlsx.read(i, 1).toString();
            if (tmp == title) {
                str = xlsx.read(i, 5).toString();
                return str;
            }
            if (tmp.isEmpty())
                break;
            ++i;
        }
        foreach (QString key, apkList.keys()) {
            ApkInfo apk = apkList.value(key);
            if (apk.zhName == title) {
                xlsx.write(i, 1, apk.zhName);
                xlsx.write(i, 2, 64);
                xlsx.write(i, 3, apk.debVersion);
                xlsx.write(i, 4, apk.debName);
                xlsx.write(i, 5, apk.description);
            }
        }
    } else {
        //创建表
        xlsx.write("A1", "app");
        xlsx.write("B1", "位数");
        xlsx.write("C1", "version");
        xlsx.write("D1", "package");
        xlsx.write("E1", "softName");
        int i = 2;
        foreach (QString key, apkList.keys()) {
            ApkInfo apk = apkList.value(key);
            xlsx.write(i, 1, apk.zhName);
            xlsx.write(i, 2, 64);
            xlsx.write(i, 3, apk.debVersion);
            xlsx.write(i, 4, apk.debName);
            xlsx.write(i, 5, apk.description);
            i++;
        }
    }
    xlsx.saveAs("app_list.xlsx");/*保存*/

    return  str;
}

bool MainWindow::setApkInfo(ApkInfo &apk,QString filePath)
{
    QSet<QString> beforeInstall = kbox_init;
    installApk(filePath);
    QSet<QString> afterInstall = getApkList();
    int num = 0;
    while (beforeInstall == afterInstall && num < 5) {
        afterInstall = getApkList();
        num++;
        pause(3000);
    }

    if (beforeInstall == afterInstall) {
        //卸载apk
        QString uninstall = QString("/usr/bin/android-appmgr.sh uninstall %1").arg(apk.androidName);
        QPair<int, QString> res5 = threadCallDbus(uninstall);
        ui->outText->append("ERROR: 安装后列表查询失败！！");
        pause(500);
        return false;
    }

    auto it = afterInstall.subtract(beforeInstall);
    foreach (QString str, it) {
        QString android = str.split("package:")[1];
        apk.debName = android;
        apk.androidName = android;
        apk.appIcon = android + ".png";
        apk.appDesktop = android + ".desktop";
        ui->outText->append(str);
    }
    return true;
}

void MainWindow::createJson(QString filePath)
{
    if(filePath.isEmpty()){
        filePath = curPath + "/test/android_app.json";
    }
    if (apkList.empty()) {
        showTextBox("当前apk属性列表为空，请点击启动按钮获取apk属性");
        return ;
    }

    QDir dir(curPath);
    dir.mkpath(curPath + "/test");
    QJsonObject rootObj;

    foreach (QString key, apkList.keys()) {
        QJsonObject info;
        ApkInfo apk = apkList.value(key);
        info.insert("debName", apk.debName);
        info.insert("debVersion", apk.debVersion);
        info.insert("platform", apk.platform);
        info.insert("appDesktop", apk.appDesktop);
        info.insert("appIcon", apk.appIcon);
        info.insert("androidName", apk.androidName);
        info.insert("zhName", apk.zhName);
        info.insert("description", apk.description);
        rootObj.insert(key, info);
    }

    QJsonDocument doc(rootObj);
    publisherFunc::createFile(filePath, doc.toJson());
}



QPair<int, QString> MainWindow::threadCallDbus(const QString &cmd, bool isQProcess, int msec)
{
    QPair<int, QString>res{-1, "ERROR"};
    bool threadEixt = false;
    std::thread t([&]() {
        if (isQProcess) { //使用QProcess
            QStringList list = cmd.split(" ");
            if (list.count()) {
                QProcess p(nullptr);
                QString _cmd = list[0];
                list.removeAt(0);
                p.start(_cmd, list);
                p.waitForFinished();
                res.first = p.exitCode();
                res.second = p.readAllStandardOutput();
                res.second = p.readAllStandardError();
            }
        } else {
            res = publisherFunc::startPopen(cmd);
        }
        threadEixt = true;
    });
    t.detach();
    while (!threadEixt && msec > 0) {
        publisherFunc::pause(200);
        msec -= 200;
    }
    return  res;
}

















