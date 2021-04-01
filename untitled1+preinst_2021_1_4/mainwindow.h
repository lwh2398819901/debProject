#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QProcess>
#include "apkinfo.h"
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
    //创建deb相关
    void slot_loadAPKDir();
    void slot_outputDir();
    void slot_desktopDir();
    void slot_appDir();
    void slot_createDirAndDeb();

    //bash命令行输出  标准输出 标准错误
    void readBashStandardOutputInfo();
    void readBashStandardErrorInfo();

    //apk属性管理  添加apk属性 管理apk属性
    void slot_addApkInfo();
private:
    void getDirPath(QLineEdit*line);
    void createDeb(QString debPath,QString debName);
    QString replaceString(QString src,const ApkInfo&apk);
    void iconChanged(const ApkInfo&apk,const QString filePath);

    //读写apk属性
    void readAppPackageNames();
    void writeAppPackageNames();
    //读写配置文件
    void readConfig();
    void writeConfig();

private:
    Ui::MainWindow *ui;
    QString m_loadDir;
    QString m_outputDir;
    QString m_desktopDir;
    QString m_apkDir;
    QString m_addApksDir;
    QProcess* m_proces_bash {nullptr};
    QMap<QString,ApkInfo>m_apppAckageNames;

    QString model_control;
    QString model_preinst;
    QString model_prerm;
    QString model_info;

    bool isAddApk;

    QString m_iconDir;
};



#endif // MAINWINDOW_H
