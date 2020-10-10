/********************************************************************************
** Form generated from reading UI file 'apkinfomanager.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APKINFOMANAGER_H
#define UI_APKINFOMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ApkInfoManager
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *saveBtn;
    QPushButton *addBtn;
    QPushButton *deleteBtn;

    void setupUi(QWidget *ApkInfoManager)
    {
        if (ApkInfoManager->objectName().isEmpty())
            ApkInfoManager->setObjectName(QStringLiteral("ApkInfoManager"));
        ApkInfoManager->resize(453, 316);
        gridLayout = new QGridLayout(ApkInfoManager);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit = new QLineEdit(ApkInfoManager);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        treeWidget = new QTreeWidget(ApkInfoManager);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        gridLayout->addWidget(treeWidget, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        saveBtn = new QPushButton(ApkInfoManager);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));

        horizontalLayout->addWidget(saveBtn);

        addBtn = new QPushButton(ApkInfoManager);
        addBtn->setObjectName(QStringLiteral("addBtn"));

        horizontalLayout->addWidget(addBtn);

        deleteBtn = new QPushButton(ApkInfoManager);
        deleteBtn->setObjectName(QStringLiteral("deleteBtn"));

        horizontalLayout->addWidget(deleteBtn);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);


        retranslateUi(ApkInfoManager);

        QMetaObject::connectSlotsByName(ApkInfoManager);
    } // setupUi

    void retranslateUi(QWidget *ApkInfoManager)
    {
        ApkInfoManager->setWindowTitle(QApplication::translate("ApkInfoManager", "Form", nullptr));
        saveBtn->setText(QApplication::translate("ApkInfoManager", "\344\277\235\345\255\230", nullptr));
        addBtn->setText(QApplication::translate("ApkInfoManager", "\346\267\273\345\212\240", nullptr));
        deleteBtn->setText(QApplication::translate("ApkInfoManager", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApkInfoManager: public Ui_ApkInfoManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APKINFOMANAGER_H
