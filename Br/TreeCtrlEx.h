#pragma once

#include "Tree.h"

// CTreeCtrlEx

class CTreeCtrlEx : public CTreeCtrl
{
	DECLARE_DYNAMIC(CTreeCtrlEx)

public:
	CTreeCtrlEx();
	virtual ~CTreeCtrlEx();

//	HTREEITEM FindItem(HTREEITEM hti, Tree::Node *p);

protected:
	DECLARE_MESSAGE_MAP()

	HTREEITEM FindNextItem(HTREEITEM hItem);
	HTREEITEM ReverseSearch(HTREEITEM hItem);
};


