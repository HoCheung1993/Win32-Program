// CreateFolder.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
void main(void)
{
	SECURITY_ATTRIBUTES sa;  //和文件有关的安全结构
	SECURITY_DESCRIPTOR sd;  //声明一个SD
	BYTE aclBuffer[1024];
	PACL pacl = (PACL)&aclBuffer; //声明一个ACL，长度是1024
	BYTE sidBuffer[100];
	PSID psid = (PSID)&sidBuffer;  //声明一个SID，长度是100
	DWORD sidBufferSize = 100;
	char domainBuffer[80];
	DWORD domainBufferSize = 80;
	SID_NAME_USE snu;
	HANDLE file;
	//初始化一个SD
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	//初始化一个ACL
	InitializeAcl(pacl, 1024, ACL_REVISION);
	//查找一个用户hchen，并取该用户的SID
	LookupAccountName(0, "Guest", psid,
		&sidBufferSize, domainBuffer,
		&domainBufferSize, &snu);
	//设置该用户的Access-Allowed的ACE，其权限为“所有权限”
	AddAccessAllowedAce(pacl, ACL_REVISION, GENERIC_WRITE, psid);
	//把ACL设置到SD中
	SetSecurityDescriptorDacl(&sd, TRUE, pacl, FALSE);

	//把SD放到文件安全结构SA中
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = FALSE;
	sa.lpSecurityDescriptor = &sd;

	//创建文件
	file = CreateFile("D:\\testfile",
		0, 0, &sa, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
	CloseHandle(file);
	system("pause");
}
