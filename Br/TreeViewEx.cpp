// TreeViewEx.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "Br.h"
#include "TreeViewEx.h"


// CTreeViewEx

IMPLEMENT_DYNCREATE(CTreeViewEx, CTreeView)

CTreeViewEx::CTreeViewEx()
{

}

CTreeViewEx::~CTreeViewEx()
{
}

BEGIN_MESSAGE_MAP(CTreeViewEx, CTreeView)
END_MESSAGE_MAP()


// CTreeViewEx �f�f

#ifdef _DEBUG
void CTreeViewEx::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CTreeViewEx::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTreeViewEx ���b�Z�[�W �n���h��

void CTreeViewEx::ExpandBranch(HTREEITEM hItem)
{
	CTreeCtrl& tc = GetTreeCtrl();
	if (hItem != NULL && tc.ItemHasChildren(hItem)) {
		tc.Expand(hItem, TVE_EXPAND);
		hItem = tc.GetChildItem(hItem);
		do {
			ExpandBranch(hItem);
		} while ((hItem = tc.GetNextSiblingItem(hItem)) != NULL);
	}
	tc.EnsureVisible(tc.GetSelectedItem());
}

void CTreeViewEx::ExpandAll()
{
	CTreeCtrl& tc = GetTreeCtrl();
	HTREEITEM hItem = tc.GetRootItem();
	while (hItem != NULL) {
		ExpandBranch(hItem);
		hItem = tc.GetNextSiblingItem(hItem);
	}
}
