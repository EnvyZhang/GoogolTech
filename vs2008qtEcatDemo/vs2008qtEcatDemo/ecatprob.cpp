#include "StdAfx.h"
#include "ecatprob.h"

EcatProb::EcatProb(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.comboBox_probel1->setView(new QListView());
	ui.comboBox_rising1->setView(new QListView());
	ui.comboBox_type1->setView(new QListView());
	ui.comboBox_falling1->setView(new QListView());
	ui.comboBox_probel2->setView(new QListView());
	ui.comboBox_rising2->setView(new QListView());
	ui.comboBox_type2->setView(new QListView());
	ui.comboBox_falling2->setView(new QListView());

	g_uProbelPrm.sProbelPrm = 0;
	g_tProbelStatus.uProbelStatus.sProbelStatus = 0;
	g_tProbelStatus.lProbelFallValue1 = 0;
	g_tProbelStatus.lProbelFallValue2 = 0;
	g_tProbelStatus.lProbelRiseValue1 = 0;
	g_tProbelStatus.lProbelRiseValue2 = 0;


	updateProbelPrmUi();
	updateProbelStatusUi();
	connect(ui.comboBox_probel1,SIGNAL(currentIndexChanged(int)),this,SLOT(probelPrmWidgetChangeSlot()));
	connect(ui.comboBox_type1,SIGNAL(currentIndexChanged(int)),this,SLOT(probelPrmWidgetChangeSlot()));
	connect(ui.comboBox_rising1,SIGNAL(currentIndexChanged(int)),this,SLOT(probelPrmWidgetChangeSlot()));
	connect(ui.comboBox_falling1,SIGNAL(currentIndexChanged(int)),this,SLOT(probelPrmWidgetChangeSlot()));

	connect(ui.comboBox_probel2,SIGNAL(currentIndexChanged(int)),this,SLOT(probelPrmWidgetChangeSlot()));
	connect(ui.comboBox_type2,SIGNAL(currentIndexChanged(int)),this,SLOT(probelPrmWidgetChangeSlot()));
	connect(ui.comboBox_rising2,SIGNAL(currentIndexChanged(int)),this,SLOT(probelPrmWidgetChangeSlot()));
	connect(ui.comboBox_falling2,SIGNAL(currentIndexChanged(int)),this,SLOT(probelPrmWidgetChangeSlot()));
}

EcatProb::~EcatProb()
{

}
//************************************
// Method:    	initUi
// Description:	
// Returns:   void
//************************************
void EcatProb::updateProbelPrmUi()
{
	QString qstr = QString("%1").arg(g_uProbelPrm.sProbelPrm);
	ui.lineEdit_probelPrm->setText(qstr);
	if (g_uProbelPrm.tProbelPrmBit.uchProbel1)
	{
		ui.comboBox_probel1->setCurrentIndex(1);
	}//if
	else
	{
		ui.comboBox_probel1->setCurrentIndex(0);
	}//if..else
	if (g_uProbelPrm.tProbelPrmBit.uchType1)
	{
		ui.comboBox_type1->setCurrentIndex(1);
	}//if
	else
	{
		ui.comboBox_type1->setCurrentIndex(0);
	}//if..else
	if (g_uProbelPrm.tProbelPrmBit.uchRising1)
	{
		ui.comboBox_rising1->setCurrentIndex(1);
	}//if
	else
	{
		ui.comboBox_rising1->setCurrentIndex(0);
	}//if..else
	if (g_uProbelPrm.tProbelPrmBit.uchFalling1)
	{
		ui.comboBox_falling1->setCurrentIndex(1);
	}//if
	else
	{
		ui.comboBox_falling1->setCurrentIndex(0);
	}//if..else
	//Ì½Õë2
	if (g_uProbelPrm.tProbelPrmBit.uchProbel2)
	{
		ui.comboBox_probel2->setCurrentIndex(1);
	}//if
	else
	{
		ui.comboBox_probel2->setCurrentIndex(0);
	}//if..else
	if (g_uProbelPrm.tProbelPrmBit.uchType2)
	{
		ui.comboBox_type2->setCurrentIndex(1);
	}//if
	else
	{
		ui.comboBox_type2->setCurrentIndex(0);
	}//if..else
	if (g_uProbelPrm.tProbelPrmBit.uchRising2)
	{
		ui.comboBox_rising2->setCurrentIndex(1);
	}//if
	else
	{
		ui.comboBox_rising2->setCurrentIndex(0);
	}//if..else
	if (g_uProbelPrm.tProbelPrmBit.uchFalling2)
	{
		ui.comboBox_falling2->setCurrentIndex(1);
	}//if
	else
	{
		ui.comboBox_falling2->setCurrentIndex(0);
	}//if..else
}
//************************************
// Method:    	updateProbelStstusUi
// Description:	
// Returns:   void
//************************************
void EcatProb::updateProbelStatusUi()
{
	QString qstr = QString("0x%1").arg(g_tProbelStatus.uProbelStatus.sProbelStatus,0,16);
	ui.lineEdit_probelSts->setText(qstr);
	if (g_tProbelStatus.uProbelStatus.tProbelStatusBit.uchProbel1)
	{
		ui.label_probel1->setStyleSheet("background: rgb(0,255,0);color: black;border:none;");
	}//if
	else
	{
		ui.label_probel1->setStyleSheet("background-color: rgb(85, 85, 127);color: rgb(255, 255, 255);border:none;");
	}//if..else
	if (g_tProbelStatus.uProbelStatus.tProbelStatusBit.uchRising1)
	{
		ui.label_rising1->setStyleSheet("background: rgb(0,255,0);color: black;border:none;");
	}//if
	else
	{
		ui.label_rising1->setStyleSheet("background-color: rgb(85, 85, 127);color: rgb(255, 255, 255);border:none;");
	}//if..else
	if (g_tProbelStatus.uProbelStatus.tProbelStatusBit.uchFalling1)
	{
		ui.label_falling1->setStyleSheet("background: rgb(0,255,0);color: black;border:none;");
	}//if
	else
	{
		ui.label_falling1->setStyleSheet("background-color: rgb(85, 85, 127);color: rgb(255, 255, 255);border:none;");
	}//if..else
	qstr = QString("%1").arg(g_tProbelStatus.lProbelRiseValue1);
	ui.lineEdit_risingValue1->setText(qstr);
	qstr = QString("%1").arg(g_tProbelStatus.lProbelFallValue1);
	ui.lineEdit_fallingValue1->setText(qstr);
	//Probel2
	if (g_tProbelStatus.uProbelStatus.tProbelStatusBit.uchProbel2)
	{
		ui.label_probel2->setStyleSheet("background: rgb(0,255,0);color: black;border:none;");
	}//if
	else
	{
		ui.label_probel2->setStyleSheet("background-color: rgb(85, 85, 127);color: rgb(255, 255, 255);border:none;");
	}//if..else
	if (g_tProbelStatus.uProbelStatus.tProbelStatusBit.uchRising2)
	{
		ui.label_rising2->setStyleSheet("background: rgb(0,255,0);color: black;border:none;");
	}//if
	else
	{
		ui.label_rising2->setStyleSheet("background-color: rgb(85, 85, 127);color: rgb(255, 255, 255);border:none;");
	}//if..else
	if (g_tProbelStatus.uProbelStatus.tProbelStatusBit.uchFalling2)
	{
		ui.label_falling2->setStyleSheet("background: rgb(0,255,0);color: black;border:none;");
	}//if
	else
	{
		ui.label_falling2->setStyleSheet("background-color: rgb(85, 85, 127);color: rgb(255, 255, 255);border:none;");
	}//if..else
	qstr = QString("%1").arg(g_tProbelStatus.lProbelRiseValue2);
	ui.lineEdit_risingValue2->setText(qstr);
	qstr = QString("%1").arg(g_tProbelStatus.lProbelFallValue2);
	ui.lineEdit_fallingValue2->setText(qstr);
}
//************************************
// Method:    	probelPrmWidgetChangeSlot
// Description:	
// Returns:   void
//************************************
void EcatProb::probelPrmWidgetChangeSlot()
{
	g_uProbelPrm.tProbelPrmBit.uchProbel1 = ui.comboBox_probel1->currentIndex();
	g_uProbelPrm.tProbelPrmBit.uchType1 = ui.comboBox_type1->currentIndex();
	g_uProbelPrm.tProbelPrmBit.uchRising1 = ui.comboBox_rising1->currentIndex();
	g_uProbelPrm.tProbelPrmBit.uchFalling1 = ui.comboBox_falling1->currentIndex();

	g_uProbelPrm.tProbelPrmBit.uchProbel2 = ui.comboBox_probel2->currentIndex();
	g_uProbelPrm.tProbelPrmBit.uchType2 = ui.comboBox_type2->currentIndex();
	g_uProbelPrm.tProbelPrmBit.uchRising2 = ui.comboBox_rising2->currentIndex();
	g_uProbelPrm.tProbelPrmBit.uchFalling2 = ui.comboBox_falling2->currentIndex();

	QString qstr = QString("0x%1").arg(g_uProbelPrm.sProbelPrm,0,16);
	ui.lineEdit_probelPrm->setText(qstr);
}
//************************************
// Method:    	on_pushButton_set_clicked
// Description:	
// Returns:   void
//************************************
void EcatProb::on_pushButton_set_clicked()
{
	short sRtn = GTN_SetTouchProbeFunction(g_sCurCore,g_sCurAxis,g_uProbelPrm.sProbelPrm);
	this->checkEcatProbelRtnValue("GTN_SetTouchProbeFunction",sRtn);
}
//************************************
// Method:    	on_pushButton_get_clicked
// Description:	
// Returns:   void
//************************************
void EcatProb::on_pushButton_get_clicked()
{

}
void EcatProb::checkEcatProbelRtnValue( QString qstr, short iRtn )
{
	if (iRtn!=0)
	{
		if (!qstr.isEmpty())
		{
			QString qstrText = QString("%1=%2").arg(iRtn).arg(qstr);
			QMessageBox::warning(this,"Warnning",qstrText);
		}//if
	}//if
}
//************************************
// Method:    	refreshEcatProbelStatus
// Description:	
// Returns:   void
//************************************
void EcatProb::refreshEcatProbelStatus()
{
	if (this->isHidden())
	{
		return;
	}//if
	if (!ui.pushButton_get->isChecked())
	{
		return;
	}//if
	short sRtn = GTN_GetTouchProbeStatus(g_sCurCore,g_sCurAxis,&g_tProbelStatus.uProbelStatus.sProbelStatus,
		&g_tProbelStatus.lProbelRiseValue1,&g_tProbelStatus.lProbelFallValue1,
		&g_tProbelStatus.lProbelRiseValue2,&g_tProbelStatus.lProbelFallValue2);
	this->checkEcatProbelRtnValue("GTN_GetTouchProbeStatus",sRtn);
	this->updateProbelStatusUi();
}