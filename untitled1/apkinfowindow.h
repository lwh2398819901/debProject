#ifndef APKINFOWINDOW_H
#define APKINFOWINDOW_H

#include <QWidget>
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
    void writeApkInfo();
private:
    void init();
private:
    Ui::ApkInfoWindow *ui;
    ApkInfo*apk;
};

#endif // APKINFOWINDOW_H
