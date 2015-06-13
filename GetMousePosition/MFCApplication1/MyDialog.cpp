// MyDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MyDialog.h"
#include "afxdialogex.h"


// MyDialog 对话框

IMPLEMENT_DYNAMIC(MyDialog, CDialog)

MyDialog::MyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(MyDialog::IDD, pParent)
	, m_str(_T("测试"))
{
	
}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_str);
}


BEGIN_MESSAGE_MAP(MyDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &MyDialog::OnBnClickedButton1)
	ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTTON2, &MyDialog::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON3, &MyDialog::OnBnClickedButton3)
ON_EN_CHANGE(IDC_EDIT2, &MyDialog::OnChangeEdit2)
ON_WM_CREATE()
END_MESSAGE_MAP()


// MyDialog 消息处理程序


void MyDialog::OnBnClickedButton1()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);
	MessageBox(str, _T("获取文本"), MB_OK);
	// TODO:  在此添加控件通知处理程序代码
}


void MyDialog::OnMouseMove(UINT nFlags, CPoint point)
{
	SetTimer(1, 1, NULL);//计时器方法 计时器编号，间隔时间，回调函数默认OnTimer

	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CWnd * pWnd = GetDlgItem(IDC_Posation1);
	CString str;
	str.Format(_T("X:%ld,Y:%ld"), point.x,point.y);
	pWnd->SetWindowTextW(str);

	CWnd * pWnd2 = GetDlgItem(IDC_Posation2);
	CString str2;
	CPoint point2;
	GetCursorPos(&point2);
	str2.Format(_T("X:%ld,Y:%ld"), point2.x, point2.y);
	pWnd2->SetWindowTextW(str2);


	CDialog::OnMouseMove(nFlags, point);
}


void MyDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	this->SetCapture();
	CDialog::OnLButtonDown(nFlags, point);
}


void MyDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	::ReleaseCapture();
	CDialog::OnLButtonUp(nFlags, point);
}


void MyDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CWnd * pWnd2 = GetDlgItem(IDC_Posation3);
	CString str2;
	CPoint point2;
	GetCursorPos(&point2);
	str2.Format(_T("X:%ld,Y:%ld"), point2.x, point2.y);
	pWnd2->SetWindowTextW(str2);
	CDialog::OnTimer(nIDEvent);
}


void MyDialog::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	KillTimer(1);
}




void MyDialog::OnBnClickedButton3()
{
	UpdateData();
	// TODO:  在此添加控件通知处理程序代码
	CWnd * pWnd = GetDlgItem(IDC_TEXT);
	MessageBox(m_str, _T("获取文本"), MB_OK);
	pWnd->SetWindowTextW(m_str);
}


void MyDialog::OnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData();
	CWnd * pWnd = GetDlgItem(IDC_TEXT);
	pWnd->SetWindowTextW(m_str);
	// TODO:  在此添加控件通知处理程序代码
}


int MyDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	// 修改窗体图标
	HICON hicon = AfxGetApp()->LoadIcon(IDI_ICON2);
	SetIcon(hicon,TRUE);
	SetIcon(hicon, FALSE);
	return 0;
}
