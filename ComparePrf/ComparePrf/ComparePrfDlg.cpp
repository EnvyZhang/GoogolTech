// ComparePrfDlg.cpp : ʵ���ļ�
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
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CComparePrfDlg �Ի���




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


// CComparePrfDlg ��Ϣ�������

BOOL CComparePrfDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CComparePrfDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CComparePrfDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void commandhandler(char *command, short error)    // ���GTָ���ִ�н����errorΪָ��ִ�з���ֵ				
{	
	if(error)                                      // ָ���ֵ��0��ָ��ִ�д���
	{
		printf("%s = %d\n", command, error);	
	}
}

void CComparePrfDlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	short sRtn;
	short i;
	sRtn = GT_Open(0);							 // ���˶�������
	commandhandler("GT_Open",sRtn);
	sRtn = GT_Reset(0);							 // ��λ�˶�������
	commandhandler("GT_Reset",sRtn);
	sRtn = GT_LoadConfig(0,"test.cfg");			 // ���ؿ����������ļ�
	commandhandler("GT_LoadConfig", sRtn);	
	sRtn = GT_ClrSts(0, 1, 4);					 // ���1~4�����״̬
	commandhandler("GT_ClrSts", sRtn);	
	for(i=1;i<=4;++i)
	{
		sRtn = GT_AxisOn(0, i);					 // ʹ���˶���
		commandhandler("GT_AxisOn", sRtn);
		sRtn = GT_ZeroPos(0, i);				 // ����滮λ�ú�ʵ��λ��
		commandhandler("GT_ZeroPos", sRtn);	
	}
}

void CComparePrfDlg::OnBnClickedButton1crd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	short sRtn;
	short pStatus,pFifo,pFifoCount,pBufCount;
	long pCount;
	T2DComparePrm prm;
	T2DCompareData databuf[100];
	HANDLE ShowT;
	sRtn=GT_2DCompareClear(0,0);                 //���λ�ñȽ��������
	commandhandler("GT_2DCompareClear", sRtn);
	/*���ø���ͨ��0�ıȽ�*/
	sRtn=GT_2DCompareMode(0,0,COMPARE2D_MODE_1D);//����λ�ñȽ����һάģʽ
	commandhandler("GT_2DCompareMode", sRtn);
	prm.encx=2;     							 //һάģʽx�᲻���Ƚ�
	prm.ency=1;     							 //һάģʽֻ�Ƚ�Y��
	prm.maxerr=300; 							 //����������(��λ:pulse)
	prm.outputType=0;							 //�������: 0����;1��ƽ
	prm.source=1;   							 //�Ƚ�Դ:0�滮,1������
	prm.startLevel=0;							 //��ʼ��ƽ�Ƿ�ת��0��λ��ƽ��1��ת
	prm.threshold=10;							 //�����㷨��ֵ
	prm.time=500;   							 //������(��λus)
	sRtn=GT_2DCompareSetPrm(0,0,                 //ͨ���� 0�� HSIO0 ͨ���� 1�� HSIO1
		&prm);                                   
	commandhandler("GT_2DCompareSetPrm", sRtn);
	databuf[0].px = 0;							 //��һ�Ƚϵ�10000
	databuf[0].py = 10000;
	databuf[1].px = 0;							 //�ڶ��Ƚϵ�20000
	databuf[1].py = 20000;
	sRtn = GT_2DCompareStatus(0,0,&pStatus,      //��ȡλ�ñȽ�״̬������Ҫ��ȡ����fifo
		&pCount,&pFifo,&pFifoCount,&pBufCount);
	sRtn=GT_2DCompareData(0,0,                   // ͨ���� 0�� HSIO0 ͨ���� 1�� HSIO1
		2,                     //λ�ñȽ����ݸ���
		databuf,               // ����
		pFifo);                //����FIFO
	commandhandler("GT_2DCompareData", sRtn);
	sRtn=GT_2DCompareStart(0,0);                 //����λ�ñȽ�
	commandhandler("GT_2DCompareStart", sRtn);
	
	ShowFlag = 1;
	ShowT = CreateThread(NULL,
		0,
		ShowThread,
		this,
		NULL,
		NULL);

	//��λ�˶�
	TTrapPrm trap;
	//long sts;
	//double prfPos;
	//short pStatus,pFifo,pFifoCount,pBufCount;
	sRtn = GT_PrfTrap(0,AXIS);					//���óɵ�λģʽ
	commandhandler("GT_PrfTrap", sRtn);			
	sRtn = GT_GetTrapPrm(0,AXIS, &trap);			// ��ȡ��λ�˶�����
	commandhandler("GT_GetTrapPrm", sRtn);
	trap.acc = 0.25;
	trap.dec = 0.125;
	trap.smoothTime = 25;						
	sRtn = GT_SetTrapPrm(0,AXIS, &trap);			// ���õ�λ�˶�����
	commandhandler("GT_SetTrapPrm", sRtn);		
	sRtn = GT_SetPos(0,AXIS, 20000L);				// ����AXIS���Ŀ��λ��
	commandhandler("GT_SetPos", sRtn);			
	sRtn = GT_SetVel(0,AXIS, 50);					// ����AXIS���Ŀ���ٶ�
	commandhandler("GT_SetVel", sRtn);			
	sRtn = GT_Update(0,1<<(AXIS-1));				// ����AXIS����˶�
	commandhandler("GT_Update", sRtn);
}


void CComparePrfDlg::OnBnClickedButton2crd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	short sRtn;
	short pStatus,pFifo,pFifoCount,pBufCount;
	long pCount;
	T2DComparePrm prm;
	T2DCompareData databuf[100];
	HANDLE ShowT;
	sRtn = GT_2DCompareClear(0,0);                 //��ն�άλ�ñȽ��������
	commandhandler("GT_2DCompareClear", sRtn);
	//sRtn = GT_SetComparePort(0,COMPARE_PORT_GPO,0,1);
	/*���ø���ͨ��0�ıȽ�*/
	sRtn=GT_2DCompareMode(0,0,COMPARE2D_MODE_2D);//����λ�ñȽ����ģʽ
	commandhandler("GT_2DCompareMode", sRtn);
	prm.encx=1;     							 //1�����Ƚ���x
	prm.ency=2;     							 //2�����Ƚ���y
	prm.maxerr=300; 							 //����������(��λ:pulse)
	prm.outputType=0;							 //�������: 0����;1��ƽ
	prm.source=1;   							 //�Ƚ�Դ:0�滮,1������
	prm.startLevel=0;							 //��ʼ��ƽ�Ƿ�ת��0��λ��ƽ��1��ת
	prm.threshold=10;							 //�����㷨��ֵ
	prm.time=500;   							 //������(��λus)
	sRtn=GT_2DCompareSetPrm(0,0,                 //ͨ���� 0�� HSIO0 ͨ���� 1�� HSIO1
		&prm);                                   
	commandhandler("GT_2DCompareSetPrm", sRtn);
	databuf[0].px = 10000;                       //��һ�Ƚϵ�(10000,10000)
	databuf[0].py = 10000;
	databuf[1].px = 10000;                       //�ڶ��Ƚϵ�(20000,20000)
	databuf[1].py = 10000;
	//databuf[2].px = 35000;                       //�����Ƚϵ�(35000,50000)
	//databuf[2].py = 35000;
	//databuf[3].px = 40000;                       //�����Ƚϵ�(35000,50000)
	//databuf[3].py = 60000;
	//databuf[4].px = 40000;                       //��һ�Ƚϵ�(10000,10000)
	//databuf[4].py = 60000;
	sRtn = GT_2DCompareStatus(0,0,&pStatus,      //��ȡλ�ñȽ�״̬������Ҫ��ȡ����fifo
		&pCount,&pFifo,&pFifoCount,&pBufCount);
	sRtn=GT_2DCompareData(0,0,                   // ͨ���� 0�� HSIO0 ͨ���� 1�� HSIO1
		2,                     //λ�ñȽ����ݸ���
		databuf,               // ����
		pFifo);                //����FIFO
	commandhandler("GT_2DCompareData", sRtn);
	sRtn=GT_2DCompareStart(0,0);                 //����λ�ñȽ�
	commandhandler("GT_2DCompareStart", sRtn);

	ShowFlag = 1;
	ShowT = CreateThread(NULL,
		0,
		ShowThread,
		this,
		NULL,
		NULL);

	//��������ϵ
	//long space,segment,pCount2;
	//double value1,value2;
	long space;
	TCrdPrm crdPrm;
	memset(&crdPrm,0,sizeof(crdPrm));
	crdPrm.dimension = 2;              			 // ������ά������ϵ
	crdPrm.synVelMax = 500;            			 // ����ϵ�����ϳ��ٶ���: 500 pulse/ms
	crdPrm.synAccMax = 2;              			 // ����ϵ�����ϳɼ��ٶ���: 2 pulse/ms^2
	crdPrm.evenTime = 0;               			 // ����ϵ����С����ʱ��Ϊ0
	crdPrm.profile[0] = 1;             			 // �滮��1��Ӧ��X��                       
	crdPrm.profile[1] = 2;             			 // �滮��2��Ӧ��Y��                     
	crdPrm.setOriginFlag = 1;          			 // ��Ҫ���üӹ�����ϵԭ��λ��
	crdPrm.originPos[0] = 0;           			 // �ӹ�����ϵԭ��λ����(0,0)�������������ϵԭ���غ�
	crdPrm.originPos[1] = 0;
	sRtn = GT_SetCrdPrm(0, 1, &crdPrm);
	commandhandler("GT_SetCrdPrm",sRtn);
	sRtn = GT_CrdClear(0, 1, 0);          		 // ���������ݴ�������ϵ1��FIFO0�У�����Ҫ��������˻������е�����
	commandhandler("GT_CrdClear",sRtn);	
	sRtn = GT_LnXY(0, 
		1,							   			 // �ò岹�ε�����ϵ������ϵ1
		10000, 10000,				   			 // �ò岹�ε��յ�����(30000, 30000)
		100,						   			 // �ò岹�ε�Ŀ���ٶȣ�100pulse/ms
		0.1,						   			 // �岹�εļ��ٶȣ�0.1pulse/ms^2
		100,									 // �յ��ٶ�Ϊ100
		0);						 	   			 // ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����
	commandhandler("GT_LnXY",sRtn);
	sRtn = GT_LnXY(0, 1, 35000, 35000, 100,
		0.1, 0, 0);
	commandhandler("GT_LnXY",sRtn);
	sRtn = GT_CrdSpace(0, 1, &space, 0);		 // ��ѯ����ϵ1��FIFO0��ʣ��Ŀռ�
	commandhandler("GT_CrdSpace", sRtn);	
	sRtn = GT_CrdStart(0, 1, 0);				 // ��������ϵ1��FIFO0�Ĳ岹�˶�
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
		sRtn = GT_GetPrfPos(0,1,prfPos,4,NULL);           // ��1~4��Ĺ滮λ��
		sRtn = GT_CrdStatus(0,1,&run,&segment,0);         // ��ȡ����ϵ�˶�״̬
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	short sRtn;
	int i;
	//sRtn = GT_2DCompareStop(0,0);		//ֹͣλ�ñȽ����
	//sRtn=GT_2DCompareClear(0,0);        //���λ�ñȽ��������
	sRtn = GT_Reset(0); 
}
