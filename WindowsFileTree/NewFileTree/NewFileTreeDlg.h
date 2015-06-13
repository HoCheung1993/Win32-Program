#ifndef MainDialog_H
#define MainDialog_H

//////////////////////////////////////////////////////////////////////////

#pragma warning(disable:4097)
#pragma warning(disable:4100)

//////////////////////////////////////////////////////////////////////////

#include <AfxWin.h>

#include <AfxCmn.h>
#include <Shlwapi.h>

#include <TChar.h>

#include <list>

#include "Resource.h"

#include "TreeCtrlBuilder.h"
#include "SystemImageList.h"


//////////////////////////////////////////////////////////////////////////

const bool bBuildOnce = false;

//////////////////////////////////////////////////////////////////////////

struct PathBuildPolicy
{
public:
	PathBuildPolicy(CTreeCtrlBuilder<PathBuildPolicy, bBuildOnce> * const pOwner)
		: m_pOwner(pOwner)
	{
	}

public:
	CSystemImageList & GetSystemImageList() {
		return m_SysImageList;
	}

	bool InsertItem(const CString &strItmeName, HTREEITEM hParent)
	{
		if (!hParent || !m_pOwner) {
			return false;
		}

		CString strFullPath(m_pOwner->GetFullPath(hParent));
		if (strFullPath.IsEmpty()) {
			return false;
		}

		strFullPath.TrimRight(GetPathFlag());
		strFullPath += GetPathFlag();
		strFullPath += strItmeName;

		TCHAR szItemText[1024] = { _T('0') };
		if (strItmeName.GetLength() > sizeof(szItemText) / sizeof(TCHAR) - 1) {
			return false;
		}

		_tcscpy_s(szItemText, strItmeName);

		int nIconIndex = m_SysImageList.GetIconIndex(strFullPath);
		int nSelIconIndex = m_SysImageList.GetSelectIconIndex(strFullPath);
		nIconIndex = (nIconIndex == -1) ? 0 : nIconIndex;
		nSelIconIndex = (nSelIconIndex == -1) ? 0 : nSelIconIndex;

		TV_INSERTSTRUCT tvInsertStruct;
		ZeroMemory(&tvInsertStruct, sizeof(TV_INSERTSTRUCT));
		tvInsertStruct.hParent = hParent;
		tvInsertStruct.hInsertAfter = TVI_LAST;
		tvInsertStruct.item.mask = TVIF_CHILDREN | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		tvInsertStruct.item.pszText = szItemText;
		tvInsertStruct.item.iImage = nIconIndex;
		tvInsertStruct.item.iSelectedImage = nSelIconIndex;
		tvInsertStruct.item.cChildren = HasChildren(strFullPath);

		CTreeCtrl *pTreeCtrl = m_pOwner->GetTreeCtrl();
		if (pTreeCtrl) {
			pTreeCtrl->InsertItem(&tvInsertStruct);
		}
		return true;
	}

	bool HasChildren(const CString &strFullPath) const
	{
		bool bHasChildren = false;

		if (!PathIsDirectory(strFullPath)) {
			goto Exit;
		}

		if (PathIsDirectoryEmpty(strFullPath)) {
			goto Exit;
		}

		bHasChildren = true;
	Exit:
		return bHasChildren;
	}

	bool GetChildItem(const CString &strFullPath, CStringArray &listChildItem) const
	{
		listChildItem.RemoveAll();

		CFileFind fileFind;
		CString strItemName(strFullPath);
		strItemName.TrimRight(GetPathFlag());
		strItemName += GetPathFlag();
		strItemName += _T("*.*");

		std::list<CString> _listChildItem;
		BOOL bFind = fileFind.FindFile(strItemName);
		while (bFind) {
			bFind = fileFind.FindNextFile();

			if (!fileFind.IsDots()) {
				_listChildItem.push_back(fileFind.GetFilePath());
			}
			else {
				continue;
			}
		}

		//		_listChildItem.sort();
		std::list<CString>::iterator it;
		for (it = _listChildItem.begin(); it != _listChildItem.end(); ++it) {
			listChildItem.Add(PathFindFileName(*it));
		}

		return true;
	}

	TCHAR GetPathFlag() const	{ return _T('\\'); }

private:
	CTreeCtrlBuilder<PathBuildPolicy, bBuildOnce> *m_pOwner;

	CSystemImageList m_SysImageList;
};

//////////////////////////////////////////////////////////////////////////
// CNewFileTreeDlg dialog
class CNewFileTreeDlg : public CDialogEx
{
// Construction
public:
	CNewFileTreeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_NEWFILETREE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnItemExpandingTreeCtrl(NMHDR* pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkTreectrl(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
public:
	void InitializeExplorerTree();
	CTreeCtrl m_treeCtrl;
	CTreeCtrlBuilder<PathBuildPolicy, bBuildOnce> m_treeCtrlBuilder;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	void SetChildCheck(HTREEITEM item, BOOL bCheck);
	void SetParentCheck(HTREEITEM item, BOOL bCheck);
	void SetItemCheckState(HTREEITEM item, BOOL bCheck);
	CString GetCurItemRootPath(HTREEITEM htiItem);
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonNo();

private:
	std::list<CString> m_lstFilePath;
};

#endif