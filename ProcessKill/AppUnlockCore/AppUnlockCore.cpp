// AppUnlockCore.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string.h>
#include "ProcessKillCore.h"
using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	CProcessKillCore::KillProcess(L"C:\\Users\\Jovi\\Desktop\\ÎÄ¼þ·ÛËé»ú\\FileCleaner.exe");
	return 0;
}
