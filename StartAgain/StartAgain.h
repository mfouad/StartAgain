
// StartAgainV2.h : main header file for the StartAgainV2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CStartAgainV2:
// See StartAgainV2.cpp for the implementation of this class
//

class CStartAgainV2 : public CWinApp
{
public:
	CStartAgainV2();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CStartAgainV2 theApp;
