// IconChange.h : main header file for the ICONCHANGE application
//

#if !defined(AFX_ICONCHANGE_H__8F6EEDDF_C1E4_4C3A_B1E6_71D6AC48E28F__INCLUDED_)
#define AFX_ICONCHANGE_H__8F6EEDDF_C1E4_4C3A_B1E6_71D6AC48E28F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIconChangeApp:
// See IconChange.cpp for the implementation of this class
//

class CIconChangeApp : public CWinApp
{
public:
	CIconChangeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIconChangeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIconChangeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICONCHANGE_H__8F6EEDDF_C1E4_4C3A_B1E6_71D6AC48E28F__INCLUDED_)
