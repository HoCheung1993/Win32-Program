// GetFreeSpace.h : main header file for the GETFREESPACE application
//

#if !defined(AFX_GETFREESPACE_H__7E709B0A_4B49_4D1B_9FD0_A8BC5064277E__INCLUDED_)
#define AFX_GETFREESPACE_H__7E709B0A_4B49_4D1B_9FD0_A8BC5064277E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGetFreeSpaceApp:
// See GetFreeSpace.cpp for the implementation of this class
//

class CGetFreeSpaceApp : public CWinApp
{
public:
	CGetFreeSpaceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetFreeSpaceApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGetFreeSpaceApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETFREESPACE_H__7E709B0A_4B49_4D1B_9FD0_A8BC5064277E__INCLUDED_)
