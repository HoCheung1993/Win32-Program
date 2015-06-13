
// RandomNumberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RandomNumber.h"
#include "RandomNumberDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <vector>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRandomNumberDlg dialog



CRandomNumberDlg::CRandomNumberDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRandomNumberDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRandomNumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_RANDOM, m_btnRandom);
	DDX_Control(pDX, IDC_BTN_REDO, m_btnRedo);
	DDX_Control(pDX, IDC_EDIT_END, m_editEnd);
	DDX_Control(pDX, IDC_EDIT_NUM, m_editNum);
	DDX_Control(pDX, IDC_EDIT_START, m_editStart);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_editResult);
}

BEGIN_MESSAGE_MAP(CRandomNumberDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RANDOM, &CRandomNumberDlg::OnBnClickedBtnRandom)
	ON_BN_CLICKED(IDC_BTN_REDO, &CRandomNumberDlg::OnBnClickedBtnRedo)
END_MESSAGE_MAP()


// CRandomNumberDlg message handlers

BOOL CRandomNumberDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	srand((unsigned int )time(NULL));         //生成种子 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRandomNumberDlg::OnPaint()
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
HCURSOR CRandomNumberDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRandomNumberDlg::OnBnClickedBtnRandom()
{
	// TODO: Add your control notification handler code here
	CString strStart, strEnd, strNum;
	m_editStart.GetWindowText(strStart);
	m_editEnd.GetWindowText(strEnd);
	m_editNum.GetWindowText(strNum);
	m_editResult.SetWindowText(L"");


	INT64 iStart = 0, iEnd = 0, iNum = 0;
	iStart = _ttoi64(strStart);
	iEnd = _ttoi64(strEnd);
	iNum = _ttoi64(strNum);


	if (iStart <= 0 || iEnd <= 0 || iNum <= 0)
	{
		MessageBox(L"为什么不能够正确输入？", L"错误", MB_OK | MB_ICONINFORMATION);
		return;
	}

	if (iEnd <= iStart)
	{
		MessageBox(L"请给我个正确的范围", L"错误", MB_OK | MB_ICONINFORMATION);
		return;
	}

	if (iNum >  iEnd - iStart + 1 )
	{
		MessageBox(L"请给我个正确的抽取数量", L"错误", MB_OK | MB_ICONINFORMATION);
		return;
	}

	size_t len = (size_t)(iEnd - iStart);
	vector<UINT64> vecNum;
	for (size_t i = 0; i <= len; i++)
	{
		vecNum.push_back(i + iStart);
	}
	
	size_t nRange = len;
	size_t nRandomCount = 0;
	while (nRandomCount < iNum )
	{
		size_t index = 0;
		UINT64 Num = vecNum[index];
		if (nRange - nRandomCount != 0 )
		{
			index = rand() % (nRange - nRandomCount);
			Num = vecNum[index];
			swap(vecNum[index], vecNum[nRange - nRandomCount]);
		}
		CString temp;
		m_editResult.GetWindowText(temp);
		CString temp2;
		temp2.Format(L"%I64d\t", Num);
		temp.Append(temp2);
		if ((nRandomCount + 1) % 3 == 0)
		{
			temp.Append(L"\r\n");
		}
		m_editResult.SetWindowText(temp);
		nRandomCount++;
	}
}

BOOL CRandomNumberDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN   &&   pMsg->wParam == VK_ESCAPE)     return   TRUE;
	if (pMsg->message == WM_KEYDOWN   &&   pMsg->wParam == VK_RETURN)   return   TRUE;
	else
		return CDialogEx::PreTranslateMessage(pMsg);
}


void CRandomNumberDlg::OnBnClickedBtnRedo()
{
	// TODO: Add your control notification handler code here
	m_editResult.SetWindowText(L"");
}
