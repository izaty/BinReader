#pragma once

#include "UndoObject.h"

class UndoList
{
protected:
	enum STATUS {CONT, END};
	struct Content {
		UndoObject *obj;
		void *para;
		STATUS status;
		Content *next;
	};
	Content *m_pUndoCur;

	STATUS m_currStatus;

public:
	UndoList(void);
	virtual ~UndoList(void);

	void ClearList();

	void MarkEnd() {m_currStatus = END;}
	void Register(UndoObject *pObj, void *pPara);

	void Undo();

	BOOL IsUndoable() const {return (m_pUndoCur != NULL);}
	int GetCount() const;
};
