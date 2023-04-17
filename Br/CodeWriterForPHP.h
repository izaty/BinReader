#pragma once
#include "CodeWriter.h"

class CodeWriterForPHP :
	public CodeWriter
{
public:
	CodeWriterForPHP(FileStream *pFs, LoopIndexManager *pLim);
public:
	virtual ~CodeWriterForPHP(void);

	virtual BOOL IsVariableLocal() const {return TRUE;}

	virtual void WriteStart();
	virtual void WriteEnd();

	virtual void WriteFuncStart();
	virtual void WriteFuncEnd();

	virtual void WriteFileOpen();
	virtual void WriteFileClose();

	virtual void WriteLoopStart(int nLoopLevel, LPCTSTR lpszCount);
	virtual void WriteLoopEnd  (int nLoopLevel, LPCTSTR lpszCount);

	virtual void WriteAllocate(Variable& variable,
		int nLoopLevel, LPCTSTR lpszSize);
	virtual void WriteFree(Variable& variable, int nLoopLevel);

	virtual void WriteRead(Variable& variable,
		int nLoopLevel, LPCTSTR lpszSize = NULL);

	virtual void WriteDeclareLoopIndices(int nLevel);
	virtual void WriteDeclareVariable(Variable& variable);
	virtual void WriteDeclareFileDesc();

	virtual void WriteVariable(Variable& variable, int nLoopLevel);

	virtual void WriteDriver();

	virtual void WriteEndianConv();

	virtual void WriteUnpack();

	virtual void WriteSize(LPCTSTR lpszSize);

	// Appended on Mar.22,'16
	// start
	virtual void WriteWFuncStart();
	virtual void WriteWFuncEnd();

	virtual void WriteWFileOpen();
	virtual void WriteWFileClose();

	virtual void WriteWrite(Variable& variable,
		int nLoopLevel, LPCTSTR lpszSize = NULL);

	virtual void WriteWDeclareFileDesc();
	// end
};
