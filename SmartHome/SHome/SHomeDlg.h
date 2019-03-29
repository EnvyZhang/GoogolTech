
// SHomeDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CSHomeDlg 对话框
class CSHomeDlg : public CDialog
{
// 构造
public:
	CSHomeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SHOME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	//报警状态控件
	CButton m_bFlagAlarm;
	CButton m_bFlagPosLimit;
	CButton m_bFlagNegLimit;
	CButton m_bFlagServoOn;
	//复选框控件
	CButton m_CHomeCapture;
	CButton m_CIndexCapture;	
	//捕获状态控件
	CButton m_bHCapture;
	CButton m_bICapture;
	//运动参数	
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
