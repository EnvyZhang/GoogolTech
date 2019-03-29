// coordinate.h : main header file for the COORDINATE application
//

#if !defined(AFX_COORDINATE_H__4FDAF048_6002_4B4B_96D3_340FA9B0AE56__INCLUDED_)
#define AFX_COORDINATE_H__4FDAF048_6002_4B4B_96D3_340FA9B0AE56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCoordinateApp:
// See coordinate.cpp for the implementation of this class
//

class CCoordinateApp : public CWinApp
{
public:
	CCoordinateApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoordinateApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCoordinateApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COORDINATE_H__4FDAF048_6002_4B4B_96D3_340FA9B0AE56__INCLUDED_)
