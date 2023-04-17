#pragma once
#include "CodeWriter.h"

class CodeWriterForCplus : public CodeWriter
{
public:
	CodeWriterForCplus(FileStream *pFs, LoopIndexManager *pLim);
public:
	virtual ~CodeWriterForCplus(void);

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

	virtual void WriteDeclareVariable(Variable& variable);
	virtual void WriteDeclareFileDesc();

	virtual void WriteDriver();

	virtual void WriteEndianConv();

	virtual void WriteClearFuncStart();
	virtual void WriteClearFuncEnd();

	// Appended on Mar.21,'16
	// start
	virtual void WriteWFuncStart();
	virtual void WriteWFuncEnd();

	virtual void WriteWFileOpen();
	virtual void WriteWFileClose();

	virtual void WriteWrite(Variable& variable,
		int nLoopLevel, LPCTSTR lpszSize = NULL);

	virtual void WriteWDeclareFileDesc();

private:
	void ConvEndian(Variable& variable, int nPointer,
		int nLoopLevel, LPCTSTR lpszSize = NULL);
	// end
};
