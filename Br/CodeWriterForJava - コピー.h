#pragma once
#include "CodeWriter.h"

class CodeWriterForJava : public CodeWriter
{
public:
	CodeWriterForJava(FileStream *pFs, LoopIndexManager *pLim);
	virtual ~CodeWriterForJava(void);

	virtual void WriteTop();

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

	virtual void WriteDriver();

	virtual void WriteEndianConv();
};
