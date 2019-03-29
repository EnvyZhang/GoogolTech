
// SHomeDlg.cpp : 实现文件

#include "stdafx.h"
#include "SHome.h"
#include "SHomeDlg.h"
#include "gts.h"
#pragma comment(lib,"gts.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define AXIS_MAX 8
short rtn;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSHomeDlg 对话框


CSHomeDlg::CSHomeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSHomeDlg::IDD, pParent)
	, m_fJogAcc(0)
	//, m_iSmartHomeMode(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSHomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ALARMFLAG, m_bFlagAlarm);
	DDX_Control(pDX, IDC_BUTTON_POSLIMITFLAG, m_bFlagPosLimit);
	DDX_Control(pDX, IDC_BUTTON_NEGLIMITFLAG, m_bFlagNegLimit);
	DDX_Control(pDX, IDC_BUTTON_SERVOFLAG, m_bFlagServoOn);
	DDX_Text(pDX, IDC_EDIT_JOGVEL, m_fJogVel);
	DDX_Text(pDX, IDC_EDIT_JOGACC, m_fJogAcc);
	DDX_Control(pDX, IDC_CHECK_HCAPTURE, m_CHomeCapture);
	DDX_Control(pDX, IDC_CHECK_ICAPTURE, m_CIndexCapture);
	DDX_Control(pDX, IDC_BUTTON_HCAPTURE, m_bHCapture);
	DDX_Control(pDX, IDC_BUTTON_ICAPTURE, m_bICapture);	
	DDX_Control(pDX, IDC_COMBO_SHMODE, m_iSmartHomeMode);
}

BEGIN_MESSAGE_MAP(CSHomeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_OPEN, &CSHomeDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_RESET, &CSHomeDlg::OnBnClickedReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SmartHome, &CSHomeDlg::OnBnClickedSmarthome)
	ON_BN_CLICKED(IDC_ZeroPos, &CSHomeDlg::OnBnClickedZeropos)
	ON_BN_CLICKED(IDC_BUTTON_CLEARSTS, &CSHomeDlg::OnBnClickedButtonClearsts)
	ON_BN_CLICKED(IDC_NegJog, &CSHomeDlg::OnBnClickedNegjog)
	ON_BN_CLICKED(IDC_PosJog, &CSHomeDlg::OnBnClickedPosjog)
	ON_BN_CLICKED(IDC_STOP, &CSHomeDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_CHECK_HCAPTURE, &CSHomeDlg::OnBnClickedCheckHcapture)
	ON_BN_CLICKED(IDC_CHECK_ICAPTURE, &CSHomeDlg::OnBnClickedCheckIcapture)
END_MESSAGE_MAP()


// CSHomeDlg 消息处理程序

BOOL CSHomeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	//1.初始化界面
	int i;
	CString strTemp;

	GetDlgItem(IDC_BUTTON_HCAPTURE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ICAPTURE)->EnableWindow(FALSE);
	
	//往当前轴下拉列表框中添加轴编号，并设置当前轴为1号轴
	m_iCurrentAxis=1;
	for (i=0;i<AXIS_MAX;i++)
	{
		strTemp.Format("%d",i+1);
		((CComboBox *)GetDlgItem(IDC_COMBO_CURRENTAXIS))->AddString(strTemp);
	}
	((CComboBox *)GetDlgItem(IDC_COMBO_CURRENTAXIS))->SetCurSel(m_iCurrentAxis-1);
	//设置当前回原点模式为20（HOME回原点）
	//UpdateData(TRUE);
	//int nIndex = m_iSmartHomeMode.GetCurSel();				//当前选中的项	
	m_iSmartHomeMode.InsertString(0,_T("Limit"));				//模式10  
	m_iSmartHomeMode.InsertString(1,_T("Limit+Home"));			//模式11 
	m_iSmartHomeMode.InsertString(2,_T("Limit+Index"));  		//模式12 
	m_iSmartHomeMode.InsertString(3,_T("Limit+Home+Index"));	//模式13 
	m_iSmartHomeMode.InsertString(4,_T("Home"));  				//模式20 
	m_iSmartHomeMode.InsertString(5,_T("Home+Index"));			//模式22   
	m_iSmartHomeMode.InsertString(6,_T("Index"));  				//模式30 		
	
	m_iSmartHomeMode.SetCurSel(4);									//默认选择第5项

	//2.打开板卡
	rtn = GT_Open();
	if (rtn != 0)
	{
		CString string;

		string.Format("GT_Open %d",rtn); //将变量组装到字符串中

		MessageBox(string);
	}
	rtn = GT_Reset();
	//3.启动定时器，采集数据
	SetTimer(1,100,NULL);				//创建定时器	
	
	//变量初始化
	m_fJogVel=5;
	m_fJogAcc=0.1;
	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSHomeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSHomeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSHomeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//-----------------------------------------------------菜单响应：板卡复位
void CSHomeDlg::OnBnClickedReset()
{
	rtn = GT_Reset();
	if (rtn != 0)
	{
		CString string;

		string.Format("GT_Reset %d",rtn);

		MessageBox(string);
	}
}

//-----------------------------------------------------按钮消息响应：位置清零
void CSHomeDlg::OnBnClickedZeropos()
{
	rtn = GT_ZeroPos(m_iCurrentAxis);	
	if (rtn != 0)
	{
		CString string;

		string.Format("GT_ZeroPos %d",rtn);

		MessageBox(string);
	}
}

//-----------------------------------------------------按钮消息响应：清除状态
void CSHomeDlg::OnBnClickedButtonClearsts()
{
	// TODO: 在此添加控件通知处理程序代码
	rtn = GT_ClrSts(m_iCurrentAxis);
	if (rtn != 0)
	{
		CString string;

		string.Format("GT_ClrSts %d",rtn);

		MessageBox(string);
	}
}

//-----------------------------------------------------按钮消息响应：紧急停止
void CSHomeDlg::OnBnClickedStop()
{
	rtn = GT_Stop(255,255);
}

//-----------------------------------------------------定时器：采集数据
void CSHomeDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString tempStr;
	double volue;

	short status[2];
	long pos;
	double encPos;
	HBITMAP bitmap[2];
	bitmap[1]=LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_ON));
	bitmap[0]=LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_OFF));

			//获取标志位状态
			long sts;
			rtn = GT_GetSts(m_iCurrentAxis,&sts,1,NULL);
			if (0 == rtn)
			{
				if (sts != m_iAxisStatus)
				{
					m_iAxisStatus = sts;
					UpdateAxisStatus();
				}
			}
			//获取运动状态

			//----------------运动数据的显示---------------------------------------//
			rtn=GT_GetPrfPos(m_iCurrentAxis,&volue,1,NULL);	//Error("GT_GetPrfPos",rtn);
			tempStr.Format(_T("%.1f"),volue);
			SetDlgItemText(IDC_PRFPOS,tempStr);
			
			rtn=GT_GetPrfVel(m_iCurrentAxis,&volue,1,NULL);	//Error("GT_GetPrfVel",rtn);
			tempStr.Format(_T("%.4f"),volue);
			SetDlgItemText(IDC_PRFVEL,tempStr);	
			
			rtn=GT_GetPrfAcc(m_iCurrentAxis,&volue,1,NULL);	//Error("GT_GetPrfAcc",rtn);
			tempStr.Format(_T("%.1f"),volue);
			SetDlgItemText(IDC_ATLACC,tempStr);
			
			rtn=GT_GetEncPos(m_iCurrentAxis,&volue,1,NULL);	//Error("GT_GetEncPos",rtn);
			tempStr.Format(_T("%.1f"),volue);
			SetDlgItemText(IDC_ATLPOS,tempStr);
			
			rtn=GT_GetEncVel(m_iCurrentAxis,&volue,1,NULL);	//Error("GT_GetEncVel",rtn);
			tempStr.Format(_T("%.4f"),volue);
			SetDlgItemText(IDC_ATLVEL,tempStr);

			rtn = GT_GetCaptureStatus(m_iCurrentAxis, &status[0], &pos);	// 查询Home捕获状态
			if(status[0] == 0)
			{
				m_bHCapture.SetBitmap(bitmap[0]);	
			}
			else
			{
				m_bHCapture.SetBitmap(bitmap[1]);
				rtn=GT_GetEncPos(m_iCurrentAxis,&volue,1,NULL);
				tempStr.Format(_T("%.1f"),volue);
				SetDlgItemText(IDC_CAPTUREHOMEPOS,tempStr);
				//GT_Stop(255,255);												//触发Home时运动暂停
			}

			rtn = GT_GetCaptureStatus(m_iCurrentAxis, &status[0], &pos);	// 查询Index捕获状态
			if(status[1] == 0)
			{		
				m_bICapture.SetBitmap(bitmap[1]);		
				rtn=GT_GetEncPos(m_iCurrentAxis,&volue,1,NULL);
				tempStr.Format(_T("%.1f"),volue);
				SetDlgItemText(IDC_CAPTUREINDEXPOS,tempStr);
				//GT_Stop(255,255);											//触发Index时运动暂停
			}
			else
			{
				m_bICapture.SetBitmap(bitmap[0]);
			}
		CDialog::OnTimer(nIDEvent);
}

void CSHomeDlg::UpdateAxisStatus()
{
	HBITMAP bitmap[2];
	bitmap[1]=LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_ON));
	bitmap[0]=LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_OFF));

	CString tempStr;
	//伺服报警
	if (m_iAxisStatus & 0x2)
	{
		m_bFlagAlarm.SetBitmap(bitmap[1]);
	}
	else
	{
		m_bFlagAlarm.SetBitmap(bitmap[0]);
	}
	//正向限位
	if (m_iAxisStatus & 0x20)
	{
		m_bFlagPosLimit.SetBitmap(bitmap[1]);
	}
	else
	{
		m_bFlagPosLimit.SetBitmap(bitmap[0]);
	}
	//负向限位
	if (m_iAxisStatus & 0x40)
	{
		m_bFlagNegLimit.SetBitmap(bitmap[1]);
	}
	else
	{
		m_bFlagNegLimit.SetBitmap(bitmap[0]);
	}	
	//伺服
	if(m_iAxisStatus & 0x200)
	{
		m_bFlagServoOn.SetBitmap(bitmap[1]);
		//tempStr="伺服关闭";
	}
	else
	{
		m_bFlagServoOn.SetBitmap(bitmap[0]);
		//tempStr="伺服使能";	
	}
	//SetDlgItemText(IDC_BUTTON_SERVOON,tempStr);
}
//-----------------------------------------------------菜单响应：加载配置文件并将轴使能
void CSHomeDlg::OnBnClickedOpen()
{
	CString str;
	rtn = GT_LoadConfig("test.cfg");
	if (rtn != 0)
	{
		CString string;

		string.Format("GT_LoadConfig %d",rtn);

		MessageBox(string);
	}
	rtn = GT_ClrSts(m_iCurrentAxis);
	//直接根据按钮的Caption判断
	GetDlgItemText(IDC_OPEN,str);
	if("AxisOn"==str)
	{
		rtn=GT_AxisOn(m_iCurrentAxis);
		if (rtn != 0)
		{
			CString string;

			string.Format("GT_AxisOn %d",rtn);

			MessageBox(string);
		}
		if (rtn)
		{
			return;
		}
		SetDlgItemText(IDC_OPEN,"AxisOff");			//伺服使能，成功则修改按钮的Caption
	}
	else
	{
		rtn=GT_AxisOff(m_iCurrentAxis);				//Error(rtn,"GT_AxisOff");
		if (rtn)
		{
			return;
		}
		SetDlgItemText(IDC_OPEN,"AxisOn");
	}
}

//-----------------------------------------------------菜单响应：智能回零
void CSHomeDlg::OnBnClickedSmarthome()
{
	//short a = 20;
	//short a = m_iSmartHomeMode;
	UpdateData(TRUE);
	int GoHomeMode = m_iSmartHomeMode.GetCurSel();						//当前选中的项		
	switch(GoHomeMode)
	{
	case 0:
		mMode = 10;													//参数传递
		break;
	case 1:
		mMode = 11;
		break;
	case 2:
		mMode = 12;
		break;
	case 3:
		mMode = 13;
		break;
	case 4:
		mMode = 20;
		break;
	case 5:
		mMode = 22;
		break;
	case 6:
		mMode = 30;
		break;
	}
	SmartHome();
}


//-----------------------------------------------------按钮消息响应：开始正方向Jog运动
void CSHomeDlg::OnBnClickedPosjog()
{

}


//-----------------------------------------------------按钮消息响应：开始负方向Jog运动
void CSHomeDlg::OnBnClickedNegjog()
{

}


//-----------------------------------------------------按钮消息响应：实现Jog点动
BOOL CSHomeDlg::PreTranslateMessage(MSG* pMsg)
{	
	// 正方向Jog运动									//在消息传递的过程中，捕获父窗口消息预处理时按钮的按下和抬起
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_PosJog)->m_hWnd)
		{
			
			if (0 == UpdateData())						//1.调用系统的检验函数对输入参数格式进行判断
			{
				return 0;
			}

			if(m_fJogVel<=0 || m_fJogAcc<=0)			//2.对输入参数范围进行判断
			{
				MessageBox("参数范围不正确，加速度取值范围为大于零");
				return 0;
			}
			TJogPrm jog;
			rtn = GT_PrfJog(m_iCurrentAxis);
			rtn = GT_GetJogPrm(m_iCurrentAxis, &jog);	// 读取 Jog 运动参数(需要读取全部运动参数到上位机变量)
			jog.acc = m_fJogAcc;						//设置需要修改的运动参数
			jog.dec = m_fJogAcc;
			jog.smooth=0;
			rtn = GT_SetJogPrm(m_iCurrentAxis, &jog);	// 设置 Jog 运动参数
			rtn = GT_SetVel(m_iCurrentAxis, m_fJogVel);	// 设置 m_iCurrentAxis 轴的目标速度
			rtn = GT_Update(1<<(m_iCurrentAxis-1));		// 启动 m_iCurrentAxis 轴的运动
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_PosJog)->m_hWnd)
		{
			rtn = GT_Stop(255,255);
		}
	}

 	// 负方向Jog运动
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_NegJog)->m_hWnd)
		{

			if (0 == UpdateData())						//1.调用系统的检验函数对输入参数格式进行判断
			{
				return 0;
			}

			if(m_fJogVel<=0 || m_fJogAcc<=0)			//2.对输入参数范围进行判断
			{
				MessageBox("参数范围不正确，加速度取值范围为大于零");
				return 0;
			}
			TJogPrm jog;
			rtn = GT_PrfJog(m_iCurrentAxis);
			rtn = GT_GetJogPrm(m_iCurrentAxis, &jog);	// 读取 Jog 运动参数(需要读取全部运动参数到上位机变量)
			jog.acc = m_fJogAcc;						//设置需要修改的运动参数
			jog.dec = m_fJogAcc;
			jog.smooth=0;
			rtn = GT_SetJogPrm(m_iCurrentAxis, &jog);	// 设置 Jog 运动参数
			rtn = GT_SetVel(m_iCurrentAxis, -m_fJogVel);	// 设置 m_iCurrentAxis 轴的目标速度
			rtn = GT_Update(1<<(m_iCurrentAxis-1));		// 启动 m_iCurrentAxis 轴的运动
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_NegJog)->m_hWnd)
		{
			rtn = GT_Stop(255,255);
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

//-----------------------------------------------------复选框消息响应：Home捕获
void CSHomeDlg::OnBnClickedCheckHcapture()
{
	if (m_CHomeCapture.GetCheck() == 1)
	{
		GetDlgItem(IDC_BUTTON_HCAPTURE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_HCAPTURE)->EnableWindow(FALSE);
	}
	rtn = GT_SetCaptureMode(m_iCurrentAxis,CAPTURE_HOME);
}
//-----------------------------------------------------复选框消息响应：Index捕获
void CSHomeDlg::OnBnClickedCheckIcapture()
{
	if (m_CIndexCapture.GetCheck() == 1)
	{
		GetDlgItem(IDC_BUTTON_ICAPTURE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_ICAPTURE)->EnableWindow(FALSE);
	}
	rtn = GT_SetCaptureMode(m_iCurrentAxis,CAPTURE_INDEX);
}
/************************************************************Zhang.jw************************************************************/

//void CSHomeDlg::CaptureHome()
//{
//	short status;
//	long pos;
//	double encPos;
//	CString tempStr;
//	HBITMAP bitmap[2];
//	bitmap[1]=LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_ON));
//	bitmap[0]=LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_OFF));
//	((CButton*)GetDlgItem(IDC_CHECK_HCAPTURE))->GetCheck();
//	if (m_CHomeCapture.GetCheck() == TRUE)
//	{
//		rtn = GT_SetCaptureMode(m_iCurrentAxis, CAPTURE_HOME);		// 启动Home捕获		//ERROR("GT_SetCaptureMode", rtn);
//		do
//		{
//			rtn = GT_GetCaptureStatus(m_iCurrentAxis, &status, &pos);	// 查询捕获状态
//			if(status == 0)
//			{
//				m_bHCapture.SetBitmap(bitmap[0]);
//			}
//			else
//			{
//				m_bHCapture.SetBitmap(bitmap[1]);
//			}
//			rtn = GT_GetEncPos(m_iCurrentAxis, &encPos);
//			tempStr.Format(_T("%.1f"),pos);
//			SetDlgItemText(IDC_HCapturePos,tempStr);
//		}while( 0 == status );
//	}
//}

//-----------------------------------------------------功能实现：智能回零
void CSHomeDlg::SmartHome()
{
	rtn = GT_ClrSts(m_iCurrentAxis);	//无清除状态会导致回零失败
	THomePrm tHomePrm;					//设置 Smart Home 回原点参数
	rtn = GT_GetHomePrm(m_iCurrentAxis,&tHomePrm);
	tHomePrm.mode = mMode;
	tHomePrm.moveDir = 1;
	tHomePrm.indexDir = 1;
	tHomePrm.edge = 0;
	tHomePrm.velHigh = 5;
	tHomePrm.velLow = 1;
	tHomePrm.acc = 0.1;
	tHomePrm.dec = 0.1;
	tHomePrm.searchHomeDistance = 200000;
	tHomePrm.searchIndexDistance = 30000;
	tHomePrm.escapeStep = 1000;
	rtn = GT_GoHome(m_iCurrentAxis,&tHomePrm);	 //启动 Smart Home 回原
	if (rtn != 0)
	{
		CString string;

		string.Format("GT_GoHome %d",rtn);

		MessageBox(string);
	}
}