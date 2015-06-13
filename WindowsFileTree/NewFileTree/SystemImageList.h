#ifndef SystemImageList_H
#define SystemImageList_H

#include <AfxCmn.h>

class CSystemImageList
{
public:
	CSystemImageList();
	~CSystemImageList();

	CImageList & GetImageList();

	int GetIconIndex(const CString &strFileName);
	int GetSelectIconIndex(const CString &strFileName);

protected:
	CImageList m_ImageList;

	static int m_nRefCount;
};

#endif
