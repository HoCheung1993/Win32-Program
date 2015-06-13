// NewWinThread.cpp : implementation file
//

#include "stdafx.h"
#include "MulThreadTest.h"
#include "NewWinThread.h"
#include "CreateThread.h"


// CNewWinThread

IMPLEMENT_DYNCREATE(CNewWinThread, CWinThread)

CNewWinThread::CNewWinThread()
{
}

CNewWinThread::~CNewWinThread()
{
}

BOOL CNewWinThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	CCreateThread *pDlg;
	pDlg = new CCreateThread;
	pDlg->Create(IDD_DIALOG1);								//创建非模态对话框
	pDlg->ShowWindow(SW_SHOW);								//显示对话
	return TRUE;
}

int CNewWinThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	delete this;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CNewWinThread, CWinThread)
END_MESSAGE_MAP()


// CNewWinThread message handlers
