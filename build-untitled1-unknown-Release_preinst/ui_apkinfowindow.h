/********************************************************************************
** Form generated from reading UI file 'apkinfowindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APKINFOWINDOW_H
#define UI_APKINFOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ApkInfoWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *apkNameLine;
    QLabel *label_2;
    QLineEdit *debNameLine;
    QLabel *label_3;
    QLineEdit *debVerLine;
    QLabel *label_4;
    QLineEdit *platformLine;
    QLabel *label_5;
    QLineEdit *desktopLine;
    QLabel *label_6;
    QLineEdit *appIconLine;
    QLabel *label_7;
    QLineEdit *appNameLine;
    QLabel *label_8;
    QLineEdit *zhNameLine;
    QLabel *label_9;
    QLineEdit *descriptionLine;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *ApkInfoWindow)
    {
        if (ApkInfoWindow->objectName().isEmpty())
            ApkInfoWindow->setObjectName(QStringLiteral("ApkInfoWindow"));
        ApkInfoWindow->resize(491, 437);
        gridLayout = new QGridLayout(ApkInfoWindow);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(ApkInfoWindow);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        apkNameLine = new QLineEdit(ApkInfoWindow);
        apkNameLine->setObjectName(QStringLiteral("apkNameLine"));

        gridLayout->addWidget(apkNameLine, 0, 1, 1, 1);

        label_2 = new QLabel(ApkInfoWindow);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        debNameLine = new QLineEdit(ApkInfoWindow);
        debNameLine->setObjectName(QStringLiteral("debNameLine"));

        gridLayout->addWidget(debNameLine, 1, 1, 1, 1);

        label_3 = new QLabel(ApkInfoWindow);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        debVerLine = new QLineEdit(ApkInfoWindow);
        debVerLine->setObjectName(QStringLiteral("debVerLine"));

        gridLayout->addWidget(debVerLine, 2, 1, 1, 1);

        label_4 = new QLabel(ApkInfoWindow);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        platformLine = new QLineEdit(ApkInfoWindow);
        platformLine->setObjectName(QStringLiteral("platformLine"));

        gridLayout->addWidget(platformLine, 3, 1, 1, 1);

        label_5 = new QLabel(ApkInfoWindow);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        desktopLine = new QLineEdit(ApkInfoWindow);
        desktopLine->setObjectName(QStringLiteral("desktopLine"));

        gridLayout->addWidget(desktopLine, 4, 1, 1, 1);

        label_6 = new QLabel(ApkInfoWindow);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        appIconLine = new QLineEdit(ApkInfoWindow);
        appIconLine->setObjectName(QStringLiteral("appIconLine"));

        gridLayout->addWidget(appIconLine, 5, 1, 1, 1);

        label_7 = new QLabel(ApkInfoWindow);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        appNameLine = new QLineEdit(ApkInfoWindow);
        appNameLine->setObjectName(QStringLiteral("appNameLine"));

        gridLayout->addWidget(appNameLine, 6, 1, 1, 1);

        label_8 = new QLabel(ApkInfoWindow);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 7, 0, 1, 1);

        zhNameLine = new QLineEdit(ApkInfoWindow);
        zhNameLine->setObjectName(QStringLiteral("zhNameLine"));

        gridLayout->addWidget(zhNameLine, 7, 1, 1, 1);

        label_9 = new QLabel(ApkInfoWindow);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 8, 0, 1, 1);

        descriptionLine = new QLineEdit(ApkInfoWindow);
        descriptionLine->setObjectName(QStringLiteral("descriptionLine"));

        gridLayout->addWidget(descriptionLine, 8, 1, 1, 1);

        widget = new QWidget(ApkInfoWindow);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(458, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        gridLayout->addWidget(widget, 9, 0, 1, 2);


        retranslateUi(ApkInfoWindow);

        QMetaObject::connectSlotsByName(ApkInfoWindow);
    } // setupUi

    void retranslateUi(QWidget *ApkInfoWindow)
    {
        ApkInfoWindow->setWindowTitle(QApplication::translate("ApkInfoWindow", "Form", nullptr));
        label->setText(QApplication::translate("ApkInfoWindow", "apk\347\250\213\345\272\217\357\274\232", nullptr));
        label_2->setText(QApplication::translate("ApkInfoWindow", "deb\345\220\215\347\247\260\357\274\232", nullptr));
        label_3->setText(QApplication::translate("ApkInfoWindow", "deb\347\211\210\346\234\254\357\274\232", nullptr));
        label_4->setText(QApplication::translate("ApkInfoWindow", "\345\256\211\350\243\205\345\271\263\345\217\260\357\274\232", nullptr));
        label_5->setText(QApplication::translate("ApkInfoWindow", "app\345\233\276\346\240\207\357\274\232", nullptr));
        label_6->setText(QApplication::translate("ApkInfoWindow", "app\345\233\276\347\211\207\357\274\232", nullptr));
        label_7->setText(QApplication::translate("ApkInfoWindow", "abdroid\345\272\224\347\224\250\345\220\215\347\247\260\357\274\232", nullptr));
        label_8->setText(QApplication::translate("ApkInfoWindow", "\344\270\255\346\226\207\345\220\215\347\247\260", nullptr));
        label_9->setText(QApplication::translate("ApkInfoWindow", "\346\217\217\350\277\260", nullptr));
        descriptionLine->setText(QString());
        pushButton->setText(QApplication::translate("ApkInfoWindow", "\344\277\235\345\255\230", nullptr));
        pushButton_2->setText(QApplication::translate("ApkInfoWindow", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApkInfoWindow: public Ui_ApkInfoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APKINFOWINDOW_H