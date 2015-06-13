
// iniEncayptDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CiniEncayptDlg dialog
class CiniEncayptDlg : public CDialogEx
{
// Construction
public:
	CiniEncayptDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_INIENCAYPT_DIALOG };

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
	CEdit m_tb_sString;
	CEdit m_tb_dString;
	afx_msg void OnBnClickedBtnEncrypt();
	afx_msg void OnBnClickedBtnDecrypt();
	afx_msg void OnBnClickedBtnInput();
	afx_msg void OnBnClickedBtnOutput();
};

CString Encrypt(CString S, WORD Key);
CString Decrypt(CString S, WORD Key);
CStringW CStrA2CStrW(const CStringA &cstrSrcA);
CStringA CStrW2CStrA(const CStringW &cstrSrcW);