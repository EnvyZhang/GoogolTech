
// SHomeDlg.cpp : ʵ���ļ�

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


// CSHomeDlg �Ի���


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


// CSHomeDlg ��Ϣ�������

BOOL CSHomeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	//1.��ʼ������
	int i;
	CString strTemp;

	GetDlgItem(IDC_BUTTON_HCAPTURE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ICAPTURE)->EnableWindow(FALSE);
	
	//����ǰ�������б����������ţ������õ�ǰ��Ϊ1����
	m_iCurrentAxis=1;
	for (i=0;i<AXIS_MAX;i++)
	{
		strTemp.Format("%d",i+1);
		((CComboBox *)GetDlgItem(IDC_COMBO_CURRENTAXIS))->AddString(strTemp);
	}
	((CComboBox *)GetDlgItem(IDC_COMBO_CURRENTAXIS))->SetCurSel(m_iCurrentAxis-1);
	//���õ�ǰ��ԭ��ģʽΪ20��HOME��ԭ�㣩
	//UpdateData(TRUE);
	//int nIndex = m_iSmartHomeMode.GetCurSel();				//��ǰѡ�е���	
	m_iSmartHomeMode.InsertString(0,_T("Limit"));				//ģʽ10  
	m_iSmartHomeMode.InsertString(1,_T("Limit+Home"));			//ģʽ11 
	m_iSmartHomeMode.InsertString(2,_T("Limit+Index"));  		//ģʽ12 
	m_iSmartHomeMode.InsertString(3,_T("Limit+Home+Index"));	//ģʽ13 
	m_iSmartHomeMode.InsertString(4,_T("Home"));  				//ģʽ20 
	m_iSmartHomeMode.InsertString(5,_T("Home+Index"));			//ģʽ22   
	m_iSmartHomeMode.InsertString(6,_T("Index"));  				//ģʽ30 		
	
	m_iSmartHomeMode.SetCurSel(4);									//Ĭ��ѡ���5��

	//2.�򿪰忨
	rtn = GT_Open();
	if (rtn != 0)
	{
		CString string;

		string.Format("GT_Open %d",rtn); //��������װ���ַ�����

		MessageBox(string);
	}
	rtn = GT_Reset();
	//3.������ʱ�����ɼ�����
	SetTimer(1,100,NULL);				//������ʱ��	
	
	//������ʼ��
	m_fJogVel=5;
	m_fJogAcc=0.1;
	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSHomeDlg::OnPaint()
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
HCURSOR CSHomeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//-----------------------------------------------------�˵���Ӧ���忨��λ
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

//-----------------------------------------------------��ť��Ϣ��Ӧ��λ������
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

//-----------------------------------------------------��ť��Ϣ��Ӧ�����״̬
void CSHomeDlg::OnBnClickedButtonClearsts()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	rtn = GT_ClrSts(m_iCurrentAxis);
	if (rtn != 0)
	{
		CString string;

		string.Format("GT_ClrSts %d",rtn);

		MessageBox(string);
	}
}

//-----------------------------------------------------��ť��Ϣ��Ӧ������ֹͣ
void CSHomeDlg::OnBnClickedStop()
{
	rtn = GT_Stop(255,255);
}

//-----------------------------------------------------��ʱ�����ɼ�����
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

			//��ȡ��־λ״̬
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
			//��ȡ�˶�״̬

			//----------------�˶����ݵ���ʾ---------------------------------------//
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

			rtn = GT_GetCaptureStatus(m_iCurrentAxis, &status[0], &pos);	// ��ѯHome����״̬
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
				//GT_Stop(255,255);												//����Homeʱ�˶���ͣ
			}

			rtn = GT_GetCaptureStatus(m_iCurrentAxis, &status[0], &pos);	// ��ѯIndex����״̬
			if(status[1] == 0)
			{		
				m_bICapture.SetBitmap(bitmap[1]);		
				rtn=GT_GetEncPos(m_iCurrentAxis,&volue,1,NULL);
				tempStr.Format(_T("%.1f"),volue);
				SetDlgItemText(IDC_CAPTUREINDEXPOS,tempStr);
				//GT_Stop(255,255);											//����Indexʱ�˶���ͣ
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
	//�ŷ�����
	if (m_iAxisStatus & 0x2)
	{
		m_bFlagAlarm.SetBitmap(bitmap[1]);
	}
	else
	{
		m_bFlagAlarm.SetBitmap(bitmap[0]);
	}
	//������λ
	if (m_iAxisStatus & 0x20)
	{
		m_bFlagPosLimit.SetBitmap(bitmap[1]);
	}
	else
	{
		m_bFlagPosLimit.SetBitmap(bitmap[0]);
	}
	//������λ
	if (m_iAxisStatus & 0x40)
	{
		m_bFlagNegLimit.SetBitmap(bitmap[1]);
	}
	else
	{
		m_bFlagNegLimit.SetBitmap(bitmap[0]);
	}	
	//�ŷ�
	if(m_iAxisStatus & 0x200)
	{
		m_bFlagServoOn.SetBitmap(bitmap[1]);
		//tempStr="�ŷ��ر�";
	}
	else
	{
		m_bFlagServoOn.SetBitmap(bitmap[0]);
		//tempStr="�ŷ�ʹ��";	
	}
	//SetDlgItemText(IDC_BUTTON_SERVOON,tempStr);
}
//-----------------------------------------------------�˵���Ӧ�����������ļ�������ʹ��
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
	//ֱ�Ӹ��ݰ�ť��Caption�ж�
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
		SetDlgItemText(IDC_OPEN,"AxisOff");			//�ŷ�ʹ�ܣ��ɹ����޸İ�ť��Caption
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

//-----------------------------------------------------�˵���Ӧ�����ܻ���
void CSHomeDlg::OnBnClickedSmarthome()
{
	//short a = 20;
	//short a = m_iSmartHomeMode;
	UpdateData(TRUE);
	int GoHomeMode = m_iSmartHomeMode.GetCurSel();						//��ǰѡ�е���		
	switch(GoHomeMode)
	{
	case 0:
		mMode = 10;													//��������
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


//-----------------------------------------------------��ť��Ϣ��Ӧ����ʼ������Jog�˶�
void CSHomeDlg::OnBnClickedPosjog()
{

}


//-----------------------------------------------------��ť��Ϣ��Ӧ����ʼ������Jog�˶�
void CSHomeDlg::OnBnClickedNegjog()
{

}


//-----------------------------------------------------��ť��Ϣ��Ӧ��ʵ��Jog�㶯
BOOL CSHomeDlg::PreTranslateMessage(MSG* pMsg)
{	
	// ������Jog�˶�									//����Ϣ���ݵĹ����У����񸸴�����ϢԤ����ʱ��ť�İ��º�̧��
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_PosJog)->m_hWnd)
		{
			
			if (0 == UpdateData())						//1.����ϵͳ�ļ��麯�������������ʽ�����ж�
			{
				return 0;
			}

			if(m_fJogVel<=0 || m_fJogAcc<=0)			//2.�����������Χ�����ж�
			{
				MessageBox("������Χ����ȷ�����ٶ�ȡֵ��ΧΪ������");
				return 0;
			}
			TJogPrm jog;
			rtn = GT_PrfJog(m_iCurrentAxis);
			rtn = GT_GetJogPrm(m_iCurrentAxis, &jog);	// ��ȡ Jog �˶�����(��Ҫ��ȡȫ���˶���������λ������)
			jog.acc = m_fJogAcc;						//������Ҫ�޸ĵ��˶�����
			jog.dec = m_fJogAcc;
			jog.smooth=0;
			rtn = GT_SetJogPrm(m_iCurrentAxis, &jog);	// ���� Jog �˶�����
			rtn = GT_SetVel(m_iCurrentAxis, m_fJogVel);	// ���� m_iCurrentAxis ���Ŀ���ٶ�
			rtn = GT_Update(1<<(m_iCurrentAxis-1));		// ���� m_iCurrentAxis ����˶�
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_PosJog)->m_hWnd)
		{
			rtn = GT_Stop(255,255);
		}
	}

 	// ������Jog�˶�
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_NegJog)->m_hWnd)
		{

			if (0 == UpdateData())						//1.����ϵͳ�ļ��麯�������������ʽ�����ж�
			{
				return 0;
			}

			if(m_fJogVel<=0 || m_fJogAcc<=0)			//2.�����������Χ�����ж�
			{
				MessageBox("������Χ����ȷ�����ٶ�ȡֵ��ΧΪ������");
				return 0;
			}
			TJogPrm jog;
			rtn = GT_PrfJog(m_iCurrentAxis);
			rtn = GT_GetJogPrm(m_iCurrentAxis, &jog);	// ��ȡ Jog �˶�����(��Ҫ��ȡȫ���˶���������λ������)
			jog.acc = m_fJogAcc;						//������Ҫ�޸ĵ��˶�����
			jog.dec = m_fJogAcc;
			jog.smooth=0;
			rtn = GT_SetJogPrm(m_iCurrentAxis, &jog);	// ���� Jog �˶�����
			rtn = GT_SetVel(m_iCurrentAxis, -m_fJogVel);	// ���� m_iCurrentAxis ���Ŀ���ٶ�
			rtn = GT_Update(1<<(m_iCurrentAxis-1));		// ���� m_iCurrentAxis ����˶�
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

//-----------------------------------------------------��ѡ����Ϣ��Ӧ��Home����
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
//-----------------------------------------------------��ѡ����Ϣ��Ӧ��Index����
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
//		rtn = GT_SetCaptureMode(m_iCurrentAxis, CAPTURE_HOME);		// ����Home����		//ERROR("GT_SetCaptureMode", rtn);
//		do
//		{
//			rtn = GT_GetCaptureStatus(m_iCurrentAxis, &status, &pos);	// ��ѯ����״̬
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

//-----------------------------------------------------����ʵ�֣����ܻ���
void CSHomeDlg::SmartHome()
{
	rtn = GT_ClrSts(m_iCurrentAxis);	//�����״̬�ᵼ�»���ʧ��
	THomePrm tHomePrm;					//���� Smart Home ��ԭ�����
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
	rtn = GT_GoHome(m_iCurrentAxis,&tHomePrm);	 //���� Smart Home ��ԭ
	if (rtn != 0)
	{
		CString string;

		string.Format("GT_GoHome %d",rtn);

		MessageBox(string);
	}
}