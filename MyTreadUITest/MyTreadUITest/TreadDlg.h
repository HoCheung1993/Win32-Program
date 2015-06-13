#pragma once
#include "afxwin.h"



struct m_data //传递参数
{
	CStatic cont;
};

// CTreadDlg 对话框

class CTreadDlg : public CDialog
{
	DECLARE_DYNAMIC(CTreadDlg)

public:
	CTreadDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTreadDlg();
	CWinThread * pWorkThread;
	static UINT MulThreadFunc(LPVOID lpParam); //定义为静态函数使进程能够使用该函数
	m_data data;

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
