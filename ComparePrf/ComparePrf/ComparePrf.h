// ComparePrf.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CComparePrfApp:
// �йش����ʵ�֣������ ComparePrf.cpp
//

class CComparePrfApp : public CWinApp
{
public:
	CComparePrfApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CComparePrfApp theApp;