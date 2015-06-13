// ToolHelp sample.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
using namespace std;

BOOL ListHeapWalking(DWORD dwOwnerPID)
{
	HEAPLIST32 hl;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, dwOwnerPID);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	ZeroMemory(&hl, sizeof(HEAPLIST32));
	hl.dwSize = sizeof(HEAPLIST32);
	if (Heap32ListFirst(hSnapshot,&hl))
	{
		do
		{
			HEAPENTRY32 he;
			ZeroMemory(&he, sizeof(HEAPENTRY32));
			he.dwSize = sizeof(HEAPENTRY32);
			if (Heap32First(&he, GetCurrentProcessId(), hl.th32HeapID))
			{
				cout << "Heap ID:"<<he.th32HeapID << endl;
				do
				{
					cout << "BlockSize:" << he.dwBlockSize << endl;
				} while (Heap32Next(&he));
			}
		} while (Heap32ListNext(hSnapshot, &hl));
	}
	CloseHandle(hSnapshot);
	return TRUE;
}

BOOL ListProcessWalking()
{
	PROCESSENTRY32 pe;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	ZeroMemory(&pe, sizeof(PROCESSENTRY32));
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnapshot, &pe))
	{
		CloseHandle(hSnapshot);
		return FALSE;
	}
	do 
	{
		printf("\n-----------------------------------------------------");
		printf("\n  PROCESS NAME:     = %s", pe.szExeFile);
		printf("\n  parent process ID = 0x%08X", pe.th32ParentProcessID);
		printf("\n  process ID        = 0x%08X", pe.th32ProcessID);
		printf("\n  thread count      = %d", pe.cntThreads);
		printf("\n  Priority Base     = %d", pe.pcPriClassBase);
	} while (Process32Next(hSnapshot,&pe));

	CloseHandle(hSnapshot);
	return TRUE;
}

BOOL ListTreadWalking(DWORD dwOwnerPID)
{
	THREADENTRY32 te;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwOwnerPID);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	ZeroMemory(&te, sizeof(THREADENTRY32));
	te.dwSize = sizeof(THREADENTRY32);
	if (!Thread32First(hSnapshot,&te))
	{
		CloseHandle(hSnapshot);
		return FALSE;
	}
	do 
	{
		if (te.th32OwnerProcessID == dwOwnerPID)
		{
			printf("\n\n     THREAD ID      = 0x%08X", te.th32ThreadID);
			printf("\n     base priority  = %d", te.tpBasePri);
			printf("\n     delta priority = %d", te.tpDeltaPri);
		}
	} while (Thread32Next(hSnapshot,&te));
	CloseHandle(hSnapshot);
	return TRUE;
}

BOOL ListModuleWalking(DWORD dwOwnerPID)
{
	MODULEENTRY32 me;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwOwnerPID);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	ZeroMemory(&me,sizeof(MODULEENTRY32));
	me.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(hSnapshot,&me))
	{
		CloseHandle(hSnapshot);
		return FALSE;
	}
	do 
	{
		printf("\n\n     MODULE NAME:     %s", me.szModule);
		printf("\n     executable     = %s", me.szExePath);
		printf("\n     process ID     = 0x%08X", me.th32ProcessID);
		printf("\n     ref count (g)  =     0x%04X", me.GlblcntUsage);
		printf("\n     ref count (p)  =     0x%04X", me.ProccntUsage);
		printf("\n     base address   = 0x%08X", (DWORD)me.modBaseAddr);
		printf("\n     base size      = %d", me.modBaseSize);
	} while (Module32Next(hSnapshot,&me));
	CloseHandle(hSnapshot);
	return TRUE;
}


int _tmain(int argc, _TCHAR* argv[])
{
//	ListHeapWalking(GetCurrentProcessId());
//	ListProcessWalking();
//	ListTreadWalking(GetCurrentProcessId());
	ListModuleWalking(GetCurrentProcessId());
	system("pause");
	return 0;
}

