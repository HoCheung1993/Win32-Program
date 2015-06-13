
// AccessCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AccessCtrl.h"
#include "AccessCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAccessCtrlDlg dialog

CAccessCtrlDlg::CAccessCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAccessCtrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAccessCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAccessCtrlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAccessCtrlDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAccessCtrlDlg message handlers

BOOL CAccessCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAccessCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAccessCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAccessCtrlDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	InitializeAccessTable(L"user1", L"Dt DATETIME,OpenP CURRENCY,HighP CURRENCY,LowP CURRENCY,CloseP CURRENCY,Volume INTEGER,AdjCloseP CURRENCY");
	WriteToAccessTable(L"C:\\Users\\Jovi\\Desktop\\AccessCtrl\\Debug\\000001_sz", L"user1", L"2015-5-1", L"2015-6-3");
}

E_RESULT CAccessCtrlDlg::ExcuteSQL(CString strCmd)
{
	_variant_t RecordsAffected;
	try
	{
		theApp.m_pConnection->Execute(strCmd.GetBuffer(), &RecordsAffected, adCmdText);
	}
	catch (_com_error &e)
	{
		AfxMessageBox(L"SQL语句执行错误：" + e.Description());
	}
	return TRUE;
}
E_RESULT CAccessCtrlDlg::InitializeAccessTable(CString strTableName, CString strInitializeCommmd)
{
	CString strSql = L"DROP TABLE ";
	strSql.Append(strTableName);
	_variant_t RecordsAffected;
	try
	{
		theApp.m_pConnection->Execute(strSql.GetBuffer(), &RecordsAffected, adCmdText);
	}
	catch (_com_error )
	{
		//判断表是否存在
//		AfxMessageBox(e.Description());
	}
	strSql = L"CREATE TABLE ";
	strSql.Append(strTableName);
	strSql.Append(L"(");
	strSql.Append(strInitializeCommmd);
	strSql.Append(L")");
	try
	{
		theApp.m_pConnection->Execute(strSql.GetBuffer(), &RecordsAffected, adCmdText);
	}
	catch (_com_error &e)
	{
		AfxMessageBox(L"表初始化失败：" + e.Description());
	}
	return TRUE;
}
E_RESULT CAccessCtrlDlg::WriteToAccessTable(CString strFilepath, CString strTableName, CString strStartTime, CString strEndTime)
{
	CStdioFile sfile;
	if (!sfile.Open(strFilepath, CStdioFile::modeRead | CStdioFile::typeText))
	{
		return FALSE;
	}
	CString temp;
	sfile.ReadString(temp);
	if (temp != L"Date,Open,High,Low,Close,Volume,Adj Close")
	{
		//非正常数据文件
		return FALSE;
	}
	while (sfile.ReadString(temp))
	{
		CString date;
		float open, high, low, close, adjclose;
		LONG volume;
		int pos = temp.Find(',');
		if (pos == -1)
		{
			return FALSE;
		}
		date = temp.Mid(0, pos);
		if (!IsValidTime(date))
		{
			return FALSE;
		}
		//判断时间是否在开始期之前
		if (!TimeCompare(strStartTime,date))
		{
			break;
		}
		//判断时间范围
		if (!IsBetweenRangeTime(date, strStartTime, strEndTime))
		{
			continue;
		}		
		temp = temp.Mid(pos);
		if (swscanf_s(temp.GetBuffer(temp.GetLength()), L",%f,%f,%f,%f,%ld,%f", &open, &high, &low, &close, &volume, &adjclose) != 6)
		{
			return FALSE;
		}
		CString sql;
		sql.Format(L"Insert into " + strTableName + L"(Dt,OpenP,HighP,LowP,CloseP,Volume,AdjCloseP)values('" + date + "',%f,%f,%f,%f,%ld,%f)", open, high, low, close, volume, adjclose);
		ExcuteSQL(sql);
	}
	return TRUE;
}


BOOL CAccessCtrlDlg::IsBetweenRangeTime(CString strCheckTime, CString strStartTime, CString strEndTime)
{
	if (TimeCompare(strStartTime,strCheckTime) && TimeCompare(strCheckTime,strEndTime))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CAccessCtrlDlg::IsValidTime(CString time)
{
	int nYear, nMonth, nDay;
	if (swscanf_s(time.GetBuffer(time.GetLength()), L"%d-%d-%d", &nYear, &nMonth, &nDay) != 3)
	{
		return FALSE;
	}
	COleDateTime dt;
	if (dt.SetDate(nYear, nMonth, nDay))
	{
		//判断日期合法
		return FALSE;
	}
	return TRUE;
}

BOOL CAccessCtrlDlg::TimeCompare(CString strTimeStart, CString strTimeEnd)
{
	int nYear, nMonth, nDay;
	if (swscanf_s(strTimeStart.GetBuffer(strTimeStart.GetLength()), L"%d-%d-%d", &nYear, &nMonth, &nDay) != 3)
	{
		return FALSE;
	}
	CTime  time1(nYear, nMonth, nDay, 0, 0, 0);
	if (swscanf_s(strTimeEnd.GetBuffer(strTimeEnd.GetLength()), L"%d-%d-%d", &nYear, &nMonth, &nDay) != 3)
	{
		return FALSE;
	}
	CTime  time2(nYear, nMonth, nDay, 0, 0, 0);
	CTimeSpan ts = time2 - time1;
	if (ts < 0)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}