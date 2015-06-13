
// RandomNumberDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CRandomNumberDlg dialog
class CRandomNumberDlg : public CDialogEx
{
// Construction
public:
	CRandomNumberDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RANDOMNUMBER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnRandom;
	CButton m_btnRedo;
	CEdit m_editStart;
	CEdit m_editNum;
	CEdit m_editEnd;
	afx_msg void OnBnClickedBtnRandom();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_editResult;
	afx_msg void OnBnClickedBtnRedo();
};
