#include "StdAfx.h"
#include "TreeManager.h"
#include "TypeDef.h"
#include "LoopDef.h"
#include "BracketPos.h"

TreeManager::TreeManager(Tree *pT, CTreeCtrl *pTC,
						 LoopIndexManager *pLM, UndoList *pU)
{
	m_pT = pT;
	m_pTC = pTC;
	m_pLM = pLM;
	m_pU = pU;
}

TreeManager::TreeManager(Tree& T, CTreeCtrl& TC,
						 LoopIndexManager& LM, UndoList& U)
{
	m_pT = &T;
	m_pTC = &TC;
	m_pLM = &LM;
	m_pU = &U;
}

TreeManager::~TreeManager(void)
{
}

Node *TreeManager::GetNode(HTREEITEM hItem)
{
	return (Node *)m_pTC->GetItemData(hItem);
}

HTREEITEM TreeManager::GetItem(Node *pNode)
{
	HTREEITEM hItem = m_pTC->GetRootItem();
	while (hItem != NULL) {
		Node *q = GetNode(hItem);
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

Node *TreeManager::GetSelectedNode()
{
	HTREEITEM hItem = GetSelectedItem();
	return GetNode(hItem);
}

HTREEITEM TreeManager::GetSelectedItem()
{
	return m_pTC->GetSelectedItem();
}

Node *TreeManager::GetFirstVisibleNode()
{
	HTREEITEM hItem = GetFirstVisibleItem();
	return GetNode(hItem);
}

HTREEITEM TreeManager::GetFirstVisibleItem()
{
	return m_pTC->GetFirstVisibleItem();
}

BOOL TreeManager::SelectRoot()
{
	HTREEITEM hRoot = GetRootItem();
	return SelectItem(hRoot);
}

BOOL TreeManager::SelectNode(Node *pNode)
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

BOOL TreeManager::SetFirstVisibleNode(Node *pNode)
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

BOOL TreeManager::CreateTree()
{
	// clear
	RemoveAll();
	// add root
	Node *pRoot = m_pT->GetRootNode();
	HTREEITEM hRoot = m_pTC->InsertItem(pRoot->GetVariable().GetName(), TVI_ROOT);
	m_pTC->SetItemData(hRoot, (DWORD_PTR)pRoot);
	m_pTC->SetItemImage(hRoot, 2, 2);
	// add all descendants
	return InsertChildNodes(pRoot, hRoot);
}

void TreeManager::CorrectLoopIndices()
{
	m_pT->CorrectLoopIndices(m_pLM);
}

BOOL TreeManager::InsertNode(Node *pNode, HTREEITEM hParent)
{
	return InsertNode(pNode, hParent, TVI_LAST);
}

BOOL TreeManager::InsertNode(Node *pNode,
							 HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	/*
	TCHAR szBuffer[200];
	
	if (pNode->m_nNodeType == Node::NT_LEAF) {
		TypeDef *q = (TypeDef *)pNode;
		lstrcpy(szBuffer, q->GetVariable().GetDataType().GetTypeString());
		lstrcat(szBuffer, _T(" : "));
		lstrcat(szBuffer, q->GetVariable().GetName());
		volatile int i;
		for (i = 0; i < q->GetLoopLevel(); i++) {
			lstrcat(szBuffer, _T("["));
			lstrcat(szBuffer, m_pLM->GetVariableString(i));
			lstrcat(szBuffer, _T("]"));
		}
	}
	else {
		LoopDef *q = (LoopDef *)pNode;
		lstrcpy(szBuffer, 
			m_pLM->GetVariableString(q->GetLoopLevel()));
		lstrcat(szBuffer, _T(" : "));
		lstrcat(szBuffer, q->GetVariable().GetName());
	}
	*/
	LPTSTR psz = GetNodeText(pNode);

	HTREEITEM hCurr = m_pTC->InsertItem(psz, hParent, hInsertAfter);
	m_pTC->SetItemData(hCurr, (DWORD_PTR)pNode);

	m_pTC->SetItemImage(hCurr, (int)pNode->m_nNodeType, (int)pNode->m_nNodeType);

	if (pNode->m_pC != NULL) {
		InsertChildNodes(pNode, hCurr); 
	}

	return TRUE;
}

BOOL TreeManager::InsertNode(Node *pNode,
							 Node *pParent, Node *pInsertAfter)
{
	HTREEITEM hParent = GetItem(pParent);
	if (hParent == NULL) {
		hParent = TVI_ROOT;
	}
	HTREEITEM hInsertAfter = GetItem(pInsertAfter);
	if (hInsertAfter == NULL) {
		hInsertAfter = TVI_FIRST;
		//hInsertAfter = TVI_LAST;
	}
	return InsertNode(pNode, hParent, hInsertAfter);
}

BOOL TreeManager::InsertChildNodes(Node *pNode, HTREEITEM hParent)
{
	return InsertChildNodes(pNode, hParent, TVI_LAST);
}

BOOL TreeManager::InsertChildNodes(Node *pNode,
								   HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	Node *q = pNode->m_pC;
	while (q) {
		InsertNode(q, hParent, hInsertAfter);
		q = q->m_pY;
	}
	return TRUE;
}

BOOL TreeManager::InsertChildNodes(Node *pNode,
								   Node *pParent, Node *pInsertAfter)
{
	HTREEITEM hParent = GetItem(pParent);
	if (hParent == NULL) {
		hParent = TVI_ROOT;
	}
	HTREEITEM hInsertAfter = GetItem(pInsertAfter);
	if (hInsertAfter == NULL) {
		hInsertAfter = TVI_FIRST;
	}
	return InsertChildNodes(pNode, hParent, hInsertAfter);
}

BOOL TreeManager::RemoveNode(Node *pNode)
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

BOOL TreeManager::UpdateNode(Node *pNode)
{
	HTREEITEM hItem = GetItem(pNode);
	if (hItem == NULL) {
		return FALSE;
	}

	LPTSTR psz = GetNodeText(pNode);
	m_pTC->SetItemText(hItem, psz);
	return TRUE;
}

//
BOOL TreeManager::DoMoveUp(Node *pNode)
{
	m_pU->MarkEnd();
	BOOL bRet = m_pT->MoveUp(pNode, m_pU);
	if (bRet) {
		RemoveNode(pNode);
		InsertNode(pNode, pNode->m_pP, pNode->m_pE);
		SelectNode(pNode);
	}
	return bRet;
}

BOOL TreeManager::DoMoveDown(Node *pNode)
{
	m_pU->MarkEnd();
	BOOL bRet = m_pT->MoveDown(pNode, m_pU);
	if (bRet) {
		RemoveNode(pNode);
		InsertNode(pNode, pNode->m_pP, pNode->m_pE);
		SelectNode(pNode);
	}
	return bRet;
}

BOOL TreeManager::DoMoveLeft(Node *pNode)
{
	m_pU->MarkEnd();
	BOOL bRet = m_pT->MoveLeft(pNode, m_pU);
	if (bRet) {
		RemoveNode(pNode);
		InsertNode(pNode, pNode->m_pP, pNode->m_pE);
		SelectNode(pNode);
	}
	return bRet;
}

BOOL TreeManager::DoMoveRight(Node *pNode)
{
	m_pU->MarkEnd();
	BOOL bRet = m_pT->MoveRight(pNode, m_pU);
	if (bRet) {
		RemoveNode(pNode);
		InsertNode(pNode, pNode->m_pP, pNode->m_pE);
		SelectNode(pNode);
	}
	return bRet;
}

BOOL TreeManager::DoInsert(Node *pNode,
						   Node *pParent, Node *pInsertAfter)
{
	m_pU->MarkEnd();
	BOOL bRet = FALSE;
	Node *pNewNode = m_pT->InsertNode(pNode, pParent, pInsertAfter, m_pU);
	if (pNewNode != NULL) {
		InsertNode(pNewNode, pParent, pInsertAfter);
		SelectNode(pNewNode);
		bRet = TRUE;
	}
	return bRet;
}

BOOL TreeManager::DoDelete(Node *pNode)
{
	if (!RemoveNode(pNode)) {
		return FALSE;
	}
	m_pU->MarkEnd();
	m_pT->DeleteNode(pNode, m_pU);
	return TRUE;
}

BOOL TreeManager::DoSetLoop(Node *pNode, LPCTSTR lpsz)
{
	m_pU->MarkEnd();
	pNode->GetVariable().SetName(lpsz, m_pU);
//	pNode->GetVariable().SetName(lpsz);
	SelectNode(pNode);

	return UpdateNode(pNode);
}

BOOL TreeManager::DoSetData(Node *pNode, DataType::Type nType, LPCTSTR lpsz)
{
	m_pU->MarkEnd();
	pNode->GetVariable().GetDataType().SetType(nType, m_pU);
	pNode->GetVariable().SetName(lpsz, m_pU);
//	pNode->GetVariable().GetDataType().SetType(nType);
//	pNode->GetVariable().SetName(lpsz);
	SelectNode(pNode);

	return UpdateNode(pNode);
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

LPTSTR TreeManager::GetNodeText(Node *pNode)
{
	static TCHAR szBuffer[1000], szSBuffer[1000], szTemp[1000];
	
	if (pNode->m_nNodeType == Node::NT_LEAF) {
		TypeDef *q = (TypeDef *)pNode;
		lstrcpy(szBuffer, q->GetVariable().GetDataType().GetTypeString());
		lstrcat(szBuffer, _T(" : "));
		lstrcat(szBuffer, q->GetVariable().GetName());
		volatile int i;
		for (i = 0; i < q->GetLoopLevel(); i++) {
			lstrcat(szBuffer, _T("["));
			lstrcat(szBuffer, m_pLM->GetVariableString(i));
			lstrcat(szBuffer, _T("]"));
		}
	}
	else {
		LoopDef *q = (LoopDef *)pNode;
		lstrcpy(szTemp, q->GetVariable().GetName());
		//
		try {
			BracketPos *pBp = NULL;
			Variable::CheckLoopName(szTemp, &pBp);

			if (pBp != NULL) {
				BracketPos::Var *p = pBp->m_var.next;
				while (p) {
					int nLevel = m_pLM->GetVariableLevel(p->lpsz);
					if (nLevel >= 0) {
						//if (p->level > 0) {
						//	break;
						//}
						lstrcpyn(szSBuffer, szTemp, p->start + 1);
						lstrcat(szSBuffer, m_pLM->GetVariableString(nLevel));
						lstrcat(szSBuffer, &szTemp[p->start+p->length]);
						lstrcpy(szTemp, szSBuffer);
					}
					p = p->next;
				}
				delete pBp;
			}
		}
		catch (Variable::ErrorCode e) {
		}
		//

		lstrcpy(szBuffer, 
			m_pLM->GetVariableString(q->GetLoopLevel()));
		lstrcat(szBuffer, _T(" : "));
		//lstrcat(szBuffer, q->GetVariable().GetName());
		lstrcat(szBuffer, szTemp);
	}

	return szBuffer;
}