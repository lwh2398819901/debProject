#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "apkinfo.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onStart();
    void onCreateDir();
    void onCreateJson();
    void onOpenDir();
    void onShowJson();
    void onAllCreate();
    void onSelectListItem();
    void onSelectPath();
private:
    QPair<int,QString> threadCallDbus(const QString &cmd,bool isQProcess =true,int msec=60000*5);
    void initConnect();
    ApkInfo getApkInfo(QString filePath);
    QSet<QString> getApkList();
    void installApk(QString filePath);
private:
    Ui::MainWindow *ui;
    QMap<QString,ApkInfo>apkList;
};

#endif // MAINWINDOW_H
