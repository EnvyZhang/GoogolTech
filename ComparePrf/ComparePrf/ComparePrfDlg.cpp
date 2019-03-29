// ComparePrfDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ComparePrf.h"
#include "ComparePrfDlg.h"
#include "gts.h"
#pragma comment (lib,"gts.lib")
#define AXIS 1

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int ShowFlag;
DWORD WINAPI ShowThread(LPVOID lpParameter);
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


// CComparePrfDlg 对话框




CComparePrfDlg::CComparePrfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComparePrfDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComparePrfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CComparePrfDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CComparePrfDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_1crd, &CComparePrfDlg::OnBnClickedButton1crd)
	ON_BN_CLICKED(IDC_BUTTON_2crd, &CComparePrfDlg::OnBnClickedButton2crd)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CComparePrfDlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CComparePrfDlg 消息处理程序

BOOL CComparePrfDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CComparePrfDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CComparePrfDlg::OnPaint()
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
HCURSOR CComparePrfDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void commandhandler(char *command, short error)    // 检测GT指令的执行结果，error为指令执行返回值				
{	
	if(error)                                      // 指令返回值非0，指令执行错误
	{
		printf("%s = %d\n", command, error);	
	}
}

void CComparePrfDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	short sRtn;
	short i;
	sRtn = GT_Open(0);							 // 打开运动控制器
	commandhandler("GT_Open",sRtn);
	sRtn = GT_Reset(0);							 // 复位运动控制器
	commandhandler("GT_Reset",sRtn);
	sRtn = GT_LoadConfig(0,"test.cfg");			 // 下载控制器配置文件
	commandhandler("GT_LoadConfig", sRtn);	
	sRtn = GT_ClrSts(0, 1, 4);					 // 清除1~4轴的轴状态
	commandhandler("GT_ClrSts", sRtn);	
	for(i=1;i<=4;++i)
	{
		sRtn = GT_AxisOn(0, i);					 // 使能运动轴
		commandhandler("GT_AxisOn", sRtn);
		sRtn = GT_ZeroPos(0, i);				 // 清零规划位置和实际位置
		commandhandler("GT_ZeroPos", sRtn);	
	}
}

void CComparePrfDlg::OnBnClickedButton1crd()
{
	// TODO: 在此添加控件通知处理程序代码
	short sRtn;
	short pStatus,pFifo,pFifoCount,pBufCount;
	long pCount;
	T2DComparePrm prm;
	T2DCompareData databuf[100];
	HANDLE ShowT;
	sRtn=GT_2DCompareClear(0,0);                 //清空位置比较输出数据
	commandhandler("GT_2DCompareClear", sRtn);
	/*设置高速通道0的比较*/
	sRtn=GT_2DCompareMode(0,0,COMPARE2D_MODE_1D);//设置位置比较输出一维模式
	commandhandler("GT_2DCompareMode", sRtn);
	prm.encx=2;     							 //一维模式x轴不做比较
	prm.ency=1;     							 //一维模式只比较Y轴
	prm.maxerr=300; 							 //最大允许误差(单位:pulse)
	prm.outputType=0;							 //输出类型: 0脉冲;1电平
	prm.source=1;   							 //比较源:0规划,1编码器
	prm.startLevel=0;							 //初始电平是否反转：0复位电平，1反转
	prm.threshold=10;							 //最优算法阈值
	prm.time=500;   							 //脉冲宽度(单位us)
	sRtn=GT_2DCompareSetPrm(0,0,                 //通道号 0： HSIO0 通道号 1： HSIO1
		&prm);                                   
	commandhandler("GT_2DCompareSetPrm", sRtn);
	databuf[0].px = 0;							 //第一比较点10000
	databuf[0].py = 10000;
	databuf[1].px = 0;							 //第二比较点20000
	databuf[1].py = 20000;
	sRtn = GT_2DCompareStatus(0,0,&pStatus,      //读取位置比较状态这里主要获取空闲fifo
		&pCount,&pFifo,&pFifoCount,&pBufCount);
	sRtn=GT_2DCompareData(0,0,                   // 通道号 0： HSIO0 通道号 1： HSIO1
		2,                     //位置比较数据个数
		databuf,               // 数据
		pFifo);                //空闲FIFO
	commandhandler("GT_2DCompareData", sRtn);
	sRtn=GT_2DCompareStart(0,0);                 //启动位置比较
	commandhandler("GT_2DCompareStart", sRtn);
	
	ShowFlag = 1;
	ShowT = CreateThread(NULL,
		0,
		ShowThread,
		this,
		NULL,
		NULL);

	//点位运动
	TTrapPrm trap;
	//long sts;
	//double prfPos;
	//short pStatus,pFifo,pFifoCount,pBufCount;
	sRtn = GT_PrfTrap(0,AXIS);					//设置成点位模式
	commandhandler("GT_PrfTrap", sRtn);			
	sRtn = GT_GetTrapPrm(0,AXIS, &trap);			// 读取点位运动参数
	commandhandler("GT_GetTrapPrm", sRtn);
	trap.acc = 0.25;
	trap.dec = 0.125;
	trap.smoothTime = 25;						
	sRtn = GT_SetTrapPrm(0,AXIS, &trap);			// 设置点位运动参数
	commandhandler("GT_SetTrapPrm", sRtn);		
	sRtn = GT_SetPos(0,AXIS, 20000L);				// 设置AXIS轴的目标位置
	commandhandler("GT_SetPos", sRtn);			
	sRtn = GT_SetVel(0,AXIS, 50);					// 设置AXIS轴的目标速度
	commandhandler("GT_SetVel", sRtn);			
	sRtn = GT_Update(0,1<<(AXIS-1));				// 启动AXIS轴的运动
	commandhandler("GT_Update", sRtn);
}


void CComparePrfDlg::OnBnClickedButton2crd()
{
	// TODO: 在此添加控件通知处理程序代码
	short sRtn;
	short pStatus,pFifo,pFifoCount,pBufCount;
	long pCount;
	T2DComparePrm prm;
	T2DCompareData databuf[100];
	HANDLE ShowT;
	sRtn = GT_2DCompareClear(0,0);                 //清空二维位置比较输出数据
	commandhandler("GT_2DCompareClear", sRtn);
	//sRtn = GT_SetComparePort(0,COMPARE_PORT_GPO,0,1);
	/*设置高速通道0的比较*/
	sRtn=GT_2DCompareMode(0,0,COMPARE2D_MODE_2D);//设置位置比较输出模式
	commandhandler("GT_2DCompareMode", sRtn);
	prm.encx=1;     							 //1关联比较轴x
	prm.ency=2;     							 //2关联比较轴y
	prm.maxerr=300; 							 //最大允许误差(单位:pulse)
	prm.outputType=0;							 //输出类型: 0脉冲;1电平
	prm.source=1;   							 //比较源:0规划,1编码器
	prm.startLevel=0;							 //初始电平是否反转：0复位电平，1反转
	prm.threshold=10;							 //最优算法阈值
	prm.time=500;   							 //脉冲宽度(单位us)
	sRtn=GT_2DCompareSetPrm(0,0,                 //通道号 0： HSIO0 通道号 1： HSIO1
		&prm);                                   
	commandhandler("GT_2DCompareSetPrm", sRtn);
	databuf[0].px = 10000;                       //第一比较点(10000,10000)
	databuf[0].py = 10000;
	databuf[1].px = 10000;                       //第二比较点(20000,20000)
	databuf[1].py = 10000;
	//databuf[2].px = 35000;                       //第三比较点(35000,50000)
	//databuf[2].py = 35000;
	//databuf[3].px = 40000;                       //第三比较点(35000,50000)
	//databuf[3].py = 60000;
	//databuf[4].px = 40000;                       //第一比较点(10000,10000)
	//databuf[4].py = 60000;
	sRtn = GT_2DCompareStatus(0,0,&pStatus,      //读取位置比较状态这里主要获取空闲fifo
		&pCount,&pFifo,&pFifoCount,&pBufCount);
	sRtn=GT_2DCompareData(0,0,                   // 通道号 0： HSIO0 通道号 1： HSIO1
		2,                     //位置比较数据个数
		databuf,               // 数据
		pFifo);                //空闲FIFO
	commandhandler("GT_2DCompareData", sRtn);
	sRtn=GT_2DCompareStart(0,0);                 //启动位置比较
	commandhandler("GT_2DCompareStart", sRtn);

	ShowFlag = 1;
	ShowT = CreateThread(NULL,
		0,
		ShowThread,
		this,
		NULL,
		NULL);

	//建立坐标系
	//long space,segment,pCount2;
	//double value1,value2;
	long space;
	TCrdPrm crdPrm;
	memset(&crdPrm,0,sizeof(crdPrm));
	crdPrm.dimension = 2;              			 // 建立二维的坐标系
	crdPrm.synVelMax = 500;            			 // 坐标系的最大合成速度是: 500 pulse/ms
	crdPrm.synAccMax = 2;              			 // 坐标系的最大合成加速度是: 2 pulse/ms^2
	crdPrm.evenTime = 0;               			 // 坐标系的最小匀速时间为0
	crdPrm.profile[0] = 1;             			 // 规划器1对应到X轴                       
	crdPrm.profile[1] = 2;             			 // 规划器2对应到Y轴                     
	crdPrm.setOriginFlag = 1;          			 // 需要设置加工坐标系原点位置
	crdPrm.originPos[0] = 0;           			 // 加工坐标系原点位置在(0,0)，即与机床坐标系原点重合
	crdPrm.originPos[1] = 0;
	sRtn = GT_SetCrdPrm(0, 1, &crdPrm);
	commandhandler("GT_SetCrdPrm",sRtn);
	sRtn = GT_CrdClear(0, 1, 0);          		 // 即将把数据存入坐标系1的FIFO0中，所以要首先清除此缓存区中的数据
	commandhandler("GT_CrdClear",sRtn);	
	sRtn = GT_LnXY(0, 
		1,							   			 // 该插补段的坐标系是坐标系1
		10000, 10000,				   			 // 该插补段的终点坐标(30000, 30000)
		100,						   			 // 该插补段的目标速度：100pulse/ms
		0.1,						   			 // 插补段的加速度：0.1pulse/ms^2
		100,									 // 终点速度为100
		0);						 	   			 // 向坐标系1的FIFO0缓存区传递该直线插补数据
	commandhandler("GT_LnXY",sRtn);
	sRtn = GT_LnXY(0, 1, 35000, 35000, 100,
		0.1, 0, 0);
	commandhandler("GT_LnXY",sRtn);
	sRtn = GT_CrdSpace(0, 1, &space, 0);		 // 查询坐标系1的FIFO0所剩余的空间
	commandhandler("GT_CrdSpace", sRtn);	
	sRtn = GT_CrdStart(0, 1, 0);				 // 启动坐标系1的FIFO0的插补运动
	commandhandler("GT_CrdStart",sRtn);
}

DWORD WINAPI ShowThread(LPVOID lpParameter)
{
	CComparePrfDlg *dlg;
	double prfPos[4];
	short run;
	short sRtn;
	long segment,pCount;
	CString strTemp;
	short pStatus,pFifo,pFifoCount,pBufCount;
	dlg = (CComparePrfDlg *)lpParameter;

	while(ShowFlag)
	{
		sRtn = GT_GetPrfPos(0,1,prfPos,4,NULL);           // 读1~4轴的规划位置
		sRtn = GT_CrdStatus(0,1,&run,&segment,0);         // 读取坐标系运动状态
		sRtn = GT_2DCompareStatus(0,0,&pStatus,      
			&pCount,&pFifo,&pFifoCount,&pBufCount);
		commandhandler("GT_2DCompareStatus",sRtn);
		strTemp.Format(_T("%lf"),prfPos[0]);
		(dlg->GetDlgItem(IDC_STATIC_PRFPOS_1))->SetWindowText(strTemp);
		strTemp.Format(_T("%lf"),prfPos[1]);
		(dlg->GetDlgItem(IDC_STATIC_PRFPOS_2))->SetWindowText(strTemp);
		strTemp.Format("%ld",pCount);
		(dlg->GetDlgItem(IDC_STATIC_pCount))->SetWindowText(strTemp);
		strTemp.Format("%ld",pStatus);
		(dlg->GetDlgItem(IDC_STATIC_pStatus))->SetWindowText(strTemp);
	}
	return 0;
}
void CComparePrfDlg::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	short sRtn;
	int i;
	//sRtn = GT_2DCompareStop(0,0);		//停止位置比较输出
	//sRtn=GT_2DCompareClear(0,0);        //清空位置比较输出数据
	sRtn = GT_Reset(0); 
}
