#include "StdAfx.h"
#include "TreeManager.h"
//#include "CodeWriter.h"
#include "TypeDef.h"
#include "LoopDef.h"

TreeManager::TreeManager(Tree *pT, CTreeCtrl *pTC, LoopIndexManager *pLM)
{
	m_pT = pT;
	m_pTC = pTC;
	m_pLM = pLM;
}

TreeManager::TreeManager(Tree& T, CTreeCtrl& TC, LoopIndexManager& LM)
{
	m_pT = &T;
	m_pTC = &TC;
	m_pLM = &LM;
}

TreeManager::~TreeManager(void)
{
}

Tree::Node *TreeManager::GetNode(HTREEITEM hItem)
{
	return (Tree::Node *)m_pTC->GetItemData(hItem);
}

HTREEITEM TreeManager::GetItem(Tree::Node *pNode)
{
	HTREEITEM hItem = m_pTC->GetRootItem();
	while (hItem != NULL) {
		Tree::Node *q = GetNode(hItem);
		if (pNode == q) {
			return hItem;
		}
		hItem = FindNextItem(hItem);
	}
	return NULL;
}

HTREEITEM TreeManager::GetRootItem()
{
	return m_pTC->GetRootItem();
}

Tree::Node *TreeManager::GetSelectedNode()
{
	HTREEITEM hItem = GetSelectedItem();
	return GetNode(hItem);
}

HTREEITEM TreeManager::GetSelectedItem()
{
	return m_pTC->GetSelectedItem();
}

Tree::Node *TreeManager::GetFirstVisibleNode()
{
	HTREEITEM hItem = GetFirstVisibleItem();
	return GetNode(hItem);
}

HTREEITEM TreeManager::GetFirstVisibleItem()
{
	return m_pTC->GetFirstVisibleItem();
}

BOOL TreeManager::SelectNode(Tree::Node *pNode)
{
	HTREEITEM hItem = GetItem(pNode);
	return SelectItem(hItem);
}

BOOL TreeManager::SelectItem(HTREEITEM hItem)
{
	if (hItem == NULL) {
		return FALSE;
	}
	m_pTC->SelectItem(hItem);
//	m_pTC->Select(hItem, TVGN_CARET);
	return TRUE;
}

BOOL TreeManager::SetFirstVisibleNode(Tree::Node *pNode)
{
	HTREEITEM hItem = GetItem(pNode);
	return SetFirstVisibleItem(hItem);
}

BOOL TreeManager::SetFirstVisibleItem(HTREEITEM hItem)
{
	if (hItem == NULL) {
		return FALSE;
	}
	m_pTC->Select(hItem, TVGN_FIRSTVISIBLE);
	return TRUE;
}

BOOL TreeManager::CreateTree(LoopIndexManager *pLM)//CodeWriter *W)
{
	// clear
	RemoveAll();
	// add root
	Tree::Node *pRoot = m_pT->GetRootNode();
//	HTREEITEM hRoot = m_pTC->InsertItem(pRoot->GetVariable(), TVI_ROOT);
	HTREEITEM hRoot = m_pTC->InsertItem(pRoot->GetVariable().GetName(), TVI_ROOT);
	m_pTC->SetItemData(hRoot, (DWORD_PTR)pRoot);
	m_pTC->SetItemImage(hRoot, 2, 2);
	// add all descendants
	return InsertChildNodes(pRoot, hRoot, pLM);
}

BOOL TreeManager::InsertNode(Tree::Node *pNode, 
							 HTREEITEM hParent, LoopIndexManager *pLM)//
{
	return InsertNode(pNode, hParent, TVI_LAST, pLM);//W);
}

BOOL TreeManager::InsertNode(Tree::Node *pNode,
							 HTREEITEM hParent, HTREEITEM hInsertAfter,
							 LoopIndexManager *pLM)//CodeWriter *W)
{
	TCHAR szBuffer[200];
	
	if (pNode->m_nNodeType == Common::NT_LEAF) {
		TypeDef *q = (TypeDef *)pNode;
//		lstrcpy(szBuffer, W->GetTypeString(q->GetDataType()));
		lstrcpy(szBuffer, q->GetVariable().GetDataType().GetTypeString());
		lstrcat(szBuffer, _T(" : "));
//		lstrcat(szBuffer, q->GetVariable());
		lstrcat(szBuffer, q->GetVariable().GetName());
		volatile int i;
//		for (i = 0; i < q->m_nLoopLevel; i++) {
		for (i = 0; i < q->GetLoopLevel(); i++) {
			lstrcat(szBuffer, _T("["));
			lstrcat(szBuffer, m_pLM->GetIndexName(i));//W->GetLoopIndexManager()->GetIndexName(i));
			lstrcat(szBuffer, _T("]"));
		}
	}
	else {
		LoopDef *q = (LoopDef *)pNode;
//		lstrcpy(szBuffer, W->GetLoopIndexManager()->GetIndexName(q->m_nLoopLevel));
		lstrcpy(szBuffer, 
			m_pLM->GetIndexName(q->GetLoopLevel()));//W->GetLoopIndexManager()->GetIndexName(q->GetLoopLevel()));
		lstrcat(szBuffer, _T(" : "));
//		lstrcat(szBuffer, q->GetVariable());
		lstrcat(szBuffer, q->GetVariable().GetName());
	}

	HTREEITEM hCurr = m_pTC->InsertItem(szBuffer, hParent, hInsertAfter);
	m_pTC->SetItemData(hCurr, (DWORD_PTR)pNode);

	m_pTC->SetItemImage(hCurr, (int)pNode->m_nNodeType, (int)pNode->m_nNodeType);

	if (pNode->m_pC != NULL) {
		InsertChildNodes(pNode, hCurr, pLM);//W); 
	}

	return TRUE;
}

BOOL TreeManager::InsertNode(Tree::Node *pNode,
							 Tree::Node *pParent, Tree::Node *pInsertAfter,
							 LoopIndexManager *pLM)//CodeWriter *W)
{
	HTREEITEM hParent = GetItem(pParent);
	if (hParent == NULL) {
		hParent = TVI_ROOT;
	}
	HTREEITEM hInsertAfter = GetItem(pInsertAfter);
	if (hInsertAfter == NULL) {
		//hInsertAfter = TVI_FIRST;
		hInsertAfter = TVI_LAST;
	}
	return InsertNode(pNode, hParent, hInsertAfter, pLM);//W);
}

BOOL TreeManager::InsertChildNodes(Tree::Node *pNode, 
								   HTREEITEM hParent, LoopIndexManager *pLM)//CodeWriter *W)
{
	return InsertChildNodes(pNode, hParent, TVI_LAST, pLM);//W);
}

BOOL TreeManager::InsertChildNodes(Tree::Node *pNode,
								   HTREEITEM hParent, HTREEITEM hInsertAfter,
								   LoopIndexManager *pLM)//CodeWriter *W)
{
	Tree::Node *q = pNode->m_pC;
	while (q) {
		InsertNode(q, hParent, hInsertAfter, pLM);//W);
		q = q->m_pY;
	}
	return TRUE;
}

BOOL TreeManager::InsertChildNodes(Tree::Node *pNode,
								   Tree::Node *pParent, Tree::Node *pInsertAfter,
								   LoopIndexManager *pLM)//CodeWriter *W)
{
	HTREEITEM hParent = GetItem(pParent);
	if (hParent == NULL) {
		hParent = TVI_ROOT;
	}
	HTREEITEM hInsertAfter = GetItem(pInsertAfter);
	if (hInsertAfter == NULL) {
		hInsertAfter = TVI_FIRST;
	}
	return InsertChildNodes(pNode, hParent, hInsertAfter, pLM);//W);
}

BOOL TreeManager::RemoveNode(Tree::Node *pNode)
{
	HTREEITEM hItem = GetItem(pNode);
	return RemoveItem(hItem);
}

BOOL TreeManager::RemoveItem(HTREEITEM hItem)
{
	if (hItem == NULL) {
		return FALSE;
	}
	m_pTC->DeleteItem(hItem);
	return TRUE;
}

BOOL TreeManager::RemoveAll()
{
	return m_pTC->DeleteAllItems();
}

//
BOOL TreeManager::DoMoveUp(Tree::Node *pNode, LoopIndexManager *pLM)//CodeWriter *W)
{
	BOOL bRet = m_pT->MoveUp(pNode);
	m_pT->AssignLevels();
	if (bRet) {
		RemoveNode(pNode);
		InsertNode(pNode, pNode->m_pP, pNode->m_pE, pLM);//W);
		SelectNode(pNode);
	}
	return bRet;
}

BOOL TreeManager::DoMoveDown(Tree::Node *pNode, LoopIndexManager *pLM)//CodeWriter *W)
{
	BOOL bRet = m_pT->MoveDown(pNode);
	m_pT->AssignLevels();
	if (bRet) {
		RemoveNode(pNode);
		InsertNode(pNode, pNode->m_pP, pNode->m_pE, pLM);//W);
		SelectNode(pNode);
	}
	return bRet;
}

BOOL TreeManager::DoMoveLeft(Tree::Node *pNode, LoopIndexManager *pLM)//CodeWriter *W)
{
	BOOL bRet = m_pT->MoveLeft(pNode);
	m_pT->AssignLevels();
	if (bRet) {
		RemoveNode(pNode);
		InsertNode(pNode, pNode->m_pP, pNode->m_pE, pLM);//W);
		SelectNode(pNode);
	}
	return bRet;
}

BOOL TreeManager::DoMoveRight(Tree::Node *pNode, LoopIndexManager *pLM)//CodeWriter *W)
{
	BOOL bRet = m_pT->MoveRight(pNode);
	m_pT->AssignLevels();
	if (bRet) {
		RemoveNode(pNode);
		InsertNode(pNode, pNode->m_pP, pNode->m_pE, pLM);//W);
		SelectNode(pNode);
	}
	return bRet;
}

BOOL TreeManager::DoInsert(Tree::Node *pNode,
						   Tree::Node *pParent, Tree::Node *pInsertAfter,
						   LoopIndexManager *pLM)//CodeWriter *W)
{
	m_pT->InsertNode(pNode, pParent, pInsertAfter);
	return InsertNode(pNode, pParent, pInsertAfter, pLM);//W);
}

BOOL TreeManager::DoDelete(Tree::Node *pNode)
{
	if (!RemoveNode(pNode)) {
		return FALSE;
	}
	m_pT->DeleteNode(pNode);
	return TRUE;
}



HTREEITEM TreeManager::FindNextItem(HTREEITEM hItem)
{
	// no item found
	if (hItem == NULL) {
		return NULL;
	}

	// if child exists
	HTREEITEM hChild = m_pTC->GetChildItem(hItem);
	if (hChild != NULL) {
		return hChild;
	}

	// if next sibling exists
	HTREEITEM hNext = m_pTC->GetNextSiblingItem(hItem);
	if (hNext != NULL) {
		return hNext;
	}

	// go back to parent to find next item
	return RevFindNextItem(hItem);
}

// Go up to parent to find next item
HTREEITEM TreeManager::RevFindNextItem(HTREEITEM hItem)
{
	// if parent not exist
	HTREEITEM hParent = m_pTC->GetParentItem(hItem);
	if (hParent == NULL) {
		return NULL;
	}

	// if parent's next sibling exists
	HTREEITEM hParentNext = m_pTC->GetNextSiblingItem(hParent);
	if (hParentNext != NULL) {
		return hParentNext;
	}

	// go back to parent's parent
	return RevFindNextItem(hParent);
}
