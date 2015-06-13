
// Leave MessagesDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "Http.h"
#include "CheckCodeDlg.h"

// CLeaveMessagesDlg 对话框
class CLeaveMessagesDlg : public CDialogEx
{
// 构造
public:
	CLeaveMessagesDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LEAVEMESSAGES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedbtngetmsg();
	CEdit m_edtGetMsg;
	CEdit m_edtName;
	CEdit m_edtsenMsg;
	CString strRadomUrl;
	CString strCheckCode;
	CString strMaxID;  //获取最新消息标识符
	afx_msg void OnBnClickedbtnsendmsg();
	afx_msg void OnBnClickedbtnrefresh();
	BOOL m_bConneted;
};
