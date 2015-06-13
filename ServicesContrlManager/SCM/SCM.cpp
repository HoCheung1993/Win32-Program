// SCM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		std::cout << "OpenSCManager failed!\n";
		return 0;
	}

	DWORD ServiceCount = 0;
	DWORD dwSize = 0;
	LPENUM_SERVICE_STATUS lpInfo;

	BOOL bRet = EnumServicesStatus(hSCM, SERVICE_TYPE_ALL, SERVICE_STATE_ALL, NULL, 0, &dwSize, &ServiceCount, NULL);

	if (!bRet && GetLastError() == ERROR_MORE_DATA)
	{
		lpInfo = (LPENUM_SERVICE_STATUS)(new BYTE[dwSize]);
		bRet = EnumServicesStatus(hSCM, SERVICE_TYPE_ALL, SERVICE_STATE_ALL, (LPENUM_SERVICE_STATUS)lpInfo, dwSize, &dwSize, &ServiceCount, NULL);
		if (!bRet)
		{
			delete lpInfo;
			CloseServiceHandle(hSCM);
			return 0;
		}
	}

	for (DWORD i = 0; i < ServiceCount; i++)
	{
		if ((!strcmp("Wired AutoConfig", lpInfo[i].lpDisplayName) && (lpInfo[i].ServiceStatus.dwCurrentState == 4)))
		{
//			std::cout << lpInfo[i].lpDisplayName << " " << lpInfo[i].ServiceStatus.dwCurrentState << std::endl;
			SC_HANDLE hSCService = OpenService(hSCM, lpInfo[i].lpServiceName, SERVICE_ALL_ACCESS);
			SERVICE_STATUS ServiceStatus;
			BOOL bRet = ControlService(hSCService, SERVICE_CONTROL_STOP, &ServiceStatus);
			if (bRet)
			{
				std::cout << " stop succeed! \n";
			}
			else
			{
				std::cout << " stop failed! \n";
			}
			CloseServiceHandle(hSCService);
		}
	}
	CloseServiceHandle(hSCM);
	delete lpInfo;
	system("pause");
	return 0;
}

