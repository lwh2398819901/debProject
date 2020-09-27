#include "addapks.h"
#include "ui_addapks.h"

AddApks::AddApks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddApks)
{
    ui->setupUi(this);
}

AddApks::~AddApks()
{
    delete ui;
}
