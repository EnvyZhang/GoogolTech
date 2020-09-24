
// Crd_GSN.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCrd_GSNApp:
// See Crd_GSN.cpp for the implementation of this class
//

class CCrd_GSNApp : public CWinApp
{
public:
	CCrd_GSNApp();
	bool aHead = false;
	bool newAhead = false;
	bool oldAhead = false;
	bool watchOn = false;
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCrd_GSNApp theApp;