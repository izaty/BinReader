// TreeCtrlEx.cpp : 実装ファイル
//

#include "stdafx.h"
#include "Br.h"
#include "TreeCtrlEx.h"


// CTreeCtrlEx

IMPLEMENT_DYNAMIC(CTreeCtrlEx, CTreeCtrl)

CTreeCtrlEx::CTreeCtrlEx()
{

}

CTreeCtrlEx::~CTreeCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CTreeCtrlEx, CTreeCtrl)
END_MESSAGE_MAP()

HTREEITEM CTreeCtrlEx::FindNextItem(HTREEITEM hItem)
{
	if (hItem == NULL) {
		return NULL;
	}

	HTREEITEM hNext;

	hNext = GetChildItem(hItem);
	if (hNext != NULL) {
		return hNext;
	}

	hNext = GetNextSiblingItem(hItem);
	if (hNext != NULL) {
		return hNext;
	}

	return ReverseSearch(hItem);
}

HTREEITEM CTreeCtrlEx::ReverseSearch(HTREEITEM hItem)
{
	HTREEITEM hParent = GetParentItem(hItem);
	if (hParent == NULL) {
		return NULL;
	}

	HTREEITEM hParentNext = GetNextSiblingItem(hParent);
	if (hParentNext != NULL) {
		return hParentNext;
	}

	return ReverseSearch(hParent);
}
/*
HTREEITEM CTreeCtrlEx::FindItem(HTREEITEM hItem, Tree::Node *p)
{
	if (hItem == NULL || p == NULL) {
		return NULL;
	}

	do {
		Tree::Node *q = (Tree::Node *)GetItemData(hItem);
		if (p == q) {
			return hItem;
		}
		if (ItemHasChildren(hItem)) {
			HTREEITEM hRet = FindItem(GetChildItem(hItem), p);
			if (hRet != NULL) {
				return hRet;
			}
		}
		hItem = GetNextSiblingItem(hItem);
	} while (hti != NULL);


	if (hti != NULL && p != NULL && ItemHasChildren(hti)) {
		hti = GetChildItem(hti);
		do {
			Tree::Node *q = (Tree::Node *)GetItemData(hti);
			if (p == q) {
				if (strChild == strDir) {
					return hti;
				}
				else {
					int nRightLength = 
						strDir.GetLength() - strItem.GetLength() - 1;
					strDir = strDir.Right(nRightLength);
					return FindDirectory(hti, strDir);
				}
			}
		} while ((hti = GetNextSiblingItem(hti)) != NULL);
	}
	return NULL;
}
*/


// CTreeCtrlEx メッセージ ハンドラ


