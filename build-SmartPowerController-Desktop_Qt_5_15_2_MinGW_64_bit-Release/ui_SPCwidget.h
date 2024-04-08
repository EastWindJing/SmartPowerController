/********************************************************************************
** Form generated from reading UI file 'SPCwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPCWIDGET_H
#define UI_SPCWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_10;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_47;
    QComboBox *comboBox_powerLink;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *btn_PowerConnect;
    QPushButton *btn_PowerDisconnect;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QPushButton *btn_on_6;
    QLabel *label_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btn_off_5;
    QLabel *label_1;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_on_2;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btn_off_8;
    QLabel *label_6;
    QPushButton *btn_on_8;
    QPushButton *btn_on_1;
    QPushButton *btn_off_1;
    QPushButton *btn_on_4;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *btn_off_4;
    QLabel *label_5;
    QPushButton *btn_off_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_on_3;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *btn_off_6;
    QPushButton *btn_off_7;
    QLabel *label_3;
    QLabel *label_8;
    QPushButton *btn_off_2;
    QPushButton *btn_on_5;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btn_on_7;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_on_all;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_off_all;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(922, 293);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/spclogo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Widget->setWindowIcon(icon);
        gridLayout_2 = new QGridLayout(Widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 73, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 0, 1, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(734, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 1, 0, 1, 1);

        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_1 = new QWidget(widget);
        widget_1->setObjectName(QString::fromUtf8("widget_1"));
        horizontalLayout_2 = new QHBoxLayout(widget_1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_47 = new QLabel(widget_1);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        label_47->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setPointSize(10);
        label_47->setFont(font);

        horizontalLayout_2->addWidget(label_47);

        comboBox_powerLink = new QComboBox(widget_1);
        comboBox_powerLink->setObjectName(QString::fromUtf8("comboBox_powerLink"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(3);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_powerLink->sizePolicy().hasHeightForWidth());
        comboBox_powerLink->setSizePolicy(sizePolicy);
        comboBox_powerLink->setMinimumSize(QSize(0, 30));
        comboBox_powerLink->setFont(font);

        horizontalLayout_2->addWidget(comboBox_powerLink);

        horizontalSpacer_9 = new QSpacerItem(230, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_9);

        btn_PowerConnect = new QPushButton(widget_1);
        btn_PowerConnect->setObjectName(QString::fromUtf8("btn_PowerConnect"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btn_PowerConnect->sizePolicy().hasHeightForWidth());
        btn_PowerConnect->setSizePolicy(sizePolicy1);
        btn_PowerConnect->setMinimumSize(QSize(0, 30));
        btn_PowerConnect->setFont(font);

        horizontalLayout_2->addWidget(btn_PowerConnect);

        btn_PowerDisconnect = new QPushButton(widget_1);
        btn_PowerDisconnect->setObjectName(QString::fromUtf8("btn_PowerDisconnect"));
        sizePolicy1.setHeightForWidth(btn_PowerDisconnect->sizePolicy().hasHeightForWidth());
        btn_PowerDisconnect->setSizePolicy(sizePolicy1);
        btn_PowerDisconnect->setMinimumSize(QSize(0, 30));
        btn_PowerDisconnect->setFont(font);

        horizontalLayout_2->addWidget(btn_PowerDisconnect);


        verticalLayout->addWidget(widget_1);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btn_on_6 = new QPushButton(widget_2);
        btn_on_6->setObjectName(QString::fromUtf8("btn_on_6"));
        btn_on_6->setFont(font);

        gridLayout->addWidget(btn_on_6, 0, 10, 1, 1);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font1;
        font1.setPointSize(14);
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 2, 6, 1, 1);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 2, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 7, 1, 1);

        btn_off_5 = new QPushButton(widget_2);
        btn_off_5->setObjectName(QString::fromUtf8("btn_off_5"));
        btn_off_5->setFont(font);

        gridLayout->addWidget(btn_off_5, 1, 8, 1, 1);

        label_1 = new QLabel(widget_2);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setFont(font1);
        label_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_1, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 3, 1, 1);

        btn_on_2 = new QPushButton(widget_2);
        btn_on_2->setObjectName(QString::fromUtf8("btn_on_2"));
        btn_on_2->setFont(font);

        gridLayout->addWidget(btn_on_2, 0, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 0, 9, 1, 1);

        btn_off_8 = new QPushButton(widget_2);
        btn_off_8->setObjectName(QString::fromUtf8("btn_off_8"));
        btn_off_8->setFont(font);

        gridLayout->addWidget(btn_off_8, 1, 14, 1, 1);

        label_6 = new QLabel(widget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_6, 2, 10, 1, 1);

        btn_on_8 = new QPushButton(widget_2);
        btn_on_8->setObjectName(QString::fromUtf8("btn_on_8"));
        btn_on_8->setFont(font);

        gridLayout->addWidget(btn_on_8, 0, 14, 1, 1);

        btn_on_1 = new QPushButton(widget_2);
        btn_on_1->setObjectName(QString::fromUtf8("btn_on_1"));
        btn_on_1->setFont(font);

        gridLayout->addWidget(btn_on_1, 0, 0, 1, 1);

        btn_off_1 = new QPushButton(widget_2);
        btn_off_1->setObjectName(QString::fromUtf8("btn_off_1"));
        btn_off_1->setFont(font);

        gridLayout->addWidget(btn_off_1, 1, 0, 1, 1);

        btn_on_4 = new QPushButton(widget_2);
        btn_on_4->setObjectName(QString::fromUtf8("btn_on_4"));
        btn_on_4->setFont(font);

        gridLayout->addWidget(btn_on_4, 0, 6, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 0, 11, 1, 1);

        btn_off_4 = new QPushButton(widget_2);
        btn_off_4->setObjectName(QString::fromUtf8("btn_off_4"));
        btn_off_4->setFont(font);

        gridLayout->addWidget(btn_off_4, 1, 6, 1, 1);

        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_5, 2, 8, 1, 1);

        btn_off_3 = new QPushButton(widget_2);
        btn_off_3->setObjectName(QString::fromUtf8("btn_off_3"));
        btn_off_3->setFont(font);

        gridLayout->addWidget(btn_off_3, 1, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        btn_on_3 = new QPushButton(widget_2);
        btn_on_3->setObjectName(QString::fromUtf8("btn_on_3"));
        btn_on_3->setFont(font);

        gridLayout->addWidget(btn_on_3, 0, 4, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 0, 13, 1, 1);

        btn_off_6 = new QPushButton(widget_2);
        btn_off_6->setObjectName(QString::fromUtf8("btn_off_6"));
        btn_off_6->setFont(font);

        gridLayout->addWidget(btn_off_6, 1, 10, 1, 1);

        btn_off_7 = new QPushButton(widget_2);
        btn_off_7->setObjectName(QString::fromUtf8("btn_off_7"));
        btn_off_7->setFont(font);

        gridLayout->addWidget(btn_off_7, 1, 12, 1, 1);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 2, 4, 1, 1);

        label_8 = new QLabel(widget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font1);
        label_8->setLayoutDirection(Qt::LeftToRight);
        label_8->setAutoFillBackground(false);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_8, 2, 14, 1, 1);

        btn_off_2 = new QPushButton(widget_2);
        btn_off_2->setObjectName(QString::fromUtf8("btn_off_2"));
        btn_off_2->setFont(font);

        gridLayout->addWidget(btn_off_2, 1, 2, 1, 1);

        btn_on_5 = new QPushButton(widget_2);
        btn_on_5->setObjectName(QString::fromUtf8("btn_on_5"));
        btn_on_5->setFont(font);

        gridLayout->addWidget(btn_on_5, 0, 8, 1, 1);

        label_7 = new QLabel(widget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_7, 2, 12, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 5, 1, 1);

        btn_on_7 = new QPushButton(widget_2);
        btn_on_7->setObjectName(QString::fromUtf8("btn_on_7"));
        btn_on_7->setFont(font);

        gridLayout->addWidget(btn_on_7, 0, 12, 1, 1);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btn_on_all = new QPushButton(widget_3);
        btn_on_all->setObjectName(QString::fromUtf8("btn_on_all"));
        btn_on_all->setMinimumSize(QSize(0, 30));
        btn_on_all->setFont(font);

        horizontalLayout->addWidget(btn_on_all);

        horizontalSpacer = new QSpacerItem(639, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_off_all = new QPushButton(widget_3);
        btn_off_all->setObjectName(QString::fromUtf8("btn_off_all"));
        btn_off_all->setMinimumSize(QSize(0, 30));
        btn_off_all->setFont(font);

        horizontalLayout->addWidget(btn_off_all);


        verticalLayout->addWidget(widget_3);


        gridLayout_2->addWidget(widget, 1, 1, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(734, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_11, 1, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 72, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 1, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\346\231\272\350\203\275\347\224\265\346\272\220 iBanana SR-828 \346\216\247\345\210\266\345\231\250", nullptr));
        label_47->setText(QCoreApplication::translate("Widget", "\344\270\262\345\217\243\351\200\211\346\213\251\357\274\232", nullptr));
        btn_PowerConnect->setText(QCoreApplication::translate("Widget", "\350\277\236\346\216\245", nullptr));
        btn_PowerDisconnect->setText(QCoreApplication::translate("Widget", "\346\226\255\345\274\200", nullptr));
        btn_on_6->setText(QCoreApplication::translate("Widget", "\345\274\200", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "4", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "2", nullptr));
        btn_off_5->setText(QCoreApplication::translate("Widget", "\345\205\263", nullptr));
        label_1->setText(QCoreApplication::translate("Widget", "1", nullptr));
        btn_on_2->setText(QCoreApplication::translate("Widget", "\345\274\200", nullptr));
        btn_off_8->setText(QCoreApplication::translate("Widget", "\345\205\263", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "6", nullptr));
        btn_on_8->setText(QCoreApplication::translate("Widget", "\345\274\200", nullptr));
        btn_on_1->setText(QCoreApplication::translate("Widget", "\345\274\200", nullptr));
        btn_off_1->setText(QCoreApplication::translate("Widget", "\345\205\263", nullptr));
        btn_on_4->setText(QCoreApplication::translate("Widget", "\345\274\200", nullptr));
        btn_off_4->setText(QCoreApplication::translate("Widget", "\345\205\263", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "5", nullptr));
        btn_off_3->setText(QCoreApplication::translate("Widget", "\345\205\263", nullptr));
        btn_on_3->setText(QCoreApplication::translate("Widget", "\345\274\200", nullptr));
        btn_off_6->setText(QCoreApplication::translate("Widget", "\345\205\263", nullptr));
        btn_off_7->setText(QCoreApplication::translate("Widget", "\345\205\263", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "3", nullptr));
        label_8->setText(QCoreApplication::translate("Widget", "8", nullptr));
        btn_off_2->setText(QCoreApplication::translate("Widget", "\345\205\263", nullptr));
        btn_on_5->setText(QCoreApplication::translate("Widget", "\345\274\200", nullptr));
        label_7->setText(QCoreApplication::translate("Widget", "7", nullptr));
        btn_on_7->setText(QCoreApplication::translate("Widget", "\345\274\200", nullptr));
        btn_on_all->setText(QCoreApplication::translate("Widget", "\345\205\250\345\274\200", nullptr));
        btn_off_all->setText(QCoreApplication::translate("Widget", "\345\205\250\345\205\263", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPCWIDGET_H
