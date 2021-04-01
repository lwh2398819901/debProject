#include "apkinfowindow.h"
#include "ui_apkinfowindow.h"

ApkInfoWindow::ApkInfoWindow(ApkInfo*const _apk,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApkInfoWindow),
    apk(_apk){
    ui->setupUi(this);
    init();
}

ApkInfoWindow::~ApkInfoWindow(){
    delete ui;
}

void ApkInfoWindow::slot_writeApkInfo(){
    if(apk!=nullptr){
        apk->apkName=ui->apkNameLine->text();
        apk->debName=ui->debNameLine->text();
        apk->debVersion=ui->debVerLine->text();
        apk->platform=ui->platformLine->text();
        apk->appDesktop=ui->desktopLine->text();
        apk->appIcon=ui->appIconLine->text();
        apk->androidName=ui->appNameLine->text();
        apk->zhName=ui->zhNameLine->text();
        apk->description=ui->descriptionLine->text();
    }
    emit sig_save(true);
    close();
}

void ApkInfoWindow::slot_cancel(){
    emit sig_save(false);
    close();
}

void ApkInfoWindow::init(){
    setAttribute(Qt::WA_ShowModal, true);
    setAttribute(Qt::WA_DeleteOnClose);
    if(apk!=nullptr){
        ui->apkNameLine->setText(apk->apkName);
        ui->debNameLine->setText(apk->debName);
        ui->debVerLine->setText(apk->debVersion);
        ui->platformLine->setText(apk->platform);
        ui->desktopLine->setText(apk->appDesktop);
        ui->appIconLine->setText(apk->appIcon);
        ui->appNameLine->setText(apk->androidName);
        ui->zhNameLine->setText(apk->zhName);
        ui->descriptionLine->setText(apk->description);
    }
    connect(ui->pushButton,&QPushButton::clicked,this,&ApkInfoWindow::slot_writeApkInfo);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&ApkInfoWindow::slot_cancel);
}
