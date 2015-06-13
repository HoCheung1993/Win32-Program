#ifndef TreeCtrlBuilder_H
#define TreeCtrlBuilder_H

//////////////////////////////////////////////////////////////////////////

#include <AfxCmn.h>

//////////////////////////////////////////////////////////////////////////

template <class BuildPolicy, bool bBuildOnce = false>
class CTreeCtrlBuilder
{
	friend BuildPolicy;

	template <bool bValue>
	struct Bool2Type
	{
		enum { TypeValue = bValue };
	};

public:
	CTreeCtrlBuilder(CTreeCtrl *pTreeCtrl = NULL)
		: m_pTreeCtrl(pTreeCtrl),
		m_pBuildPolicy(NULL)
	{
		m_pBuildPolicy = new BuildPolicy(this);
	}

	virtual ~CTreeCtrlBuilder()
	{
		if (m_pBuildPolicy != NULL) {
			delete m_pBuildPolicy;
			m_pBuildPolicy = NULL;
		}
	}

	CTreeCtrl * GetTreeCtrl() const			{ return m_pTreeCtrl; }
	void SetTreeCtrl(CTreeCtrl *pTreeCtrl)	{ m_pTreeCtrl = pTreeCtrl; }

	CString GetFullPath(HTREEITEM hItem) const
	{
		CString strItemPath;
		HTREEITEM hParent = NULL;
		if (!hItem || !m_pTreeCtrl) {
			goto Exit;
		}

		{
			CString strItemName;
			hParent = hItem;
			while (hParent != NULL) {
				strItemName = m_pTreeCtrl->GetItemText(hParent);
				strItemName.TrimRight(m_pBuildPolicy->GetPathFlag());
				strItemName += m_pBuildPolicy->GetPathFlag();
				strItemPath = strItemName + strItemPath;
				hParent = m_pTreeCtrl->GetParentItem(hParent);
			}
		}

		strItemPath.TrimRight(m_pBuildPolicy->GetPathFlag());
	Exit:
		return strItemPath;
	}

	void OnItemExpanding(NMHDR *pNMHDR, LRESULT *pResult)
	{
		CWaitCursor waitCursor;
		OnItemExpanding(pNMHDR, pResult, Bool2Type<bBuildOnce>());
	}

	BuildPolicy & GetBuildPolicy() const
	{
		return (*m_pBuildPolicy);
	}

	BOOL HasChildren(const CString &strFullPath) const
	{
		return m_pBuildPolicy->HasChildren(strFullPath);
	}

	//{{AFX_VIRTUAL(CTreeCtrlBuilder)
	//}}AFX_VIRTUAL

private:
	void OnItemExpanding(NMHDR *pNMHDR, LRESULT *pResult, Bool2Type<true>)
	{
		HTREEITEM hItem = NULL;
		NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *)pNMHDR;
		if (pNMTreeView->action != TVE_EXPAND) {
			goto Exit;
		}

		hItem = pNMTreeView->itemNew.hItem;
		if (GetChildItem(hItem) != NULL) {
			goto Exit;
		}

		BuildGrandson(hItem);
	Exit:;
	}

	void OnItemExpanding(NMHDR *pNMHDR, LRESULT *pResult, Bool2Type<false>)
	{
		NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *)pNMHDR;
		if (pNMTreeView->action != TVE_EXPAND) {
			goto Exit;
		}

		{
			CString strFullPath(GetFullPath(pNMTreeView->itemNew.hItem));
			if (strFullPath.IsEmpty()) {
				goto Exit;
			}

			if (!m_pBuildPolicy->HasChildren(strFullPath)) {
				goto Exit;
			}
		}

		BuildChildren(pNMTreeView->itemNew.hItem);

	Exit:
		*pResult = 0;
	}

	BOOL BuildChildren(HTREEITEM hItem)
	{
		if (!hItem || !m_pTreeCtrl) {
			return FALSE;
		}

		if (m_pTreeCtrl->GetChildItem(hItem) != NULL) {
			return TRUE;
		}

		{
			CString strFullPath(GetFullPath(hItem));
			if (!m_pBuildPolicy->HasChildren(strFullPath)) {
				return FALSE;
			}

			CStringArray listChildItem;
			if (!m_pBuildPolicy->GetChildItem(strFullPath, listChildItem)) {
				return FALSE;
			}

			INT_PTR nChildCount = listChildItem.GetSize();
			for (INT_PTR i = 0; i < nChildCount; ++i) {
				m_pBuildPolicy->InsertItem(listChildItem[i], hItem);
			}
		}
		return TRUE;
	}

	BOOL BuildGrandson(HTREEITEM hItem)
	{
		if (!hItem) {
			return FALSE;
		}

		BuildChildren(hItem);

		HTREEITEM hChildren = GetChildItem(hItem);
		while (hChildren) {
			BuildGrandson(hChildren);
			hChildren = GetNextSiblingItem(hChildren);
		}

		return TRUE;
	}

private:
	BuildPolicy *m_pBuildPolicy;

	CTreeCtrl *m_pTreeCtrl;
};

//////////////////////////////////////////////////////////////////////////

#endif
