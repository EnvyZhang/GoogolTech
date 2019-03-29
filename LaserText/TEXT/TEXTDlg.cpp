// TEXTDlg.cpp : ʵ���ļ�
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


// CTEXTDlg �Ի���




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


// CTEXTDlg ��Ϣ�������

BOOL CTEXTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_cardNum.SetCurSel(0);
	int CardNum = m_cardNum.GetCurSel();
	short rtn;
	rtn = GT_Open(CardNum);           //����
	CString str;
	rtn = GT_Reset(CardNum);          //��λ
	SetTimer(1,10,NULL);

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
	m_mode.InsertString(0,"ռ�ձ�");
	m_mode.InsertString(1,"Ƶ��");
	m_mode.InsertString(2,"ģ����");
	m_mode.SetCurSel(0);
	m_chanel.SetCurSel(0);
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTEXTDlg::OnPaint()
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
HCURSOR CTEXTDlg::OnQueryDragIcon() 
{
	return static_cast<HCURSOR>(m_hIcon);
}

// �ú������ĳ��GTָ���ִ�н����commandΪָ�����ƣ�errorΪָ��ִ�з���ֵ
void commandhandler(char *command, short error)
{

	switch(error)
	{
	case 0:break;
	default:MessageBox(NULL,TEXT("�򿪰忨ʧ�ܣ�����ԭ��1.�忨û�в�ã�2.�������ĳ������ڶ԰忨������"), TEXT("LaserTest"), MB_OK);break;
	}
}


void CTEXTDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	short rtn;
	int LaserMode = m_mode.GetCurSel();    //0:ռ�ձ�ģʽ��1��Ƶ��ģʽ��2��ģ����ģʽ
	int LaserChanel = m_chanel.GetCurSel();
	int CardNum = m_cardNum.GetCurSel();
	rtn = GT_Stop(0,4095,4095);                                         //�������ģʽ�л������Ǿ�ǿ�ƹرռ���
	switch (LaserMode)
	{
	case 0:
		if ((m_power<0)|( m_power>100))
		{
			MessageBox("ռ�ձȷ�Χ��0~100");
			return;
		}
		rtn = GT_LaserPowerMode(CardNum,0,100,0,LaserChanel);    //����Ϊռ�ձ�ģʽ
		rtn = GT_LaserOutFrq(CardNum,10,LaserChanel);            //����ռ�ձ�Ƶ��Ϊ10KHz
		rtn = GT_LaserPrfCmd(CardNum,m_power,LaserChanel);       //����ռ�ձ�Ϊ25%
		rtn =GT_SetHSIOOpt(CardNum,1,LaserChanel);               //�򿪼���
		break;
	case 1:
		if ((m_power<0)|(m_power>96))
		{
			MessageBox("Ƶ�ʷ�Χ��0~96KHz");             //Ĭ�ϸ�λ��Ϊ�߷ֱ���24K�����õͷֱ��ɴﵽ96K
			return;
		}
		rtn = GT_LaserPowerMode(CardNum,1,96,0,LaserChanel);     //����ΪƵ��ģʽ
		rtn = GT_SetPulseWidth(CardNum,10,LaserChanel);          //��������Ϊ10us
		rtn = GT_LaserPrfCmd(CardNum,m_power,LaserChanel);       //����Ƶ��Ϊ20KHz
		rtn =GT_SetHSIOOpt(CardNum,1,LaserChanel);               //�򿪼���
		break;
	case 2:
		if ((m_power<0)|(m_power>10))
		{
			MessageBox("��ѹ��Χ��0~10V");
			return;
		}
		rtn = GT_LaserPowerMode(CardNum,2,10,0,LaserChanel);     //����Ϊģ����ģʽ
		rtn = GT_LaserPrfCmd(CardNum,m_power,LaserChanel);       //���������ѹΪ5V	
		rtn =GT_SetHSIOOpt(CardNum,1,LaserChanel);               //�򿪼���
		break;	
	}
	UpdateData(FALSE);
}

void CTEXTDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int CardNum = m_cardNum.GetCurSel();
	short rtn;
	rtn = GT_LoadConfig(CardNum,"GTS800.cfg");   //���������ļ�
	rtn = GT_ClrSts(CardNum,1,2);      //�������״̬
	rtn = GT_AxisOn(CardNum,1);
	rtn = GT_AxisOn(CardNum,2);        //ʹ��
	rtn = GT_ZeroPos(CardNum,1,2);     //����λ��
	TCrdPrm crdprm;
	memset(&crdprm,0,sizeof(crdprm));
	crdprm.dimension = 2;         //������ά����ϵ
	crdprm.synVelMax = 5000;       //���ϳ��ٶ�500pulse/ms
	crdprm.synAccMax = 1000;        //���ϳɼ��ٶ�10pulse/ms^2
	crdprm.evenTime = 5;          //ÿ���岹����С����ʱ��5ms
	crdprm.profile[0] = 1;
	crdprm.profile[1] = 2;        //1��2ͨ������XY����ϵ
	crdprm.setOriginFlag = 1;     //ָ������ϵԭ��λ��Ϊ��0��0��
	crdprm.originPos[0] = 0;
	crdprm.originPos[1] = 0;
	rtn = GT_SetCrdPrm(CardNum,1,&crdprm);
	if (rtn!=0)
	{
		MessageBox("��������ϵʧ��");
	}
	rtn = GT_CrdClear(CardNum,1,0);                 //�������ϵ1FIFO 0�е�����

}


void CTEXTDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//T_CrdClear(0,1,0);
	short rtn;
	/*���������ٶ����*/
	rtn = GT_Stop(0,4095,4095);                                         //����ģʽ�л�������ǿ�ƹرռ���
	int LaserMode = m_mode.GetCurSel();                               //0:ռ�ձ�ģʽ��1��Ƶ��ģʽ��2��ģ����ģʽ
	int LaserChanel = m_chanel.GetCurSel();
	int CardNum = m_cardNum.GetCurSel();
	switch (LaserMode)
	{
	case 0:
		rtn = GT_LaserPowerMode(CardNum,0,100,0,LaserChanel);                 //ռ�ձ�ģʽ
		rtn = GT_LaserOutFrq(CardNum,10,LaserChanel);                         //ռ�ձ�Ƶ��10KHz
		break;
	case 1:
		rtn = GT_LaserPowerMode(CardNum,1,96,0,LaserChanel);                  //Ƶ��ģʽ
		rtn = GT_SetPulseWidth(CardNum,10,LaserChanel);                       //��������10us
		break;
	case 2:
		rtn = GT_LaserPowerMode(CardNum,2,10,1,LaserChanel);                  //ģ����ģʽ
		break;
	}
	rtn = GT_BufLaserFollowMode(CardNum,1,0,0,LaserChanel);					//�����ڲ��������������
	rtn = GT_BufLaserFollowRatio(CardNum,1,0.1,0,10,0,LaserChanel);          //���ø������Ϊ0.1          
	rtn = GT_BufLaserOn(CardNum,1,0,LaserChanel);                            //�򿪻���������
	rtn = GT_LnXY(CardNum,1,10000,10000,10,1,0,0);                           //ѹ���һ��λ��ָ�� 
	rtn = GT_LnXY(CardNum,1,20000,20000,20,1,0,0);                           //ѹ�������λ��ָ�� 
	rtn = GT_LnXY(CardNum,1,0,0,10,1,0,0);                                  //ѹ�������λ��ָ��
	rtn = GT_BufLaserOff(CardNum,1,0,LaserChanel);                          //�رռ���
	rtn = GT_CrdStart(CardNum,1,0);                                         //�����岹�˶�

}

void CTEXTDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int CardNum = m_cardNum.GetCurSel();
	short rtn;
	int LaserChanel = m_chanel.GetCurSel();
	rtn = GT_Stop(CardNum,0x100,0);//��ͣ
	rtn = GT_SetHSIOOpt(CardNum,0,LaserChanel);
	//TCrdData data1[200];
}

void CTEXTDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int CardNum = m_cardNum.GetCurSel();
	short rtn;
	rtn = GT_Reset(CardNum);         //��λ���ƿ�
}


void CTEXTDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	short rtn;
	unsigned short sts;
	int LaserChanel = m_chanel.GetCurSel();
	int CardNum = m_cardNum.GetCurSel();
	rtn = GT_GetHSIOOpt(CardNum,&sts,LaserChanel);                 //��ȡ����״̬
	if (sts==1)
	{
		SetDlgItemText(IDC_EDIT1,"��");
	} 
	else if(sts==0)
	{
		SetDlgItemText(IDC_EDIT1,"��");
	}
	else
		SetDlgItemText(IDC_EDIT1,"�쳣");

	/*double pos[2] ={0,0};
	rtn = GT_GetPrfPos(0,1,pos,2);
	CString str;
	str.Format("Xpos = %.2f    Ypos = %.2f\n",pos[0],pos[1]);
	SetDlgItemText(IDC_EDIT13,str);*/

	CDialog::OnTimer(nIDEvent);
}
