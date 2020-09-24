
// Crd_GSNDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CCrd_GSNDlg dialog
class CCrd_GSNDlg : public CDialogEx
{
// Construction
public:
	CCrd_GSNDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CRD_GSN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonInitial();
	afx_msg void OnBnClickedButtonInitialCoordinate();
	afx_msg void OnBnClickedCheckOldahead();
	afx_msg void OnBnClickedCheckNehead();
	afx_msg void OnBnClickedButtonCrdstart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckPoscompare();
	afx_msg void OnBnClickedCheckWatch();
	afx_msg void OnBnClickedradnewahead();
	afx_msg void OnBnClickedradoldahead();
	CButton m_CWatch;
	CButton m_CPosCompare;
	CButton m_COldahead;
	CButton m_CNewahead;
	afx_msg void OnBnClickedButtonAxisenbale();
	afx_msg void OnBnClickedCheckFifocompare();
	CButton m_CFifoCompare;
	short m_iCurrentAxis;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	short m_iOffset;
	short m_iSize;
	afx_msg void OnBnClickedButton1();
	short m_di;
	short m_type;
	short m_index;
	short m_bit;
	short m_offset;
	short m_Cdi;
};
