// ���� 6-9 ��������ϵ
// ���� 6-10 ֱ�߲岹����
// ���� 6-11 Բ���岹����
// ���� 6-12 �岹FIFO����
// ���� 6-13 ǰհԤ��������
// ���� 6-14 ������湦��GT_BufMove()
// ���� 6-15 ������湦��GT_BufGear()
// ���� 6-16 ������湦��--ʵ�ʹ����ӹ�
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

	sRtn = GT_Open();                             // ���˶�������
	sRtn = GT_Reset();                            // ��λ�˶�������
	sRtn = GT_LoadConfig("test.cfg");             // ���ؿ����������ļ�
	sRtn = GT_ClrSts(1,4);                        // ���1~4�����״̬

	for(i=1;i<=4;++i)
	{
		sRtn = GT_AxisOn(i);                      // ʹ���˶���
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
		GT_GetPrfPos(1,prfPos,4,NULL);           // ��1~4��Ĺ滮λ��
		GT_CrdStatus(1,&run,&segment,0);         // ��ȡ����ϵ�˶�״̬
		
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
			strTemp.Format("��ֹ");
		}
		else
		{
			strTemp.Format("�˶�");
		}
		(dlg->GetDlgItem(IDC_STATIC_CRD_STATUS))->SetWindowText(strTemp);

		strTemp.Format("%ld",segment);
		(dlg->GetDlgItem(IDC_STATIC_SEGMENT))->SetWindowText(strTemp);
		
	}
	return 0;
}

// ���� 6-9 ��������ϵ
void CCoordinateDlg::OnButtonInitialCoordinate() 
{
	// TODO: Add your control notification handler code here
	short sRtn;
	TCrdPrm crdPrm;

	memset(&crdPrm,0,sizeof(crdPrm));
	crdPrm.dimension = 2;                        // ������ά������ϵ
	crdPrm.synVelMax = 500;                      // ����ϵ�����ϳ��ٶ���: 500 pulse/ms
	crdPrm.synAccMax = 2;                        // ����ϵ�����ϳɼ��ٶ���: 2 pulse/ms^2
	crdPrm.evenTime = 0;                         // ����ϵ����С����ʱ��Ϊ0
	crdPrm.profile[0] = 1;                       // �滮��1��Ӧ��X��                       
	crdPrm.profile[1] = 2;                       // �滮��2��Ӧ��Y��
	crdPrm.profile[2] = 0;                       
	crdPrm.profile[3] = 0;
	crdPrm.profile[4] = 0;
	crdPrm.profile[5] = 0;
	crdPrm.profile[6] = 0;
	crdPrm.profile[7] = 0;                      
	crdPrm.setOriginFlag = 1;                    // ��Ҫ���üӹ�����ϵԭ��λ��
	crdPrm.originPos[0] = 0;                     // �ӹ�����ϵԭ��λ����(0,0)�������������ϵԭ���غ�
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

// ���� 6-10 ֱ�߲岹����
void CCoordinateDlg::OnButtonLinearMotion() 
{
	// TODO: Add your control notification handler code here
	MSG msg;
	// ָ���ֵ����
	short sRtn;
	// ����ϵ�˶�״̬��ѯ����
	short run;
	// ����ϵ�˶���ɶβ�ѯ����
	long segment;
	// ����ϵ�Ļ�����ʣ��ռ��ѯ����
	long space;

	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(FALSE);
	for(int i=1;i<=4;++i)
	{
		sRtn = GT_ZeroPos(i);                      // ����滮λ�ú�ʵ��λ��
	}

	// ���������ݴ�������ϵ1��FIFO0�У�����Ҫ��������˻������е�����
	sRtn = GT_CrdClear(1, 0);
	// �򻺴���д���һ�β岹����
	sRtn = GT_LnXY( 
		1,				// �ò岹�ε�����ϵ������ϵ1
		200000, 0,		// �ò岹�ε��յ�����(200000, 0)
		100,			// �ò岹�ε�Ŀ���ٶȣ�100pulse/ms
		0.1,			// �岹�εļ��ٶȣ�0.1pulse/ms^2
		0,				// �յ��ٶ�Ϊ0
		0);				// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����

	// �򻺴���д��ڶ��β岹����
	sRtn = GT_LnXY(1, 100000, 173205, 100, 0.1, 0, 0);
	// ���������������
	sRtn = GT_BufIO( 
		1,				// ����ϵ������ϵ1
		MC_GPO,			// ������������ͣ�ͨ�����
		0xffff,			// bit0~bit15ȫ�������
		0x55,			// �������ֵΪ0x55
		0);				// ������ϵ1��FIFO0���������ݸ����������
	// �����β岹����
	sRtn = GT_LnXY(1, -100000, 173205, 100, 0.1, 0, 0);
	// ���������������
	sRtn = GT_BufIO(1, MC_GPO, 0xffff, 0xaa, 0);
	// ���Ķβ岹����
	sRtn = GT_LnXY(1, -200000, 0, 100, 0.1, 0, 0);
	// ��������ʱָ��
	sRtn = GT_BufDelay( 
		1,				// ����ϵ������ϵ1
		400,			// ��ʱ400ms
		0);				// ������ϵ1��FIFO0���������ݸ���ʱ
	// ����β岹����
	sRtn = GT_LnXY(1, -100000, -173205, 100, 0.1, 0, 0);
	// ���������������
	sRtn = GT_BufIO(1, MC_GPO, 0xffff, 0x55, 0);
	// ��������ʱָ��
	sRtn = GT_BufDelay(1, 100, 0);
	// �����β岹����
	sRtn = GT_LnXY(1, 100000, -173205, 100, 0.1, 0, 0);
	// ���߶β岹����
	sRtn = GT_LnXY(1, 200000, 0, 100, 0.1, 0, 0);
	// ��ѯ����ϵ1��FIFO0��ʣ��Ŀռ�
	sRtn = GT_CrdSpace(1, &space, 0);
	// ��������ϵ1��FIFO0�Ĳ岹�˶�
	sRtn = GT_CrdStart(1, 0); 
	// �ȴ��˶����
	sRtn = GT_CrdStatus(1, &run, &segment, 0); 
	do
	{
		// ��ѯ����ϵ1��FIFO�Ĳ岹�˶�״̬
		sRtn = GT_CrdStatus(
			1,			// ����ϵ������ϵ1
			&run,		// ��ȡ�岹�˶�״̬
			&segment,	// ��ȡ��ǰ�Ѿ���ɵĲ岹����
			0);			// ��ѯ����ϵ1��FIFO0������

		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}while(run == 1);                            // ����ϵ���˶�,��ѯ����run��ֵΪ1

	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(TRUE);
 	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(TRUE);
}

// ���� 6-11 Բ���岹����
void CCoordinateDlg::OnButtonArcMotion() 
{
	// TODO: Add your control notification handler code here
	MSG msg;
	// ָ���ֵ����
	short sRtn;
	// ����ϵ�˶�״̬��ѯ����
	short run;
	// ����ϵ�˶���ɶβ�ѯ����
	long segment;
	// ����ϵ�Ļ�����ʣ��ռ��ѯ����
	long space;

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(FALSE);

	for(int i=1;i<=4;++i)
	{
		sRtn = GT_ZeroPos(i);                      // ����滮λ�ú�ʵ��λ��
	}
	// ���������ݴ�������ϵ1��FIFO0�У�����Ҫ��������˻������е�����
	sRtn = GT_CrdClear(1, 0);
	// �򻺴���д���һ�β岹����
	sRtn = GT_LnXY(
		1,					// �ò岹�ε�����ϵ������ϵ1
		200000, 0,			// �ò岹�ε��յ�����(200000, 0)
		100,				// �ò岹�ε�Ŀ���ٶȣ�100pulse/ms
		0.1,				// �岹�εļ��ٶȣ�0.1pulse/ms^2
		0,					// �յ��ٶ�Ϊ0
		0);					// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����

	// �򻺴���д��ڶ��β岹���ݣ��ö���������Բ����������������һ����Բ
	sRtn = GT_ArcXYC(
		1,					// ����ϵ������ϵ1
		200000, 0,			// ��Բ�����յ�����(200000, 0)
		-100000, 0,			// Բ���岹��Բ����������λ�õ�ƫ����(-100000, 0)
		0,					// ��Բ����˳ʱ��Բ��
		100,				// �ò岹�ε�Ŀ���ٶȣ�100pulse/ms
		0.1,				// �ò岹�εļ��ٶȣ�0.1pulse/ms^2
		0,					// �յ��ٶ�Ϊ0
		0);					// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����

	// �򻺴���д������β岹���ݣ��ö��������԰뾶��������������һ��1/4Բ��
	sRtn = GT_ArcXYR(
		1,					// ����ϵ������ϵ1
		0, 200000,			// ��Բ�����յ�����(0, 200000)
		200000,				// �뾶��200000pulse
		1,					// ��Բ������ʱ��Բ��
		100,				// �ò岹�ε�Ŀ���ٶȣ�100pulse/ms
		0.1,				// �ò岹�εļ��ٶȣ�0.1pulse/ms^2
		0,					// �յ��ٶ�Ϊ0
		0);					// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����

	// �򻺴���д����Ķβ岹���ݣ��ص�ԭ��λ��
	sRtn = GT_LnXY(1, 0, 0, 100, 0.1, 0, 0);
	// ��ѯ����ϵ1��FIFO0��ʣ��Ŀռ�
	sRtn = GT_CrdSpace(1, &space, 0);
	// ��������ϵ1��FIFO0�Ĳ岹�˶�
	sRtn = GT_CrdStart(1, 0); 
	// �ȴ��˶����
	sRtn = GT_CrdStatus(1, &run, &segment, 0);    
	do
	{
		// ��ѯ����ϵ1��FIFO�Ĳ岹�˶�״̬
		sRtn = GT_CrdStatus(
				1,			// ����ϵ������ϵ1
				&run,		// ��ȡ�岹�˶�״̬
				&segment,	// ��ȡ��ǰ�Ѿ���ɵĲ岹����
				0);			// ��ѯ����ϵ1��FIFO0������
		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	// ����ϵ���˶�, ��ѯ����run��ֵΪ1
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


// ���� 6-12 �岹FIFO����
void CCoordinateDlg::OnButtonFifoManage() 
{
	// TODO: Add your control notification handler code here
	MSG msg;
	// ��������ֵ
	short sRtn;
	// ��ѯ����ϵ���б�־
	short run;
	// ��ѯ����ϵ���еĶ���
	long seg;
	// ������ֲ����б�־�����˶�����ʱΪ1��ֹͣʱΪ0
	short flag;	
	// ����ϵ�滮λ��
	double crdPos[2];
	// ����ϵ��ͣλ��
	double crdstoppos[2];

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(FALSE);

	for(int i=1;i<=4;++i)
	{
		sRtn = GT_ZeroPos(i);                      // ����滮λ�ú�ʵ��λ��
	}
	// ���fifo����
	sRtn = GT_CrdClear(1, 0);
	sRtn = GT_CrdClear(1, 1);

	// ��FIFO0������д�����˶��岹����
	sRtn = GT_LnXY( 
		1,						// �ò岹�ε�����ϵ������ϵ1
		100000, 100000,			// �ò岹�ε��յ�����(100000, 100000)
		10,						// �ò岹�ε�Ŀ���ٶȣ�10pulse/ms
		1,						// �岹�εļ��ٶȣ�1pulse/ms^2
		0,						// �յ��ٶ�Ϊ0
		0);						// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����
	// �������˶���������־flag��1
	sRtn = GT_CrdStart(1, 0);	
	flag = 1;

	do
	{
		// ��ѯ�岹����λ��
		sRtn = GT_GetCrdPos(1, crdPos);	
		// ��X�������λ�ô���50000ʱ����ͣ
		if(crdPos[0] > 50000.0)
		{
			// ֹͣ����ϵ1���˶�
			sRtn = GT_Stop(1<<8, 1<<8);
			// ע��:Ҫ������ϵ����ֹͣ����ȥ��ȡ��ǰ��λ��
			do
			{
				// ��ȡ����ϵ��״̬���鿴�Ƿ�ֹͣ
				sRtn = GT_CrdStatus(1, &run, &seg, 0);
				while(PeekMessage(&msg,0,0,0,PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}while(run == 1);
			// ��ȡ��ͣ��ǰ��λ�ã�������־flag��0���˳�whileѭ��
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

	// ��FIFO1������д�븨���˶��岹����
	sRtn = GT_LnXY(1, 70000, 30000, 10, 1, 0, 1);
	sRtn = GT_LnXY(1, 110000, 50000, 10, 1, 0, 1);
	// ��������ϵ1��FIFO1���˶�
	sRtn = GT_CrdStart(1, 1);
	do
	{
		// ��ѯ�岹�滮λ��
		sRtn = GT_GetCrdPos(1, crdPos);
		// �ȴ������˶����
		sRtn = GT_CrdStatus(1, &run, &seg, 1);
		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//printf("crdPos[0]=%-10.1lf    crdPos[1]=%-10.1lf\r", crdPos[0], crdPos[1]);
	}while(1 == run);

	// ��FIFO1ѹ����ͣ���λ�õ�
	sRtn = GT_LnXY(1, (long)crdstoppos[0], (long)crdstoppos[1], 10, 1, 0, 1);
	// ��������ͣ���˶�
	sRtn = GT_CrdStart(1, 1);
	do
	{
		// ��ѯ�岹�滮λ��
		sRtn = GT_GetCrdPos(1, crdPos);
		// �ȴ��ص���ͣ��λ���˶����
		sRtn = GT_CrdStatus(1, &run, &seg, 1);
		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//printf("crdPos[0]=%-10.1lf    crdPos[1]=%-10.1lf\r", crdPos[0], crdPos[1]);
	}while(1 == run);

	// �ָ����˶�
	sRtn = GT_CrdStart(1, 0);
	do
	{
		// ��ȡ��ǰ��λ��
		sRtn = GT_GetCrdPos(1, crdPos);	
		// �ȴ����˶����
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

// ���� 6-13 ǰհԤ��������
void CCoordinateDlg::OnButtonLookAhead() 
{
	// TODO: Add your control notification handler code here
	// ָ���ֵ
	short sRtn;
	short run;
	// ѭ������
	int i;
	// ����ǰհ�������ڴ���
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
		sRtn = GT_ZeroPos(i);                      // ����滮λ�ú�ʵ��λ��
	}
	// ���fifo����
	sRtn = GT_CrdClear(1, 0);
	sRtn = GT_CrdClear(1, 1);

	// ��ʼ������ϵ1��FIFO0��ǰհģ��
	sRtn = GT_InitLookAhead(1, 0, 5, 1, 200, crdData);
	// ѹ�岹���ݣ�С�߶μӹ�
	posTest[0] = 0;
	posTest[1] = 0;
	for(i=0;i<300;++i)
	{
		sRtn = GT_LnXY(1, 8000+posTest[0], 9000+posTest[1], 100, 0.8, 0, 0);
		// ��ѯ����ֵ�Ƿ�ɹ�
		if(0 != sRtn)
		{
			do
			{
				// ��ѯ�˶��������ռ䣬ֱ���ռ䲻Ϊ0
				sRtn = GT_CrdSpace(1, &space, 0);
			}while(0 == space);
			// ���µ����ϴ�ʧ�ܵĲ岹ָ��
			sRtn = GT_LnXY(1, 8000+posTest[0], 9000+posTest[1], 100, 0.8, 0, 0);
		}
		posTest[0] += 1600;
		posTest[1] += 1852;
	}

	// ��ǰհ�������е�����ѹ�������
	sRtn = GT_CrdData(1, NULL, 0);
	// �����˶�
	sRtn = GT_CrdStart(1, 0);

	do
	{
		// �ȴ����˶����
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

// ���� 6-14 ������湦��GT_BufMove()
void CCoordinateDlg::OnButtonBufMove() 
{
	// TODO: Add your control notification handler code here
	MSG msg;
	// ����ָ���ֵ����
	short sRtn;
	// ��������ϵ�˶�״̬��ѯ����
	short run;
	// ��������ϵ�˶���ɶβ�ѯ����
	long segment;

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(FALSE);

	for(int i=1;i<=4;++i)
	{
		sRtn = GT_ZeroPos(i);                      // ����滮λ�ú�ʵ��λ��
	}
	// �������ϵ1��FIFO0�е�����
	sRtn = GT_CrdClear(1, 0);
	// ��FIFO0������д��һ��ֱ�߲岹����
	sRtn = GT_LnXY( 
		1,					// �ò岹�ε�����ϵ������ϵ1
		200000, 200000,		// �ò岹�ε��յ�����(200000, 200000)
		100,				// �ò岹�ε�Ŀ���ٶȣ�100pulse/ms
		0.1,				// �岹�εļ��ٶȣ�0.1pulse/ms^2
		0,					// �յ��ٶ�Ϊ0
		0);					// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����
	// ��FIFO0������д��һ�η�ģ̬��λ�˶�����
	sRtn = GT_BufMove ( 
		1,					// �ò岹�ε�����ϵ������ϵ1
		4,					// ��λ�˶�����ţ���4��
		50000,				// ��λ�˶���Ŀ��λ�ã�50000 pulse
		30,					// ��λ�˶���Ŀ���ٶȣ�30 pulse/ms
		0.1,				// ��λ�˶���Ŀ����ٶȣ�0.1 pulse/(ms*ms)
		0,					// �õ�λ�˶��Ƿ�ģָ̬��
		0);					// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����
	// ��FIFO0������д��һ��ֱ�߲岹����
	sRtn = GT_LnXY(1, 200000, 0, 100, 0.1, 0, 0);   // ֱ�߲岹ָ��
	// ��FIFO0������д��һ��ģ̬��λ�˶�����
	sRtn = GT_BufMove ( 
		1,					// �ò岹�ε�����ϵ������ϵ1
		4,					// ��λ�˶�����ţ���4��
		100000,				// ��λ�˶���Ŀ��λ�ã�100000 pulse
		30,					// ��λ�˶���Ŀ���ٶȣ�30 pulse/ms
		0.1,				// ��λ�˶���Ŀ����ٶȣ�0.1 pulse/(ms*ms)
		1,					// �õ�λ�˶���ģָ̬��
		0);					// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����
	// �򻺴���д��һ��Բ���岹���ݣ��ö���������Բ����������������һ����Բ
	sRtn = GT_ArcXYC(
		1,					// ����ϵ������ϵ1
		-200000, 0,			// ��Բ�����յ�����(-200000, 0)
		-200000, 0,			// Բ���岹��Բ����������λ�õ�ƫ����(-200000, 0)
		0,					// ��Բ����˳ʱ��Բ��
		100,				// �ò岹�ε�Ŀ���ٶȣ�100pulse/ms
		0.1,				// �ò岹�εļ��ٶȣ�0.1pulse/ms^2
		0,					// �յ��ٶ�Ϊ0
		0);					// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����

	// ��������ϵ1��FIFO
	sRtn = GT_CrdStart(1, 0); 

	do
	{
		// ����ϵ���˶�, ��ѯ����run��ֵΪ1
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

//���� 6-15 ������湦��GT_BufGear()
void CCoordinateDlg::OnButtonBufGear() 
{
	// TODO: Add your control notification handler code here
	MSG msg;
	// ����ָ���ֵ����
	short sRtn;
	// ��������ϵ�˶�״̬��ѯ����
	short run;
	// ��������ϵ�˶���ɶβ�ѯ����
	long segment;

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REAL_MACHINING)->EnableWindow(FALSE);

	for(int i=1;i<=4;++i)
	{
		sRtn = GT_ZeroPos(i);                      // ����滮λ�ú�ʵ��λ��
	}
	// �������ϵ1��FIFO0�е�����
	sRtn = GT_CrdClear(1, 0);
	// ��FIFO0������д��һ��ֱ�߲岹����
	sRtn = GT_LnXY( 
		1,				// �ò岹�ε�����ϵ������ϵ1
		200000, 200000,	// �ò岹�ε��յ�����(200000, 200000)
		100,			// �ò岹�ε�Ŀ���ٶȣ�100pulse/ms
		0.1,			// �岹�εļ��ٶȣ�0.1pulse/ms^2
		0,				// �յ��ٶ�Ϊ0
		0);				// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����
	// ��FIFO0������д��һ�θ����˶����ݣ�
	// GT_BufGear()ָ����Ҫ����Ҫ����Ĳ岹��ǰ
	sRtn = GT_BufGear(
		1,				// �ò岹�ε�����ϵ������ϵ1
		4,				// �����˶�����ţ���4��
		50000,			// �����˶���λ������50000 pulse�������λ�ò��������λ�á�
		0);				// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����
	// ��FIFO0������д��һ��ֱ�߲岹����
	sRtn = GT_LnXY(1, 200000, 0, 100, 0.1, 0, 0);
	// ��FIFO0������д��һ�θ����˶�����
	sRtn = GT_BufGear(
		1,				// �ò岹�ε�����ϵ������ϵ1
		4,				// �����˶�����ţ���4��
		50000,			// �����˶���λ������50000 pulse�������λ�ò��������λ�á�
		0);				// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����
	// �򻺴���д��һ��Բ���岹���ݣ��ö���������Բ����������������һ����Բ
	sRtn = GT_ArcXYC(
		1,				// ����ϵ������ϵ1
		-200000, 0,		// ��Բ�����յ�����(-200000, 0)
		-200000, 0,		// Բ���岹��Բ����������λ�õ�ƫ����(-200000, 0)
		0,				// ��Բ����˳ʱ��Բ��
		100,			// �ò岹�ε�Ŀ���ٶȣ�100pulse/ms
		0.1,			// �ò岹�εļ��ٶȣ�0.1pulse/ms^2
		0,				// �յ��ٶ�Ϊ0
		0);				// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����

	// ��������ϵ1��FIFO
	sRtn = GT_CrdStart(1, 0); 

	do
	{
		// ����ϵ���˶�, ��ѯ����run��ֵΪ1
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
// ���� 6-16 ������湦��--ʵ�ʹ����ӹ�
void CCoordinateDlg::OnButtonRealMachining() 
{
	// TODO: Add your control notification handler code here
	MSG msg;
	// ����ָ���ֵ����
	short sRtn;
	// ��������ϵ�˶�״̬��ѯ����
	short run;
	// ��������ϵ�˶���ɶβ�ѯ����
	long segment;

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(FALSE);

	for(int i=1;i<=4;++i)
	{
		sRtn = GT_ZeroPos(i);                      // ����滮λ�ú�ʵ��λ��
	}

	// �������ϵ1��FIFO0�е�����
	sRtn = GT_CrdClear(1, 0);
	
	// ��FIFO0������д��һ��ֱ�߲岹����
	sRtn = GT_BufMove ( 
		1,			// �ò岹�ε�����ϵ������ϵ1
		3,			// ��λ�˶�����ţ���3��
		500,		// ��λ�˶���Ŀ��λ�ã�500 pulse
		10,			// ��λ�˶���Ŀ���ٶȣ�10 pulse/ms
		0.1,		// ��λ�˶���Ŀ����ٶȣ�0.1 pulse/(ms*ms)
		1,			// �õ�λ�˶���ģָ̬���ɰ��̧�ߺ��ִ�������ָ��
		0);			// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����
	// ֱ�߲岹ָ�����A��
	sRtn = GT_LnXY(1, 6000, 6000, 50, 0.1, 0, 0);	
	sRtn = GT_BufMove ( 
		1,			// �ò岹�ε�����ϵ������ϵ1
		4,			// ��λ�˶�����ţ���4��
		-1250,		// ʹ����ʱ����ת45����BA����һ��
		10,			// ��λ�˶���Ŀ���ٶȣ�10 pulse/ms
		0.1,		// ��λ�˶���Ŀ����ٶȣ�0.1 pulse/(ms*ms)
		1,			// �õ�λ�˶���ģָ̬��ȽǶȵ�λ�ź��ִ�������ָ��
		0);			// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����
	// ģָ̬���ɰ�ַ��µ��ӹ��߶�λ��
	sRtn = GT_BufMove(1, 3, -100, 10, 0.1, 1, 0);
	// ֱ�߲岹ָ�����B��
	sRtn = GT_LnXY(1, 6000, 12000, 50, 0.1, 0, 0);	
	sRtn = GT_BufGear(
		1,			// �ò岹�ε�����ϵ������ϵ1
		4,			// �����˶�����ţ���4��
		2500,		// �����˶���λ������2500 pulse����ӦΪ90�㣩
		0);			// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����
	// ����C��λ��
	sRtn = GT_ArcXYR(
		1,			// ����ϵ������ϵ1
		0, 14000,	// ��Բ�����յ�����(0, 200000)
		8000,		// �뾶��8000pulse
		0,			// ��Բ����˳ʱ��Բ��
		50,			// �ò岹�ε�Ŀ���ٶȣ�50pulse/ms
		0.1,		// �ò岹�εļ��ٶȣ�0.1pulse/ms^2
		0,			// �յ��ٶ�Ϊ0
		0);			// ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����
	// ֱ�߲岹ָ�����D��
	sRtn = GT_LnXY(1, 24000, 20000, 50, 0.1, 0, 0);	 
	// �����˶���λ������2500 pulse����ӦΪ90�㣩
	sRtn = GT_BufGear(1, 4, 2500, 0);
	// ����F��
	sRtn = GT_ArcXYR(1, 38000, 6000, 14000, 0, 50, 0.1, 0, 0);
	// ģָ̬���ɰ��̧�ߵ���ȫ�߶�λ��
	sRtn = GT_BufMove(1, 3, 500, 10, 0.1, 1, 0);
	// ģָ̬���ɰ��̧��ת����FA����һ��
	//��λ����Գ�ʼλ��Ϊ225�㣬��Ŀ��λ��6250
	sRtn = GT_BufMove(1, 4, 6250, 10, 0.1, 1, 0);
	// ģָ̬���ɰ�ַ��µ��ӹ��߶�λ��
	sRtn = GT_BufMove(1, 3, -100, 10, 0.1, 1, 0);
	// ֱ�߲岹ָ�����A��
	sRtn = GT_LnXY(1, 6000, 6000, 50, 0.1, 0, 0);
	// �����˶�
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
	// ����ϵ���˶�, ��ѯ����run��ֵΪ1
	}while(run == 1);

	GetDlgItem(IDC_BUTTON_LINEAR_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ARC_MOTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOOK_AHEAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FIFO_MANAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_MOVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BUF_GEAR)->EnableWindow(TRUE);		
}
