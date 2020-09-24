#ifndef ECATHOME_H
#define ECATHOME_H

#include <QWidget>
#include "ui_ecathome.h"



class EcatHome : public QWidget
{
	Q_OBJECT

public:
	EcatHome(QWidget *parent = 0);
	~EcatHome();

	void refreshEcatHomeStatus();
private:
	Ui::EcatHome ui;
	void checkEcatHomeRtnValue(QString qstr, short iRtn);
private slots:
	void on_comboBox_homeMode_currentIndexChanged (int index);
	void on_pushButton_homeMode_clicked();
	void on_pushButton_cspMode_clicked();
	void on_pushButton_startHome_clicked();
	void on_pushButton_stopHome_clicked();
	void on_pushButton_servOn_clicked();

private:
	short m_sRtn;

	short m_sLastDirection;

protected:
	void resizeEvent(QResizeEvent *e);
};

#endif // ECATHOME_H
