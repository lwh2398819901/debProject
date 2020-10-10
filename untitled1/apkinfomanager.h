#ifndef APKINFOMANAGER_H
#define APKINFOMANAGER_H

#include "publisherfunc.h"
#include "apkinfowindow.h"

#include <QVector>
#include <QWidget>


namespace Ui {
class ApkInfoManager;
}

class ApkInfoManager : public QWidget
{
    Q_OBJECT

public:
    explicit ApkInfoManager(QMap<QString,ApkInfo>*const apkinfoList,QWidget *parent = nullptr);
    ~ApkInfoManager();
    void init();
public slots:
    void slot_addApk();
    void slot_saveApk();
    void slot_deleteApk();

private:
    Ui::ApkInfoManager *ui;
    QMap<QString,ApkInfo>*apkInfoLIst;
};

#endif // APKINFOMANAGER_H
