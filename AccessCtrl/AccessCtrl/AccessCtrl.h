
// AccessCtrl.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAccessCtrlApp:
// See AccessCtrl.cpp for the implementation of this class
//

class CAccessCtrlApp : public CWinApp
{
public:
	CAccessCtrlApp();
	_ConnectionPtr m_pConnection;
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAccessCtrlApp theApp;