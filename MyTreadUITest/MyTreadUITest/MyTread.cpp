// MyTread.cpp : 实现文件
//

#include "stdafx.h"
#include "MyTreadUITest.h"
#include "MyTread.h"
#include "TreadDlg.h"


// CMyTread

IMPLEMENT_DYNCREATE(CMyTread, CWinThread)

CMyTread::CMyTread()
{
}

CMyTread::~CMyTread()
{
}

BOOL CMyTread::InitInstance()
{
	// TODO:    在此执行任意逐线程初始化
	CTreadDlg *dlg =new CTreadDlg;
	dlg->Create(IDD_DIALOG1);
	dlg->ShowWindow(SW_SHOW);
	return TRUE;
}

int CMyTread::ExitInstance()
{
	// TODO:    在此执行任意逐线程清理
	delete this;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMyTread, CWinThread)
END_MESSAGE_MAP()


// CMyTread 消息处理程序
