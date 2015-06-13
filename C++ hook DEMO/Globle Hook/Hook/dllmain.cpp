// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <tchar.h>

HINSTANCE g_hInstance;
HHOOK g_hKeybord;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	g_hInstance = hModule;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


//Keyboard Hook Procedure
LRESULT CALLBACK MyKeyboardProc(int code,
	WPARAM wParam,
	LPARAM lParam
	)
{
	if (VK_SPACE == wParam)
	{
		//It is going to occur for 2 times ,Just from WM_KEYDOWN and WM_CHAR ,WM_CHAR is produced when DefWndProc is running,TranslateMessage function too.
		//MessageBox(NULL, _T("123"), _T("456"), MB_OK);  
		return 1;
	}
	return CallNextHookEx(g_hKeybord,WH_KEYBOARD,wParam,lParam);
}


VOID Sethook()
{
	g_hKeybord = SetWindowsHookEx(WH_KEYBOARD, MyKeyboardProc, g_hInstance/*GetModuleHandle("Hook")*/, 0);
}

VOID Unhook()
{
	UnhookWindowsHookEx(g_hKeybord);
}