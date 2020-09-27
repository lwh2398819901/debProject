#include "apkinfomanager.h"
#include "ui_apkinfomanager.h"
#include <QTreeWidgetItem>

ApkInfoManager::ApkInfoManager(QMap<QString,ApkInfo>*const apkList,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApkInfoManager),
    apkInfoLIst(apkList)
{
    ui->setupUi(this);
    init();

    connect(ui->saveBtn,&QPushButton::clicked,this,&ApkInfoManager::save);
    connect(ui->addBtn,&QPushButton::clicked,this,&ApkInfoManager::addApkInfo);
    connect(ui->cancelBtn,&QPushButton::clicked,this,&ApkInfoManager::cencle);
}

ApkInfoManager::~ApkInfoManager()
{
    delete ui;
}

void ApkInfoManager::addApkInfo()
{
    ApkInfoWindow* w=new ApkInfoWindow(new ApkInfo,this);
    QTreeWidgetItem*item =new QTreeWidgetItem();
    QTreeWidgetItem*item2=new QTreeWidgetItem();
    item->addChild(item2);
    ui->treeWidget->addTopLevelItem(item);
    ui->treeWidget->setItemWidget(item2,0,w);

}

void ApkInfoManager::save()
{

}

void ApkInfoManager::cencle()
{

}

void ApkInfoManager::init()
{
    int i=1;
    foreach(QString key,apkInfoLIst->keys())
    {
        ApkInfoWindow* w=new ApkInfoWindow(&(*apkInfoLIst)[key],this);
        QTreeWidgetItem*item =new QTreeWidgetItem(QStringList()<<QString("No.")+QString::number(i++)+":     "+key);
        QTreeWidgetItem*item2=new QTreeWidgetItem();
        item->addChild(item2);
        ui->treeWidget->addTopLevelItem(item);
        ui->treeWidget->setItemWidget(item2,0,w);

    }
}
