#include "apkinfomanager.h"
#include "ui_apkinfomanager.h"
#include <QFileDialog>
#include <QTreeWidgetItem>

ApkInfoManager::ApkInfoManager(QMap<QString,ApkInfo>*const apkList,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApkInfoManager),
    apkInfoLIst(apkList)
{
    ui->setupUi(this);
    init();

    connect(ui->saveBtn,&QPushButton::clicked,this,&ApkInfoManager::slot_saveApk);
    connect(ui->addBtn,&QPushButton::clicked,this,&ApkInfoManager::slot_addApk);
    connect(ui->deleteBtn,&QPushButton::clicked,this,&ApkInfoManager::slot_deleteApk);
}

ApkInfoManager::~ApkInfoManager()
{
    ui->treeWidget->clear();
    delete ui;
}

void ApkInfoManager::slot_addApk()
{
    QString filepath = QFileDialog::getOpenFileName(nullptr,"","","*.apk");

    if(!filepath.isEmpty())
    {
        QFileInfo fileINfo(filepath);
        ApkInfo *apk;
        QString apkName = fileINfo.fileName();
        auto it = apkInfoLIst->find(apkName);
        if(it!=apkInfoLIst->end())
        {
            apk = new ApkInfo(it.value());
        }
        else {
            apk = new ApkInfo();
            apk->apkName = apkName;
            apk->platform ="all";
        }
        ApkInfoWindow* w=new ApkInfoWindow(apk,nullptr,true);
        connect(w,&ApkInfoWindow::sig_save,[=](){
            apkInfoLIst->insert(apk->apkName,*apk);
            init();
            delete apk;
        });
        connect(w,&ApkInfoWindow::sig_cancel,[=](){
            delete apk;
        });
        w->show();
    }
}

void ApkInfoManager::slot_saveApk()
{
    //获取控件
    //调用write函数
    int size = ui->treeWidget->topLevelItemCount();
    QTreeWidgetItem *child;
    for (int i = 0; i < size; i++)
    {
        child = ui->treeWidget->topLevelItem(i);
        QTreeWidgetItem * grandson = child->child(0);
        ApkInfoWindow*w =(ApkInfoWindow*)ui->treeWidget->itemWidget(grandson,0);
        w->slot_writeApkInfo();
    }
    init();
}

void ApkInfoManager::slot_deleteApk()
{
    //获取选中行号
    //获取apk名称
    //删除apk
    //更新map
    //初始化
    init();
}

void ApkInfoManager::init()
{
    ui->treeWidget->clear();
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
