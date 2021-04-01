#ifndef APKINFOWINDOW_H
#define APKINFOWINDOW_H

#include <QWidget>
#include "apkinfo.h"
#include "publisherfunc.h"

namespace Ui {
class ApkInfoWindow;
}

class ApkInfoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ApkInfoWindow(ApkInfo*const _apk,QWidget *parent = nullptr);
    ~ApkInfoWindow();
    void slot_writeApkInfo();
    void slot_cancel();
signals:
    void sig_save(bool );
private:
    void init();
private:
    Ui::ApkInfoWindow *ui;
    ApkInfo*apk;
};

#endif // APKINFOWINDOW_H
