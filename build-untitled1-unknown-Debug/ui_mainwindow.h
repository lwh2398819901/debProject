/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QLineEdit *loadLine;
    QPushButton *loadDirBtn;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *outLine;
    QPushButton *outputDirBtn;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox;
    QPushButton *actionBtn;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *desktoLine;
    QPushButton *desktopBtn;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *apkDirLine;
    QPushButton *apkDirBtn;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *addApksLine;
    QPushButton *addApksBtn;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *iconCheckBox;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *apkManagerBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(387, 361);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        loadLine = new QLineEdit(tab);
        loadLine->setObjectName(QStringLiteral("loadLine"));
        loadLine->setReadOnly(true);

        horizontalLayout->addWidget(loadLine);

        loadDirBtn = new QPushButton(tab);
        loadDirBtn->setObjectName(QStringLiteral("loadDirBtn"));

        horizontalLayout->addWidget(loadDirBtn);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        outLine = new QLineEdit(tab);
        outLine->setObjectName(QStringLiteral("outLine"));
        outLine->setReadOnly(true);

        horizontalLayout_2->addWidget(outLine);

        outputDirBtn = new QPushButton(tab);
        outputDirBtn->setObjectName(QStringLiteral("outputDirBtn"));

        horizontalLayout_2->addWidget(outputDirBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer = new QSpacerItem(210, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        checkBox = new QCheckBox(tab);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_6->addWidget(checkBox);

        actionBtn = new QPushButton(tab);
        actionBtn->setObjectName(QStringLiteral("actionBtn"));

        horizontalLayout_6->addWidget(actionBtn);


        verticalLayout->addLayout(horizontalLayout_6);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        desktoLine = new QLineEdit(tab_2);
        desktoLine->setObjectName(QStringLiteral("desktoLine"));
        desktoLine->setReadOnly(false);

        horizontalLayout_3->addWidget(desktoLine);

        desktopBtn = new QPushButton(tab_2);
        desktopBtn->setObjectName(QStringLiteral("desktopBtn"));

        horizontalLayout_3->addWidget(desktopBtn);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        apkDirLine = new QLineEdit(tab_2);
        apkDirLine->setObjectName(QStringLiteral("apkDirLine"));
        apkDirLine->setReadOnly(false);

        horizontalLayout_4->addWidget(apkDirLine);

        apkDirBtn = new QPushButton(tab_2);
        apkDirBtn->setObjectName(QStringLiteral("apkDirBtn"));

        horizontalLayout_4->addWidget(apkDirBtn);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        addApksLine = new QLineEdit(tab_2);
        addApksLine->setObjectName(QStringLiteral("addApksLine"));

        horizontalLayout_7->addWidget(addApksLine);

        addApksBtn = new QPushButton(tab_2);
        addApksBtn->setObjectName(QStringLiteral("addApksBtn"));

        horizontalLayout_7->addWidget(addApksBtn);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        iconCheckBox = new QCheckBox(tab_2);
        iconCheckBox->setObjectName(QStringLiteral("iconCheckBox"));
        iconCheckBox->setChecked(false);
        iconCheckBox->setTristate(false);

        horizontalLayout_5->addWidget(iconCheckBox);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        apkManagerBtn = new QPushButton(tab_2);
        apkManagerBtn->setObjectName(QStringLiteral("apkManagerBtn"));

        horizontalLayout_8->addWidget(apkManagerBtn);


        verticalLayout_2->addLayout(horizontalLayout_8);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
#ifndef QT_NO_ACCESSIBILITY
        tab->setAccessibleName(QApplication::translate("MainWindow", "a", nullptr));
#endif // QT_NO_ACCESSIBILITY
        loadLine->setText(QString());
        loadDirBtn->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\347\233\256\345\275\225", nullptr));
        outLine->setText(QString());
        outputDirBtn->setText(QApplication::translate("MainWindow", "\350\276\223\345\207\272\347\233\256\345\275\225", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "deb", nullptr));
        actionBtn->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\346\226\207\344\273\266", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\344\270\273\347\225\214\351\235\242", nullptr));
        desktoLine->setText(QString());
        desktopBtn->setText(QApplication::translate("MainWindow", "\345\233\276\346\240\207\347\233\256\345\275\225", nullptr));
        apkDirLine->setText(QString());
        apkDirBtn->setText(QApplication::translate("MainWindow", "\345\272\224\347\224\250\347\233\256\345\275\225", nullptr));
        addApksBtn->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240apk", nullptr));
        iconCheckBox->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271icon", nullptr));
        apkManagerBtn->setText(QApplication::translate("MainWindow", "apk\345\261\236\346\200\247\347\256\241\347\220\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
