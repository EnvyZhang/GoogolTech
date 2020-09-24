/********************************************************************************
** Form generated from reading UI file 'ecathome.ui'
**
** Created: Tue Sep 15 15:14:56 2020
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ECATHOME_H
#define UI_ECATHOME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EcatHome
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_homeMode;
    QLabel *label_6;
    QLabel *label_homeSts;
    QLabel *label_StsWord;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEdit_speed1;
    QLabel *label_4;
    QLineEdit *lineEdit_speed2;
    QLabel *label_2;
    QLineEdit *lineEdit_acc;
    QLabel *label_5;
    QLineEdit *lineEdit_offset;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_homePix;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_nLmt;
    QLabel *label_dir1;
    QLabel *label_home;
    QLabel *label_dir2;
    QLabel *label_pLmt;
    QVBoxLayout *verticalLayout;
    QLabel *label_ecatMode;
    QPushButton *pushButton_servOn;
    QPushButton *pushButton_cspMode;
    QPushButton *pushButton_homeMode;
    QPushButton *pushButton_startHome;
    QPushButton *pushButton_stopHome;

    void setupUi(QWidget *EcatHome)
    {
        if (EcatHome->objectName().isEmpty())
            EcatHome->setObjectName(QString::fromUtf8("EcatHome"));
        EcatHome->resize(639, 362);
        EcatHome->setStyleSheet(QString::fromUtf8("QComboBox QAbstractItemView::item { min-height: 40px; min-width: 60px; }"));
        verticalLayout_3 = new QVBoxLayout(EcatHome);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(EcatHome);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        comboBox_homeMode = new QComboBox(EcatHome);
        comboBox_homeMode->setObjectName(QString::fromUtf8("comboBox_homeMode"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_homeMode->sizePolicy().hasHeightForWidth());
        comboBox_homeMode->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        comboBox_homeMode->setFont(font);
        comboBox_homeMode->setContextMenuPolicy(Qt::NoContextMenu);
        comboBox_homeMode->setStyleSheet(QString::fromUtf8(""));
        comboBox_homeMode->setMaxVisibleItems(16);
        comboBox_homeMode->setInsertPolicy(QComboBox::InsertAtTop);
        comboBox_homeMode->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        horizontalLayout->addWidget(comboBox_homeMode);

        label_6 = new QLabel(EcatHome);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);

        label_homeSts = new QLabel(EcatHome);
        label_homeSts->setObjectName(QString::fromUtf8("label_homeSts"));
        label_homeSts->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_homeSts);

        label_StsWord = new QLabel(EcatHome);
        label_StsWord->setObjectName(QString::fromUtf8("label_StsWord"));
        label_StsWord->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_StsWord);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 7);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 2);
        horizontalLayout->setStretch(4, 2);

        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(EcatHome);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_3);

        lineEdit_speed1 = new QLineEdit(EcatHome);
        lineEdit_speed1->setObjectName(QString::fromUtf8("lineEdit_speed1"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_speed1->sizePolicy().hasHeightForWidth());
        lineEdit_speed1->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(lineEdit_speed1);

        label_4 = new QLabel(EcatHome);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_4);

        lineEdit_speed2 = new QLineEdit(EcatHome);
        lineEdit_speed2->setObjectName(QString::fromUtf8("lineEdit_speed2"));
        sizePolicy1.setHeightForWidth(lineEdit_speed2->sizePolicy().hasHeightForWidth());
        lineEdit_speed2->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(lineEdit_speed2);

        label_2 = new QLabel(EcatHome);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        lineEdit_acc = new QLineEdit(EcatHome);
        lineEdit_acc->setObjectName(QString::fromUtf8("lineEdit_acc"));
        sizePolicy1.setHeightForWidth(lineEdit_acc->sizePolicy().hasHeightForWidth());
        lineEdit_acc->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(lineEdit_acc);

        label_5 = new QLabel(EcatHome);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_5);

        lineEdit_offset = new QLineEdit(EcatHome);
        lineEdit_offset->setObjectName(QString::fromUtf8("lineEdit_offset"));
        sizePolicy1.setHeightForWidth(lineEdit_offset->sizePolicy().hasHeightForWidth());
        lineEdit_offset->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(lineEdit_offset);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 1);
        horizontalLayout_2->setStretch(3, 2);
        horizontalLayout_2->setStretch(4, 1);
        horizontalLayout_2->setStretch(5, 2);
        horizontalLayout_2->setStretch(6, 1);
        horizontalLayout_2->setStretch(7, 2);

        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_homePix = new QLabel(EcatHome);
        label_homePix->setObjectName(QString::fromUtf8("label_homePix"));
        label_homePix->setStyleSheet(QString::fromUtf8(""));
        label_homePix->setPixmap(QPixmap(QString::fromUtf8(":/EcatDemo/Resources/HM_1.png")));
        label_homePix->setScaledContents(false);

        verticalLayout_2->addWidget(label_homePix);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_nLmt = new QLabel(EcatHome);
        label_nLmt->setObjectName(QString::fromUtf8("label_nLmt"));
        label_nLmt->setStyleSheet(QString::fromUtf8("background: rgb(0,255,0);\n"
"color: black;\n"
"border:none;\n"
""));
        label_nLmt->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_nLmt);

        label_dir1 = new QLabel(EcatHome);
        label_dir1->setObjectName(QString::fromUtf8("label_dir1"));
        label_dir1->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"font: 28pt \"Agency FB\";"));
        label_dir1->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_dir1);

        label_home = new QLabel(EcatHome);
        label_home->setObjectName(QString::fromUtf8("label_home"));
        label_home->setStyleSheet(QString::fromUtf8("background: rgb(0,255,0);\n"
"color: black;\n"
"border:none;\n"
""));
        label_home->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_home);

        label_dir2 = new QLabel(EcatHome);
        label_dir2->setObjectName(QString::fromUtf8("label_dir2"));
        label_dir2->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"font: 28pt \"Agency FB\";"));
        label_dir2->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_dir2);

        label_pLmt = new QLabel(EcatHome);
        label_pLmt->setObjectName(QString::fromUtf8("label_pLmt"));
        label_pLmt->setStyleSheet(QString::fromUtf8("background: rgb(0,255,0);\n"
"color: black;\n"
"border:none;\n"
""));
        label_pLmt->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_pLmt);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 3);
        horizontalLayout_3->setStretch(2, 1);
        horizontalLayout_3->setStretch(3, 3);
        horizontalLayout_3->setStretch(4, 1);

        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout_2->setStretch(0, 8);
        verticalLayout_2->setStretch(1, 1);

        horizontalLayout_4->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, 16);
        label_ecatMode = new QLabel(EcatHome);
        label_ecatMode->setObjectName(QString::fromUtf8("label_ecatMode"));
        label_ecatMode->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_ecatMode);

        pushButton_servOn = new QPushButton(EcatHome);
        pushButton_servOn->setObjectName(QString::fromUtf8("pushButton_servOn"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_servOn->sizePolicy().hasHeightForWidth());
        pushButton_servOn->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(pushButton_servOn);

        pushButton_cspMode = new QPushButton(EcatHome);
        pushButton_cspMode->setObjectName(QString::fromUtf8("pushButton_cspMode"));
        sizePolicy2.setHeightForWidth(pushButton_cspMode->sizePolicy().hasHeightForWidth());
        pushButton_cspMode->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(pushButton_cspMode);

        pushButton_homeMode = new QPushButton(EcatHome);
        pushButton_homeMode->setObjectName(QString::fromUtf8("pushButton_homeMode"));
        sizePolicy2.setHeightForWidth(pushButton_homeMode->sizePolicy().hasHeightForWidth());
        pushButton_homeMode->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(pushButton_homeMode);

        pushButton_startHome = new QPushButton(EcatHome);
        pushButton_startHome->setObjectName(QString::fromUtf8("pushButton_startHome"));
        sizePolicy2.setHeightForWidth(pushButton_startHome->sizePolicy().hasHeightForWidth());
        pushButton_startHome->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(pushButton_startHome);

        pushButton_stopHome = new QPushButton(EcatHome);
        pushButton_stopHome->setObjectName(QString::fromUtf8("pushButton_stopHome"));
        sizePolicy2.setHeightForWidth(pushButton_stopHome->sizePolicy().hasHeightForWidth());
        pushButton_stopHome->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(pushButton_stopHome);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(4, 1);
        verticalLayout->setStretch(5, 1);

        horizontalLayout_4->addLayout(verticalLayout);

        horizontalLayout_4->setStretch(0, 8);
        horizontalLayout_4->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_4);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 1);
        verticalLayout_3->setStretch(2, 9);

        retranslateUi(EcatHome);

        QMetaObject::connectSlotsByName(EcatHome);
    } // setupUi

    void retranslateUi(QWidget *EcatHome)
    {
        EcatHome->setWindowTitle(QApplication::translate("EcatHome", "EcatHome", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("EcatHome", "HomeMode:", 0, QApplication::UnicodeUTF8));
        comboBox_homeMode->clear();
        comboBox_homeMode->insertItems(0, QStringList()
         << QApplication::translate("EcatHome", "New Item", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("EcatHome", "New Item", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("EcatHome", "New Item", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("EcatHome", "New Item", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("EcatHome", "New Item", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("EcatHome", "HomeSts:", 0, QApplication::UnicodeUTF8));
        label_homeSts->setText(QApplication::translate("EcatHome", "0", 0, QApplication::UnicodeUTF8));
        label_StsWord->setText(QString());
        label_3->setText(QApplication::translate("EcatHome", "SearchVel:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("EcatHome", "LoctVel:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("EcatHome", "Acc:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("EcatHome", "offset:", 0, QApplication::UnicodeUTF8));
        label_homePix->setText(QString());
        label_nLmt->setText(QApplication::translate("EcatHome", "Lmt-", 0, QApplication::UnicodeUTF8));
        label_dir1->setText(QApplication::translate("EcatHome", ">>>>>>>>>>>>", 0, QApplication::UnicodeUTF8));
        label_home->setText(QApplication::translate("EcatHome", "Home", 0, QApplication::UnicodeUTF8));
        label_dir2->setText(QApplication::translate("EcatHome", ">>>>>>>>>>>>", 0, QApplication::UnicodeUTF8));
        label_pLmt->setText(QApplication::translate("EcatHome", "Lmt+", 0, QApplication::UnicodeUTF8));
        label_ecatMode->setText(QApplication::translate("EcatHome", "8.CSP", 0, QApplication::UnicodeUTF8));
        pushButton_servOn->setText(QApplication::translate("EcatHome", "ServOn", 0, QApplication::UnicodeUTF8));
        pushButton_cspMode->setText(QApplication::translate("EcatHome", "CSPMode", 0, QApplication::UnicodeUTF8));
        pushButton_homeMode->setText(QApplication::translate("EcatHome", "HomeMode", 0, QApplication::UnicodeUTF8));
        pushButton_startHome->setText(QApplication::translate("EcatHome", "StartHome", 0, QApplication::UnicodeUTF8));
        pushButton_stopHome->setText(QApplication::translate("EcatHome", "StopHome", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EcatHome: public Ui_EcatHome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ECATHOME_H
