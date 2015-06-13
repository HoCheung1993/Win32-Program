
// Leave MessagesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Leave Messages.h"
#include "Leave MessagesDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLeaveMessagesDlg 对话框


CLeaveMessagesDlg::CLeaveMessagesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLeaveMessagesDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLeaveMessagesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_edtMsg, m_edtGetMsg);
	DDX_Control(pDX, IDC_edtName, m_edtName);
	DDX_Control(pDX, IDC_edtsendMSG, m_edtsenMsg);
}

BEGIN_MESSAGE_MAP(CLeaveMessagesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_btnGetMsg, &CLeaveMessagesDlg::OnBnClickedbtngetmsg)
	ON_BN_CLICKED(IDC_btnSendMsg, &CLeaveMessagesDlg::OnBnClickedbtnsendmsg)
	ON_BN_CLICKED(IDC_btnRefresh, &CLeaveMessagesDlg::OnBnClickedbtnrefresh)
END_MESSAGE_MAP()


// CLeaveMessagesDlg 消息处理程序

BOOL CLeaveMessagesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_bConneted = FALSE;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLeaveMessagesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLeaveMessagesDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLeaveMessagesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLeaveMessagesDlg::OnBnClickedbtngetmsg()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strGetmsg;
	CHttp http;
	CString strXm,strNr,strSj,strNum; //名字，内容，时间，数量
	CString strNextUrl="",strFistUrl;
	int iStart,iEnd;
	strGetmsg = http.get("http://www.ys168.com/ht/login.aspx");
	CheckCodeDlg dlg;
	dlg.m_image = *http.GetImg("http://www.ys168.com/ht/sjzx/ys_vf_img.aspx?lx=htdl&sj=2014-9-24%2014:10:34");
	dlg.DoModal();
	http.post("http://www.ys168.com/ht/login.aspx?dlmc=hx1993", " ", "__VIEWSTATE=%2FwEPDwULLTE1MjE0MTMwMDRkZDhFgZHvoK43hqajyGzBvbR8au2ToMVjK7T86vmOkEtz&__VIEWSTATEGENERATOR=D52EB38E&__EVENTVALIDATION=%2FwEWBQLwisq4DALxl%2FvQBQKMgZnmDwKn6rb7CQLzl5fRBSDBZw1ezgebemz0U6uYyF4yRyZMR9ADkNAAQZ2VicBG&dl1=hx1993&dl2=19930807&dl3=" + strCheckCode + "&bu1=+%B5%C7+%C2%BC+");
	strGetmsg = http.get("http://www.ys168.com/ht/qt/ly.aspx");
	//已获取全部HTML代码

	//搜索数量和最高ID函数,中文2个字节
	iStart = strGetmsg.Find("name='name");
	iStart += 10;
	iEnd = strGetmsg.Find("'", iStart);
	strMaxID = strGetmsg.Mid(iStart, iEnd - iStart);

	iStart = strGetmsg.Find("共", iEnd);
	iStart += 2;
	iEnd = strGetmsg.Find("条记录", iStart);
	strNum = strGetmsg.Mid(iStart, iEnd - iStart);

	//进行搜索遍历聊天内容

	int MaxID = atoi(strMaxID);
	int num = atoi(strNum);
	num = (int)(num*0.02) + 1;  //获得页数，一页50个
	if (num > 10)
	{
		num = 10;
	}

	strGetmsg = http.get("http://www.ys168.com/ht/qt/ly.aspx");
	for (int i = 0; i < num; i++)
	{
		iStart = 0;
		do
		{
			iStart = strGetmsg.Find("title='选中/不选'></td><td>", iStart);
			iStart += 27;
			iEnd = strGetmsg.Find("<", iStart);
			strXm = strGetmsg.Mid(iStart, iEnd - iStart);

			iStart = strGetmsg.Find("<td style='word-break:break-all;'>", iEnd);
			iStart = strGetmsg.Find(">", iStart);
			iStart += 1;
			iEnd = strGetmsg.Find("</td>", iStart);
			strNr = strGetmsg.Mid(iStart, iEnd - iStart);
			strNr.Replace("<br>", "\r\n     ");

			iStart = strGetmsg.Find("<td>", iEnd);
			iStart += 4;
			iEnd = strGetmsg.Find("<", iStart);
			strSj = strGetmsg.Mid(iStart, iEnd - iStart);

			iStart = strGetmsg.Find("title='选中/不选'></td><td>", iStart);
			CString strTemp;
			m_edtGetMsg.GetWindowText(strTemp);
			m_edtGetMsg.SetWindowText(strTemp + strXm + "  (" + strSj + ")\r\n" + "     " + strNr + "\r\n");
		} while (iStart != -1);
		if (strGetmsg.Find("'>下页</a>")!=-1)
		{
			iEnd = strGetmsg.Find("'>下页</a>");
			strGetmsg = strGetmsg.Mid(0, iEnd);
			iStart = strGetmsg.ReverseFind('\'');
			strNextUrl = strGetmsg.Mid(iStart + 1, iEnd - iStart);
			strGetmsg = http.get("http://www.ys168.com/ht/qt/ly.aspx" + strNextUrl);
		}
		else
			break;
	}
}


void CLeaveMessagesDlg::OnBnClickedbtnsendmsg()
{
	if (!m_bConneted)
	{
		OnBnClickedbtngetmsg();
		m_bConneted = TRUE;
	}
	// TODO:  在此添加控件通知处理程序代码
	CString strGetmsg;
	CHttp http;
	CString strName;
	m_edtName.GetWindowText(strName);
	CString strNr;
	m_edtsenMsg.GetWindowText(strNr);
	int iStart, iEnd;
	strGetmsg = http.get("http://hx1993.ys168.com/");
	iStart = strGetmsg.Find("http://c3.ys168.com/Ccenter.aspx?z=");
	iEnd = strGetmsg.Find("\"", iStart);
	strRadomUrl = strGetmsg.Mid(iStart, iEnd - iStart);

	//登录后台留言不要验证码，为什么JS弹窗验证码这么难搞
	strGetmsg = http.post(strRadomUrl," ", "Yz0=gly_dl&Yz1=19930807&Yz2=&Yz3=&Yz4=");
	strGetmsg = http.get(strRadomUrl);
	strGetmsg = http.post(strRadomUrl, " ", "Yz0=lytj&Yz1=n1&Yz2="+strName+"&Yz3="+strNr+"&Yz4=");
	m_edtsenMsg.SetWindowText("");
	m_edtName.SetWindowText("");
	OnBnClickedbtnrefresh();
}


void CLeaveMessagesDlg::OnBnClickedbtnrefresh()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strResult="";
	CInternetSession mySession(NULL, 0);
	CHttpFile* myHttpFile = NULL;
	CString myData;
	CString strURL = strRadomUrl;
	CString strXm, strNr, strSj; //名字，内容，时间
	CString strID;  //对比ID大小
	int iStart, iEnd;
	myHttpFile = (CHttpFile*)mySession.OpenURL(strURL);
	while (myHttpFile->ReadString(myData))
	{
		strResult = strResult + " ";
		strResult += myData;
	}
	myHttpFile->Close();
	mySession.Close();

	iStart = strResult.Find("Xm_");
	iStart += 3;
	iEnd = strResult.Find("'", iStart);
	strID = strResult.Mid(iStart, iEnd - iStart);

	if (atoi(strID) - atoi(strMaxID) > 0)
	{
		iStart = strResult.Find(">", iStart);
		iStart += 1;
		iEnd = strResult.Find("<", iStart);
		strXm = strResult.Mid(iStart, iEnd - iStart);

		iStart = strResult.Find("Nr", iEnd);
		iStart = strResult.Find(">", iStart);
		iStart += 1;
		iEnd = strResult.Find("</span>", iStart);
		strNr = strResult.Mid(iStart, iEnd - iStart);
		strNr.Replace("<br>", "\r\n     ");

		iStart = strResult.Find("<label>", iEnd);
		iStart += 7;
		iEnd = strResult.Find("<", iStart);
		strSj = strResult.Mid(iStart, iEnd - iStart);

		CString strTemp;
		m_edtGetMsg.GetWindowText(strTemp);
		m_edtGetMsg.SetWindowText(strXm + "  (" + strSj + ")\r\n" + "     " + strNr + "\r\n" + strTemp );
		strMaxID = strID;
	}
}
