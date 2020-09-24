#ifndef ECATPROB_H
#define ECATPROB_H

#include <QWidget>
#include "ui_ecatprob.h"

class EcatProb : public QWidget
{
	Q_OBJECT

public:
	EcatProb(QWidget *parent = 0);
	~EcatProb();

	void refreshEcatProbelStatus();
private:
	Ui::ecatProb ui;

	void updateProbelPrmUi();
	void updateProbelStatusUi();
	void checkEcatProbelRtnValue( QString qstr, short iRtn );
private slots:
	void probelPrmWidgetChangeSlot();
	void on_pushButton_set_clicked();
	void on_pushButton_get_clicked();
	
};

#endif // ECATPROB_H
