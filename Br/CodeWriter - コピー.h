#pragma once

#include "FileStream.h"
#include "Variable.h"
#include "LoopIndexManager.h"

#define _MAX_INDENT 21
#define _MAX_NEW_LINE 5

class CodeWriter
{
public:
	enum IndentType {
		IT_SPACE4 = 0,
		IT_SPACE8,
		IT_TAB1,
		IT_TAB2,
		IT_OTHER
	};
	enum NewLineType {
		NL_N = 0,
		NL_RN
	};

protected:
	TCHAR m_szIndent[_MAX_INDENT];
	TCHAR m_szNewLine[_MAX_NEW_LINE];
	BOOL m_bUseLocal;
	BOOL m_bDriver;
	BOOL m_bEndian;
	BOOL m_bLittleEndian;
	BOOL m_bFreeRequired;

	FileStream *m_pFs;
	LoopIndexManager *m_pLim;

public:
	CodeWriter(FileStream *pFs, LoopIndexManager *pLim);
public:
	virtual ~CodeWriter(void);
public:
	void SetIndent(IndentType nType);
	void SetIndent(LPCTSTR lpsz);
	IndentType GetIndentType();
	LPCTSTR GetIndent() {return m_szIndent;}

	void SetNewLine(NewLineType nType);
	void SetNewLine(LPCTSTR lpsz);
	NewLineType GetNewLineType();
	LPCTSTR GetNewLine() {return m_szNewLine;}

public:

	void MakeVariableLocal(BOOL bLocal) {m_bUseLocal = bLocal;}
	virtual BOOL IsVariableLocal() const {return m_bUseLocal;}

	void EnableDriver(BOOL bEnable) {m_bDriver = bEnable;}
	BOOL IsDriverEnabled() const {return m_bDriver;}

	void EnableEndianConv(BOOL bEnable) {m_bEndian = bEnable;}
	BOOL IsEndianConvEnabled() const {return m_bEndian;}
	void SetLittleEndian(BOOL bFlag) {m_bLittleEndian = bFlag;}
	BOOL IsLittleEndian() const {return m_bLittleEndian;}

	virtual BOOL IsFreeRequired() const {return m_bFreeRequired;}

	void SetFileStream(FileStream *pFs) {m_pFs = pFs;}
	void SetLoopIndexManager(LoopIndexManager *pLim) {m_pLim = pLim;}

	FileStream *GetFileStream() const {return m_pFs;}
	LoopIndexManager *GetLoopIndexManager() const {return m_pLim;}

	virtual void WriteIndent(int nCount);
	virtual void WriteEOL(int nCount);
	virtual void WriteLine(int nIndent, int nEOL, LPCTSTR lpsz);

	virtual void WriteStart() = 0;
	virtual void WriteEnd() = 0;

	virtual void WriteFuncStart() = 0;
	virtual void WriteFuncEnd() = 0;

	virtual void WriteFileOpen() = 0;
	virtual void WriteFileClose() = 0;

	virtual void WriteLoopStart(int nLoopLevel, LPCTSTR lpszCount) = 0;
	virtual void WriteLoopEnd  (int nLoopLevel, LPCTSTR lpszCount) = 0;

	virtual void WriteAllocate(Variable& variable,
		int nLoopLevel, LPCTSTR lpszSize) = 0;
	virtual void WriteFree(Variable& variable, int nLoopLevel) = 0;

	virtual void WriteRead(Variable& variable,
		int nLoopLevel, LPCTSTR lpszSize = NULL) = 0;

	virtual void WriteImplPart();

	virtual void WriteDeclareLoopIndices(int nLevel);
	virtual void WriteDeclareVariable(Variable& variable) = 0;
	virtual void WriteDeclareFileDesc() = 0;

	virtual void WriteVariable(Variable& variable, int nLoopLevel);

	virtual void WriteDriver() = 0;

	virtual void WriteEndianConv() = 0;

	virtual void WriteClearFuncStart();
	virtual void WriteClearFuncEnd();
};
