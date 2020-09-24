
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
CString axisOff = (_T("ʹ�ܹر�"));
CString axisOn = (_T("ʹ�ܿ���"));
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
	//����ǰ�������б������������ţ������õ�ǰ��Ϊ1����
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
	rtn = GTN_Open();								// ���˶�������													
	rtn = GTN_InitEcatComm(1);						// ��ʼ��EtherCATͨѶ����
	do {
 		rtn = GTN_IsEcatReady(1, &sEcatSts);		// ��ѯEtherCATͨѶ�Ƿ�׼������
	} while (sEcatSts != 1 || rtn != 0);			// ��ʼEtherCATͨѶ
	rtn += GTN_StartEcatComm(1);
	rtn += GTN_Reset(1);                            // ��λ�˶�������
	//rtn += GTN_LoadConfig(1, "test.cfg");           // ���ؿ����������ļ�
	rtn += GTN_AlarmOff(1, 1);
	rtn += GTN_LmtsOff(1, 1, -1);
	rtn += GTN_ClrSts(1, 1, 4);                     // ���1~4�����״̬
	if (rtn != 0){ MessageBox(_T("��ʼ��ʧ�ܣ�")); }

	aHead = false;
	newAhead = false;
	oldAhead = false;
	watchOn = false; 
	axisFlag = false; //��ʼ������
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
		for (int i = 1; i <= 4; ++i){ rtn = GTN_AxisOn(1, i); }  // ��ʹ��
		if (rtn == 0)
		{
			SetDlgItemText(IDC_BUTTON_AXISENBALE, axisOff);
			axisFlag = !axisFlag;
		}
		else{ MessageBox(_T("ʹ�ܿ���ʧ��")); }
		
	}
	else if (axisFlag == true)
	{
		for (int i = 1; i <= 4; ++i){ rtn = GTN_AxisOff(1, i); }  // �ر�ʹ��
		if(rtn == 0)
		{
			SetDlgItemText(IDC_BUTTON_AXISENBALE, axisOn);
			axisFlag = !axisFlag;
		}
		else{ MessageBox(_T("ʹ�ܹر�ʧ��")); }
	}
}

void CCrd_GSNDlg::OnBnClickedButtonInitialCoordinate()
{
	short rtn;
	TCrdPrm crdPrm;

	memset(&crdPrm, 0, sizeof(crdPrm));
	crdPrm.dimension = 3;                        // ������ά������ϵ
	crdPrm.synVelMax = 500;                      // ����ϵ�����ϳ��ٶ���: 500 pulse/ms
	crdPrm.synAccMax = 2;                        // ����ϵ�����ϳɼ��ٶ���: 2 pulse/ms^2
	crdPrm.evenTime = 0;                         // ����ϵ����С����ʱ��Ϊ0
	crdPrm.profile[0] = 1;                       // �滮��1��Ӧ��X��                       
	crdPrm.profile[1] = 2;                       // �滮��2��Ӧ��Y��
	crdPrm.profile[2] = 3;
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

	rtn = GTN_SetCrdPrm(1, 1, &crdPrm);
	rtn = GTN_CrdClear(1, 1, 0);
	if (rtn != 0){ MessageBox(_T("��������ϵʧ�ܣ�")); }

	aHead = false;
	newAhead = false;
	oldAhead = false;
}

void CCrd_GSNDlg::OnBnClickedradoldahead()
{
	short rtn;
	CString strMsg;
	if (m_COldahead.GetCheck()) //����ѡ��ѡ��
	{
		if (oldAhead == false)  //�ж�״̬����ֻ֤����һ��ǰհ
		{
			TCrdData crdData[200];// ����ǰհ�������ڴ���
			rtn = GTN_InitLookAhead(1, 1, 0, 5, 1, 200, crdData);// ��ʼ������ϵ1��FIFO0��ǰհģ��
			if (rtn == 0)
			{
				aHead = false;
				oldAhead = true;//ָ��ִ�гɹ�����־λ����
			}
			else
			{
				strMsg.Format(_T("%d"), rtn);
				MessageBox(_T("ǰհ��ʼ������") + strMsg);
				m_COldahead.SetCheck(false);
			}
		}
	}
	else if (m_COldahead.GetCheck() == false && oldAhead == false)
	{
		MessageBox(_T("ǰհ�ѽ���"));
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
	//*****************************************************��ǰհ��׼ʹ�÷���*************************************************************
	//��ʼ������ǰհģ��
	if (m_CNewahead.GetCheck())
	{
		if (newAhead == false)
		{
			EMachineMode machineMode;  //��������
			EVelSettingDef velDefineMode; //�ٶȶ���ģʽ
			int axisLimitMode[8]; //������ģʽ
			EWorkLimitMode workLimitMode;  //��������ϵ����ģʽ
			int axisFollowMode[8]; //�����ģʽ
			TLookAheadParameter lookAheadPara;  //ǰհ����

			machineMode = NORMAL_THREE_AXIS; //��׼�������
			velDefineMode = NORMAL_DEF_VEL; //�����ٶ�Ϊ����ϳ��ٶ�
			workLimitMode = WORK_LIMIT_VALID; //��������ϵ������Ч
			for (int i = 0; i < 8; ++i)
			{
				axisLimitMode[i] = AXIS_LIMIT_NONE; //�����Ʋ���Ч
				axisFollowMode[i] = 0; //�Ǹ�����
			}

			lookAheadPara.lookAheadNum = lookAheadNum;
			lookAheadPara.time = 1;//ʱ�䳣��
			lookAheadPara.radiusRatio = 50;//���ʲ���
			for (int i = 0; i < 8; ++i)
			{
				lookAheadPara.vMax[i] = 5000;	//������ٶ�����
				lookAheadPara.aMax[i] = 100;//�������ٶ�����
				lookAheadPara.DVMax[i] = 500;//�������ٶ�����
				lookAheadPara.axisRelation[i] = i + 1;	//����ϵ����ǰհ��һһӳ��
				lookAheadPara.scale[i] = 1000;	//���嵱��
			}

			rtn = GTN_SetupLookAheadCrd(core, crd, machineMode);//���û���ģʽ
			rtn += GTN_SetAxisFollowModeLa(core, crd, axisFollowMode);//���ø���ģʽ
			rtn += GTN_SetAxisLimitModeLa(core, crd, axisLimitMode);//����������ģʽ
			rtn += GTN_SetAxisVelValidModeLa(core, crd, 0xF);//�������ٶ���Ч����λ���ã�0xF��ʾǰ4����
			rtn += GTN_InitLookAheadEx(core, crd, &lookAheadPara, fifo, 0); //����ǰհ��������Ҫ����������ã�
			if (rtn == 0)
			{
				aHead = true;
				newAhead = true;
			}
			else
			{
				strMsg.Format(_T("%d"), rtn);
				MessageBox(_T("��ǰհ��ʼ������") + strMsg);
				m_CNewahead.SetCheck(false);
			}
		}
	}
	else if (m_CNewahead.GetCheck() == false && newAhead == true)
	{
		MessageBox(_T("��ǰհ�ѽ���"));
	}
}



void CCrd_GSNDlg::OnBnClickedButtonCrdstart()
{
	short rtn;
	short core = 1;

	rtn = GTN_CrdClear(core, 1, 0);
	if (aHead == false)//aHeadΪ��ִ����ǰհ�岹����λΪ������pulse�����ٶȣ�pulse/ms�������ٶȣ�pulse/ms^2)
	{
		/*rtn = GTN_LnXY(core, 1, 0, 20000, 10, 0.1, 0, 0);								 //ѹ���һ��λ��ָ��
		rtn = GTN_LnXY(core, 1, 20000, 20000, 10, 0.1, 0, 0);                           //ѹ��ڶ���λ��ָ��
		rtn = GTN_LnXY(core, 1, 20000, 0, 10, 0.1, 0, 0);								 //ѹ�������λ��ָ��
		rtn = GTN_LnXY(core, 1, 0, 0, 10, 0.1, 0, 0);									//ѹ����Ķ�λ��ָ��*/
		rtn = GTN_LnXY(core, 1, 20000, 20000, 50, 1, 0, 0);
		rtn = GTN_LnXY(core, 1, 0, 0, 50, 1, 0, 0);
		rtn = GTN_CrdData(core, 1, NULL, 0);											//��ǰհ�������е�����ѹ�������
	}
	else if (aHead == true)//aHeadΪ����ִ����ǰհ�岹����λΪ������mm�����ٶȣ�mm/s�������ٶȣ�mm/s^2)
	{
		/*rtn = GTN_LnXYEx(core, 1, 0, 20, 10, 100, 0, 0);								 //ѹ���һ��λ��ָ��
		rtn = GTN_LnXYEx(core, 1, 20, 20, 10, 100, 0, 0);								//ѹ��ڶ���λ��ָ��
		rtn = GTN_LnXYEx(core, 1, 20, 0, 10, 100, 0, 0);								 //ѹ�������λ��ָ��
		rtn = GTN_LnXYEx(core, 1, 0, 0, 10, 100, 0, 0);									//ѹ����Ķ�λ��ָ��*/
		rtn = GTN_LnXYEx(core, 1, 20, 20, 50, 1000, 0, 0);
		rtn = GTN_LnXYEx(core, 1, 0, 0, 50, 1000, 0, 0);
		rtn = GTN_CrdDataEx(core, 1, NULL, 0);											//��ǰհ�������е�����ѹ�������
	}
	rtn = GTN_CrdStart(1, 1, 0);														//�����岹�˶�
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

	rtn = GTN_GetPrfPos(core, 1, prfPos, 4, NULL);							// ��1~4��Ĺ滮λ��
	strTemp.Format(_T("%.3f"), prfPos[0]);
	SetDlgItemText(IDC_STATIC_PRFPOS_1, strTemp);
	strTemp.Format(_T("%.3f"), prfPos[1]);
	SetDlgItemText(IDC_STATIC_PRFPOS_2, strTemp);
	strTemp.Format(_T("%.3f"), prfPos[2]);
	SetDlgItemText(IDC_STATIC_PRFPOS_3, strTemp);
	strTemp.Format(_T("%.3f"), prfPos[3]);
	SetDlgItemText(IDC_STATIC_PRFPOS_4, strTemp);
	
	rtn = GTN_CrdStatus(core, 1, &run, &segment, 0);						// ��ȡ����ϵ�˶�״̬
	if (run == 0)
	{
		strTemp.Format(_T("��ֹ"));
	}
	else
	{
		strTemp.Format(_T("�˶�"));
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
	// ����λ�ñȽ�������� 
	//short rtn;
	//short index = 1;
	//short core = 1;

	//if (m_CPosCompare.GetCheck() == 1)
	//{
	//	short permit;
	//	rtn = GTN_GetTerminalPermitEx(core, 1, MC_HSO, &permit, 1, 1);		//���ÿ���Ȩ
	//	permit = 0x2;
	//	rtn = GTN_SetTerminalPermitEx(core, 1, MC_HSO, &permit, 1, 1);
	//	rtn = GTN_PosCompareClear(core, index); //���λ�ñȽ��������
	//	TPosCompareMode mode;
	//	rtn = GTN_GetPosCompareMode(core, index, &mode);//����λ�ñȽ����ģʽ
	//	mode.mode = 2;
	//	mode.dimension = 2; //2άģʽ
	//	mode.sourceMode = 1; //����Ƚ�Դ��0:��������1�����������
	//	mode.sourceX = 1; //X��Ƚ�Դ[1,12]
	//	mode.sourceY = 2; //Y��Ƚ�Դ[1,12]
	//	mode.outputMode = 0; //0��������壬�������ƽ
	//	mode.outputCounter = 1; //��������Ҫ����0.
	//	mode.outputPulseWidth = 100; //���������ȣ���λ��.1ms,��ƽģʽ�¸ò�����Ч
	//	mode.errorBand = 50;
	//	rtn = GTN_SetPosCompareMode(core, index, &mode);
	//	if (rtn)
	//	{
	//		printf("GTN_SetPosCompareMode=%d\n", rtn);
	//	}
	//	TPosComparePsoPrm psoPrm;
	//	rtn = GTN_GetPosComparePsoPrm(core, index, &psoPrm);	//���õȼ�������ز���
	//	psoPrm.count = 1;										//�����������ʱ������ʹ��ʱ������д
	//	psoPrm.syncPos = 100;									//�����࣬X��Y�ĺϳɾ��룬��λ��Pulse
	//	rtn = GTN_SetPosComparePsoPrm(core, index, &psoPrm);
	//	rtn = GTN_PosCompareStart(core, index);					//����λ�ñȽ����
	//}
	//else if (m_CPosCompare.GetCheck() == 0)
	//{
	//	rtn = GTN_PosCompareStop(core, index);					//ֹͣλ�ñȽ�
	//	rtn = GTN_PosCompareClear(core, index);					//���λ�ñȽ�����
	//}
}

void CCrd_GSNDlg::OnBnClickedCheckFifocompare()
{
	// ����λ�ñȽ�������� 
	//short rtn;
	//short index = 1;
	//short core = 1;
	//int m_count = 10;
	//int i = 0;
	//
	//if (m_CFifoCompare.GetCheck() == 1)
	//{
	//	short permit;
	//	rtn = GTN_GetTerminalPermitEx(core, 1, MC_HSO, &permit, 1, 1);//���ÿ���Ȩ
	//	//���õ�1 ·GPO ��HSO Ϊ��1 ·λ�ñȽ����ģʽ
	//	permit = 0x2;
	//	rtn = GTN_SetTerminalPermitEx(core, 1, MC_GPO, &permit, 1, 1);
	//	rtn = GTN_SetTerminalPermitEx(core, 1, MC_HSO, &permit, 1, 1);
	//	rtn = GTN_PosCompareClear(core, index); //���λ�ñȽ��������

	//	TPosCompareMode mode;
	//	rtn = GTN_GetPosCompareMode(core, index, &mode); //��ȡλ�ñȽ����ģʽ
	//	mode.dimension = 2; //��ά
	//	mode.errorBand = 10; //�����λ10Pulse
	//	mode.mode = 0; //FIFOģʽ
	//	mode.outputMode = 0; // 0-���壬1-��ƽ��2-��ƽ�Զ���ת
	//	mode.outputPulseWidth = 10; //�����������
	//	mode.sourceMode = 1; //0-��������1-�������
	//	mode.sourceX = 1; //x���Ӧ��ʵ����Ϊ��1
	//	mode.sourceY = 2; //y���Ӧ��ʵ����Ϊ��2
	//	rtn = GTN_SetPosCompareMode(core, index, &mode); //����λ�ñȽ����ģʽ

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
	//	rtn = GTN_PosCompareStop(core, index);					//ֹͣλ�ñȽ�
	//	rtn = GTN_PosCompareClear(core, index);					//���λ�ñȽ�����
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

	//		//wVar.type = WATCH_VAR_AXIS_PRF_VEL;//��ȡ�ϳ��ٶ�
	//		wVar.type = WATCH_VAR_CRD_PRF_VEL;
	//		//wVar.type = WATCH_VAR_COMMAND_CODE;
	//		wVar.index = 1;					//����ϵ��
	//		rtn += GTN_AddWatchVar(CORE, &wVar);

	//		wVar.type = WATCH_VAR_PRF_VEL;//��ȡ�滮�ٶ�
	//		//wVar.type = WATCH_VAR_COMMAND_CODE;
	//		wVar.index = 1;					//���
	//		rtn += GTN_AddWatchVar(CORE, &wVar);

	//		wVar.type = WATCH_VAR_PRF_VEL;//��ȡ�滮�ٶ�
	//		//wVar.type = WATCH_VAR_COMMAND_CODE;
	//		wVar.index = 2;					//���
	//		rtn += GTN_AddWatchVar(CORE, &wVar);

	//		TWatchEvent watchEvent;   //���òɼ��¼�������һ�滮�˶��ſ���ɼ�����

	//		watchEvent.type = WATCH_EVENT_RUN;
	//		watchEvent.loop = 0;
	//		watchEvent.watchCount = 150; //�˶�ֹͣ��ɶ�������
	//		watchEvent.var.type = WATCH_VAR_PRF_RUN;
	//		watchEvent.var.index = 1;
	//		watchEvent.condition = WATCH_CONDITION_EQ;
	//		watchEvent.value = 1;
	//		rtn += GTN_AddWatchEvent(CORE, &watchEvent);
	//		rtn += GTN_WatchOn(CORE, 4, 0, 0);   //���������λ��250��s
	//		if (rtn == 0)
	//		{
	//			MessageBox(_T("���ݲɼ���"));
	//			watchOn = true;
	//		}
	//		else 
	//		{ 
	//			MessageBox(_T("���ݲɼ���ʧ�ܣ�")); 
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
	//		MessageBox(_T("���ݲɼ���ӡʧ�ܣ�"));
	//		m_CWatch.SetCheck(0);
	//	}
	//}
}
//-----------------------------------------------------��ť��Ϣ��Ӧ��ʵ��Jog�㶯
BOOL CCrd_GSNDlg::PreTranslateMessage(MSG* pMsg)
{
	short rtn;
	short core = 1;
	short crd = 1;
	// ������Jog�˶�									//����Ϣ���ݵĹ����У����񸸴�����ϢԤ����ʱ��ť�İ��º�̧��
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_PosJog)->m_hWnd)
		{

			//if (0 == UpdateData())						//1.����ϵͳ�ļ��麯�������������ʽ�����ж�
			//{
			//	return 0;
			//}

			//if (m_fJogVel <= 0 || m_fJogAcc <= 0)			//2.�����������Χ�����ж�
			//{
			//	MessageBox("������Χ����ȷ�����ٶ�ȡֵ��ΧΪ������");
			//	return 0;
			//}
			TJogPrm jog;
			rtn = GTN_PrfJog(core, m_iCurrentAxis);
			rtn = GTN_GetJogPrm(core, m_iCurrentAxis, &jog);	// ��ȡ Jog �˶�����(��Ҫ��ȡȫ���˶���������λ������)
			jog.acc = 0.5;						//������Ҫ�޸ĵ��˶�����
			jog.dec = 0.5;
			jog.smooth = 0;
			rtn = GTN_SetJogPrm(core, m_iCurrentAxis, &jog);	// ���� Jog �˶�����
			rtn = GTN_SetVel(core, m_iCurrentAxis, 5);	// ���� m_iCurrentAxis ���Ŀ���ٶ�
			rtn = GTN_Update(core, 1 << (m_iCurrentAxis - 1));		// ���� m_iCurrentAxis ����˶�
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_PosJog)->m_hWnd)
		{
			rtn = GTN_Stop(core, 255, 255);
		}
	}

	// ������Jog�˶�
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_NegJog)->m_hWnd)
		{

			//if (0 == UpdateData())						//1.����ϵͳ�ļ��麯�������������ʽ�����ж�
			//{
			//	return 0;
			//}

			//if (m_fJogVel <= 0 || m_fJogAcc <= 0)			//2.�����������Χ�����ж�
			//{
			//	MessageBox("������Χ����ȷ�����ٶ�ȡֵ��ΧΪ������");
			//	return 0;
			//}
			TJogPrm jog;
			rtn = GTN_PrfJog(core, m_iCurrentAxis);
			rtn = GTN_GetJogPrm(core, m_iCurrentAxis, &jog);	// ��ȡ Jog �˶�����(��Ҫ��ȡȫ���˶���������λ������)
			jog.acc = 0.5;						//������Ҫ�޸ĵ��˶�����
			jog.dec = 0.5;
			jog.smooth = 0;
			rtn = GTN_SetJogPrm(core, m_iCurrentAxis, &jog);	// ���� Jog �˶�����
			rtn = GTN_SetVel(core, m_iCurrentAxis, -5);	// ���� m_iCurrentAxis ���Ŀ���ٶ�
			rtn = GTN_Update(core, 1 << (m_iCurrentAxis - 1));		// ���� m_iCurrentAxis ����˶�
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

	// TODO:  �ڴ˴�������Ϣ�����������
}


void CCrd_GSNDlg::OnBnClickedButton1()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	short rtn;
	short core = 1;
	UpdateData(TRUE);
	rtn = GTN_RelateEcatSlaveToMcGpiBit(core, m_di, m_type, m_index, m_bit, m_offset);
}