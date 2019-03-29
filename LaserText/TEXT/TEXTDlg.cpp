// TEXTDlg.cpp : 实现文件
#include "stdafx.h"
#include "TEXT.h"
#include "TEXTDlg.h"
#include "gts.h"
#pragma comment(lib,"gts.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

short sRtn;


THomeStatus tHomeSts;

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


// CTEXTDlg 对话框




CTEXTDlg::CTEXTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTEXTDlg::IDD, pParent)
	, m_power(5)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTEXTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_mode);
	DDX_Control(pDX, IDC_COMBO2, m_chanel);
	DDX_Text(pDX, IDC_EDIT2, m_power);
	DDX_Control(pDX, IDC_COMBO3, m_cardNum);
}

BEGIN_MESSAGE_MAP(CTEXTDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTEXTDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTEXTDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTEXTDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTEXTDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTEXTDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTEXTDlg::OnBnClickedButton6)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTEXTDlg 消息处理程序

BOOL CTEXTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_cardNum.SetCurSel(0);
	int CardNum = m_cardNum.GetCurSel();
	short rtn;
	rtn = GT_Open(CardNum);           //开卡
	CString str;
	rtn = GT_Reset(CardNum);          //复位
	SetTimer(1,10,NULL);

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
	m_mode.InsertString(0,"占空比");
	m_mode.InsertString(1,"频率");
	m_mode.InsertString(2,"模拟量");
	m_mode.SetCurSel(0);
	m_chanel.SetCurSel(0);
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTEXTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTEXTDlg::OnPaint()
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
HCURSOR CTEXTDlg::OnQueryDragIcon() 
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 该函数检测某条GT指令的执行结果，command为指令名称，error为指令执行返回值
void commandhandler(char *command, short error)
{

	switch(error)
	{
	case 0:break;
	default:MessageBox(NULL,TEXT("打开板卡失败，可能原因：1.板卡没有插好；2.有其他的程序正在对板卡操作。"), TEXT("LaserTest"), MB_OK);break;
	}
}


void CTEXTDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	short rtn;
	int LaserMode = m_mode.GetCurSel();    //0:占空比模式；1：频率模式；2：模拟量模式
	int LaserChanel = m_chanel.GetCurSel();
	int CardNum = m_cardNum.GetCurSel();
	rtn = GT_Stop(0,4095,4095);                                         //如果激光模式切换错误，那就强制关闭激光
	switch (LaserMode)
	{
	case 0:
		if ((m_power<0)|( m_power>100))
		{
			MessageBox("占空比范围是0~100");
			return;
		}
		rtn = GT_LaserPowerMode(CardNum,0,100,0,LaserChanel);    //设置为占空比模式
		rtn = GT_LaserOutFrq(CardNum,10,LaserChanel);            //设置占空比频率为10KHz
		rtn = GT_LaserPrfCmd(CardNum,m_power,LaserChanel);       //设置占空比为25%
		rtn =GT_SetHSIOOpt(CardNum,1,LaserChanel);               //打开激光
		break;
	case 1:
		if ((m_power<0)|(m_power>96))
		{
			MessageBox("频率范围是0~96KHz");             //默认复位后为高分辨率24K，设置低分辨后可达到96K
			return;
		}
		rtn = GT_LaserPowerMode(CardNum,1,96,0,LaserChanel);     //设置为频率模式
		rtn = GT_SetPulseWidth(CardNum,10,LaserChanel);          //设置脉宽为10us
		rtn = GT_LaserPrfCmd(CardNum,m_power,LaserChanel);       //设置频率为20KHz
		rtn =GT_SetHSIOOpt(CardNum,1,LaserChanel);               //打开激光
		break;
	case 2:
		if ((m_power<0)|(m_power>10))
		{
			MessageBox("电压范围是0~10V");
			return;
		}
		rtn = GT_LaserPowerMode(CardNum,2,10,0,LaserChanel);     //设置为模拟量模式
		rtn = GT_LaserPrfCmd(CardNum,m_power,LaserChanel);       //设置输出电压为5V	
		rtn =GT_SetHSIOOpt(CardNum,1,LaserChanel);               //打开激光
		break;	
	}
	UpdateData(FALSE);
}

void CTEXTDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	int CardNum = m_cardNum.GetCurSel();
	short rtn;
	rtn = GT_LoadConfig(CardNum,"GTS800.cfg");   //加载配置文件
	rtn = GT_ClrSts(CardNum,1,2);      //清除各轴状态
	rtn = GT_AxisOn(CardNum,1);
	rtn = GT_AxisOn(CardNum,2);        //使能
	rtn = GT_ZeroPos(CardNum,1,2);     //清零位置
	TCrdPrm crdprm;
	memset(&crdprm,0,sizeof(crdprm));
	crdprm.dimension = 2;         //建立二维坐标系
	crdprm.synVelMax = 5000;       //最大合成速度500pulse/ms
	crdprm.synAccMax = 1000;        //最大合成加速度10pulse/ms^2
	crdprm.evenTime = 5;          //每个插补段最小匀速时间5ms
	crdprm.profile[0] = 1;
	crdprm.profile[1] = 2;        //1、2通到建立XY坐标系
	crdprm.setOriginFlag = 1;     //指定坐标系原点位置为（0，0）
	crdprm.originPos[0] = 0;
	crdprm.originPos[1] = 0;
	rtn = GT_SetCrdPrm(CardNum,1,&crdprm);
	if (rtn!=0)
	{
		MessageBox("建立坐标系失败");
	}
	rtn = GT_CrdClear(CardNum,1,0);                 //清除坐标系1FIFO 0中的数据

}


void CTEXTDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
//T_CrdClear(0,1,0);
	short rtn;
	/*能量跟随速度输出*/
	rtn = GT_Stop(0,4095,4095);                                         //激光模式切换错误则强制关闭激光
	int LaserMode = m_mode.GetCurSel();                               //0:占空比模式；1：频率模式；2：模拟量模式
	int LaserChanel = m_chanel.GetCurSel();
	int CardNum = m_cardNum.GetCurSel();
	switch (LaserMode)
	{
	case 0:
		rtn = GT_LaserPowerMode(CardNum,0,100,0,LaserChanel);                 //占空比模式
		rtn = GT_LaserOutFrq(CardNum,10,LaserChanel);                         //占空比频率10KHz
		break;
	case 1:
		rtn = GT_LaserPowerMode(CardNum,1,96,0,LaserChanel);                  //频率模式
		rtn = GT_SetPulseWidth(CardNum,10,LaserChanel);                       //设置脉宽10us
		break;
	case 2:
		rtn = GT_LaserPowerMode(CardNum,2,10,1,LaserChanel);                  //模拟量模式
		break;
	}
	rtn = GT_BufLaserFollowMode(CardNum,1,0,0,LaserChanel);					//设置内部脉冲计数器跟随
	rtn = GT_BufLaserFollowRatio(CardNum,1,0.1,0,10,0,LaserChanel);          //设置跟随比例为0.1          
	rtn = GT_BufLaserOn(CardNum,1,0,LaserChanel);                            //打开缓存区激光
	rtn = GT_LnXY(CardNum,1,10000,10000,10,1,0,0);                           //压入第一段位置指令 
	rtn = GT_LnXY(CardNum,1,20000,20000,20,1,0,0);                           //压入第三段位置指令 
	rtn = GT_LnXY(CardNum,1,0,0,10,1,0,0);                                  //压入第三段位置指令
	rtn = GT_BufLaserOff(CardNum,1,0,LaserChanel);                          //关闭激光
	rtn = GT_CrdStart(CardNum,1,0);                                         //启动插补运动

}

void CTEXTDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int CardNum = m_cardNum.GetCurSel();
	short rtn;
	int LaserChanel = m_chanel.GetCurSel();
	rtn = GT_Stop(CardNum,0x100,0);//急停
	rtn = GT_SetHSIOOpt(CardNum,0,LaserChanel);
	//TCrdData data1[200];
}

void CTEXTDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	short rtn;
	int LaserChanel = m_chanel.GetCurSel();
	int CardNum = m_cardNum.GetCurSel();
	rtn =GT_CrdStart(CardNum,1,0);
	rtn = GT_SetHSIOOpt(CardNum,1,LaserChanel); 
	//CString stt;
	//stt.Format("%d\n",rtn);
	//m_list.AddString("GT_CrdStart="+stt);
}

void CTEXTDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	int CardNum = m_cardNum.GetCurSel();
	short rtn;
	rtn = GT_Reset(CardNum);         //复位控制卡
}


void CTEXTDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	short rtn;
	unsigned short sts;
	int LaserChanel = m_chanel.GetCurSel();
	int CardNum = m_cardNum.GetCurSel();
	rtn = GT_GetHSIOOpt(CardNum,&sts,LaserChanel);                 //获取激光状态
	if (sts==1)
	{
		SetDlgItemText(IDC_EDIT1,"开");
	} 
	else if(sts==0)
	{
		SetDlgItemText(IDC_EDIT1,"关");
	}
	else
		SetDlgItemText(IDC_EDIT1,"异常");

	/*double pos[2] ={0,0};
	rtn = GT_GetPrfPos(0,1,pos,2);
	CString str;
	str.Format("Xpos = %.2f    Ypos = %.2f\n",pos[0],pos[1]);
	SetDlgItemText(IDC_EDIT13,str);*/

	CDialog::OnTimer(nIDEvent);
}
