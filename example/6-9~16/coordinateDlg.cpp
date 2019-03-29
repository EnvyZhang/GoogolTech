// 例程 6-9 建立坐标系
// 例程 6-10 直线插补例程
// 例程 6-11 圆弧插补例程
// 例程 6-12 插补FIFO管理
// 例程 6-13 前瞻预处理例程
// 例程 6-14 刀向跟随功能GT_BufMove()
// 例程 6-15 刀向跟随功能GT_BufGear()
// 例程 6-16 刀向跟随功能--实际工件加工
// coordinateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "coordinate.h"
#include "coordinateDlg.h"
#include "gts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int ShowFlag;
DWORD WINAPI ShowThread(LPVOID lpParameter);

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoordinateDlg dialog

CCoordinateDlg::CCoordinateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCoordinateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCoordinateDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCoordinateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCoordinateDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCoordinateDlg, CDialog)
	//{{AFX_MSG_MAP(CCoordinateDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INITIAL, OnButtonInitial)
	ON_BN_CLICKED(IDC_BUTTON_INITIAL_COORDINATE, OnButtonInitialCoordinate)
	ON_BN_CLICKED(IDC_BUTTON_LINEAR_MOTION, OnButtonLinearMotion)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_ARC_MOTION, OnButtonArcMotion)
	ON_BN_CLICKED(IDC_BUTTON_FIFO_MANAGE, OnButtonFifoManage)
	ON_BN_CLICKED(IDC_BUTTON_LOOK_AHEAD, OnButtonLookAhead)
	ON_BN_CLICKED(IDC_BUTTON_BUF_MOVE, OnButtonBufMove)
	ON_BN_CLICKED(IDC_BUTTON_BUF_GEAR, OnButtonBufGear)
	ON_BN_CLICKED(IDC_BUTTON_REAL_MACHINING, OnButtonRealMachining)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoordinateDlg message handlers

BOOL CCoordinateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	GetDlgItem(IDC_BUTTON_INITIAL_COORDINATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCoordinateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCoordinateDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCoordinateDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCoordinateDlg::OnButtonInitial() 
{
	// TODO: Add your control notification handler code here
	short sRtn;
	short i;
	HANDLE ShowT;

	sRtn = GT_Open();                             // 打开运动控制器
	sRtn = GT_Reset();                            // 复位运动控制器
	sRtn = GT_LoadConfig("test.cfg");             // 下载控制器配置文件
	sRtn = GT_ClrSts(1,4);                        // 清除1~4轴的轴状态

	for(i=1;i<=4;++i)
	{
		sRtn = GT_AxisOn(i);                      // 使能运动轴
	}

	ShowFlag = 1;
	ShowT = CreateThread(NULL,
		                 0,
						 ShowThread,
						 this,
						 NULL,
						 NULL);
	GetDlgItem(IDC_BUTTON_INITIAL_COORDINATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(FALSE);
}

DWORD WINAPI ShowThread(LPVOID lpParameter)
{
	CCoordinateDlg *dlg;
	double prfPos[4];
	short run;
	long segment;
	CString strTemp;
	dlg = (CCoordinateDlg *)lpParameter;
	
	while(ShowFlag)
	{
		GT_GetPrfPos(1,prfPos,4,NULL);           // 读1~4轴的规划位置
		GT_CrdStatus(1,&run,&segment,0);         // 读取坐标系运动状态
		
		strTemp.Format("%lf",prfPos[0]);
		(dlg->GetDlgItem(IDC_STATIC_PRFPOS_1))->SetWindowText(strTemp);
		strTemp.Format("%lf",prfPos[1]);
		(dlg->GetDlgItem(IDC_STATIC_PRFPOS_2))->SetWindowText(strTemp);
		strTemp.Format("%lf",prfPos[2]);
		(dlg->GetDlgItem(IDC_STATIC_PRFPOS_3))->SetWindowText(strTemp);
		strTemp.Format("%lf",prfPos[3]);
		(dlg->GetDlgItem(IDC_STATIC_PRFPOS_4))->SetWindowText(strTemp);

		if(run == 0)
		{
			strTemp.Format("静止");
		}
		else
		{
			strTemp.Format("运动");
		}
		(dlg->GetDlgItem(IDC_STATIC_CRD_STATUS))->SetWindowText(strTemp);

		strTemp.Format("%ld",segment);
		(dlg->GetDlgItem(IDC_STATIC_SEGMENT))->SetWindowText(strTemp);
		
	}
	return 0;
}

// 例程 6-9 建立坐标系
void CCoordinateDlg::OnButtonInitialCoordinate() 
{
	// TODO: Add your control notification handler code here
	short sRtn;
	TCrdPrm crdPrm;

	memset(&crdPrm,0,sizeof(crdPrm));
	crdPrm.dimension = 2;                        // 建立三维的坐标系
	crdPrm.synVelMax = 500;                      // 坐标系的最大合成速度是: 500 pulse/ms
	crdPrm.synAccMax = 2;                        // 坐标系的最大合成加速度是: 2 pulse/ms^2
	crdPrm.evenTime = 0;                         // 坐标系的最小匀速时间为0
	crdPrm.profile[0] = 1;                       // 规划器1对应到X轴                       
	crdPrm.profile[1] = 2;                       // 规划器2对应到Y轴
	crdPrm.profile[2] = 0;                       
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

	sRtn = GT_SetCrdPrm(1,&crdPrm);

	GetDlgItem(IDC_BUTTON_INITIAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(TRUE);

}

// 例程 6-10 直线插补例程
void CCoordinateDlg::OnButtonLinearMotion() 
{
	// TODO: Add your control notification handler code here
	MSG msg;
	// 指令返回值变量
	short sRtn;
	// 坐标系运动状态查询变量
	short run;
	// 坐标系运动完成段查询变量
	long segment;
	// 坐标系的缓存区剩余空间查询变量
	long space;

	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(FALSE);
	for(int i=1;i<=4;++i)
	{
		sRtn = GT_ZeroPos(i);                      // 清零规划位置和实际位置
	}

	// 即将把数据存入坐标系1的FIFO0中，所以要首先清除此缓存区中的数据
	sRtn = GT_CrdClear(1, 0);
	// 向缓存区写入第一段插补数据
	sRtn = GT_LnXY( 
		1,				// 该插补段的坐标系是坐标系1
		200000, 0,		// 该插补段的终点坐标(200000, 0)
		100,			// 该插补段的目标速度：100pulse/ms
		0.1,			// 插补段的加速度：0.1pulse/ms^2
		0,				// 终点速度为0
		0);				// 向坐标系1的FIFO0缓存区传递该直线插补数据

	// 向缓存区写入第二段插补数据
	sRtn = GT_LnXY(1, 100000, 173205, 100, 0.1, 0, 0);
	// 缓存区数字量输出
	sRtn = GT_BufIO( 
		1,				// 坐标系是坐标系1
		MC_GPO,			// 数字量输出类型：通用输出
		0xffff,			// bit0~bit15全部都输出
		0x55,			// 输出的数值为0x55
		0);				// 向坐标系1的FIFO0缓存区传递该数字量输出
	// 第三段插补数据
	sRtn = GT_LnXY(1, -100000, 173205, 100, 0.1, 0, 0);
	// 缓存区数字量输出
	sRtn = GT_BufIO(1, MC_GPO, 0xffff, 0xaa, 0);
	// 第四段插补数据
	sRtn = GT_LnXY(1, -200000, 0, 100, 0.1, 0, 0);
	// 缓存区延时指令
	sRtn = GT_BufDelay( 
		1,				// 坐标系是坐标系1
		400,			// 延时400ms
		0);				// 向坐标系1的FIFO0缓存区传递该延时
	// 第五段插补数据
	sRtn = GT_LnXY(1, -100000, -173205, 100, 0.1, 0, 0);
	// 缓存区数字量输出
	sRtn = GT_BufIO(1, MC_GPO, 0xffff, 0x55, 0);
	// 缓存区延时指令
	sRtn = GT_BufDelay(1, 100, 0);
	// 第六段插补数据
	sRtn = GT_LnXY(1, 100000, -173205, 100, 0.1, 0, 0);
	// 第七段插补数据
	sRtn = GT_LnXY(1, 200000, 0, 100, 0.1, 0, 0);
	// 查询坐标系1的FIFO0所剩余的空间
	sRtn = GT_CrdSpace(1, &space, 0);
	// 启动坐标系1的FIFO0的插补运动
	sRtn = GT_CrdStart(1, 0); 
	// 等待运动完成
	sRtn = GT_CrdStatus(1, &run, &segment, 0); 
	do
	{
		// 查询坐标系1的FIFO的插补运动状态
		sRtn = GT_CrdStatus(
			1,			// 坐标系是坐标系1
			&run,		// 读取插补运动状态
			&segment,	// 读取当前已经完成的插补段数
			0);			// 查询坐标系1的FIFO0缓存区

		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}while(run == 1);                            // 坐标系在运动,查询到的run的值为1

	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(TRUE);
 	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(TRUE);
}

// 例程 6-11 圆弧插补例程
void CCoordinateDlg::OnButtonArcMotion() 
{
	// TODO: Add your control notification handler code here
	MSG msg;
	// 指令返回值变量
	short sRtn;
	// 坐标系运动状态查询变量
	short run;
	// 坐标系运动完成段查询变量
	long segment;
	// 坐标系的缓存区剩余空间查询变量
	long space;

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(FALSE);

	for(int i=1;i<=4;++i)
	{
		sRtn = GT_ZeroPos(i);                      // 清零规划位置和实际位置
	}
	// 即将把数据存入坐标系1的FIFO0中，所以要首先清除此缓存区中的数据
	sRtn = GT_CrdClear(1, 0);
	// 向缓存区写入第一段插补数据
	sRtn = GT_LnXY(
		1,					// 该插补段的坐标系是坐标系1
		200000, 0,			// 该插补段的终点坐标(200000, 0)
		100,				// 该插补段的目标速度：100pulse/ms
		0.1,				// 插补段的加速度：0.1pulse/ms^2
		0,					// 终点速度为0
		0);					// 向坐标系1的FIFO0缓存区传递该直线插补数据

	// 向缓存区写入第二段插补数据，该段数据是以圆心描述方法描述了一个整圆
	sRtn = GT_ArcXYC(
		1,					// 坐标系是坐标系1
		200000, 0,			// 该圆弧的终点坐标(200000, 0)
		-100000, 0,			// 圆弧插补的圆心相对于起点位置的偏移量(-100000, 0)
		0,					// 该圆弧是顺时针圆弧
		100,				// 该插补段的目标速度：100pulse/ms
		0.1,				// 该插补段的加速度：0.1pulse/ms^2
		0,					// 终点速度为0
		0);					// 向坐标系1的FIFO0缓存区传递该直线插补数据

	// 向缓存区写入第三段插补数据，该段数据是以半径描述方法描述了一个1/4圆弧
	sRtn = GT_ArcXYR(
		1,					// 坐标系是坐标系1
		0, 200000,			// 该圆弧的终点坐标(0, 200000)
		200000,				// 半径：200000pulse
		1,					// 该圆弧是逆时针圆弧
		100,				// 该插补段的目标速度：100pulse/ms
		0.1,				// 该插补段的加速度：0.1pulse/ms^2
		0,					// 终点速度为0
		0);					// 向坐标系1的FIFO0缓存区传递该直线插补数据

	// 向缓存区写入第四段插补数据，回到原点位置
	sRtn = GT_LnXY(1, 0, 0, 100, 0.1, 0, 0);
	// 查询坐标系1的FIFO0所剩余的空间
	sRtn = GT_CrdSpace(1, &space, 0);
	// 启动坐标系1的FIFO0的插补运动
	sRtn = GT_CrdStart(1, 0); 
	// 等待运动完成
	sRtn = GT_CrdStatus(1, &run, &segment, 0);    
	do
	{
		// 查询坐标系1的FIFO的插补运动状态
		sRtn = GT_CrdStatus(
				1,			// 坐标系是坐标系1
				&run,		// 读取插补运动状态
				&segment,	// 读取当前已经完成的插补段数
				0);			// 查询坐标系1的FIFO0缓存区
		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	// 坐标系在运动, 查询到的run的值为1
	}while(run == 1);

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(TRUE);
}

void CCoordinateDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	short sRtn;

	ShowFlag = 0;

	Sleep(1000);

	sRtn = GT_Reset();
	sRtn = GT_Close();

	GetDlgItem(IDC_BUTTON_INITIAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_INITIAL_COORDINATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(FALSE);
}


// 例程 6-12 插补FIFO管理
void CCoordinateDlg::OnButtonFifoManage() 
{
	// TODO: Add your control notification handler code here
	MSG msg;
	// 函数返回值
	short sRtn;
	// 查询坐标系运行标志
	short run;
	// 查询坐标系运行的段数
	long seg;
	// 本程序局部运行标志，主运动启动时为1，停止时为0
	short flag;	
	// 坐标系规划位置
	double crdPos[2];
	// 坐标系暂停位置
	double crdstoppos[2];

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(FALSE);

	for(int i=1;i<=4;++i)
	{
		sRtn = GT_ZeroPos(i);                      // 清零规划位置和实际位置
	}
	// 清除fifo数据
	sRtn = GT_CrdClear(1, 0);
	sRtn = GT_CrdClear(1, 1);

	// 向FIFO0缓存区写入主运动插补数据
	sRtn = GT_LnXY( 
		1,						// 该插补段的坐标系是坐标系1
		100000, 100000,			// 该插补段的终点坐标(100000, 100000)
		10,						// 该插补段的目标速度：10pulse/ms
		1,						// 插补段的加速度：1pulse/ms^2
		0,						// 终点速度为0
		0);						// 向坐标系1的FIFO0缓存区传递该直线插补数据
	// 启动主运动，并将标志flag置1
	sRtn = GT_CrdStart(1, 0);	
	flag = 1;

	do
	{
		// 查询插补坐标位置
		sRtn = GT_GetCrdPos(1, crdPos);	
		// 当X轴的坐标位置大于50000时，暂停
		if(crdPos[0] > 50000.0)
		{
			// 停止坐标系1的运动
			sRtn = GT_Stop(1<<8, 1<<8);
			// 注意:要等坐标系真正停止下来去获取当前的位置
			do
			{
				// 读取坐标系的状态，查看是否停止
				sRtn = GT_CrdStatus(1, &run, &seg, 0);
				while(PeekMessage(&msg,0,0,0,PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}while(run == 1);
			// 获取暂停后当前的位置，并将标志flag置0，退出while循环
			sRtn = GT_GetCrdPos(1, crdstoppos);						
			flag = 0;
		}
		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//printf("crdPos[0]=%-10.1lf    crdPos[1]=%-10.1lf\r", crdPos[0], crdPos[1]);
	}while(flag == 1);

	// 向FIFO1缓存区写入辅助运动插补数据
	sRtn = GT_LnXY(1, 70000, 30000, 10, 1, 0, 1);
	sRtn = GT_LnXY(1, 110000, 50000, 10, 1, 0, 1);
	// 启动坐标系1的FIFO1中运动
	sRtn = GT_CrdStart(1, 1);
	do
	{
		// 查询插补规划位置
		sRtn = GT_GetCrdPos(1, crdPos);
		// 等待辅助运动完毕
		sRtn = GT_CrdStatus(1, &run, &seg, 1);
		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//printf("crdPos[0]=%-10.1lf    crdPos[1]=%-10.1lf\r", crdPos[0], crdPos[1]);
	}while(1 == run);

	// 向FIFO1压入暂停后的位置点
	sRtn = GT_LnXY(1, (long)crdstoppos[0], (long)crdstoppos[1], 10, 1, 0, 1);
	// 启动回暂停点运动
	sRtn = GT_CrdStart(1, 1);
	do
	{
		// 查询插补规划位置
		sRtn = GT_GetCrdPos(1, crdPos);
		// 等待回到暂停点位置运动完毕
		sRtn = GT_CrdStatus(1, &run, &seg, 1);
		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//printf("crdPos[0]=%-10.1lf    crdPos[1]=%-10.1lf\r", crdPos[0], crdPos[1]);
	}while(1 == run);

	// 恢复主运动
	sRtn = GT_CrdStart(1, 0);
	do
	{
		// 获取当前的位置
		sRtn = GT_GetCrdPos(1, crdPos);	
		// 等待主运动完毕
		sRtn = GT_CrdStatus(1, &run, &seg, 0);
		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//printf("crdPos[0]=%-10.1lf    crdPos[1]=%-10.1lf\r", crdPos[0], crdPos[1]);
	}while(1 == run);
		
	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(TRUE);	
}

// 例程 6-13 前瞻预处理例程
void CCoordinateDlg::OnButtonLookAhead() 
{
	// TODO: Add your control notification handler code here
	// 指令返回值
	short sRtn;
	short run;
	// 循环变量
	int i;
	// 定义前瞻缓存区内存区
	TCrdData crdData[200];
	long posTest[2];
	long space,seg;
	MSG msg;

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(FALSE);

	for(i=1;i<=4;++i)
	{
		sRtn = GT_ZeroPos(i);                      // 清零规划位置和实际位置
	}
	// 清除fifo数据
	sRtn = GT_CrdClear(1, 0);
	sRtn = GT_CrdClear(1, 1);

	// 初始化坐标系1的FIFO0的前瞻模块
	sRtn = GT_InitLookAhead(1, 0, 5, 1, 200, crdData);
	// 压插补数据：小线段加工
	posTest[0] = 0;
	posTest[1] = 0;
	for(i=0;i<300;++i)
	{
		sRtn = GT_LnXY(1, 8000+posTest[0], 9000+posTest[1], 100, 0.8, 0, 0);
		// 查询返回值是否成功
		if(0 != sRtn)
		{
			do
			{
				// 查询运动缓存区空间，直至空间不为0
				sRtn = GT_CrdSpace(1, &space, 0);
			}while(0 == space);
			// 重新调用上次失败的插补指令
			sRtn = GT_LnXY(1, 8000+posTest[0], 9000+posTest[1], 100, 0.8, 0, 0);
		}
		posTest[0] += 1600;
		posTest[1] += 1852;
	}

	// 将前瞻缓存区中的数据压入控制器
	sRtn = GT_CrdData(1, NULL, 0);
	// 启动运动
	sRtn = GT_CrdStart(1, 0);

	do
	{
		// 等待主运动完毕
		sRtn = GT_CrdStatus(1, &run, &seg, 0);
		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//printf("crdPos[0]=%-10.1lf    crdPos[1]=%-10.1lf\r", crdPos[0], crdPos[1]);
	}while(1 == run);

// 	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(TRUE);
// 	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(TRUE);
// 	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(TRUE);
// 	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(TRUE);
// 	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(TRUE);
// 	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(TRUE);
}

// 例程 6-14 刀向跟随功能GT_BufMove()
void CCoordinateDlg::OnButtonBufMove() 
{
	// TODO: Add your control notification handler code here
	MSG msg;
	// 定义指令返回值变量
	short sRtn;
	// 定义坐标系运动状态查询变量
	short run;
	// 定义坐标系运动完成段查询变量
	long segment;

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(FALSE);

	for(int i=1;i<=4;++i)
	{
		sRtn = GT_ZeroPos(i);                      // 清零规划位置和实际位置
	}
	// 清除坐标系1的FIFO0中的数据
	sRtn = GT_CrdClear(1, 0);
	// 向FIFO0缓存区写入一段直线插补数据
	sRtn = GT_LnXY( 
		1,					// 该插补段的坐标系是坐标系1
		200000, 200000,		// 该插补段的终点坐标(200000, 200000)
		100,				// 该插补段的目标速度：100pulse/ms
		0.1,				// 插补段的加速度：0.1pulse/ms^2
		0,					// 终点速度为0
		0);					// 向坐标系1的FIFO0缓存区传递该直线插补数据
	// 向FIFO0缓存区写入一段非模态点位运动数据
	sRtn = GT_BufMove ( 
		1,					// 该插补段的坐标系是坐标系1
		4,					// 点位运动的轴号：第4轴
		50000,				// 点位运动的目标位置：50000 pulse
		30,					// 点位运动的目标速度：30 pulse/ms
		0.1,				// 点位运动的目标加速度：0.1 pulse/(ms*ms)
		0,					// 该点位运动是非模态指令
		0);					// 向坐标系1的FIFO0缓存区传递该直线插补数据
	// 向FIFO0缓存区写入一段直线插补数据
	sRtn = GT_LnXY(1, 200000, 0, 100, 0.1, 0, 0);   // 直线插补指令
	// 向FIFO0缓存区写入一段模态点位运动数据
	sRtn = GT_BufMove ( 
		1,					// 该插补段的坐标系是坐标系1
		4,					// 点位运动的轴号：第4轴
		100000,				// 点位运动的目标位置：100000 pulse
		30,					// 点位运动的目标速度：30 pulse/ms
		0.1,				// 点位运动的目标加速度：0.1 pulse/(ms*ms)
		1,					// 该点位运动是模态指令
		0);					// 向坐标系1的FIFO0缓存区传递该直线插补数据
	// 向缓存区写入一段圆弧插补数据，该段数据是以圆心描述方法描述了一个半圆
	sRtn = GT_ArcXYC(
		1,					// 坐标系是坐标系1
		-200000, 0,			// 该圆弧的终点坐标(-200000, 0)
		-200000, 0,			// 圆弧插补的圆心相对于起点位置的偏移量(-200000, 0)
		0,					// 该圆弧是顺时针圆弧
		100,				// 该插补段的目标速度：100pulse/ms
		0.1,				// 该插补段的加速度：0.1pulse/ms^2
		0,					// 终点速度为0
		0);					// 向坐标系1的FIFO0缓存区传递该直线插补数据

	// 启动坐标系1的FIFO
	sRtn = GT_CrdStart(1, 0); 

	do
	{
		// 坐标系在运动, 查询到的run的值为1
		sRtn = GT_CrdStatus(1, &run, &segment, 0);
		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}while(run == 1);

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(TRUE);
}

//例程 6-15 刀向跟随功能GT_BufGear()
void CCoordinateDlg::OnButtonBufGear() 
{
	// TODO: Add your control notification handler code here
	MSG msg;
	// 定义指令返回值变量
	short sRtn;
	// 定义坐标系运动状态查询变量
	short run;
	// 定义坐标系运动完成段查询变量
	long segment;

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(FALSE);

	for(int i=1;i<=4;++i)
	{
		sRtn = GT_ZeroPos(i);                      // 清零规划位置和实际位置
	}
	// 清除坐标系1的FIFO0中的数据
	sRtn = GT_CrdClear(1, 0);
	// 向FIFO0缓存区写入一段直线插补数据
	sRtn = GT_LnXY( 
		1,				// 该插补段的坐标系是坐标系1
		200000, 200000,	// 该插补段的终点坐标(200000, 200000)
		100,			// 该插补段的目标速度：100pulse/ms
		0.1,			// 插补段的加速度：0.1pulse/ms^2
		0,				// 终点速度为0
		0);				// 向坐标系1的FIFO0缓存区传递该直线插补数据
	// 向FIFO0缓存区写入一段跟随运动数据，
	// GT_BufGear()指令需要在所要跟随的插补段前
	sRtn = GT_BufGear(
		1,				// 该插补段的坐标系是坐标系1
		4,				// 跟随运动的轴号：第4轴
		50000,			// 跟随运动的位移量：50000 pulse。这里的位置参数是相对位置。
		0);				// 向坐标系1的FIFO0缓存区传递该直线插补数据
	// 向FIFO0缓存区写入一段直线插补数据
	sRtn = GT_LnXY(1, 200000, 0, 100, 0.1, 0, 0);
	// 向FIFO0缓存区写入一段跟随运动数据
	sRtn = GT_BufGear(
		1,				// 该插补段的坐标系是坐标系1
		4,				// 跟随运动的轴号：第4轴
		50000,			// 跟随运动的位移量：50000 pulse。这里的位置参数是相对位置。
		0);				// 向坐标系1的FIFO0缓存区传递该直线插补数据
	// 向缓存区写入一段圆弧插补数据，该段数据是以圆心描述方法描述了一个半圆
	sRtn = GT_ArcXYC(
		1,				// 坐标系是坐标系1
		-200000, 0,		// 该圆弧的终点坐标(-200000, 0)
		-200000, 0,		// 圆弧插补的圆心相对于起点位置的偏移量(-200000, 0)
		0,				// 该圆弧是顺时针圆弧
		100,			// 该插补段的目标速度：100pulse/ms
		0.1,			// 该插补段的加速度：0.1pulse/ms^2
		0,				// 终点速度为0
		0);				// 向坐标系1的FIFO0缓存区传递该直线插补数据

	// 启动坐标系1的FIFO
	sRtn = GT_CrdStart(1, 0); 

	do
	{
		// 坐标系在运动, 查询到的run的值为1
		sRtn = GT_CrdStatus(1, &run, &segment, 0);
		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}while(1 == run);

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(TRUE);	
}
// 例程 6-16 刀向跟随功能--实际工件加工
void CCoordinateDlg::OnButtonRealMachining() 
{
	// TODO: Add your control notification handler code here
	MSG msg;
	// 定义指令返回值变量
	short sRtn;
	// 定义坐标系运动状态查询变量
	short run;
	// 定义坐标系运动完成段查询变量
	long segment;

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(FALSE);

	for(int i=1;i<=4;++i)
	{
		sRtn = GT_ZeroPos(i);                      // 清零规划位置和实际位置
	}

	// 清除坐标系1的FIFO0中的数据
	sRtn = GT_CrdClear(1, 0);
	
	// 向FIFO0缓存区写入一段直线插补数据
	sRtn = GT_BufMove ( 
		1,			// 该插补段的坐标系是坐标系1
		3,			// 点位运动的轴号：第3轴
		500,		// 点位运动的目标位置：500 pulse
		10,			// 点位运动的目标速度：10 pulse/ms
		0.1,		// 点位运动的目标加速度：0.1 pulse/(ms*ms)
		1,			// 该点位运动是模态指令，等砂轮抬高后才执行下面的指令
		0);			// 向坐标系1的FIFO0缓存区传递该直线插补数据
	// 直线插补指令，到达A点
	sRtn = GT_LnXY(1, 6000, 6000, 50, 0.1, 0, 0);	
	sRtn = GT_BufMove ( 
		1,			// 该插补段的坐标系是坐标系1
		4,			// 点位运动的轴号：第4轴
		-1250,		// 使其逆时针旋转45°与BA方向一致
		10,			// 点位运动的目标速度：10 pulse/ms
		0.1,		// 点位运动的目标加速度：0.1 pulse/(ms*ms)
		1,			// 该点位运动是模态指令，等角度到位才后才执行下面的指令
		0);			// 向坐标系1的FIFO0缓存区传递该直线插补数据
	// 模态指令，将砂轮放下到加工高度位置
	sRtn = GT_BufMove(1, 3, -100, 10, 0.1, 1, 0);
	// 直线插补指令，到达B点
	sRtn = GT_LnXY(1, 6000, 12000, 50, 0.1, 0, 0);	
	sRtn = GT_BufGear(
		1,			// 该插补段的坐标系是坐标系1
		4,			// 跟随运动的轴号：第4轴
		2500,		// 跟随运动的位移量：2500 pulse（相应为90°）
		0);			// 向坐标系1的FIFO0缓存区传递该直线插补数据
	// 到达C点位置
	sRtn = GT_ArcXYR(
		1,			// 坐标系是坐标系1
		0, 14000,	// 该圆弧的终点坐标(0, 200000)
		8000,		// 半径：8000pulse
		0,			// 该圆弧是顺时针圆弧
		50,			// 该插补段的目标速度：50pulse/ms
		0.1,		// 该插补段的加速度：0.1pulse/ms^2
		0,			// 终点速度为0
		0);			// 向坐标系1的FIFO0缓存区传递该直线插补数据
	// 直线插补指令，到达D点
	sRtn = GT_LnXY(1, 24000, 20000, 50, 0.1, 0, 0);	 
	// 跟随运动的位移量：2500 pulse（相应为90°）
	sRtn = GT_BufGear(1, 4, 2500, 0);
	// 到达F点
	sRtn = GT_ArcXYR(1, 38000, 6000, 14000, 0, 50, 0.1, 0, 0);
	// 模态指令，将砂轮抬高到安全高度位置
	sRtn = GT_BufMove(1, 3, 500, 10, 0.1, 1, 0);
	// 模态指令，将砂轮抬旋转至与FA方向一致
	//该位置相对初始位置为225°，即目标位置6250
	sRtn = GT_BufMove(1, 4, 6250, 10, 0.1, 1, 0);
	// 模态指令，将砂轮放下到加工高度位置
	sRtn = GT_BufMove(1, 3, -100, 10, 0.1, 1, 0);
	// 直线插补指令，到达A点
	sRtn = GT_LnXY(1, 6000, 6000, 50, 0.1, 0, 0);
	// 启动运动
	sRtn = GT_CrdStart(1, 0);
	double prfpos3;
	sRtn=GT_GetPrfPos(3,&prfpos3);
	do
	{
		sRtn = GT_CrdStatus(1, &run, &segment, 0);
		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	// 坐标系在运动, 查询到的run的值为1
	}while(run == 1);

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(TRUE);		
}
