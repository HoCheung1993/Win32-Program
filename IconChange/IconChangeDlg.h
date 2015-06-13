// IconChangeDlg.h : header file
//

#if !defined(AFX_ICONCHANGEDLG_H__D55947BD_F206_43D3_AA0E_27C1A9792A47__INCLUDED_)
#define AFX_ICONCHANGEDLG_H__D55947BD_F206_43D3_AA0E_27C1A9792A47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CIconChangeDlg dialog

class CIconChangeDlg : public CDialog
{
// Construction
public:
	UINT m_iTimerID;
	int m_iCountOfImage;
	int m_iMaxNumImage;
	HICON hIcon;
	CImageList m_imagelist;
	CIconChangeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIconChangeDlg)
	enum { IDD = IDD_ICONCHANGE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIconChangeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIconChangeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICONCHANGEDLG_H__D55947BD_F206_43D3_AA0E_27C1A9792A47__INCLUDED_)
