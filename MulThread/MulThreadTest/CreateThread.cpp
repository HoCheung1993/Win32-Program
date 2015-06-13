// CreateThread.cpp : implementation file
//

#include "stdafx.h"
#include "MulThreadTest.h"
#include "CreateThread.h"

extern UINT n;
// CCreateThread dialog

IMPLEMENT_DYNAMIC(CCreateThread, CDialog)

UINT CCreateThread::MulThreadFunc(LPVOID lpParam)							//线程函数,属于CCreateThread类的成员函数
{
	m_data* plp=(m_data *)lpParam;										//参数类型转化
	while(1)
	{
	  for(int pos=plp->m_pro.GetPos();pos<100;pos++)
		{
			(plp->m_pro).SetPos(pos);
			Sleep(100);
			if(plp->b)
			{
				ExitThread(0);
			}
		}	
	  plp->m_pro.SetPos(0);
	}
	return 0;
}

CCreateThread::CCreateThread(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateThread::IDD, pParent)
{
	check = FALSE;
}

CCreateThread::~CCreateThread()
{
}

void CCreateThread::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_d.m_pro);
}


BEGIN_MESSAGE_MAP(CCreateThread, CDialog)
	ON_BN_CLICKED(IDOK, &CCreateThread::OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CCreateThread message handlers
void CCreateThread::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_d.b = check;
	if(!check)
	{
		pThread=AfxBeginThread(MulThreadFunc,&m_d,0,0,4);				//创建新的线程	
		pThread->ResumeThread();										//开始执行
		GetDlgItem(IDOK)->SetWindowText(TEXT("暂停"));
		SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2), FALSE);
	}
	else
	{
		GetDlgItem(IDOK)->SetWindowText(TEXT("继续"));
		SetIcon(AfxGetApp()->LoadIcon(IDI_ICON3), FALSE);
	}
	check = !check;
}

void CCreateThread::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	CString showwin;
	showwin.Format(_T("Thread: %d"),n);
	SetWindowText(showwin);
	SetIcon(AfxGetApp()->LoadIcon(IDI_ICON4), FALSE);
}
