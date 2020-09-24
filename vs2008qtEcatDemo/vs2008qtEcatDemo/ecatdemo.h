#ifndef ECATDEMO_H
#define ECATDEMO_H

#include <QtGui/QWidget>
#include "ui_ecatdemo.h"
#include "ecathome.h"
#include "ecatprob.h"
#include "ecatobject.h"

#define Cnst_Grey	0
#define Cnst_Green	1
#define  Cnst_Red	2

#define Cnst_RecdCnt 3

class EcatDemo : public QWidget
{
	Q_OBJECT

public:
	EcatDemo(QWidget *parent = 0, Qt::WFlags flags = 0);
	~EcatDemo();


private:
	Ui::EcatDemoClass ui;
	EcatHome *m_pqEcatHome;
	EcatProb *m_pqEcatProb;

	EcatObject *m_pqEcatObject;

	QTimer *m_pqTimer;



	short initMotionCard();
	void initUi();
	void checkRtnValue(QString qstr, short iRtn);
	//设置PushButton显示文字和显示颜色，0，灰色默认，1绿色，2红色
	void setButtonProperity(QPushButton *qButton,QString qstrText,short sColor=-1);
	void setLabelProperity(QLabel *qLabelt,QString qstrText,short sColor=-1);
private slots:
	void on_comboBox_core_currentIndexChanged (int index);
	void on_comboBox_axis_currentIndexChanged (int index);

	void on_pushButton_clr_clicked();
	void on_pushButton_serv_clicked();
	void on_pushButton_zero_clicked();
	void on_pushButton_stop_clicked();
	void on_pushButton_jogN_clicked();
	void on_pushButton_jogP_clicked();
	void on_pushButton_home_clicked();
	void on_pushButton_prob_clicked();
	void on_pushButton_alarm_clicked();
	void on_pushButton_object_clicked();

	//刷新状态
	void refreshStatusInfoSlot();
private:
	short m_sRtn;
	bool m_bIgnore;

};

#endif // ECATDEMO_H
