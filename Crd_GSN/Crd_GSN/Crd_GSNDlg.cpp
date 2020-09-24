
// Crd_GSNDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Crd_GSN.h"
#include "Crd_GSNDlg.h"
#include "afxdialogex.h"
#include "gts.h"
#include "LookAheadEx.h"

#pragma comment(lib,"gts.lib")

#define AXIS_MAX 8

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool aHead, newAhead, oldAhead, watchOn,axisFlag = false;
CString axisOff = (_T("使能关闭"));
CString axisOn = (_T("使能开启"));
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCrd_GSNDlg dialog



CCrd_GSNDlg::CCrd_GSNDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCrd_GSNDlg::IDD, pParent)
	, m_iCurrentAxis(0)
	, m_iOffset(0)
	, m_iSize(1)
	, m_di(1)
	, m_type(0)
	, m_index(0)
	, m_bit(0)
	, m_offset(2)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCrd_GSNDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_WATCH, m_CWatch);
	DDX_Control(pDX, IDC_CHECK_POSCOMPARE, m_CPosCompare);
	DDX_Control(pDX, IDC_radOldAhead, m_COldahead);
	DDX_Control(pDX, IDC_radNewahead, m_CNewahead);
	DDX_Control(pDX, IDC_BUTTON_CRDSTART, m_CNewahead);
	DDX_Text(pDX, IDC_EDIT_OFFSET, m_iOffset);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_iSize);

	DDX_Text(pDX, IDC_EDIT_DI, m_di);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_type);
	DDX_Text(pDX, IDC_EDIT_INDEX, m_index);
	DDX_Text(pDX, IDC_EDIT_BIT, m_bit);
	DDX_Text(pDX, IDC_EDIT_PDOOFFSET, m_offset);
}

BEGIN_MESSAGE_MAP(CCrd_GSNDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INITIAL, &CCrd_GSNDlg::OnBnClickedButtonInitial)
	ON_BN_CLICKED(IDC_BUTTON_INITIAL_COORDINATE, &CCrd_GSNDlg::OnBnClickedButtonInitialCoordinate)
	ON_BN_CLICKED(IDC_BUTTON_CRDSTART, &CCrd_GSNDlg::OnBnClickedButtonCrdstart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_POSCOMPARE, &CCrd_GSNDlg::OnBnClickedCheckPoscompare)
	ON_BN_CLICKED(IDC_CHECK_WATCH, &CCrd_GSNDlg::OnBnClickedCheckWatch)
	ON_BN_CLICKED(IDC_radNewahead, &CCrd_GSNDlg::OnBnClickedradnewahead)
	ON_BN_CLICKED(IDC_radOldAhead, &CCrd_GSNDlg::OnBnClickedradoldahead)
	ON_BN_CLICKED(IDC_BUTTON_AXISENBALE, &CCrd_GSNDlg::OnBnClickedButtonAxisenbale)
	ON_BN_CLICKED(IDC_CHECK_FIFOCOMPARE, &CCrd_GSNDlg::OnBnClickedCheckFifocompare)
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDC_BUTTON1, &CCrd_GSNDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCrd_GSNDlg message handlers

BOOL CCrd_GSNDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CString strTemp;
	//往当前轴下拉列表框中添加轴编号，并设置当前轴为1号轴
	m_iCurrentAxis = 1;
	for (int i = 0;i < AXIS_MAX; i++)
	{
		strTemp.Format(L"%d", i + 1);
		((CComboBox *)GetDlgItem(IDC_COMBO_CURRENTAXIS))->AddString(strTemp);
	}
	((CComboBox *)GetDlgItem(IDC_COMBO_CURRENTAXIS))->SetCurSel(m_iCurrentAxis - 1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCrd_GSNDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCrd_GSNDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCrd_GSNDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCrd_GSNDlg::OnBnClickedButtonInitial()
{
	short rtn;
	short sEcatSts;

	SetTimer(1, 10, NULL);
	rtn = GTN_Open();								// 打开运动控制器													
	rtn = GTN_InitEcatComm(1);						// 初始化EtherCAT通讯配置
	do {
 		rtn = GTN_IsEcatReady(1, &sEcatSts);		// 查询EtherCAT通讯是否准备好了
	} while (sEcatSts != 1 || rtn != 0);			// 开始EtherCAT通讯
	rtn += GTN_StartEcatComm(1);
	rtn += GTN_Reset(1);                            // 复位运动控制器
	//rtn += GTN_LoadConfig(1, "test.cfg");           // 下载控制器配置文件
	rtn += GTN_AlarmOff(1, 1);
	rtn += GTN_LmtsOff(1, 1, -1);
	rtn += GTN_ClrSts(1, 1, 4);                     // 清除1~4轴的轴状态
	if (rtn != 0){ MessageBox(_T("初始化失败！")); }

	aHead = false;
	newAhead = false;
	oldAhead = false;
	watchOn = false; 
	axisFlag = false; //初始化操作
	SetDlgItemText(IDC_BUTTON_AXISENBALE, axisOn);
	/*m_CFifoCompare.SetCheck(false);
	m_CPosCompare.SetCheck(false);*/
	m_COldahead.SetCheck(false);
	m_CNewahead.SetCheck(false);
	m_CWatch.SetCheck(false);
}

void CCrd_GSNDlg::OnBnClickedButtonAxisenbale()
{
	short rtn;

	if (axisFlag == false)
	{
		for (int i = 1; i <= 4; ++i){ rtn = GTN_AxisOn(1, i); }  // 打开使能
		if (rtn == 0)
		{
			SetDlgItemText(IDC_BUTTON_AXISENBALE, axisOff);
			axisFlag = !axisFlag;
		}
		else{ MessageBox(_T("使能开启失败")); }
		
	}
	else if (axisFlag == true)
	{
		for (int i = 1; i <= 4; ++i){ rtn = GTN_AxisOff(1, i); }  // 关闭使能
		if(rtn == 0)
		{
			SetDlgItemText(IDC_BUTTON_AXISENBALE, axisOn);
			axisFlag = !axisFlag;
		}
		else{ MessageBox(_T("使能关闭失败")); }
	}
}

void CCrd_GSNDlg::OnBnClickedButtonInitialCoordinate()
{
	short rtn;
	TCrdPrm crdPrm;

	memset(&crdPrm, 0, sizeof(crdPrm));
	crdPrm.dimension = 3;                        // 建立三维的坐标系
	crdPrm.synVelMax = 500;                      // 坐标系的最大合成速度是: 500 pulse/ms
	crdPrm.synAccMax = 2;                        // 坐标系的最大合成加速度是: 2 pulse/ms^2
	crdPrm.evenTime = 0;                         // 坐标系的最小匀速时间为0
	crdPrm.profile[0] = 1;                       // 规划器1对应到X轴                       
	crdPrm.profile[1] = 2;                       // 规划器2对应到Y轴
	crdPrm.profile[2] = 3;
	crdPrm.profile[3] = 0;
	crdPrm.profile[4] = 0;
	crdPrm.profile[5] = 0;
	crdPrm.profile[6] = 0;
	crdPrm.profile[7] = 0;
	crdPrm.setOriginFlag = 1;                    // 需要设置加工坐标系原点位置
	crdPrm.originPos[0] = 0;                     // 加工坐标系原点位置在(0,0)，即与机床坐标系原点重合
	crdPrm.originPos[1] = 0;
	crdPrm.originPos[2] = 0;
	crdPrm.originPos[3] = 0;
	crdPrm.originPos[4] = 0;
	crdPrm.originPos[5] = 0;
	crdPrm.originPos[6] = 0;
	crdPrm.originPos[7] = 0;

	rtn = GTN_SetCrdPrm(1, 1, &crdPrm);
	rtn = GTN_CrdClear(1, 1, 0);
	if (rtn != 0){ MessageBox(_T("建立坐标系失败！")); }

	aHead = false;
	newAhead = false;
	oldAhead = false;
}

void CCrd_GSNDlg::OnBnClickedradoldahead()
{
	short rtn;
	CString strMsg;
	if (m_COldahead.GetCheck()) //当单选框选中
	{
		if (oldAhead == false)  //判断状态，保证只建立一次前瞻
		{
			TCrdData crdData[200];// 定义前瞻缓存区内存区
			rtn = GTN_InitLookAhead(1, 1, 0, 5, 1, 200, crdData);// 初始化坐标系1的FIFO0的前瞻模块
			if (rtn == 0)
			{
				aHead = false;
				oldAhead = true;//指令执行成功，标志位置起
			}
			else
			{
				strMsg.Format(_T("%d"), rtn);
				MessageBox(_T("前瞻初始化错误：") + strMsg);
				m_COldahead.SetCheck(false);
			}
		}
	}
	else if (m_COldahead.GetCheck() == false && oldAhead == false)
	{
		MessageBox(_T("前瞻已建立"));
	}
}

void CCrd_GSNDlg::OnBnClickedradnewahead()
{
	short rtn;
	short core = 1;
	short crd = 1;
	short fifo = 0;
	int lookAheadNum = 200;
	CString strMsg;
	//*****************************************************新前瞻标准使用方法*************************************************************
	//初始化多轴前瞻模块
	if (m_CNewahead.GetCheck())
	{
		if (newAhead == false)
		{
			EMachineMode machineMode;  //机床类型
			EVelSettingDef velDefineMode; //速度定义模式
			int axisLimitMode[8]; //轴限制模式
			EWorkLimitMode workLimitMode;  //工件坐标系限制模式
			int axisFollowMode[8]; //轴跟随模式
			TLookAheadParameter lookAheadPara;  //前瞻参数

			machineMode = NORMAL_THREE_AXIS; //标准三轴机床
			velDefineMode = NORMAL_DEF_VEL; //输入速度为三轴合成速度
			workLimitMode = WORK_LIMIT_VALID; //工件坐标系限制生效
			for (int i = 0; i < 8; ++i)
			{
				axisLimitMode[i] = AXIS_LIMIT_NONE; //轴限制不生效
				axisFollowMode[i] = 0; //非跟随轴
			}

			lookAheadPara.lookAheadNum = lookAheadNum;
			lookAheadPara.time = 1;//时间常数
			lookAheadPara.radiusRatio = 50;//曲率参数
			for (int i = 0; i < 8; ++i)
			{
				lookAheadPara.vMax[i] = 5000;	//轴最大速度限制
				lookAheadPara.aMax[i] = 100;//轴最大加速度限制
				lookAheadPara.DVMax[i] = 500;//轴跳变速度限制
				lookAheadPara.axisRelation[i] = i + 1;	//坐标系轴与前瞻轴一一映射
				lookAheadPara.scale[i] = 1000;	//脉冲当量
			}

			rtn = GTN_SetupLookAheadCrd(core, crd, machineMode);//设置机床模式
			rtn += GTN_SetAxisFollowModeLa(core, crd, axisFollowMode);//设置跟随模式
			rtn += GTN_SetAxisLimitModeLa(core, crd, axisLimitMode);//设置轴限制模式
			rtn += GTN_SetAxisVelValidModeLa(core, crd, 0xF);//设置轴速度有效，按位设置，0xF表示前4个轴
			rtn += GTN_InitLookAheadEx(core, crd, &lookAheadPara, fifo, 0); //设置前瞻参数（需要放在最后设置）
			if (rtn == 0)
			{
				aHead = true;
				newAhead = true;
			}
			else
			{
				strMsg.Format(_T("%d"), rtn);
				MessageBox(_T("新前瞻初始化错误：") + strMsg);
				m_CNewahead.SetCheck(false);
			}
		}
	}
	else if (m_CNewahead.GetCheck() == false && newAhead == true)
	{
		MessageBox(_T("新前瞻已建立"));
	}
}



void CCrd_GSNDlg::OnBnClickedButtonCrdstart()
{
	short rtn;
	short core = 1;

	rtn = GTN_CrdClear(core, 1, 0);
	if (aHead == false)//aHead为假执行老前瞻插补，单位为步长（pulse），速度（pulse/ms），加速度（pulse/ms^2)
	{
		/*rtn = GTN_LnXY(core, 1, 0, 20000, 10, 0.1, 0, 0);								 //压入第一段位置指令
		rtn = GTN_LnXY(core, 1, 20000, 20000, 10, 0.1, 0, 0);                           //压入第二段位置指令
		rtn = GTN_LnXY(core, 1, 20000, 0, 10, 0.1, 0, 0);								 //压入第三段位置指令
		rtn = GTN_LnXY(core, 1, 0, 0, 10, 0.1, 0, 0);									//压入第四段位置指令*/
		rtn = GTN_LnXY(core, 1, 20000, 20000, 50, 1, 0, 0);
		rtn = GTN_LnXY(core, 1, 0, 0, 50, 1, 0, 0);
		rtn = GTN_CrdData(core, 1, NULL, 0);											//将前瞻缓存区中的数据压入控制器
	}
	else if (aHead == true)//aHead为真则执行新前瞻插补，单位为步长（mm），速度（mm/s），加速度（mm/s^2)
	{
		/*rtn = GTN_LnXYEx(core, 1, 0, 20, 10, 100, 0, 0);								 //压入第一段位置指令
		rtn = GTN_LnXYEx(core, 1, 20, 20, 10, 100, 0, 0);								//压入第二段位置指令
		rtn = GTN_LnXYEx(core, 1, 20, 0, 10, 100, 0, 0);								 //压入第三段位置指令
		rtn = GTN_LnXYEx(core, 1, 0, 0, 10, 100, 0, 0);									//压入第四段位置指令*/
		rtn = GTN_LnXYEx(core, 1, 20, 20, 50, 1000, 0, 0);
		rtn = GTN_LnXYEx(core, 1, 0, 0, 50, 1000, 0, 0);
		rtn = GTN_CrdDataEx(core, 1, NULL, 0);											//将前瞻缓存区中的数据压入控制器
	}
	rtn = GTN_CrdStart(1, 1, 0);														//启动插补运动
}


void CCrd_GSNDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	short rtn;
	double prfPos[4];
	short run;
	long segment;

	short core = 1;
	short index = 1;

	CString strTemp;
	short pPdoLen;
	unsigned char pValue;
	UpdateData(TRUE);

	rtn = GTN_GetPrfPos(core, 1, prfPos, 4, NULL);							// 读1~4轴的规划位置
	strTemp.Format(_T("%.3f"), prfPos[0]);
	SetDlgItemText(IDC_STATIC_PRFPOS_1, strTemp);
	strTemp.Format(_T("%.3f"), prfPos[1]);
	SetDlgItemText(IDC_STATIC_PRFPOS_2, strTemp);
	strTemp.Format(_T("%.3f"), prfPos[2]);
	SetDlgItemText(IDC_STATIC_PRFPOS_3, strTemp);
	strTemp.Format(_T("%.3f"), prfPos[3]);
	SetDlgItemText(IDC_STATIC_PRFPOS_4, strTemp);
	
	rtn = GTN_CrdStatus(core, 1, &run, &segment, 0);						// 读取坐标系运动状态
	if (run == 0)
	{
		strTemp.Format(_T("静止"));
	}
	else
	{
		strTemp.Format(_T("运动"));
	}
	SetDlgItemText(IDC_STATIC_CRD_STATUS, strTemp);
	strTemp.Format(_T("%ld"), segment);
	SetDlgItemText(IDC_STATIC_SEGMENT, strTemp);

	rtn = GTN_GetEcatRawData(core, m_iOffset, m_iSize, &pValue);
	strTemp.Format(_T("%d"), pValue);
	SetDlgItemText(IDC_STATIC_VALUE, strTemp);

	rtn = GTN_GetEcatPdoLength(core, &pPdoLen);
	strTemp.Format(_T("%d"), pPdoLen);
	SetDlgItemText(IDC_STATIC_EPDOLEN, strTemp);

	long value;
	rtn = GTN_GetDi(core, MC_GPI, &value);
	strTemp.Format(_T("%d"), value);
	SetDlgItemText(IDC_STATIC_GETDI, strTemp);

	CDialogEx::OnTimer(nIDEvent);
}


void CCrd_GSNDlg::OnBnClickedCheckPoscompare()
{
	// 设置位置比较输出参数 
	//short rtn;
	//short index = 1;
	//short core = 1;

	//if (m_CPosCompare.GetCheck() == 1)
	//{
	//	short permit;
	//	rtn = GTN_GetTerminalPermitEx(core, 1, MC_HSO, &permit, 1, 1);		//设置控制权
	//	permit = 0x2;
	//	rtn = GTN_SetTerminalPermitEx(core, 1, MC_HSO, &permit, 1, 1);
	//	rtn = GTN_PosCompareClear(core, index); //清空位置比较输出数据
	//	TPosCompareMode mode;
	//	rtn = GTN_GetPosCompareMode(core, index, &mode);//设置位置比较输出模式
	//	mode.mode = 2;
	//	mode.dimension = 2; //2维模式
	//	mode.sourceMode = 1; //输出比较源，0:编码器，1：脉冲计数器
	//	mode.sourceX = 1; //X轴比较源[1,12]
	//	mode.sourceY = 2; //Y轴比较源[1,12]
	//	mode.outputMode = 0; //0：输出脉冲，：输出电平
	//	mode.outputCounter = 1; //保留，需要大于0.
	//	mode.outputPulseWidth = 100; //输出脉冲宽度，单位：.1ms,电平模式下该参数无效
	//	mode.errorBand = 50;
	//	rtn = GTN_SetPosCompareMode(core, index, &mode);
	//	if (rtn)
	//	{
	//		printf("GTN_SetPosCompareMode=%d\n", rtn);
	//	}
	//	TPosComparePsoPrm psoPrm;
	//	rtn = GTN_GetPosComparePsoPrm(core, index, &psoPrm);	//设置等间距输出相关参数
	//	psoPrm.count = 1;										//输出个数，暂时保留，使用时可以先写
	//	psoPrm.syncPos = 100;									//输出间距，X、Y的合成距离，单位：Pulse
	//	rtn = GTN_SetPosComparePsoPrm(core, index, &psoPrm);
	//	rtn = GTN_PosCompareStart(core, index);					//启动位置比较输出
	//}
	//else if (m_CPosCompare.GetCheck() == 0)
	//{
	//	rtn = GTN_PosCompareStop(core, index);					//停止位置比较
	//	rtn = GTN_PosCompareClear(core, index);					//清除位置比较数据
	//}
}

void CCrd_GSNDlg::OnBnClickedCheckFifocompare()
{
	// 设置位置比较输出参数 
	//short rtn;
	//short index = 1;
	//short core = 1;
	//int m_count = 10;
	//int i = 0;
	//
	//if (m_CFifoCompare.GetCheck() == 1)
	//{
	//	short permit;
	//	rtn = GTN_GetTerminalPermitEx(core, 1, MC_HSO, &permit, 1, 1);//设置控制权
	//	//设置第1 路GPO 和HSO 为第1 路位置比较输出模式
	//	permit = 0x2;
	//	rtn = GTN_SetTerminalPermitEx(core, 1, MC_GPO, &permit, 1, 1);
	//	rtn = GTN_SetTerminalPermitEx(core, 1, MC_HSO, &permit, 1, 1);
	//	rtn = GTN_PosCompareClear(core, index); //清空位置比较输出数据

	//	TPosCompareMode mode;
	//	rtn = GTN_GetPosCompareMode(core, index, &mode); //读取位置比较输出模式
	//	mode.dimension = 2; //二维
	//	mode.errorBand = 10; //误差限位10Pulse
	//	mode.mode = 0; //FIFO模式
	//	mode.outputMode = 0; // 0-脉冲，1-电平，2-电平自动翻转
	//	mode.outputPulseWidth = 10; //设置脉冲宽度
	//	mode.sourceMode = 1; //0-编码器，1-冲计数器
	//	mode.sourceX = 1; //x轴对应的实际轴为轴1
	//	mode.sourceY = 2; //y轴对应的实际轴为轴2
	//	rtn = GTN_SetPosCompareMode(core, index, &mode); //设置位置比较输出模式

	//	TPosCompareData2D comparedata2d;
	//	for (i = 1; i <= m_count; i++)
	//	{
	//		comparedata2d.hso = 0x1;
	//		comparedata2d.gpo = 0x1;
	//		comparedata2d.posX = 2 + (i - 1) * 1000;
	//		comparedata2d.posY = 2 + (i - 1) * 1000;
	//		comparedata2d.segmentNumber = i;
	//		rtn = GTN_PosCompareData2D(core, index, &comparedata2d);
	//	}
	//	rtn = GTN_PosCompareStart(core, index);
	//}
	//else if (m_CFifoCompare.GetCheck() == 0)
	//{
	//	rtn = GTN_PosCompareStop(core, index);					//停止位置比较
	//	rtn = GTN_PosCompareClear(core, index);					//清除位置比较数据
	//}
}

void CCrd_GSNDlg::OnBnClickedCheckWatch()
{
	//if (m_CWatch.GetCheck())
	//{
	//	short rtn;
	//	short CORE = 1;
	//	if (watchOn == false)
	//	{
	//		rtn = GTN_ClearWatch(1, 0);
	//		TWatchVar wVar;

	//		//wVar.type = WATCH_VAR_AXIS_PRF_VEL;//读取合成速度
	//		wVar.type = WATCH_VAR_CRD_PRF_VEL;
	//		//wVar.type = WATCH_VAR_COMMAND_CODE;
	//		wVar.index = 1;					//坐标系号
	//		rtn += GTN_AddWatchVar(CORE, &wVar);

	//		wVar.type = WATCH_VAR_PRF_VEL;//读取规划速度
	//		//wVar.type = WATCH_VAR_COMMAND_CODE;
	//		wVar.index = 1;					//轴号
	//		rtn += GTN_AddWatchVar(CORE, &wVar);

	//		wVar.type = WATCH_VAR_PRF_VEL;//读取规划速度
	//		//wVar.type = WATCH_VAR_COMMAND_CODE;
	//		wVar.index = 2;					//轴号
	//		rtn += GTN_AddWatchVar(CORE, &wVar);

	//		TWatchEvent watchEvent;   //设置采集事件，当轴一规划运动才开如采集数据

	//		watchEvent.type = WATCH_EVENT_RUN;
	//		watchEvent.loop = 0;
	//		watchEvent.watchCount = 150; //运动停止后采多少数据
	//		watchEvent.var.type = WATCH_VAR_PRF_RUN;
	//		watchEvent.var.index = 1;
	//		watchEvent.condition = WATCH_CONDITION_EQ;
	//		watchEvent.value = 1;
	//		rtn += GTN_AddWatchEvent(CORE, &watchEvent);
	//		rtn += GTN_WatchOn(CORE, 4, 0, 0);   //采样间隔单位：250μs
	//		if (rtn == 0)
	//		{
	//			MessageBox(_T("数据采集打开"));
	//			watchOn = true;
	//		}
	//		else 
	//		{ 
	//			MessageBox(_T("数据采集打开失败！")); 
	//			m_CWatch.SetCheck(0);
	//		}
	//	}
	//}
	//else if (m_CWatch.GetCheck() == false && watchOn)
	//{
	//	short rtn;
	//	short CORE = 1;
	//	rtn = GTN_WatchOff(CORE);
	//	rtn += GTN_PrintWatch(CORE, "data.txt", 0, 60000);
	//	if (rtn != 0 )
	//	{
	//		MessageBox(_T("数据采集打印失败！"));
	//		m_CWatch.SetCheck(0);
	//	}
	//}
}
//-----------------------------------------------------按钮消息响应：实现Jog点动
BOOL CCrd_GSNDlg::PreTranslateMessage(MSG* pMsg)
{
	short rtn;
	short core = 1;
	short crd = 1;
	// 正方向Jog运动									//在消息传递的过程中，捕获父窗口消息预处理时按钮的按下和抬起
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_PosJog)->m_hWnd)
		{

			//if (0 == UpdateData())						//1.调用系统的检验函数对输入参数格式进行判断
			//{
			//	return 0;
			//}

			//if (m_fJogVel <= 0 || m_fJogAcc <= 0)			//2.对输入参数范围进行判断
			//{
			//	MessageBox("参数范围不正确，加速度取值范围为大于零");
			//	return 0;
			//}
			TJogPrm jog;
			rtn = GTN_PrfJog(core, m_iCurrentAxis);
			rtn = GTN_GetJogPrm(core, m_iCurrentAxis, &jog);	// 读取 Jog 运动参数(需要读取全部运动参数到上位机变量)
			jog.acc = 0.5;						//设置需要修改的运动参数
			jog.dec = 0.5;
			jog.smooth = 0;
			rtn = GTN_SetJogPrm(core, m_iCurrentAxis, &jog);	// 设置 Jog 运动参数
			rtn = GTN_SetVel(core, m_iCurrentAxis, 5);	// 设置 m_iCurrentAxis 轴的目标速度
			rtn = GTN_Update(core, 1 << (m_iCurrentAxis - 1));		// 启动 m_iCurrentAxis 轴的运动
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_PosJog)->m_hWnd)
		{
			rtn = GTN_Stop(core, 255, 255);
		}
	}

	// 负方向Jog运动
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_NegJog)->m_hWnd)
		{

			//if (0 == UpdateData())						//1.调用系统的检验函数对输入参数格式进行判断
			//{
			//	return 0;
			//}

			//if (m_fJogVel <= 0 || m_fJogAcc <= 0)			//2.对输入参数范围进行判断
			//{
			//	MessageBox("参数范围不正确，加速度取值范围为大于零");
			//	return 0;
			//}
			TJogPrm jog;
			rtn = GTN_PrfJog(core, m_iCurrentAxis);
			rtn = GTN_GetJogPrm(core, m_iCurrentAxis, &jog);	// 读取 Jog 运动参数(需要读取全部运动参数到上位机变量)
			jog.acc = 0.5;						//设置需要修改的运动参数
			jog.dec = 0.5;
			jog.smooth = 0;
			rtn = GTN_SetJogPrm(core, m_iCurrentAxis, &jog);	// 设置 Jog 运动参数
			rtn = GTN_SetVel(core, m_iCurrentAxis, -5);	// 设置 m_iCurrentAxis 轴的目标速度
			rtn = GTN_Update(core, 1 << (m_iCurrentAxis - 1));		// 启动 m_iCurrentAxis 轴的运动
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_NegJog)->m_hWnd)
		{
			rtn = GT_Stop(255, 255);
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CCrd_GSNDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO:  在此处添加消息处理程序代码
}


void CCrd_GSNDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	short rtn;
	short core = 1;
	UpdateData(TRUE);
	rtn = GTN_RelateEcatSlaveToMcGpiBit(core, m_di, m_type, m_index, m_bit, m_offset);
}
