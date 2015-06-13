#pragma once



// CMyTread

class CMyTread : public CWinThread
{
	DECLARE_DYNCREATE(CMyTread)

protected:
	CMyTread();           // 动态创建所使用的受保护的构造函数
	virtual ~CMyTread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


