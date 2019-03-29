// coordinateDlg.h : header file
//

#if !defined(AFX_COORDINATEDLG_H__4DA6BB8F_35EA_4ABC_AC7D_71C4F894EB31__INCLUDED_)
#define AFX_COORDINATEDLG_H__4DA6BB8F_35EA_4ABC_AC7D_71C4F894EB31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCoordinateDlg dialog

class CCoordinateDlg : public CDialog
{
// Construction
public:
	CCoordinateDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCoordinateDlg)
	enum { IDD = IDD_COORDINATE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoordinateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCoordinateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonInitial();
	afx_msg void OnButtonInitialCoordinate();
	afx_msg void OnButtonLinearMotion();
	afx_msg void OnButtonClose();
	afx_msg void OnButtonArcMotion();
	afx_msg void OnButtonFifoManage();
	afx_msg void OnButtonLookAhead();
	afx_msg void OnButtonBufMove();
	afx_msg void OnButtonBufGear();
	afx_msg void OnButtonRealMachining();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COORDINATEDLG_H__4DA6BB8F_35EA_4ABC_AC7D_71C4F894EB31__INCLUDED_)
