// FindProcess.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string.h>
using namespace std;

#define SystemProcessInformation 5  
#define NT_SUCCESS(x) ((x) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004


typedef NTSTATUS (WINAPI *NTQUERYSYSTEMINFORMATION)(
	_In_       ULONG SystemInformationClass,
	_Inout_    PVOID SystemInformation,
	_In_       ULONG SystemInformationLength,
	_Out_opt_  PULONG ReturnLength
	);

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;                 //注意，这里为Unicode类型
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _SYSTEM_PROCESS_INFORMATION
{
	DWORD NextEntryOffset;
	DWORD dThreadCount;
	DWORD dReserved01;
	DWORD dReserved02;
	DWORD dReserved03;
	DWORD dReserved04;
	DWORD dReserved05;
	DWORD dReserved06;
	FILETIME ftCreateTime; /* relative to 01-01-1601 */
	FILETIME ftUserTime; /* 100 nsec units */
	FILETIME ftKernelTime; /* 100 nsec units */
	UNICODE_STRING ProcessName;      //这就是进程名
	DWORD BasePriority;
	DWORD dUniqueProcessId;            //进程ID
	DWORD dParentProcessID;
	DWORD dHandleCount;
	DWORD dReserved07;
	DWORD dReserved08;
	DWORD VmCounters;
	DWORD dCommitCharge;
	PVOID ThreadInfos[1];
} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;


int _tmain(int argc, _TCHAR* argv[])
{
	ULONG ulSize = 0x1000;
	PSYSTEM_PROCESS_INFORMATION pSystemProcessInformation = (PSYSTEM_PROCESS_INFORMATION)malloc(ulSize);
	NTSTATUS status;
	setlocale(LC_ALL, "chs");

	NTQUERYSYSTEMINFORMATION NtQuerySystemInformation = (NTQUERYSYSTEMINFORMATION)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtQuerySystemInformation");
	if (NtQuerySystemInformation == NULL)
	{
		cout << "Loading NtQuerySystemInfomation Failed!";
		system("pause");
		return 0;
	}
	while ((status = NtQuerySystemInformation(SystemProcessInformation, pSystemProcessInformation, ulSize, &ulSize) == STATUS_INFO_LENGTH_MISMATCH))
	{
		pSystemProcessInformation = (PSYSTEM_PROCESS_INFORMATION)realloc(pSystemProcessInformation, ulSize);
	}
	while (pSystemProcessInformation->NextEntryOffset)
	{
		pSystemProcessInformation = (PSYSTEM_PROCESS_INFORMATION)((PCHAR)pSystemProcessInformation + pSystemProcessInformation->NextEntryOffset);
		if (pSystemProcessInformation->ProcessName.Length)
		{
			printf(
				"%d\t %.*S\n ",
				pSystemProcessInformation->dUniqueProcessId,
				pSystemProcessInformation->ProcessName.Length / 2,
				pSystemProcessInformation->ProcessName.Buffer
				);
		}	
	}

	system("pause");
	return 0;
}

