#include "stdafx.h"
#include "ecatdemo.h"

EcatDemo::EcatDemo(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	m_bIgnore = true;
	ui.comboBox_axis->setView(new QListView());
	ui.comboBox_core->setView(new QListView());
	m_sRtn = this->initMotionCard();
	this->checkRtnValue("",m_sRtn);
	initUi();
	m_bIgnore = false;
	m_pqEcatHome = new EcatHome;
	m_pqEcatProb = new EcatProb;
	m_pqEcatObject = new EcatObject;
	m_pqTimer = new QTimer;
	m_pqTimer->setInterval(100);
	connect(m_pqTimer,SIGNAL(timeout()),this,SLOT(refreshStatusInfoSlot()));
	if (m_sRtn==0)
	{
		m_pqTimer->start();
	}//if

}

EcatDemo::~EcatDemo()
{
}
//************************************
// Method:    	initUi
// Description:	
// Returns:   void
//************************************
void EcatDemo::initUi()
{
	g_sCurCore = 1;
	g_sCurAxis = 1;
	QStringList qstrList;
	qstrList.clear();
	for (short i=0;i<g_tResInfo.sCoreCnt;i++)
	{
		QString qstr = QString("%1").arg(i+1);
		qstrList.append(qstr);
	}//for
	//ui.comboBox_core->clear();
	ui.comboBox_core->addItems(qstrList);
	ui.comboBox_core->setCurrentIndex(0);
	
	qstrList.clear();
	for (short i=0;i<g_tResInfo.sCoreAxisResCnt;i++)
	{
		QString qstr = QString("%1").arg(i+1);
		qstrList.append(qstr);
	}//for
	//ui.comboBox_axis->clear();
	ui.comboBox_axis->addItems(qstrList);
	ui.comboBox_axis->setCurrentIndex(0);
	
}

//************************************
// Method:    	initMotionCard
// Description:	
// Returns:   short
//************************************
short EcatDemo::initMotionCard()
{
	//开卡
	m_sRtn = GTN_Open(5);
	if (m_sRtn!=CMD_SUCCESS)
	{
		return m_sRtn;
	}//if
	//获取资源数
	short sAxisResCntCore1 = 0;
	short sAxisResCntCore2 = 0;
	short sRtn1;
	short sRtn2;
	sRtn1 = GTN_GetResCount(1,MC_AXIS,&sAxisResCntCore1);
	sRtn2 = GTN_GetResCount(2,MC_AXIS,&sAxisResCntCore2);
	if (sRtn1==CMD_SUCCESS || sRtn2==CMD_SUCCESS)
	{
		g_tResInfo.sCoreAxisResCnt = sAxisResCntCore1;

		g_tResInfo.sCoreCnt = 2;
		if (sAxisResCntCore2==0 || sRtn2!=CMD_SUCCESS)
		{
			g_tResInfo.sCoreCnt--;
		}//if
		if (sAxisResCntCore1==0 || sRtn1!=CMD_SUCCESS)
		{
			g_tResInfo.sCoreCnt--;
		}//if
	}//if


	//复位卡
	for (short i=0;i<g_tResInfo.sCoreCnt;i++)
	{
		m_sRtn += GTN_Reset(i+1);
		if (m_sRtn!=CMD_SUCCESS)
		{
			return m_sRtn;
		}//if
	}//for
	//Ecat初始化
	for (short i=0;i<g_tResInfo.sCoreCnt;i++)
	{
		m_sRtn += GTN_TerminateEcatComm(i+1);
		if (m_sRtn!=CMD_SUCCESS)
		{
			return m_sRtn;
		}//if
	}//for
	m_sRtn = GTN_InitEcatComm(1);
	if(CMD_SUCCESS!=m_sRtn)
	{
		return m_sRtn;
	}
	short sStatus;
	short sCnt =0;
	do 
	{
		m_sRtn += GTN_IsEcatReady(1,&sStatus);
		Sleep(500);
		sCnt++;
	} while(((1 != sStatus)||(0 != m_sRtn))&&(sCnt <100));

	if(sCnt >=90)
	{
		return -1000;
	}

	m_sRtn = GTN_StartEcatComm(1);
	if(CMD_SUCCESS!=m_sRtn)
	{
		return -999;
	}
	GTN_ClrSts(1,1,g_tResInfo.sCoreAxisResCnt);
	GTN_ClrSts(2,1,g_tResInfo.sCoreAxisResCnt);
	return m_sRtn;
}
//************************************
// Method:    	setButtonBackground
// Description:	设置PushButton显示文字和显示颜色，0，灰色默认，1绿色，2红色
// Parameter: QPushButton * qButton
// Parameter: QString qstrText
// Parameter: short sColor
// Returns:   void
//************************************
void EcatDemo::setButtonProperity( QPushButton *qButton,QString qstrText,short sColor/*=-1*/ )
{
	qButton->setText(qstrText);
	//绿色
	if (Cnst_Green==sColor)
	{
		qButton->setStyleSheet("background: rgb(0,255,0);color: black;border:none;");
	}//if 红色
	else if (Cnst_Red==sColor)
	{
		qButton->setStyleSheet("background: rgb(255,0,0);color: black;border:none;");
	}//if
	else if (Cnst_Grey==sColor)
	{
		qButton->setStyleSheet("background: rgb(240,240,240);color: black;border:none;");
	}//if
	else
	{
		
	}//if..else
}
//************************************
// Method:    	setLabelBackground
// Description:	
// Parameter: QLabel * qLabelt
// Parameter: QString qstrText
// Parameter: short sColor
// Returns:   void
//************************************
void EcatDemo::setLabelProperity( QLabel *qLabel,QString qstrText,short sColor/*=-1*/ )
{
	if (!qstrText.isEmpty())
	{
		qLabel->setText(qstrText);
	}//if
	//绿色
	if (Cnst_Green==sColor)
	{
		qLabel->setStyleSheet("background: rgb(0,255,0);color: black;border:none;");
	}//if 红色
	else if (Cnst_Red==sColor)
	{
		qLabel->setStyleSheet("background: rgb(255,0,0);color: black;border:none;");
	}//if
	else if (Cnst_Grey==sColor)
	{
		//background: rgb(240,240,240);color: black;border:5;
		qLabel->setStyleSheet("background-color: rgb(85, 85, 127);color: rgb(255, 255, 255);border:none;");
	}//if
	else
	{		
	}//if..else	
}
//************************************
// Method:    	appendRtnTextEdit
// Description:	
// Parameter: short iRtn
// Returns:   void
//************************************
void EcatDemo::checkRtnValue( QString qstr, short iRtn )
{
	if (iRtn!=0)
	{
		setButtonProperity(ui.pushButton_alarm,"Alarm",Cnst_Red);
		if (!qstr.isEmpty() && !m_bIgnore)
		{
			QString qstrText = QString("%1=%2").arg(iRtn).arg(qstr);
			if (QMessageBox::Ignore ==  QMessageBox::warning(this,"Warnning",qstrText,QMessageBox::Ignore | QMessageBox::Ok))
			{
				m_bIgnore = true;
			}//if
		}//if
	}//if
}
//************************************
// Method:    	on_comboBox_core_currentIndexChanged
// Description:	
// Parameter: int index
// Returns:   void
//************************************
void EcatDemo::on_comboBox_core_currentIndexChanged( int index )
{
	g_sCurCore = index+1;
	m_sRtn = GTN_GetEcatAxisMode(g_sCurCore,g_sCurAxis,(unsigned short*)&g_tAxisStatus.sEcatMode);
	this->checkRtnValue("GTN_GetEcatAxisMode",m_sRtn);
}
//************************************
// Method:    	on_comboBox_axis_currentIndexChanged
// Description:	
// Parameter: int index
// Returns:   void
//************************************
void EcatDemo::on_comboBox_axis_currentIndexChanged( int index )
{
	g_sCurAxis = index+1;
	m_sRtn = GTN_GetEcatAxisMode(g_sCurCore,g_sCurAxis,(unsigned short*)&g_tAxisStatus.sEcatMode);
	this->checkRtnValue("GTN_GetEcatAxisMode",m_sRtn);
}
//************************************
// Method:    	on_pushButton_clr_clicked
// Description:	
// Returns:   void
//************************************
void EcatDemo::on_pushButton_clr_clicked()
{
	m_sRtn = GTN_ClrSts(g_sCurCore,g_sCurAxis);
		this->checkRtnValue("GTN_GetEcatAxisMode",m_sRtn);
}

//************************************
// Method:    	on_pushButton_serv_clicked
// Description:	
// Returns:   void
//************************************
void EcatDemo::on_pushButton_serv_clicked()
{
	if (g_tAxisStatus.bEnable)
	{
		m_sRtn = GTN_AxisOff(g_sCurCore,g_sCurAxis);
		this->checkRtnValue("GTN_AxisOff",m_sRtn);
	}//if
	else
	{
		m_sRtn = GTN_AxisOn(g_sCurCore,g_sCurAxis);
		this->checkRtnValue("GTN_AxisOn",m_sRtn);
	}//if..else
	
}
//************************************
// Method:    	on_pushButton_zero_clicked
// Description:	
// Returns:   void
//************************************
void EcatDemo::on_pushButton_zero_clicked()
{
	m_sRtn = GTN_ZeroPos(g_sCurCore,g_sCurAxis);
	this->checkRtnValue("GTN_ZeroPos",m_sRtn);
}
//************************************
// Method:    	on_pushButton_stop_clicked
// Description:	
// Returns:   void
//************************************
void EcatDemo::on_pushButton_stop_clicked()
{
	long mask = 0x1<<(g_sCurAxis-1);
	m_sRtn = GTN_Stop(g_sCurCore,mask,0);
	this->checkRtnValue("GTN_Stop",m_sRtn);
}
//************************************
// Method:    	on_pushButton_jogN_clicked
// Description:	
// Returns:   void
//************************************
void EcatDemo::on_pushButton_jogN_clicked()
{
	TMoveVelocityPrm tMoveVelPrm;
	tMoveVelPrm.vel = 10;
	tMoveVelPrm.acc = 1;
	tMoveVelPrm.dec = 1;
	tMoveVelPrm.jerkBegin = 1;
	tMoveVelPrm.jerkEnd = 1;
	tMoveVelPrm.direction = 1;
	m_sRtn = GTN_MoveVelocity(g_sCurCore,g_sCurAxis,&tMoveVelPrm);
	this->checkRtnValue("GTN_MoveVelocity",m_sRtn);
}
//************************************
// Method:    	on_pushButton_jogP_clicked
// Description:	
// Returns:   void
//************************************
void EcatDemo::on_pushButton_jogP_clicked()
{
	TMoveVelocityPrm tMoveVelPrm;
	tMoveVelPrm.vel = 10;
	tMoveVelPrm.acc = 1;
	tMoveVelPrm.dec = 1;
	tMoveVelPrm.jerkBegin = 1;
	tMoveVelPrm.jerkEnd = 1;
	tMoveVelPrm.direction = 0;
	m_sRtn = GTN_MoveVelocity(g_sCurCore,g_sCurAxis,&tMoveVelPrm);
	this->checkRtnValue("GTN_MoveVelocity",m_sRtn);
}
//************************************
// Method:    	on_pushButton_home_clicked
// Description:	
// Returns:   void
//************************************
void EcatDemo::on_pushButton_home_clicked()
{
	if (m_pqEcatHome->isHidden())
	{
		m_pqEcatHome->show();
	}//if
	else
	{
		m_pqEcatHome->hide();
	}//if..else
}
//************************************
// Method:    	on_pushButton_prob_clicked
// Description:	
// Returns:   void
//************************************
void EcatDemo::on_pushButton_prob_clicked()
{
	if (m_pqEcatProb->isHidden())
	{
		m_pqEcatProb->show();
	}//if
	else
	{
		m_pqEcatProb->hide();
	}//if..else
}
//************************************
// Method:    	on_pushButton_alarm_clicked
// Description:	
// Returns:   void
//************************************
void EcatDemo::on_pushButton_alarm_clicked()
{
	this->setButtonProperity(ui.pushButton_alarm,"Norm",Cnst_Green);
	m_bIgnore = false;
}
//************************************
// Method:    	refreshStatusInfoSlot
// Description:	
// Returns:   void
//************************************
void EcatDemo::refreshStatusInfoSlot()
{
	long lAxisSts;
	long lValue;
	double dPrfPos;
	double dEncPos;

	m_sRtn = GTN_GetSts(g_sCurCore,g_sCurAxis,&lAxisSts);
	this->checkRtnValue("GTN_GetSts",m_sRtn);

	m_sRtn = GTN_GetPrfPos(g_sCurCore,g_sCurAxis,&dPrfPos);
	this->checkRtnValue("GTN_GetPrfPos",m_sRtn);
	m_sRtn = GTN_GetEncPos(g_sCurCore,g_sCurAxis,&dEncPos);
	this->checkRtnValue("GTN_GetEncPos",m_sRtn);
	// 没有配置轴模式的pdo，不能一直刷新，走sdo，指令耗时在150左右，导致程序很卡
// 	DWORD dwValue = GetTickCount();
// 	m_sRtn = GTN_GetEcatAxisMode(g_sCurCore,g_sCurAxis,(unsigned short*)&g_tAxisStatus.sEcatMode);
// 	DWORD dwInternal = GetTickCount()-dwValue;
// 	qDebug()<<dwInternal;
	g_tAxisStatus.lLastEcatPos = g_tAxisStatus.lEcatPos;
	m_sRtn = GTN_GetEcatEncPos(g_sCurCore,g_sCurAxis,&g_tAxisStatus.lEcatPos);
	this->checkRtnValue("GTN_GetEcatEncPos",m_sRtn);

	m_sRtn = GTN_GetEcatAxisPdoData(g_sCurCore,g_sCurAxis,0x6041,(unsigned char *)&g_tAxisStatus.usStatusWord);
	this->checkRtnValue("GTN_GetEcatAxisPdoData",m_sRtn);
// 	DWORD dwValue = GetTickCount();
// 	m_sRtn = GTN_GetEcatEncVel(g_sCurCore,g_sCurAxis,&g_tAxisStatus.lEcatVel);
// 	DWORD dwInternal = GetTickCount()-dwValue;
// 	qDebug()<<dwInternal;
	long lEcatAxisDI;
	m_sRtn = GTN_GetEcatAxisDI(g_sCurCore,g_sCurAxis,(unsigned long*)&lEcatAxisDI);
	this->checkRtnValue("GTN_GetEcatAxisDI",m_sRtn);
	g_tAxisStatus.bAlarm = lAxisSts & (1<<1);
	g_tAxisStatus.bEnable = lAxisSts & (1<<9);
	g_tAxisStatus.bMtn = lAxisSts & (1<<10);
	g_tAxisStatus.bLmtP = lAxisSts & (1<<5);
	g_tAxisStatus.bLmtN = lAxisSts & (1<<6);
	g_tAxisStatus.fEncPos = dEncPos;
	g_tAxisStatus.fPrfPos = dPrfPos;
	g_tAxisStatus.bHome = (lEcatAxisDI>>2) & 0x1;
	g_tAxisStatus.bLmtNDi = (lEcatAxisDI>>0) & 0x1;
	g_tAxisStatus.bLmtPDi = (lEcatAxisDI>>1) & 0x1;
	
	long lDeta = g_tAxisStatus.lEcatPos-g_tAxisStatus.lLastEcatPos;
	if (abs(lDeta)>5)
	{
		g_tAxisStatus.sMovStatus = (lDeta>0)?1:-1;
	}//if
	else
	{
		g_tAxisStatus.sMovStatus = 0;
	}//if..else
	QString qstr;
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
	setLabelProperity(ui.label_ecatMode,qstr);
	qstr = QString("%1").arg(g_tAxisStatus.lEcatPos);
	setLabelProperity(ui.label_ecatPos,qstr);
	qstr = QString("%1").arg(g_tAxisStatus.fEncPos);
	setLabelProperity(ui.label_encPos,qstr);
	qstr = QString("%1").arg(g_tAxisStatus.fPrfPos);
	setLabelProperity(ui.label_prfPos,qstr);
	qstr = QString("0x%1").arg(g_tAxisStatus.usStatusWord,4,16);
	setLabelProperity(ui.label_statusWord,qstr);
	qstr.clear();
	setLabelProperity(ui.label_alrm,qstr,g_tAxisStatus.bAlarm?Cnst_Red:Cnst_Grey);
	setLabelProperity(ui.label_SrvSts,qstr,g_tAxisStatus.bEnable?Cnst_Green:Cnst_Grey);
	setLabelProperity(ui.label_prfRun,qstr,g_tAxisStatus.bMtn?Cnst_Green:Cnst_Grey);

	setLabelProperity(ui.label_nLmt,qstr,g_tAxisStatus.bLmtN?Cnst_Green:Cnst_Grey);
	setLabelProperity(ui.label_PLmt,qstr,g_tAxisStatus.bLmtP?Cnst_Green:Cnst_Grey);
	setLabelProperity(ui.label_Home,qstr,g_tAxisStatus.bHome?Cnst_Green:Cnst_Grey);

	setLabelProperity(ui.label_nMove,qstr,(g_tAxisStatus.sMovStatus==-1)?Cnst_Green:Cnst_Grey);
	setLabelProperity(ui.label_stop,qstr,(g_tAxisStatus.sMovStatus==0)?Cnst_Green:Cnst_Grey);
	setLabelProperity(ui.label_fMove,qstr,(g_tAxisStatus.sMovStatus==1)?Cnst_Green:Cnst_Grey);

	qstr = g_tAxisStatus.bEnable?"ServOff":"ServOn";
	setButtonProperity(ui.pushButton_serv,qstr);


	m_pqEcatHome->refreshEcatHomeStatus();
	m_pqEcatProb->refreshEcatProbelStatus();
	m_pqEcatObject->refreshEcatObjectValue();
}
//************************************
// Method:    	on_pushButton_object_clicked
// Description:	
// Returns:   void
//************************************
void EcatDemo::on_pushButton_object_clicked()
{
	if (m_pqEcatObject->isHidden())
	{
		m_pqEcatObject->show();
	}//if
	else
	{
		m_pqEcatObject->hide();
	}//if..else
}