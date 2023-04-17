#pragma once

class UndoObject
{
public:
	UndoObject(void);
	virtual ~UndoObject(void);

	virtual void ExeUndo(void *pPara);
	virtual void DelUndo(void *pPara);
};
