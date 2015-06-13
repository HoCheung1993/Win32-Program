#pragma once
#include "afxwin.h"


// CheckCodeDlg 对话框

class CheckCodeDlg : public CDialog
{
	DECLARE_DYNAMIC(CheckCodeDlg)

public:
	CheckCodeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CheckCodeDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtCheckCode;
	CImage m_image;
	afx_msg void OnPaint();
	virtual void OnOK();
};
