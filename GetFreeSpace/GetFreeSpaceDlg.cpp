// GetFreeSpaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetFreeSpace.h"
#include "GetFreeSpaceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetFreeSpaceDlg dialog

CGetFreeSpaceDlg::CGetFreeSpaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetFreeSpaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetFreeSpaceDlg)
	m_totalspace = _T("");
	m_totalfreespace = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetFreeSpaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetFreeSpaceDlg)
	DDX_Text(pDX, IDC_EDIT1, m_totalspace);
	DDX_Text(pDX, IDC_EDIT3, m_totalfreespace);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetFreeSpaceDlg, CDialog)
	//{{AFX_MSG_MAP(CGetFreeSpaceDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetFreeSpaceDlg message handlers

BOOL CGetFreeSpaceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	__int64 logicspace=0,logicfreespace=0; //容量参数
	__int64 totalspace=0,totalfreespace=0;
	//获取单独一个盘
	GetDiskSpaceInfo(NULL,&logicspace,&logicfreespace); //系统盘
	GetAllDiskSpaceInfo(&totalspace,&totalfreespace); //全部盘

	CString str_logicspace;
	str_logicspace.Format("%u MB",logicspace);
	CString str_logicfreespace;
	str_logicfreespace.Format("%u MB",logicfreespace);
	CString str_totalspace;
	str_totalspace.Format("%u MB",totalspace);
	CString str_totalfreespace;
	str_totalfreespace.Format("%u MB",totalfreespace);

	GetDlgItem(IDC_EDIT1)->SetWindowText(str_logicspace);
	GetDlgItem(IDC_EDIT3)->SetWindowText(str_logicfreespace);
	GetDlgItem(IDC_EDIT2)->SetWindowText(str_totalspace);
	GetDlgItem(IDC_EDIT4)->SetWindowText(str_totalfreespace);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGetFreeSpaceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGetFreeSpaceDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGetFreeSpaceDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


int CGetFreeSpaceDlg::GetDiskSpaceInfo(char cLogicdisk, __int64 *Totalspace, __int64 *Totalfreespace)
{
	DWORD SectorsPerCluster,BytesPerSector,NumberOfFreeClusters,TotalNumberOfClusters;
	char buf[3];
	LPCSTR lpclogicdisk =NULL;
	if (cLogicdisk!=NULL)
	{
		buf[0]=cLogicdisk;
		buf[1]=':';
		buf[2]='\0';
	    lpclogicdisk=buf;
	}
	GetDiskFreeSpace(lpclogicdisk,&SectorsPerCluster,//一个簇内的扇区数
			&BytesPerSector, //一个扇区内的字节数
			&NumberOfFreeClusters, //剩余簇数
			&TotalNumberOfClusters //总簇数
			); //获取系统盘空间
	*Totalspace = (__int64)SectorsPerCluster*BytesPerSector*TotalNumberOfClusters/(1024*1024);
	*Totalfreespace = (__int64)SectorsPerCluster*BytesPerSector*NumberOfFreeClusters/(1024*1024);
	return 0;
}

int CGetFreeSpaceDlg::GetAllDiskSpaceInfo(__int64 *Totalspace, __int64 *Totalfreespace)
{
	for (char i = 'a';i<'z';i++)
	{
		__int64 tspace=0;
		__int64 tfreespace=0;
		GetDiskSpaceInfo(i,&tspace,&tfreespace);
		*Totalspace+=tspace;
		*Totalfreespace+=tfreespace;
	}
	return 0;
}
