#pragma once

#include "Tree.h"
#include "LoopIndexManager.h"

class TreeManager
{
protected:
	Tree *m_pT;
	CTreeCtrl *m_pTC;
	LoopIndexManager *m_pLM;
public:
	TreeManager(Tree *pT, CTreeCtrl *pTC, LoopIndexManager *pLM);
	TreeManager(Tree& T, CTreeCtrl& TC, LoopIndexManager& LM);
	virtual ~TreeManager(void);

	// Get Node/HTREEITEM
	Tree::Node *GetNode(HTREEITEM hItem);
	HTREEITEM GetItem(Tree::Node *pNode);

	// Get Root HTREEITEM
	HTREEITEM GetRootItem();

	// Get Selected Node/HTREEITEM
	Tree::Node *GetSelectedNode();
	HTREEITEM GetSelectedItem();

	// Get First Visible Node/HTREEITEM
	Tree::Node *GetFirstVisibleNode();
	HTREEITEM GetFirstVisibleItem();

	// Select Node/HTREEITEM
	BOOL SelectNode(Tree::Node *pNode);
	BOOL SelectItem(HTREEITEM hItem);

	// Set First Visible Node/HTREEITEM
	BOOL SetFirstVisibleNode(Tree::Node *pNode);
	BOOL SetFirstVisibleItem(HTREEITEM hItem);

	// Create Tree
	BOOL CreateTree(class LoopIndexManager *pLM);//CodeWriter *W);

	// Insert Node(s)
	BOOL InsertNode(Tree::Node *pNode,
		HTREEITEM hParent, class LoopIndexManager *pLM);//CodeWriter *W);
	BOOL InsertNode(Tree::Node *pNode,
		HTREEITEM hParent, HTREEITEM hInsertAfter, class LoopIndexManager *pLM);//CodeWriter *W);
	BOOL InsertNode(Tree::Node *pNode,
		Tree::Node *pParent, Tree::Node *pInsertAfter, class LoopIndexManager *pLM);//CodeWriter *W);

	BOOL InsertChildNodes(Tree::Node *pNode,
		HTREEITEM hParent, class LoopIndexManager *pLM);//CodeWriter *W);
	BOOL InsertChildNodes(Tree::Node *pNode,
		HTREEITEM hParent, HTREEITEM hInsertAfter, class LoopIndexManager *pLM);//CodeWriter *W);
	BOOL InsertChildNodes(Tree::Node *pNode,
		Tree::Node *pParent, Tree::Node *pInsertAfter, class LoopIndexManager *pLM);//CodeWriter *W);

	// Remove Node/HTREEITEM
	BOOL RemoveNode(Tree::Node *pNode);
	BOOL RemoveItem(HTREEITEM hItem);
	BOOL RemoveAll();

public:
	// Move Node in CTreeCtrl and Tree
	BOOL DoMoveUp(Tree::Node *pNode, class LoopIndexManager *pLM);//CodeWriter *W);
	BOOL DoMoveDown(Tree::Node *pNode, class LoopIndexManager *pLM);//CodeWriter *W);
	BOOL DoMoveLeft(Tree::Node *pNode, class LoopIndexManager *pLM);//CodeWriter *W);
	BOOL DoMoveRight(Tree::Node *pNode, class LoopIndexManager *pLM);//CodeWriter *W);

	// Insert Node into Tree and CTreeCtrl
	BOOL DoInsert(Tree::Node *pNode,
	   Tree::Node *pParent, Tree::Node *pInsertAfter, class LoopIndexManager *pLM);//CodeWriter *W);

	// Delete Node from CTreeCtrl and Tree
	BOOL DoDelete(Tree::Node *pNode);

protected:
	HTREEITEM FindNextItem(HTREEITEM hItem);
	HTREEITEM RevFindNextItem(HTREEITEM hItem);
};
