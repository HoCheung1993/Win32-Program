#include "stdafx.h"
#include "SystemImageList.h"

int CSystemImageList::m_nRefCount = 0;

CSystemImageList::CSystemImageList()
{
	//	We need to implement reference counting to 
	//	overcome an MFC limitation whereby you cannot
	//	have two CImageLists attached to the one underlyinh
	//	HIMAGELIST. If this was not done then you would get 
	//	an ASSERT in MFC if you had two or more CTreeFileCtrl's
	//	in your program at the same time
	if (m_nRefCount == 0) {
		//	Attach to the system image list
		SHFILEINFO shFileInfo;
		HIMAGELIST hSystemImageList = (HIMAGELIST)SHGetFileInfo(_T("C:\\"), 0, &shFileInfo, sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
		VERIFY(m_ImageList.Attach(hSystemImageList));
	}

	//	Increment the reference count
	m_nRefCount++;
}

CSystemImageList::~CSystemImageList()
{
	//	Decrement the reference count
	m_nRefCount--;

	if (m_nRefCount == 0) {
		//	Detach from the image list to prevent problems on 95/98 where
		//	the system image list is shared across processes
		m_ImageList.Detach();
	}
}

CImageList & CSystemImageList::GetImageList()	{ return m_ImageList; }

int CSystemImageList::GetIconIndex(const CString &strFileName)
{
	SHFILEINFO shFileInfo;
	if (SHGetFileInfo(strFileName, 0, &shFileInfo, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_SMALLICON) == 0) {
		return -1;
	}

	return shFileInfo.iIcon;
}

int CSystemImageList::GetSelectIconIndex(const CString &strFileName)
{
	//	Retreive the icon index for a specified file/folder
	SHFILEINFO shFileInfo;
	if (SHGetFileInfo(strFileName, 0, &shFileInfo, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_OPENICON | SHGFI_SMALLICON) == 0) {
		return -1;
	}

	return shFileInfo.iIcon;
}
