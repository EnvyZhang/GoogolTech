/********************************************************************************
** Form generated from reading UI file 'ecatdemo.ui'
**
** Created: Tue Sep 15 15:14:56 2020
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ECATDEMO_H
#define UI_ECATDEMO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EcatDemoClass
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_core;
    QLabel *label_2;
    QComboBox *comboBox_axis;
    QSpacerItem *horizontalSpacer;
    QLabel *label_connect;
    QPushButton *pushButton_alarm;
    QHBoxLayout *horizontalLayout_36;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_31;
    QLabel *label_62;
    QLabel *label_ecatMode;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_15;
    QLabel *label_ecatPos;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *label_encPos;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLabel *label_prfPos;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_5;
    QLabel *label_statusWord;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_alrm;
    QLabel *label_SrvSts;
    QLabel *label_prfRun;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_nLmt;
    QLabel *label_Home;
    QLabel *label_PLmt;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_nMove;
    QLabel *label_stop;
    QLabel *label_fMove;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_32;
    QPushButton *pushButton_clr;
    QPushButton *pushButton_serv;
    QHBoxLayout *horizontalLayout_33;
    QPushButton *pushButton_zero;
    QPushButton *pushButton_stop;
    QHBoxLayout *horizontalLayout_34;
    QPushButton *pushButton_jogN;
    QPushButton *pushButton_jogP;
    QHBoxLayout *horizontalLayout_38;
    QPushButton *pushButton_home;
    QPushButton *pushButton_prob;
    QHBoxLayout *horizontalLayout_35;
    QPushButton *pushButton_object;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *EcatDemoClass)
    {
        if (EcatDemoClass->objectName().isEmpty())
            EcatDemoClass->setObjectName(QString::fromUtf8("EcatDemoClass"));
        EcatDemoClass->resize(628, 354);
        EcatDemoClass->setStyleSheet(QString::fromUtf8("QComboBox QAbstractItemView::item { min-height: 40px; min-width: 60px; }"));
        verticalLayout_4 = new QVBoxLayout(EcatDemoClass);
        verticalLayout_4->setSpacing(20);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(20, 10, 20, 10);
        label = new QLabel(EcatDemoClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        comboBox_core = new QComboBox(EcatDemoClass);
        comboBox_core->setObjectName(QString::fromUtf8("comboBox_core"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_core->sizePolicy().hasHeightForWidth());
        comboBox_core->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(comboBox_core);

        label_2 = new QLabel(EcatDemoClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox_axis = new QComboBox(EcatDemoClass);
        comboBox_axis->setObjectName(QString::fromUtf8("comboBox_axis"));
        sizePolicy.setHeightForWidth(comboBox_axis->sizePolicy().hasHeightForWidth());
        comboBox_axis->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(comboBox_axis);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_connect = new QLabel(EcatDemoClass);
        label_connect->setObjectName(QString::fromUtf8("label_connect"));
        label_connect->setStyleSheet(QString::fromUtf8("background: rgb(0,255,0);\n"
"color: black;\n"
"border:none;\n"
""));
        label_connect->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_connect);

        pushButton_alarm = new QPushButton(EcatDemoClass);
        pushButton_alarm->setObjectName(QString::fromUtf8("pushButton_alarm"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_alarm->sizePolicy().hasHeightForWidth());
        pushButton_alarm->setSizePolicy(sizePolicy1);
        pushButton_alarm->setStyleSheet(QString::fromUtf8("background: rgb(0,255,0);\n"
"color: black;\n"
"border:none;\n"
""));

        horizontalLayout->addWidget(pushButton_alarm);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 2);
        horizontalLayout->setStretch(4, 1);
        horizontalLayout->setStretch(5, 2);
        horizontalLayout->setStretch(6, 2);

        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setSpacing(6);
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        horizontalLayout_36->setSizeConstraint(QLayout::SetDefaultConstraint);
        groupBox = new QGroupBox(EcatDemoClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(6);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        horizontalLayout_31->setContentsMargins(-1, -1, 30, -1);
        label_62 = new QLabel(groupBox);
        label_62->setObjectName(QString::fromUtf8("label_62"));

        horizontalLayout_31->addWidget(label_62);

        label_ecatMode = new QLabel(groupBox);
        label_ecatMode->setObjectName(QString::fromUtf8("label_ecatMode"));

        horizontalLayout_31->addWidget(label_ecatMode);


        verticalLayout_2->addLayout(horizontalLayout_31);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, 30, -1);
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_2->addWidget(label_15);

        label_ecatPos = new QLabel(groupBox);
        label_ecatPos->setObjectName(QString::fromUtf8("label_ecatPos"));

        horizontalLayout_2->addWidget(label_ecatPos);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, 30, -1);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        label_encPos = new QLabel(groupBox);
        label_encPos->setObjectName(QString::fromUtf8("label_encPos"));

        horizontalLayout_3->addWidget(label_encPos);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, 30, -1);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        label_prfPos = new QLabel(groupBox);
        label_prfPos->setObjectName(QString::fromUtf8("label_prfPos"));

        horizontalLayout_4->addWidget(label_prfPos);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, -1, 30, -1);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_8->addWidget(label_5);

        label_statusWord = new QLabel(groupBox);
        label_statusWord->setObjectName(QString::fromUtf8("label_statusWord"));

        horizontalLayout_8->addWidget(label_statusWord);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_alrm = new QLabel(groupBox);
        label_alrm->setObjectName(QString::fromUtf8("label_alrm"));
        label_alrm->setStyleSheet(QString::fromUtf8("background: rgb(0,255,0);\n"
"color: black;\n"
"border:none;\n"
""));
        label_alrm->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_alrm);

        label_SrvSts = new QLabel(groupBox);
        label_SrvSts->setObjectName(QString::fromUtf8("label_SrvSts"));
        label_SrvSts->setStyleSheet(QString::fromUtf8("background: rgb(0,255,0);\n"
"color: black;\n"
"border:none;\n"
""));
        label_SrvSts->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_SrvSts);

        label_prfRun = new QLabel(groupBox);
        label_prfRun->setObjectName(QString::fromUtf8("label_prfRun"));
        label_prfRun->setStyleSheet(QString::fromUtf8("background: rgb(0,255,0);\n"
"color: black;\n"
"border:none;\n"
""));
        label_prfRun->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_prfRun);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_nLmt = new QLabel(groupBox);
        label_nLmt->setObjectName(QString::fromUtf8("label_nLmt"));
        label_nLmt->setStyleSheet(QString::fromUtf8("background: rgb(0,255,0);\n"
"color: black;\n"
"border:none;\n"
""));
        label_nLmt->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_nLmt);

        label_Home = new QLabel(groupBox);
        label_Home->setObjectName(QString::fromUtf8("label_Home"));
        label_Home->setStyleSheet(QString::fromUtf8("background: rgb(0,255,0);\n"
"color: black;\n"
"border:none;\n"
""));
        label_Home->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_Home);

        label_PLmt = new QLabel(groupBox);
        label_PLmt->setObjectName(QString::fromUtf8("label_PLmt"));
        label_PLmt->setStyleSheet(QString::fromUtf8("background: rgb(0,255,0);\n"
"color: black;\n"
"border:none;\n"
""));
        label_PLmt->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_PLmt);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_nMove = new QLabel(groupBox);
        label_nMove->setObjectName(QString::fromUtf8("label_nMove"));
        label_nMove->setStyleSheet(QString::fromUtf8("background: rgb(0,255,0);\n"
"color: black;\n"
"border:none;\n"
""));
        label_nMove->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_nMove);

        label_stop = new QLabel(groupBox);
        label_stop->setObjectName(QString::fromUtf8("label_stop"));
        label_stop->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 127);\n"
"color: rgb(255, 255, 255);\n"
"border:0;\n"
""));
        label_stop->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_stop);

        label_fMove = new QLabel(groupBox);
        label_fMove->setObjectName(QString::fromUtf8("label_fMove"));
        label_fMove->setStyleSheet(QString::fromUtf8("background: rgb(0,255,0);\n"
"color: black;\n"
"border:none;\n"
""));
        label_fMove->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_fMove);


        verticalLayout_2->addLayout(horizontalLayout_7);


        horizontalLayout_36->addWidget(groupBox);

        groupBox_2 = new QGroupBox(EcatDemoClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setSpacing(9);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(20);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        horizontalLayout_32->setContentsMargins(20, -1, 20, -1);
        pushButton_clr = new QPushButton(groupBox_2);
        pushButton_clr->setObjectName(QString::fromUtf8("pushButton_clr"));
        sizePolicy1.setHeightForWidth(pushButton_clr->sizePolicy().hasHeightForWidth());
        pushButton_clr->setSizePolicy(sizePolicy1);

        horizontalLayout_32->addWidget(pushButton_clr);

        pushButton_serv = new QPushButton(groupBox_2);
        pushButton_serv->setObjectName(QString::fromUtf8("pushButton_serv"));
        sizePolicy1.setHeightForWidth(pushButton_serv->sizePolicy().hasHeightForWidth());
        pushButton_serv->setSizePolicy(sizePolicy1);

        horizontalLayout_32->addWidget(pushButton_serv);


        verticalLayout->addLayout(horizontalLayout_32);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(20);
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        horizontalLayout_33->setContentsMargins(20, -1, 20, -1);
        pushButton_zero = new QPushButton(groupBox_2);
        pushButton_zero->setObjectName(QString::fromUtf8("pushButton_zero"));
        sizePolicy1.setHeightForWidth(pushButton_zero->sizePolicy().hasHeightForWidth());
        pushButton_zero->setSizePolicy(sizePolicy1);

        horizontalLayout_33->addWidget(pushButton_zero);

        pushButton_stop = new QPushButton(groupBox_2);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));
        sizePolicy1.setHeightForWidth(pushButton_stop->sizePolicy().hasHeightForWidth());
        pushButton_stop->setSizePolicy(sizePolicy1);

        horizontalLayout_33->addWidget(pushButton_stop);


        verticalLayout->addLayout(horizontalLayout_33);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setSpacing(20);
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        horizontalLayout_34->setContentsMargins(20, -1, 20, -1);
        pushButton_jogN = new QPushButton(groupBox_2);
        pushButton_jogN->setObjectName(QString::fromUtf8("pushButton_jogN"));
        sizePolicy1.setHeightForWidth(pushButton_jogN->sizePolicy().hasHeightForWidth());
        pushButton_jogN->setSizePolicy(sizePolicy1);

        horizontalLayout_34->addWidget(pushButton_jogN);

        pushButton_jogP = new QPushButton(groupBox_2);
        pushButton_jogP->setObjectName(QString::fromUtf8("pushButton_jogP"));
        sizePolicy1.setHeightForWidth(pushButton_jogP->sizePolicy().hasHeightForWidth());
        pushButton_jogP->setSizePolicy(sizePolicy1);

        horizontalLayout_34->addWidget(pushButton_jogP);


        verticalLayout->addLayout(horizontalLayout_34);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setSpacing(20);
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        horizontalLayout_38->setContentsMargins(20, -1, 20, -1);
        pushButton_home = new QPushButton(groupBox_2);
        pushButton_home->setObjectName(QString::fromUtf8("pushButton_home"));
        sizePolicy1.setHeightForWidth(pushButton_home->sizePolicy().hasHeightForWidth());
        pushButton_home->setSizePolicy(sizePolicy1);

        horizontalLayout_38->addWidget(pushButton_home);

        pushButton_prob = new QPushButton(groupBox_2);
        pushButton_prob->setObjectName(QString::fromUtf8("pushButton_prob"));
        sizePolicy1.setHeightForWidth(pushButton_prob->sizePolicy().hasHeightForWidth());
        pushButton_prob->setSizePolicy(sizePolicy1);

        horizontalLayout_38->addWidget(pushButton_prob);


        verticalLayout->addLayout(horizontalLayout_38);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setSpacing(20);
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        horizontalLayout_35->setContentsMargins(20, -1, 20, -1);
        pushButton_object = new QPushButton(groupBox_2);
        pushButton_object->setObjectName(QString::fromUtf8("pushButton_object"));
        sizePolicy1.setHeightForWidth(pushButton_object->sizePolicy().hasHeightForWidth());
        pushButton_object->setSizePolicy(sizePolicy1);

        horizontalLayout_35->addWidget(pushButton_object);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_35->addItem(horizontalSpacer_2);

        horizontalLayout_35->setStretch(0, 1);
        horizontalLayout_35->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_35);


        horizontalLayout_36->addWidget(groupBox_2);

        horizontalLayout_36->setStretch(0, 2);
        horizontalLayout_36->setStretch(1, 3);

        verticalLayout_4->addLayout(horizontalLayout_36);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 6);

        retranslateUi(EcatDemoClass);

        QMetaObject::connectSlotsByName(EcatDemoClass);
    } // setupUi

    void retranslateUi(QWidget *EcatDemoClass)
    {
        EcatDemoClass->setWindowTitle(QApplication::translate("EcatDemoClass", "EcatDemo", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("EcatDemoClass", "Core:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("EcatDemoClass", "Axis:", 0, QApplication::UnicodeUTF8));
        label_connect->setText(QApplication::translate("EcatDemoClass", "Connected", 0, QApplication::UnicodeUTF8));
        pushButton_alarm->setText(QApplication::translate("EcatDemoClass", "Norm", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("EcatDemoClass", "AxisStatus", 0, QApplication::UnicodeUTF8));
        label_62->setText(QApplication::translate("EcatDemoClass", "EcatMd:", 0, QApplication::UnicodeUTF8));
        label_ecatMode->setText(QApplication::translate("EcatDemoClass", "8.CSP", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("EcatDemoClass", "EcatPos:", 0, QApplication::UnicodeUTF8));
        label_ecatPos->setText(QApplication::translate("EcatDemoClass", "0.00", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("EcatDemoClass", "EncPos:", 0, QApplication::UnicodeUTF8));
        label_encPos->setText(QApplication::translate("EcatDemoClass", "0.00", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("EcatDemoClass", "PrfPos:", 0, QApplication::UnicodeUTF8));
        label_prfPos->setText(QApplication::translate("EcatDemoClass", "0.00", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("EcatDemoClass", "StatusWord:", 0, QApplication::UnicodeUTF8));
        label_statusWord->setText(QApplication::translate("EcatDemoClass", "0x0", 0, QApplication::UnicodeUTF8));
        label_alrm->setText(QApplication::translate("EcatDemoClass", "Alarm", 0, QApplication::UnicodeUTF8));
        label_SrvSts->setText(QApplication::translate("EcatDemoClass", "ServoOn", 0, QApplication::UnicodeUTF8));
        label_prfRun->setText(QApplication::translate("EcatDemoClass", "PrfRun", 0, QApplication::UnicodeUTF8));
        label_nLmt->setText(QApplication::translate("EcatDemoClass", "Lmt-", 0, QApplication::UnicodeUTF8));
        label_Home->setText(QApplication::translate("EcatDemoClass", "Home", 0, QApplication::UnicodeUTF8));
        label_PLmt->setText(QApplication::translate("EcatDemoClass", "Lmt+", 0, QApplication::UnicodeUTF8));
        label_nMove->setText(QApplication::translate("EcatDemoClass", "Negative", 0, QApplication::UnicodeUTF8));
        label_stop->setText(QApplication::translate("EcatDemoClass", "Stop", 0, QApplication::UnicodeUTF8));
        label_fMove->setText(QApplication::translate("EcatDemoClass", "Forward", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("EcatDemoClass", "AxisOperate", 0, QApplication::UnicodeUTF8));
        pushButton_clr->setText(QApplication::translate("EcatDemoClass", "ClrSts", 0, QApplication::UnicodeUTF8));
        pushButton_serv->setText(QApplication::translate("EcatDemoClass", "ServOn", 0, QApplication::UnicodeUTF8));
        pushButton_zero->setText(QApplication::translate("EcatDemoClass", "ZeroPos", 0, QApplication::UnicodeUTF8));
        pushButton_stop->setText(QApplication::translate("EcatDemoClass", "Stop", 0, QApplication::UnicodeUTF8));
        pushButton_jogN->setText(QApplication::translate("EcatDemoClass", "Jog-", 0, QApplication::UnicodeUTF8));
        pushButton_jogP->setText(QApplication::translate("EcatDemoClass", "Jog+", 0, QApplication::UnicodeUTF8));
        pushButton_home->setText(QApplication::translate("EcatDemoClass", "Home", 0, QApplication::UnicodeUTF8));
        pushButton_prob->setText(QApplication::translate("EcatDemoClass", "Prob", 0, QApplication::UnicodeUTF8));
        pushButton_object->setText(QApplication::translate("EcatDemoClass", "Object", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EcatDemoClass: public Ui_EcatDemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ECATDEMO_H
