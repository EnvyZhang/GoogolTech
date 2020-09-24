#include "StdAfx.h"
#include "ecatobject.h"

EcatObject::EcatObject(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

EcatObject::~EcatObject()
{

}
//************************************
// Method:    	refreshEcatObjectValue
// Description:	
// Returns:   void
//************************************
void EcatObject::refreshEcatObjectValue()
{
	if (this->isHidden())
	{
		return;
	}//if
	QString qstrValue;
	short sRtn = 0;
	sRtn = GTN_GetEcatAxisPdoData(g_sCurCore,g_sCurAxis,0x6040,(unsigned char *)&g_tObjectValue.sCtrlWord);
	qstrValue = (sRtn==0)?QString("0x%1").arg(g_tObjectValue.sCtrlWord,0,16):"Null";
	ui.label_6040->setText(qstrValue);

	sRtn = GTN_GetEcatAxisPdoData(g_sCurCore,g_sCurAxis,0x6041,(unsigned char *)&g_tObjectValue.sStatusWord);
	qstrValue = (sRtn==0)?QString("0x%1").arg(g_tObjectValue.sStatusWord,0,16):"Null";
	ui.label_6041->setText(qstrValue);

	sRtn = GTN_GetEcatAxisPdoData(g_sCurCore,g_sCurAxis,0x6060,(unsigned char *)&g_tObjectValue.chSetMode);
	qstrValue = (sRtn==0)?QString("%1").arg(g_tObjectValue.chSetMode):"Null";
	ui.label_6060->setText(qstrValue);

	sRtn = GTN_GetEcatAxisPdoData(g_sCurCore,g_sCurAxis,0x6061,(unsigned char *)&g_tObjectValue.chShowMode);
	qstrValue = (sRtn==0)?QString("%1").arg(short(g_tObjectValue.chShowMode)):"Null";
	ui.label_6061->setText(qstrValue);

	sRtn = GTN_GetEcatAxisPdoData(g_sCurCore,g_sCurAxis,0x607a,(unsigned char *)&g_tObjectValue.iTargePos);
	qstrValue = (sRtn==0)?QString("%1").arg(g_tObjectValue.iTargePos):"Null";
	ui.label_607a->setText(qstrValue);

	sRtn = GTN_GetEcatAxisPdoData(g_sCurCore,g_sCurAxis,0x6064,(unsigned char *)&g_tObjectValue.iEncPos);
	qstrValue = (sRtn==0)?QString("%1").arg(g_tObjectValue.iEncPos):"Null";
	ui.label_6064->setText(qstrValue);

	sRtn = GTN_GetEcatAxisPdoData(g_sCurCore,g_sCurAxis,0x60fd,(unsigned char *)&g_tObjectValue.uiDiStatus);
	qstrValue = (sRtn==0)?QString("0x%1").arg(g_tObjectValue.uiDiStatus,0,16):"Null";
	ui.label_60fd->setText(qstrValue);

	sRtn = GTN_GetEcatAxisPdoData(g_sCurCore,g_sCurAxis,0x60fe,(unsigned char *)&g_tObjectValue.uiDoStatus);
	qstrValue = (sRtn==0)?QString("0x%1").arg(g_tObjectValue.uiDoStatus,0,16):"Null";
	ui.label_60fe->setText(qstrValue);

	sRtn = GTN_GetEcatAxisPdoData(g_sCurCore,g_sCurAxis,0x60b8,(unsigned char *)&g_tObjectValue.usProbelPrm);
	qstrValue = (sRtn==0)?QString("0x%1").arg(g_tObjectValue.usProbelPrm,0,16):"Null";
	ui.label_60b8->setText(qstrValue);

	sRtn = GTN_GetEcatAxisPdoData(g_sCurCore,g_sCurAxis,0x60b9,(unsigned char *)&g_tObjectValue.usProbelStatus);
	qstrValue = (sRtn==0)?QString("0x%1").arg(g_tObjectValue.usProbelStatus,0,16):"Null";
	ui.label_60b9->setText(qstrValue);
}