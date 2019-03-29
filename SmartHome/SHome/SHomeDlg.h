
// SHomeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CSHomeDlg �Ի���
class CSHomeDlg : public CDialog
{
// ����
public:
	CSHomeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SHOME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedReset();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedSmarthome();
	void UpdateAxisStatus();
	void CaptureHome();
	void SmartHome();

private:	
	long m_iAxisStatus;
	//����״̬�ؼ�
	CButton m_bFlagAlarm;
	CButton m_bFlagPosLimit;
	CButton m_bFlagNegLimit;
	CButton m_bFlagServoOn;
	//��ѡ��ؼ�
	CButton m_CHomeCapture;
	CButton m_CIndexCapture;	
	//����״̬�ؼ�
	CButton m_bHCapture;
	CButton m_bICapture;
	//�˶�����	
	double m_fJogVel,m_fJogAcc;
public:
	afx_msg void OnBnClickedZeropos();
	afx_msg void OnBnClickedButtonClearsts();
	afx_msg void OnBnClickedNegjog();
	afx_msg void OnBnClickedPosjog();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedCheckHcapture();
	afx_msg void OnBnClickedCheckIcapture();
	short m_iCurrentAxis;
	short mMode;
	CComboBox m_iSmartHomeMode;
};
