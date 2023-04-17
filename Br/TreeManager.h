#pragma once

#include "Tree.h"
#include "LoopIndexManager.h"
#include "UndoList.h"

class TreeManager
{
protected:
	Tree *m_pT;
	CTreeCtrl *m_pTC;
	LoopIndexManager *m_pLM;
	UndoList *m_pU;
public:
	TreeManager(Tree *pT, CTreeCtrl *pTC,
		LoopIndexManager *pLM, UndoList *pU);
	TreeManager(Tree& T, CTreeCtrl& TC,
		LoopIndexManager& LM, UndoList& U);
	virtual ~TreeManager(void);

	// Get Node/HTREEITEM
	Node *GetNode(HTREEITEM hItem);
	HTREEITEM GetItem(Node *pNode);

	// Get Root HTREEITEM
	HTREEITEM GetRootItem();

	// Get Selected Node/HTREEITEM
	Node *GetSelectedNode();
	HTREEITEM GetSelectedItem();

	// Get First Visible Node/HTREEITEM
	Node *GetFirstVisibleNode();
	HTREEITEM GetFirstVisibleItem();

	// Select Node/HTREEITEM
	BOOL SelectRoot();
	BOOL SelectNode(Node *pNode);
	BOOL SelectItem(HTREEITEM hItem);

	// Set First Visible Node/HTREEITEM
	BOOL SetFirstVisibleNode(Node *pNode);
	BOOL SetFirstVisibleItem(HTREEITEM hItem);

	// Create Tree
	BOOL CreateTree();

	// Correct Loop Indices
	void CorrectLoopIndices();

	// Insert Node(s)
	BOOL InsertNode(Node *pNode, HTREEITEM hParent);
	BOOL InsertNode(Node *pNode,
		HTREEITEM hParent, HTREEITEM hInsertAfter);
	BOOL InsertNode(Node *pNode,
		Node *pParent, Node *pInsertAfter);

	BOOL InsertChildNodes(Node *pNode, HTREEITEM hParent);
	BOOL InsertChildNodes(Node *pNode,
		HTREEITEM hParent, HTREEITEM hInsertAfter);
	BOOL InsertChildNodes(Node *pNode,
		Node *pParent, Node *pInsertAfter);

	// Remove Node/HTREEITEM
	BOOL RemoveNode(Node *pNode);
	BOOL RemoveItem(HTREEITEM hItem);
	BOOL RemoveAll();

	BOOL UpdateNode(Node *pNode);

public:
	// Move Node in CTreeCtrl and Tree
	BOOL DoMoveUp(Node *pNode);
	BOOL DoMoveDown(Node *pNode);
	BOOL DoMoveLeft(Node *pNode);
	BOOL DoMoveRight(Node *pNode);

	// Insert Node into Tree and CTreeCtrl
	BOOL DoInsert(Node *pNode,
	   Node *pParent, Node *pInsertAfter);

	// Delete Node from CTreeCtrl and Tree
	BOOL DoDelete(Node *pNode);

	// Set Text to Node in CTreeCtrl and Tree
	BOOL DoSetData(Node *pNode, DataType::Type nType, LPCTSTR lpsz);
	BOOL DoSetLoop(Node *pNode, LPCTSTR lpsz);

protected:
	HTREEITEM FindNextItem(HTREEITEM hItem);
	HTREEITEM RevFindNextItem(HTREEITEM hItem);
	LPTSTR GetNodeText(Node *pNode);
};
