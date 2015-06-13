#pragma once
#include <windows.h>

#define NT_SUCCESS(x) ((NTSTATUS)(x)>=0) 
#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004


//enum 需要的类型
#define SystemHandleInformation 16
#define ObjectBasicInformation 0
#define ObjectNameInformation 1
#define ObjectTypeInformation 2

typedef NTSTATUS(NTAPI *NTQUERYSYSTEMINFORMATION)(
	__in       ULONG SystemInformationClass,  //enum
	__inout    PVOID SystemInformation,
	__in       ULONG SystemInformationLength,
	__out_opt  PULONG ReturnLength
);

typedef NTSTATUS(NTAPI *NTDUPLICATEOBJECT)(
	_In_       HANDLE SourceProcessHandle,
	_In_       HANDLE SourceHandle,
	_In_opt_   HANDLE TargetProcessHandle,
	_Out_opt_  PHANDLE TargetHandle,
	_In_       ACCESS_MASK DesiredAccess,
	_In_       ULONG HandleAttributes,
	_In_       ULONG Options
);

typedef NTSTATUS(NTAPI *NTQUERYOBJECT)(
	_In_opt_   HANDLE Handle,
	_In_       ULONG ObjectInformationClass,  //enum
	_Out_opt_  PVOID ObjectInformation,
	_In_       ULONG ObjectInformationLength,
	_Out_opt_  PULONG ReturnLength
);

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO{
	USHORT	UniqueProcessId;
	USHORT	CreatorBackTraceIndex;
	UCHAR	ObjectTypeIndex;
	UCHAR	HandleAttributes;
	USHORT	HandleValue;
	PVOID	Object;
	ULONG	GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _SYSTEM_HANDLE_INFORMATION {
	ULONG NumberOfHandles;
	SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct __PUBLIC_OBJECT_TYPE_INFORMATION {
	UNICODE_STRING TypeName;
	ULONG Reserved[22];    // reserved for internal use
} PUBLIC_OBJECT_TYPE_INFORMATION, *PPUBLIC_OBJECT_TYPE_INFORMATION;

typedef struct __PUBLIC_OBJECT_NAME_INFORMATION
{
	UNICODE_STRING  Name;
} PUBLIC_OBJECT_NAME_INFORMATION, *PPUBLIC_OBJECT_NAME_INFORMATION;

class CCore
{
public:
	CCore();
	~CCore();
};

