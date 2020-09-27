#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QProcess>
#include <QDialog>
#include "apkinfomanager.h"
#include "publisherfunc.h"
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
    void loadDir();
    void outputDir();
    void desktopDir();
    void appDir();
    void createDirAndDeb();
    void readBashStandardOutputInfo();
    void readBashStandardErrorInfo();
    void addApks();
    void showApkManager();
private:
    void getDirPath(QLineEdit*line);
    void createDeb(QString debPath,QString debName);
    void readAppPackageNames();
    void writeAppPackageNames();
    QString replaceString(QString src,const ApkInfo&apk);
    void iconChanged(const ApkInfo&apk,const QString filePaht);

    void readConfig();
    void writeConfig();
private:
    Ui::MainWindow *ui;
    QString m_loadDir;
    QString m_outputDir;
    QString m_desktopDir;
    QString m_apkDir;
    QString m_addApksDir;
    QProcess* m_proces_bash;
    QMap<QString,ApkInfo>m_apppAckageNames;

    QString model_control;
    QString model_postinst;
    QString model_prerm;

    ApkInfoManager* m_apkManager;
};



#endif // MAINWINDOW_H
