// TreeViewEx.cpp : 実装ファイル
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


// CTreeViewEx 診断

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


// CTreeViewEx メッセージ ハンドラ

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
