/********************************************************************************
** Form generated from reading UI file 'ecatprob.ui'
**
** Created: Tue Sep 15 15:14:56 2020
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ECATPROB_H
#define UI_ECATPROB_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ecatProb
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label_9;
    QLineEdit *lineEdit_probelPrm;
    QLabel *label;
    QComboBox *comboBox_probel1;
    QLabel *label_5;
    QComboBox *comboBox_probel2;
    QLabel *label_2;
    QComboBox *comboBox_type1;
    QLabel *label_6;
    QComboBox *comboBox_type2;
    QLabel *label_3;
    QComboBox *comboBox_rising1;
    QLabel *label_7;
    QComboBox *comboBox_rising2;
    QLabel *label_4;
    QComboBox *comboBox_falling1;
    QLabel *label_8;
    QComboBox *comboBox_falling2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_set;
    QPushButton *pushButton_get;
    QGridLayout *gridLayout_2;
    QLabel *label_10;
    QLabel *label_falling1;
    QLabel *label_15;
    QLineEdit *lineEdit_risingValue1;
    QLabel *label_20;
    QLineEdit *lineEdit_risingValue2;
    QLabel *label_fallingValue1;
    QLineEdit *lineEdit_fallingValue1;
    QLabel *label_21;
    QLineEdit *lineEdit_fallingValue2;
    QLineEdit *lineEdit_probelSts;
    QLabel *label_probel1;
    QLabel *label_rising1;
    QLabel *label_probel2;
    QLabel *label_rising2;
    QLabel *label_falling2;

    void setupUi(QWidget *ecatProb)
    {
        if (ecatProb->objectName().isEmpty())
            ecatProb->setObjectName(QString::fromUtf8("ecatProb"));
        ecatProb->resize(486, 313);
        ecatProb->setStyleSheet(QString::fromUtf8("QComboBox QAbstractItemView::item { min-height: 40px; min-width: 60px; }"));
        verticalLayout_2 = new QVBoxLayout(ecatProb);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(6);
        label_9 = new QLabel(ecatProb);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 0, 0, 1, 2);

        lineEdit_probelPrm = new QLineEdit(ecatProb);
        lineEdit_probelPrm->setObjectName(QString::fromUtf8("lineEdit_probelPrm"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_probelPrm->sizePolicy().hasHeightForWidth());
        lineEdit_probelPrm->setSizePolicy(sizePolicy);
        lineEdit_probelPrm->setReadOnly(true);

        gridLayout->addWidget(lineEdit_probelPrm, 0, 2, 1, 3);

        label = new QLabel(ecatProb);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        comboBox_probel1 = new QComboBox(ecatProb);
        comboBox_probel1->setObjectName(QString::fromUtf8("comboBox_probel1"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_probel1->sizePolicy().hasHeightForWidth());
        comboBox_probel1->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(comboBox_probel1, 1, 1, 1, 2);

        label_5 = new QLabel(ecatProb);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 3, 1, 1);

        comboBox_probel2 = new QComboBox(ecatProb);
        comboBox_probel2->setObjectName(QString::fromUtf8("comboBox_probel2"));
        sizePolicy1.setHeightForWidth(comboBox_probel2->sizePolicy().hasHeightForWidth());
        comboBox_probel2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(comboBox_probel2, 1, 4, 1, 1);

        label_2 = new QLabel(ecatProb);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        comboBox_type1 = new QComboBox(ecatProb);
        comboBox_type1->setObjectName(QString::fromUtf8("comboBox_type1"));
        sizePolicy1.setHeightForWidth(comboBox_type1->sizePolicy().hasHeightForWidth());
        comboBox_type1->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(comboBox_type1, 2, 1, 1, 2);

        label_6 = new QLabel(ecatProb);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 2, 3, 1, 1);

        comboBox_type2 = new QComboBox(ecatProb);
        comboBox_type2->setObjectName(QString::fromUtf8("comboBox_type2"));
        sizePolicy1.setHeightForWidth(comboBox_type2->sizePolicy().hasHeightForWidth());
        comboBox_type2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(comboBox_type2, 2, 4, 1, 1);

        label_3 = new QLabel(ecatProb);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        comboBox_rising1 = new QComboBox(ecatProb);
        comboBox_rising1->setObjectName(QString::fromUtf8("comboBox_rising1"));
        sizePolicy1.setHeightForWidth(comboBox_rising1->sizePolicy().hasHeightForWidth());
        comboBox_rising1->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(comboBox_rising1, 3, 1, 1, 2);

        label_7 = new QLabel(ecatProb);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 3, 3, 1, 1);

        comboBox_rising2 = new QComboBox(ecatProb);
        comboBox_rising2->setObjectName(QString::fromUtf8("comboBox_rising2"));
        sizePolicy1.setHeightForWidth(comboBox_rising2->sizePolicy().hasHeightForWidth());
        comboBox_rising2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(comboBox_rising2, 3, 4, 1, 1);

        label_4 = new QLabel(ecatProb);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        comboBox_falling1 = new QComboBox(ecatProb);
        comboBox_falling1->setObjectName(QString::fromUtf8("comboBox_falling1"));
        sizePolicy1.setHeightForWidth(comboBox_falling1->sizePolicy().hasHeightForWidth());
        comboBox_falling1->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(comboBox_falling1, 4, 1, 1, 2);

        label_8 = new QLabel(ecatProb);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 4, 3, 1, 1);

        comboBox_falling2 = new QComboBox(ecatProb);
        comboBox_falling2->setObjectName(QString::fromUtf8("comboBox_falling2"));
        sizePolicy1.setHeightForWidth(comboBox_falling2->sizePolicy().hasHeightForWidth());
        comboBox_falling2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(comboBox_falling2, 4, 4, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_set = new QPushButton(ecatProb);
        pushButton_set->setObjectName(QString::fromUtf8("pushButton_set"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_set->sizePolicy().hasHeightForWidth());
        pushButton_set->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(pushButton_set);

        pushButton_get = new QPushButton(ecatProb);
        pushButton_get->setObjectName(QString::fromUtf8("pushButton_get"));
        sizePolicy2.setHeightForWidth(pushButton_get->sizePolicy().hasHeightForWidth());
        pushButton_get->setSizePolicy(sizePolicy2);
        pushButton_get->setCheckable(true);

        verticalLayout->addWidget(pushButton_get);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(6);
        label_10 = new QLabel(ecatProb);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 0, 0, 1, 1);

        label_falling1 = new QLabel(ecatProb);
        label_falling1->setObjectName(QString::fromUtf8("label_falling1"));
        label_falling1->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 127);\n"
"color: rgb(255, 255, 255);\n"
"border:0;\n"
""));
        label_falling1->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_falling1, 1, 2, 1, 1);

        label_15 = new QLabel(ecatProb);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 2, 0, 1, 1);

        lineEdit_risingValue1 = new QLineEdit(ecatProb);
        lineEdit_risingValue1->setObjectName(QString::fromUtf8("lineEdit_risingValue1"));
        sizePolicy.setHeightForWidth(lineEdit_risingValue1->sizePolicy().hasHeightForWidth());
        lineEdit_risingValue1->setSizePolicy(sizePolicy);
        lineEdit_risingValue1->setReadOnly(true);

        gridLayout_2->addWidget(lineEdit_risingValue1, 2, 1, 1, 2);

        label_20 = new QLabel(ecatProb);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_2->addWidget(label_20, 2, 4, 1, 1);

        lineEdit_risingValue2 = new QLineEdit(ecatProb);
        lineEdit_risingValue2->setObjectName(QString::fromUtf8("lineEdit_risingValue2"));
        sizePolicy.setHeightForWidth(lineEdit_risingValue2->sizePolicy().hasHeightForWidth());
        lineEdit_risingValue2->setSizePolicy(sizePolicy);
        lineEdit_risingValue2->setReadOnly(true);

        gridLayout_2->addWidget(lineEdit_risingValue2, 2, 5, 1, 2);

        label_fallingValue1 = new QLabel(ecatProb);
        label_fallingValue1->setObjectName(QString::fromUtf8("label_fallingValue1"));

        gridLayout_2->addWidget(label_fallingValue1, 3, 0, 1, 1);

        lineEdit_fallingValue1 = new QLineEdit(ecatProb);
        lineEdit_fallingValue1->setObjectName(QString::fromUtf8("lineEdit_fallingValue1"));
        sizePolicy.setHeightForWidth(lineEdit_fallingValue1->sizePolicy().hasHeightForWidth());
        lineEdit_fallingValue1->setSizePolicy(sizePolicy);
        lineEdit_fallingValue1->setReadOnly(true);

        gridLayout_2->addWidget(lineEdit_fallingValue1, 3, 1, 1, 2);

        label_21 = new QLabel(ecatProb);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_2->addWidget(label_21, 3, 4, 1, 1);

        lineEdit_fallingValue2 = new QLineEdit(ecatProb);
        lineEdit_fallingValue2->setObjectName(QString::fromUtf8("lineEdit_fallingValue2"));
        sizePolicy.setHeightForWidth(lineEdit_fallingValue2->sizePolicy().hasHeightForWidth());
        lineEdit_fallingValue2->setSizePolicy(sizePolicy);
        lineEdit_fallingValue2->setReadOnly(true);

        gridLayout_2->addWidget(lineEdit_fallingValue2, 3, 5, 1, 2);

        lineEdit_probelSts = new QLineEdit(ecatProb);
        lineEdit_probelSts->setObjectName(QString::fromUtf8("lineEdit_probelSts"));
        sizePolicy.setHeightForWidth(lineEdit_probelSts->sizePolicy().hasHeightForWidth());
        lineEdit_probelSts->setSizePolicy(sizePolicy);
        lineEdit_probelSts->setReadOnly(true);

        gridLayout_2->addWidget(lineEdit_probelSts, 0, 1, 1, 2);

        label_probel1 = new QLabel(ecatProb);
        label_probel1->setObjectName(QString::fromUtf8("label_probel1"));
        label_probel1->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 127);\n"
"color: rgb(255, 255, 255);\n"
"border:0;\n"
""));
        label_probel1->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_probel1, 1, 0, 1, 1);

        label_rising1 = new QLabel(ecatProb);
        label_rising1->setObjectName(QString::fromUtf8("label_rising1"));
        label_rising1->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 127);\n"
"color: rgb(255, 255, 255);\n"
"border:0;\n"
""));
        label_rising1->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_rising1, 1, 1, 1, 1);

        label_probel2 = new QLabel(ecatProb);
        label_probel2->setObjectName(QString::fromUtf8("label_probel2"));
        label_probel2->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 127);\n"
"color: rgb(255, 255, 255);\n"
"border:0;\n"
""));
        label_probel2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_probel2, 1, 4, 1, 1);

        label_rising2 = new QLabel(ecatProb);
        label_rising2->setObjectName(QString::fromUtf8("label_rising2"));
        label_rising2->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 127);\n"
"color: rgb(255, 255, 255);\n"
"border:0;\n"
""));
        label_rising2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_rising2, 1, 5, 1, 1);

        label_falling2 = new QLabel(ecatProb);
        label_falling2->setObjectName(QString::fromUtf8("label_falling2"));
        label_falling2->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 127);\n"
"color: rgb(255, 255, 255);\n"
"border:0;\n"
""));
        label_falling2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_falling2, 1, 6, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);

        verticalLayout_2->setStretch(0, 3);
        verticalLayout_2->setStretch(1, 2);

        retranslateUi(ecatProb);

        QMetaObject::connectSlotsByName(ecatProb);
    } // setupUi

    void retranslateUi(QWidget *ecatProb)
    {
        ecatProb->setWindowTitle(QApplication::translate("ecatProb", "ecatProb", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ecatProb", "ProbeParam", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ecatProb", "Probe1", 0, QApplication::UnicodeUTF8));
        comboBox_probel1->clear();
        comboBox_probel1->insertItems(0, QStringList()
         << QApplication::translate("ecatProb", "0. OFF", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ecatProb", "1. Enable", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("ecatProb", "Probe2", 0, QApplication::UnicodeUTF8));
        comboBox_probel2->clear();
        comboBox_probel2->insertItems(0, QStringList()
         << QApplication::translate("ecatProb", "0. OFF", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ecatProb", "1. Enable", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("ecatProb", "Type", 0, QApplication::UnicodeUTF8));
        comboBox_type1->clear();
        comboBox_type1->insertItems(0, QStringList()
         << QApplication::translate("ecatProb", "0. Signal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ecatProb", "1. Continous", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("ecatProb", "Type", 0, QApplication::UnicodeUTF8));
        comboBox_type2->clear();
        comboBox_type2->insertItems(0, QStringList()
         << QApplication::translate("ecatProb", "0. Signal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ecatProb", "1. Continous", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("ecatProb", "Rising", 0, QApplication::UnicodeUTF8));
        comboBox_rising1->clear();
        comboBox_rising1->insertItems(0, QStringList()
         << QApplication::translate("ecatProb", "0. Switch off", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ecatProb", "1. Switch on", 0, QApplication::UnicodeUTF8)
        );
        label_7->setText(QApplication::translate("ecatProb", "Rising", 0, QApplication::UnicodeUTF8));
        comboBox_rising2->clear();
        comboBox_rising2->insertItems(0, QStringList()
         << QApplication::translate("ecatProb", "0. Switch off", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ecatProb", "1. Switch on", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("ecatProb", "Falling", 0, QApplication::UnicodeUTF8));
        comboBox_falling1->clear();
        comboBox_falling1->insertItems(0, QStringList()
         << QApplication::translate("ecatProb", "0. Switch off", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ecatProb", "1. Switch on", 0, QApplication::UnicodeUTF8)
        );
        label_8->setText(QApplication::translate("ecatProb", "Falling", 0, QApplication::UnicodeUTF8));
        comboBox_falling2->clear();
        comboBox_falling2->insertItems(0, QStringList()
         << QApplication::translate("ecatProb", "0. Switch off", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ecatProb", "1. Switch on", 0, QApplication::UnicodeUTF8)
        );
        pushButton_set->setText(QApplication::translate("ecatProb", "SetProbePrm", 0, QApplication::UnicodeUTF8));
        pushButton_get->setText(QApplication::translate("ecatProb", "GetProbeStatus", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("ecatProb", "ProbeStatus", 0, QApplication::UnicodeUTF8));
        label_falling1->setText(QApplication::translate("ecatProb", "Falling", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("ecatProb", "RisingValue", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("ecatProb", "RisingValue", 0, QApplication::UnicodeUTF8));
        label_fallingValue1->setText(QApplication::translate("ecatProb", "FallingValue", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("ecatProb", "FallingValue", 0, QApplication::UnicodeUTF8));
        label_probel1->setText(QApplication::translate("ecatProb", "Probel1", 0, QApplication::UnicodeUTF8));
        label_rising1->setText(QApplication::translate("ecatProb", "Rising", 0, QApplication::UnicodeUTF8));
        label_probel2->setText(QApplication::translate("ecatProb", "Probel2", 0, QApplication::UnicodeUTF8));
        label_rising2->setText(QApplication::translate("ecatProb", "Rising", 0, QApplication::UnicodeUTF8));
        label_falling2->setText(QApplication::translate("ecatProb", "Falling", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ecatProb: public Ui_ecatProb {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ECATPROB_H
