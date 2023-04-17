#include "StdAfx.h"
#include "UndoList.h"

UndoList::UndoList(void)
{
	m_pUndoCur = NULL;
	m_currStatus = CONT;
}

UndoList::~UndoList(void)
{
	ClearList();
}

void UndoList::ClearList()
{
	while (m_pUndoCur != NULL) {
		Content *pCurr = m_pUndoCur;
		Content *pNext = m_pUndoCur->next;
		// delete
		pCurr->obj->DelUndo(pCurr->para);
		delete pCurr;
		// go to next
		m_pUndoCur = pNext;
	}
}

void UndoList::Register(UndoObject *pObj, void *pPara)
{
	// create new undo data
	Content *pCurr = new Content;
	pCurr->obj = pObj;
	pCurr->para = pPara;
	pCurr->status = m_currStatus;
	// connect this data to list
	pCurr->next = m_pUndoCur;
	// update current data
	m_pUndoCur = pCurr;

	// update current status
	//m_currStatus = END;
	if (m_currStatus == END) {
		m_currStatus = CONT;
	}
}

void UndoList::Undo()
{
	while (m_pUndoCur != NULL) {
		Content *pCurr = m_pUndoCur;
		Content *pNext = m_pUndoCur->next;
		STATUS wkStatus = pCurr->status;
		// execute undo
		pCurr->obj->ExeUndo(pCurr->para);
		// delete
		delete pCurr;
		// go to next
		m_pUndoCur = pNext;
		// continue undo until status is END
		if (wkStatus == END)
			break;
	}
}

int UndoList::GetCount() const
{
	int nCount = 0;
	Content *p = m_pUndoCur;
	while (p != NULL) {
		nCount++;
		p = p->next;
	}
	return nCount;
}