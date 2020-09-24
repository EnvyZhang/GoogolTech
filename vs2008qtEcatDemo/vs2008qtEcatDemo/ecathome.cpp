#include "StdAfx.h"
#include "ecathome.h"

EcatHome::EcatHome(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.comboBox_homeMode->setView(new QListView());
	QStringList qstrList;
	qstrList.clear();
	qstrList.append(tr("1.Method"));
	qstrList.append(tr("2.Method"));
	qstrList.append(tr("3.Method"));
	qstrList.append(tr("4.Method"));
	qstrList.append(tr("5.Method"));
	qstrList.append(tr("6.Method"));
	qstrList.append(tr("7.Method"));
	qstrList.append(tr("8.Method"));
	qstrList.append(tr("9.Method"));
	qstrList.append(tr("10.Method"));
	qstrList.append(tr("11.Method"));
	qstrList.append(tr("12.Method"));
	qstrList.append(tr("13.Method"));
	qstrList.append(tr("14.Method"));
	qstrList.append(tr("15.Method"));
	qstrList.append(tr("16.Method"));
	qstrList.append(tr("17.Method"));
	qstrList.append(tr("18.Method"));
	qstrList.append(tr("19.Method"));
	qstrList.append(tr("20.Method"));
	qstrList.append(tr("21.Method"));
	qstrList.append(tr("22.Method"));
	qstrList.append(tr("23.Method"));
	qstrList.append(tr("24.Method"));
	qstrList.append(tr("25.Method"));
	qstrList.append(tr("26.Method"));
	qstrList.append(tr("27.Method"));
	qstrList.append(tr("28.Method"));
	qstrList.append(tr("29.Method"));
	qstrList.append(tr("30.Method"));
	qstrList.append(tr("31.Method"));
	qstrList.append(tr("32.Method"));
	qstrList.append(tr("33.Method"));
	qstrList.append(tr("34.Method"));
	qstrList.append(tr("35.Method"));
	
	ui.comboBox_homeMode->setStyleSheet("QComboBox QAbstractItemView::item {min-height: 30px;}");
	ui.comboBox_homeMode->clear();
	ui.comboBox_homeMode->addItems(qstrList);
	ui.comboBox_homeMode->setCurrentIndex(0);

	g_tEcatHomePrm.sMethod = 1;

	g_tEcatHomePrm.dSpeed1 = 3000;
	g_tEcatHomePrm.dSpeed2 = 2000;
	g_tEcatHomePrm.dAcc = 10000;
	g_tEcatHomePrm.lOffset = 0;

	QString qstrValue;
	qstrValue = QString("%1").arg(g_tEcatHomePrm.dSpeed1);
	ui.lineEdit_speed1->setText(qstrValue);
	qstrValue = QString("%1").arg(g_tEcatHomePrm.dSpeed2);
	ui.lineEdit_speed2->setText(qstrValue);
	qstrValue = QString("%1").arg(g_tEcatHomePrm.dAcc);
	ui.lineEdit_acc->setText(qstrValue);
	qstrValue = QString("%1").arg(g_tEcatHomePrm.lOffset);
	ui.lineEdit_offset->setText(qstrValue);	

	m_sLastDirection = 1;
}

EcatHome::~EcatHome()
{

}
//************************************
// Method:    	on_comboBox_homeMode_currentIndexChanged
// Description:	
// Parameter: int index
// Returns:   void
//************************************
void EcatHome::on_comboBox_homeMode_currentIndexChanged( int index )
{
	short homeType=index+1;
	switch(homeType)
	{
	case 15:
	case 16:
	case 31:
	case 32:
	case 36:
		ui.label_homePix->setPixmap(QPixmap(":/image/images/xxx.png"));
		break;
	default:
		QString imageHomeMode = QString(":/EcatDemo/Resources/HM_%1").arg(homeType);

		QImage Image;
		Image.load(imageHomeMode);
		QPixmap pixmap = QPixmap::fromImage(Image);
		int with = ui.label_homePix->width();
		int height = ui.label_homePix->height();
		QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
		//QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
		ui.label_homePix->setPixmap(fitpixmap);
		break;
	}
}
//************************************
// Method:    	on_pushButton_homeMode_clicked
// Description:	
// Returns:   void
//************************************
void EcatHome::on_pushButton_homeMode_clicked()
{
	m_sRtn = GTN_SetHomingMode(g_sCurCore,g_sCurAxis,6);
	this->checkEcatHomeRtnValue("GTN_SetHomingMode",m_sRtn);
	Sleep(80);
	m_sRtn = GTN_GetEcatAxisMode(g_sCurCore,g_sCurAxis,(unsigned short*)&g_tAxisStatus.sEcatMode);
	this->checkEcatHomeRtnValue("GTN_GetEcatAxisMode",m_sRtn);
}
//************************************
// Method:    	on_pushButton_cspMode_clicked
// Description:	
// Returns:   void
//************************************
void EcatHome::on_pushButton_cspMode_clicked()
{
	m_sRtn = GTN_SetHomingMode(g_sCurCore,g_sCurAxis,8);
	this->checkEcatHomeRtnValue("GTN_SetHomingMode",m_sRtn);
	Sleep(80);
	m_sRtn = GTN_GetEcatAxisMode(g_sCurCore,g_sCurAxis,(unsigned short*)&g_tAxisStatus.sEcatMode);
	this->checkEcatHomeRtnValue("GTN_GetEcatAxisMode",m_sRtn);
}
//************************************
// Method:    	on_pushButton_startHome_clicked
// Description:	
// Returns:   void
//************************************
void EcatHome::on_pushButton_startHome_clicked()
{
	g_tEcatHomePrm.sMethod = ui.comboBox_homeMode->currentIndex()+1;
	g_tEcatHomePrm.dSpeed1 = ui.lineEdit_speed1->text().toDouble();
	g_tEcatHomePrm.dSpeed2 = ui.lineEdit_speed2->text().toDouble();
	g_tEcatHomePrm.dAcc = ui.lineEdit_acc->text().toDouble();
	g_tEcatHomePrm.lOffset = ui.lineEdit_offset->text().toLong();

	m_sRtn = GTN_SetEcatHomingPrm(g_sCurCore,g_sCurAxis,g_tEcatHomePrm.sMethod,g_tEcatHomePrm.dSpeed1,
		g_tEcatHomePrm.dSpeed2,g_tEcatHomePrm.dAcc,g_tEcatHomePrm.lOffset,g_tEcatHomePrm.probe);
	this->checkEcatHomeRtnValue("GTN_SetEcatHomingPrm",m_sRtn);
	//DWORD dwTime = 200;
	//Sleep(dwTime);
	m_sRtn = GTN_StartEcatHoming(g_sCurCore,g_sCurAxis);
	this->checkEcatHomeRtnValue("GTN_StartEcatHoming",m_sRtn);
}
//************************************
// Method:    	on_pushButton_stopHome_clicked
// Description:	
// Returns:   void
//************************************
void EcatHome::on_pushButton_stopHome_clicked()
{
	m_sRtn = GTN_StopEcatHoming(g_sCurCore,g_sCurAxis);
	this->checkEcatHomeRtnValue("GTN_StopEcatHoming",m_sRtn);
	m_sRtn = GTN_GetEcatAxisMode(g_sCurCore,g_sCurAxis,(unsigned short*)&g_tAxisStatus.sEcatMode);
	this->checkEcatHomeRtnValue("GTN_GetEcatAxisMode",m_sRtn);
}
//************************************
// Method:    	checkRtnValue
// Description:	
// Parameter: QString qstr
// Parameter: short iRtn
// Returns:   void
//************************************
void EcatHome::checkEcatHomeRtnValue( QString qstr, short iRtn )
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
// Method:    	refreshEcatHomeStatus
// Description:	
// Returns:   void
//************************************
void EcatHome::refreshEcatHomeStatus()
{
	if (this->isHidden())
	{
		return;
	}//if
	m_sRtn = GTN_GetEcatHomingStatus(g_sCurCore,g_sCurAxis,&g_tAxisStatus.usHomeStatus);
	//this->checkEcatHomeRtnValue(m_sRtn);
	QString qstr = QString("%1").arg(g_tAxisStatus.usHomeStatus);
	ui.label_homeSts->setText(qstr);
	if (g_tAxisStatus.usHomeStatus==0)
	{
		ui.label_homeSts->setStyleSheet("background-color: rgb(85, 85, 127);color: rgb(255, 255, 255);border:none;");
	}//if
	else if (g_tAxisStatus.usHomeStatus==3)
	{
		ui.label_homeSts->setStyleSheet("background: rgb(0,255,0);color: black;border:none;");
	}//if
	else
	{
		ui.label_homeSts->setStyleSheet("background: rgb(255,0,0);color: black;border:none;");
	}//if..else

	if (g_tAxisStatus.bLmtNDi)
	{
		ui.label_nLmt->setStyleSheet("background: rgb(0,255,0);color: black;border:none;");
	}//if
	else
	{
		ui.label_nLmt->setStyleSheet("background-color: rgb(85, 85, 127);color: rgb(255, 255, 255);border:none;");
	}//if..else
	if (g_tAxisStatus.bLmtPDi)
	{
		ui.label_pLmt->setStyleSheet("background: rgb(0,255,0);color: black;border:none;");
	}//if
	else
	{
		ui.label_pLmt->setStyleSheet("background-color: rgb(85, 85, 127);color: rgb(255, 255, 255);border:none;");
	}//if..else
	if (g_tAxisStatus.bHome)
	{
		ui.label_home->setStyleSheet("background: rgb(0,255,0);color: black;border:none;");
	}//if
	else
	{
		ui.label_home->setStyleSheet("background-color: rgb(85, 85, 127);color: rgb(255, 255, 255);border:none;");
	}//if..else

	if (m_sLastDirection!=g_tAxisStatus.sMovStatus)
	{
		QString qstr;
		if (g_tAxisStatus.sMovStatus==1)
		{
			qstr = ">>>>>>>>>>";
		}//if
		else if (g_tAxisStatus.sMovStatus==-1)
		{
			qstr = "<<<<<<<<<<";
		}//if
		else
		{
			qstr = "";
		}//if..else
		ui.label_dir1->setText(qstr);
		ui.label_dir2->setText(qstr);
		m_sLastDirection = g_tAxisStatus.sMovStatus;
	}//if

	switch (g_tAxisStatus.sEcatMode)
	{
	case 6:
		qstr = "6.Home";		
		break;
	case 8:
		qstr = "8.CSP";		
		break;
	default:
		qstr = "Other";
		break;
	}
	ui.label_ecatMode->setText(qstr);
	if (g_tAxisStatus.bEnable)
	{
		ui.pushButton_servOn->setStyleSheet("background: rgb(0,255,0);color: black;border:none;");
		ui.pushButton_servOn->setText("ServOn");
	}//if
	else
	{
		ui.pushButton_servOn->setStyleSheet("background-color: rgb(85, 85, 127);color: rgb(255, 255, 255);border:none;");
		ui.pushButton_servOn->setText("ServOff");
	}//if..else
}
//************************************
// Method:    	resizeEvent
// Description:	重绘事件主要是图片初始化的时候尺寸不对
// Parameter: QResizeEvent * e
// Returns:   void
//************************************
void EcatHome::resizeEvent( QResizeEvent *e )
{
	short sIndex = ui.comboBox_homeMode->currentIndex();
	on_comboBox_homeMode_currentIndexChanged(sIndex);
}
//************************************
// Method:    	on_pushButton_servOn_clicked
// Description:	
// Returns:   void
//************************************
void EcatHome::on_pushButton_servOn_clicked()
{
	if (g_tAxisStatus.bEnable)
	{
		m_sRtn = GTN_AxisOff(g_sCurCore,g_sCurAxis);
		this->checkEcatHomeRtnValue("GTN_AxisOff",m_sRtn);
	}//if
	else
	{
		m_sRtn = GTN_AxisOn(g_sCurCore,g_sCurAxis);
		this->checkEcatHomeRtnValue("GTN_AxisOn",m_sRtn);
	}//if..else
}