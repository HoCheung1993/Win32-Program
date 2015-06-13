#include "stdafx.h"
#include "ProcessKillCore.h"

E_RESULT CProcessKillCore::KillProcess(std::wstring ApplicationPath)
{
	ULONG ulSize = 0x1000;
	PSYSTEM_PROCESS_INFORMATION pSystemProcessInformation = (PSYSTEM_PROCESS_INFORMATION)malloc(ulSize);
	NTSTATUS status;
	int index = ApplicationPath.find_last_of(L"/\\");
	if (index == std::string::npos)
	{
		return FAIL;
	}
	std::wstring ApplicationName = ApplicationPath.substr(index + 1);
	WCHAR Path[MAX_PATH];

	NTQUERYSYSTEMINFORMATION NtQuerySystemInformation = (NTQUERYSYSTEMINFORMATION)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtQuerySystemInformation");
	if (NtQuerySystemInformation == NULL)
	{
		return FAIL;
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
			std::wstring temp(pSystemProcessInformation->ProcessName.Buffer);
			if (temp == ApplicationName)
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pSystemProcessInformation->dUniqueProcessId);
				if (hProcess == INVALID_HANDLE_VALUE)
				{
					return FAIL;
				}
				GetModuleFileNameEx(hProcess, NULL, Path, sizeof(Path));
				if (!wcscmp(Path, ApplicationPath.c_str()))
				{
					TerminateProcess(hProcess, 0);
				}
			}
		}
	}
	return SUCCESS;
}
