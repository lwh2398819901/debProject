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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *selectPathBtn;
    QPushButton *startBtn;
    QPushButton *allCreateBtn;
    QPushButton *createDirBtn;
    QPushButton *createJsonBtn;
    QPushButton *openDirBtn;
    QPushButton *showJsonBtn;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTextEdit *outText;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QTextEdit *apkText;
    QListWidget *listWidget;
    QLineEdit *pathLine;
    QComboBox *scmdCbox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(690, 736);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        selectPathBtn = new QPushButton(groupBox_3);
        selectPathBtn->setObjectName(QStringLiteral("selectPathBtn"));

        verticalLayout_2->addWidget(selectPathBtn);

        startBtn = new QPushButton(groupBox_3);
        startBtn->setObjectName(QStringLiteral("startBtn"));

        verticalLayout_2->addWidget(startBtn);

        allCreateBtn = new QPushButton(groupBox_3);
        allCreateBtn->setObjectName(QStringLiteral("allCreateBtn"));

        verticalLayout_2->addWidget(allCreateBtn);

        createDirBtn = new QPushButton(groupBox_3);
        createDirBtn->setObjectName(QStringLiteral("createDirBtn"));

        verticalLayout_2->addWidget(createDirBtn);

        createJsonBtn = new QPushButton(groupBox_3);
        createJsonBtn->setObjectName(QStringLiteral("createJsonBtn"));

        verticalLayout_2->addWidget(createJsonBtn);

        openDirBtn = new QPushButton(groupBox_3);
        openDirBtn->setObjectName(QStringLiteral("openDirBtn"));

        verticalLayout_2->addWidget(openDirBtn);

        showJsonBtn = new QPushButton(groupBox_3);
        showJsonBtn->setObjectName(QStringLiteral("showJsonBtn"));

        verticalLayout_2->addWidget(showJsonBtn);


        verticalLayout->addWidget(groupBox_3);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        outText = new QTextEdit(groupBox);
        outText->setObjectName(QStringLiteral("outText"));
        outText->setReadOnly(true);

        gridLayout_2->addWidget(outText, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 1, 0, 1, 3);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        apkText = new QTextEdit(groupBox_2);
        apkText->setObjectName(QStringLiteral("apkText"));
        apkText->setReadOnly(true);

        gridLayout_3->addWidget(apkText, 0, 1, 1, 1);

        listWidget = new QListWidget(groupBox_2);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout_3->addWidget(listWidget, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 2, 0, 1, 3);

        pathLine = new QLineEdit(centralWidget);
        pathLine->setObjectName(QStringLiteral("pathLine"));

        gridLayout->addWidget(pathLine, 0, 0, 1, 1);

        scmdCbox = new QComboBox(centralWidget);
        scmdCbox->addItem(QString());
        scmdCbox->addItem(QString());
        scmdCbox->setObjectName(QStringLiteral("scmdCbox"));
        scmdCbox->setMinimumSize(QSize(110, 0));

        gridLayout->addWidget(scmdCbox, 0, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 690, 36));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\345\212\237\350\203\275\345\214\272", nullptr));
        selectPathBtn->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\267\257\345\276\204", nullptr));
        startBtn->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", nullptr));
        allCreateBtn->setText(QApplication::translate("MainWindow", "\344\270\200\351\224\256\347\224\237\346\210\220", nullptr));
        createDirBtn->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272anbox_app\346\226\207\344\273\266\345\244\271", nullptr));
        createJsonBtn->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272json", nullptr));
        openDirBtn->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", nullptr));
        showJsonBtn->setText(QApplication::translate("MainWindow", "showJson", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "\350\276\223\345\207\272\344\277\241\346\201\257", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "APK\344\277\241\346\201\257", nullptr));
        pathLine->setText(QString());
        scmdCbox->setItemText(0, QApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271", nullptr));
        scmdCbox->setItemText(1, QApplication::translate("MainWindow", "\351\200\211\346\213\251apk", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
