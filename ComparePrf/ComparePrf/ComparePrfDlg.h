// ComparePrfDlg.h : ͷ�ļ�
//

#pragma once


// CComparePrfDlg �Ի���
class CComparePrfDlg : public CDialog
{
// ����
public:
	CComparePrfDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COMPAREPRF_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButton1crd();
	afx_msg void OnBnClickedButton2crd();
	afx_msg void OnBnClickedButtonReset();
};
