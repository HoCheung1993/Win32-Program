// GetFreeSpaceDlg.h : header file
//

#if !defined(AFX_GETFREESPACEDLG_H__DFE1FF65_464E_4633_A9A1_9C90BFBA48CD__INCLUDED_)
#define AFX_GETFREESPACEDLG_H__DFE1FF65_464E_4633_A9A1_9C90BFBA48CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGetFreeSpaceDlg dialog

class CGetFreeSpaceDlg : public CDialog
{
// Construction
public:
	int GetAllDiskSpaceInfo(__int64 *Totalspace,__int64*Totalfreespace);
	int GetDiskSpaceInfo(char cLogicdisk ,__int64* Totalspace,__int64* Totalfreespace);
	CGetFreeSpaceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGetFreeSpaceDlg)
	enum { IDD = IDD_GETFREESPACE_DIALOG };
	CString	m_totalspace;
	CString	m_totalfreespace;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetFreeSpaceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGetFreeSpaceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETFREESPACEDLG_H__DFE1FF65_464E_4633_A9A1_9C90BFBA48CD__INCLUDED_)
