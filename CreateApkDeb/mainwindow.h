#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QtXlsx>
#include <qlabel.h>
#include "apkinfo.h"
using namespace std;


QTXLSX_USE_NAMESPACE

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
    void onStop();
private:
    QPair<int, QString> threadCallDbus(const QString &cmd, bool isQProcess = true, int msec = 60000 * 5);
    void initConnect();
    ApkInfo getApkInfo(QString filePath);
    QSet<QString> getApkList();
    void installApk(QString filePath);
    QString ApkDescription(QString title);
    bool setApkInfo(ApkInfo &apk,QString filePath);
    void createJson(QString filePath="");
private:
    Ui::MainWindow *ui;
    QMap<QString, ApkInfo>apkList;
    bool isStop{false};

    QLabel curRowlabel;
    QLabel countRowlabel;

    QSet<QString>kbox_init;


};

#endif // MAINWINDOW_H
