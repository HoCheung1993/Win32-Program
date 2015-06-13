
// AccessCtrlDlg.h : header file
//

#pragma once
typedef int E_RESULT;

// CAccessCtrlDlg dialog
class CAccessCtrlDlg : public CDialogEx
{
// Construction
public:
	CAccessCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ACCESSCTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	E_RESULT ExcuteSQL(CString strCmd);
	E_RESULT InitializeAccessTable(CString strTableName, CString strInitializeCommmd);
	E_RESULT WriteToAccessTable(CString strFilepath, CString strTableName, CString strStartTime, CString strEndTime);
	BOOL IsValidTime(CString time);
	BOOL IsBetweenRangeTime(CString strCheckTime, CString strStartTime, CString strEndTime);
	BOOL TimeCompare(CString strTimeStart, CString strTimeEnd);
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
