/********************************************************************************
** Form generated from reading UI file 'drawerMenu.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWERMENU_H
#define UI_DRAWERMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DrawerWidget
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *drawer_bt_button;
    QPushButton *drawer_wifi_button;
    QPushButton *drawer_settings_button;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *drawer_volSliderMin_label;
    QVBoxLayout *verticalLayout_2;
    QSlider *horizontalSlider;
    QLabel *drawer_volSliderMax_label;
    QHBoxLayout *horizontalLayout_2;
    QLabel *drawer_brightSliderMin_label;
    QVBoxLayout *verticalLayout_3;
    QSlider *horizontalSlider_2;
    QLabel *drawer_brightSliderMax_label;

    void setupUi(QWidget *DrawerWidget)
    {
        if (DrawerWidget->objectName().isEmpty())
            DrawerWidget->setObjectName(QString::fromUtf8("DrawerWidget"));
        DrawerWidget->resize(1024, 300);
        DrawerWidget->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	background-color: black;\n"
"}"));
        gridLayout_2 = new QGridLayout(DrawerWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        drawer_bt_button = new QPushButton(DrawerWidget);
        drawer_bt_button->setObjectName(QString::fromUtf8("drawer_bt_button"));
        drawer_bt_button->setMinimumSize(QSize(60, 60));
        drawer_bt_button->setStyleSheet(QString::fromUtf8("QPushButton { border-color: white;  border-width: 1px; border-style: solid;border-radius: 30px;}"));

        horizontalLayout->addWidget(drawer_bt_button);

        drawer_wifi_button = new QPushButton(DrawerWidget);
        drawer_wifi_button->setObjectName(QString::fromUtf8("drawer_wifi_button"));
        drawer_wifi_button->setMinimumSize(QSize(60, 60));
        drawer_wifi_button->setStyleSheet(QString::fromUtf8("QPushButton { border-color: white;  border-width: 1px; border-style: solid;border-radius: 30px;}"));

        horizontalLayout->addWidget(drawer_wifi_button);

        drawer_settings_button = new QPushButton(DrawerWidget);
        drawer_settings_button->setObjectName(QString::fromUtf8("drawer_settings_button"));
        drawer_settings_button->setMinimumSize(QSize(60, 60));
        drawer_settings_button->setStyleSheet(QString::fromUtf8("QPushButton { border-color: white;  border-width: 1px; border-style: solid;border-radius: 30px;}"));

        horizontalLayout->addWidget(drawer_settings_button);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_3, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 190, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        drawer_volSliderMin_label = new QLabel(DrawerWidget);
        drawer_volSliderMin_label->setObjectName(QString::fromUtf8("drawer_volSliderMin_label"));

        horizontalLayout_3->addWidget(drawer_volSliderMin_label);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalSlider = new QSlider(DrawerWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    border-radius: 1px;\n"
"    height: 4px;\n"
"    margin: 10px;\n"
"    background-color: white;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"    background-color: white;\n"
"    border: 4px solid white;\n"
"    height: 12px;\n"
"    width: 12px;\n"
"    margin: -6px 0;\n"
"    border-radius: 6px;\n"
"    padding: -6px 0px;\n"
"}"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSlider);


        horizontalLayout_3->addLayout(verticalLayout_2);

        drawer_volSliderMax_label = new QLabel(DrawerWidget);
        drawer_volSliderMax_label->setObjectName(QString::fromUtf8("drawer_volSliderMax_label"));

        horizontalLayout_3->addWidget(drawer_volSliderMax_label);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        drawer_brightSliderMin_label = new QLabel(DrawerWidget);
        drawer_brightSliderMin_label->setObjectName(QString::fromUtf8("drawer_brightSliderMin_label"));

        horizontalLayout_2->addWidget(drawer_brightSliderMin_label);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalSlider_2 = new QSlider(DrawerWidget);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    border-radius: 1px;\n"
"    height: 4px;\n"
"    margin: 10px;\n"
"    background-color: white;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"    background-color: white;\n"
"    border: 4px solid white;\n"
"    height: 12px;\n"
"    width: 12px;\n"
"    margin: -6px 0;\n"
"    border-radius: 6px;\n"
"    padding: -6px 0px;\n"
"}"));
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(horizontalSlider_2);


        horizontalLayout_2->addLayout(verticalLayout_3);

        drawer_brightSliderMax_label = new QLabel(DrawerWidget);
        drawer_brightSliderMax_label->setObjectName(QString::fromUtf8("drawer_brightSliderMax_label"));

        horizontalLayout_2->addWidget(drawer_brightSliderMax_label);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(DrawerWidget);

        QMetaObject::connectSlotsByName(DrawerWidget);
    } // setupUi

    void retranslateUi(QWidget *DrawerWidget)
    {
        DrawerWidget->setWindowTitle(QCoreApplication::translate("DrawerWidget", "DrawerWidget", nullptr));
        drawer_bt_button->setText(QCoreApplication::translate("DrawerWidget", "PushButton", nullptr));
        drawer_wifi_button->setText(QCoreApplication::translate("DrawerWidget", "PushButton", nullptr));
        drawer_settings_button->setText(QCoreApplication::translate("DrawerWidget", "PushButton", nullptr));
        drawer_volSliderMin_label->setText(QString());
        drawer_volSliderMax_label->setText(QString());
        drawer_brightSliderMin_label->setText(QString());
        drawer_brightSliderMax_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DrawerWidget: public Ui_DrawerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWERMENU_H
