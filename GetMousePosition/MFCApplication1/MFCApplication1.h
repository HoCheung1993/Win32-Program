
// MFCApplication1.h : MFCApplication1 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// MFCApp:
// 有关此类的实现，请参阅 MFCApplication1.cpp
//

class MFCApp : public CWinApp
{
public:
	MFCApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

public:
	DECLARE_MESSAGE_MAP()
};

extern MFCApp theApp;
