// CheckCodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Leave Messages.h"
#include "CheckCodeDlg.h"
#include "afxdialogex.h"
#include "Leave MessagesDlg.h"

// CheckCodeDlg 对话框

IMPLEMENT_DYNAMIC(CheckCodeDlg, CDialog)

CheckCodeDlg::CheckCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CheckCodeDlg::IDD, pParent)
{

}

CheckCodeDlg::~CheckCodeDlg()
{
}

void CheckCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtCheckCode);
}


BEGIN_MESSAGE_MAP(CheckCodeDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CheckCodeDlg 消息处理程序


void CheckCodeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	m_image.Draw(dc.m_hDC, 0, 0);
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}


void CheckCodeDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	CLeaveMessagesDlg * parent = (CLeaveMessagesDlg*)GetParent();
	CString str;
	this->m_edtCheckCode.GetWindowText(str);//获取当前子窗口编辑框中的值
	parent->strCheckCode=str;//把当前编辑框中的值回传给父窗口
	CDialog::OnOK();
}
