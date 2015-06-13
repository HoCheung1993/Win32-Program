#pragma once



// CNewWinThread

class CNewWinThread : public CWinThread
{
	DECLARE_DYNCREATE(CNewWinThread)

protected:
	CNewWinThread();           // protected constructor used by dynamic creation
	virtual ~CNewWinThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


