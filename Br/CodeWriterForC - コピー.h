#pragma once
#include "CodeWriter.h"

class CodeWriterForC : public CodeWriter
{
public:
	CodeWriterForC(FileStream *pFs, LoopIndexManager *pLim);
public:
	virtual ~CodeWriterForC(void);

	//virtual LPCTSTR GetTypeString(DataType1 nType);

	virtual void WriteFuncStart();
	virtual void WriteFuncEnd();

	virtual void WriteFileOpen();
	virtual void WriteFileClose();

	virtual void WriteLoopStart(int nLoopLevel, LPCTSTR lpszCount);
	virtual void WriteLoopEnd  (int nLoopLevel, LPCTSTR lpszCount);

	//virtual void WriteAllocate(DataType1 nType, int nLoopLevel, int nVarLevel,
	//	LPCTSTR lpszVariable, LPCTSTR lpszSize);
	//virtual void WriteFree(int nLoopLevel, LPCTSTR lpszVariable);
	// s
	virtual void WriteAllocate(Variable& variable,
		int nLoopLevel, LPCTSTR lpszSize);
	virtual void WriteFree(Variable& variable, int nLoopLevel);
	// e

	//virtual void WriteRead(DataType1 nType, int nReadLevel, int nVarLevel,
	//	LPCTSTR lpszVariable, LPCTSTR lpszSize = NULL);
	// s
	virtual void WriteRead(Variable& variable,
		int nLoopLevel, LPCTSTR lpszSize = NULL);
	// e

	//virtual void WriteDeclareVariable(DataType1 nType, int nPointer,
	//	LPCTSTR lpszVariable);
	// s
	virtual void WriteDeclareVariable(Variable& variable);
	// e
	virtual void WriteDeclareFileDesc();
};
