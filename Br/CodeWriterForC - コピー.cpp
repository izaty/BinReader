#include "StdAfx.h"
#include "CodeWriterForC.h"

CodeWriterForC::CodeWriterForC(FileStream *pFs,
							   LoopIndexManager *pLim) : CodeWriter(pFs, pLim)
{
}

CodeWriterForC::~CodeWriterForC(void)
{
}

/*
static LPCTSTR _lpszInt		= _T("int");
static LPCTSTR _lpszFloat	= _T("float");
static LPCTSTR _lpszDouble	= _T("double");
static LPCTSTR _lpszChar	= _T("char");

LPCTSTR CodeWriterForC::GetTypeString(DataType1 nType)
{
	if (nType == DT_INT) {
		return _lpszInt;
	}
	if (nType == DT_FLOAT) {
		return _lpszFloat;
	}
	if (nType == DT_DOUBLE) {
		return _lpszDouble;
	}
	if (nType == DT_CHAR) {
		return _lpszChar;
	}
	return _lpszInt;
}
*/

void CodeWriterForC::WriteFuncStart()
{
	m_pFs->Write("#include <stdio.h>");
	WriteEOL(2);
	m_pFs->Write("int readBinary(char *arg0)");
	WriteEOL(1);
	m_pFs->Write("{");
	WriteEOL(1);
}

void CodeWriterForC::WriteFuncEnd()
{
	WriteIndent(1);
	m_pFs->Write("return 0;");
	WriteEOL(1);
	m_pFs->Write("}");
	WriteEOL(1);
}

void CodeWriterForC::WriteFileOpen()
{
	WriteIndent(1);
	m_pFs->Write("if ((fp = fopen(arg0, \"r\")) == NULL) {");
	WriteEOL(1);

	WriteIndent(2);
	m_pFs->Write("return -3;");
	WriteEOL(1);

	WriteIndent(1);
	m_pFs->Write("}");
	WriteEOL(1);
}

void CodeWriterForC::WriteFileClose()
{
	WriteIndent(1);
	m_pFs->Write("fclose(fp);");
	WriteEOL(1);
}

void CodeWriterForC::WriteLoopStart(int nLoopLevel, LPCTSTR lpszCount)
{
	WriteIndent(nLoopLevel + 1);
	m_pFs->Write("for (");
	m_pFs->Write(m_pLim->GetIndexName(nLoopLevel));
	m_pFs->Write(" = 0; ");
	m_pFs->Write(m_pLim->GetIndexName(nLoopLevel));
	m_pFs->Write(" < ");
	m_pFs->Write(lpszCount);
	m_pFs->Write("; ");
	m_pFs->Write(m_pLim->GetIndexName(nLoopLevel));
	m_pFs->Write("++) {");
	WriteEOL(1);
}

void CodeWriterForC::WriteLoopEnd(int nLoopLevel, LPCTSTR lpszCount)
{
	WriteIndent(nLoopLevel + 1);
	m_pFs->Write("}");
	WriteEOL(1);
}

/*
void CodeWriterForC::WriteAllocate(DataType1 nType,
							   int nLoopLevel, int nVarLevel,
							   LPCTSTR lpszVariable, LPCTSTR lpszSize)
{
	int nPointer = nVarLevel - nLoopLevel;
	if (nPointer < 0) {
		return;
	}

	volatile int i;

	WriteIndent(nLoopLevel + 1);
	m_pFs->Write("if ((");
	WriteVariable(lpszVariable, nLoopLevel);
	m_pFs->Write(" = (");
	m_pFs->Write(GetTypeString(nType));
	m_pFs->Write(" ");
	for (i = 0; i < nPointer; i++) {
		m_pFs->Write("*");
	}
	m_pFs->Write(")malloc(");
	m_pFs->Write(lpszSize);
	m_pFs->Write(" * sizeof(");
	m_pFs->Write(GetTypeString(nType));
	if (nPointer > 1) {
		m_pFs->Write(" ");
		for (i = 0; i < nPointer - 1; i++) {
			m_pFs->Write("*");
		}
	}
	m_pFs->Write("))) == NULL) {");
	WriteEOL(1);

	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("return -2;");
	WriteEOL(1);

	WriteIndent(nLoopLevel + 1);
	m_pFs->Write("}");
	WriteEOL(1);
}

void CodeWriterForC::WriteFree(int nLoopLevel, LPCTSTR lpszVariable)
{
	WriteIndent(nLoopLevel + 1);
	m_pFs->Write("free(");
	WriteVariable(lpszVariable, nLoopLevel);
	m_pFs->Write(");");
	WriteEOL(1);
}
*/
// s
void CodeWriterForC::WriteAllocate(Variable& variable,
								   int nLoopLevel, LPCTSTR lpszSize)
{
	int nPointer = variable.GetLoopLevel() - nLoopLevel;
	if (nPointer < 0) {
		return;
	}

	volatile int i;

	WriteIndent(nLoopLevel + 1);
	m_pFs->Write("if ((");
//	WriteVariable(variable.GetName(), nLoopLevel);
	WriteVariable(variable, nLoopLevel);
	m_pFs->Write(" = (");
	m_pFs->Write(variable.GetDataType().GetTypeString());
	m_pFs->Write(" ");
	for (i = 0; i < nPointer; i++) {
		m_pFs->Write("*");
	}
	m_pFs->Write(")malloc(");
	m_pFs->Write(lpszSize);
	m_pFs->Write(" * sizeof(");
	m_pFs->Write(variable.GetDataType().GetTypeString());
	if (nPointer > 1) {
		m_pFs->Write(" ");
		for (i = 0; i < nPointer - 1; i++) {
			m_pFs->Write("*");
		}
	}
	m_pFs->Write("))) == NULL) {");
	WriteEOL(1);

	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("return -2;");
	WriteEOL(1);

	WriteIndent(nLoopLevel + 1);
	m_pFs->Write("}");
	WriteEOL(1);
}

void CodeWriterForC::WriteFree(Variable& variable, int nLoopLevel)
{
	WriteIndent(nLoopLevel + 1);
	m_pFs->Write("free(");
//	WriteVariable(variable.GetName(), nLoopLevel);
	WriteVariable(variable, nLoopLevel);
	m_pFs->Write(");");
	WriteEOL(1);
}
// e


/*
void CodeWriterForC::WriteRead(DataType1 nType, 
						   int nReadLevel, int nVarLevel,
						   LPCTSTR lpszVariable,
						   LPCTSTR lpszSize)
{
	int nPointer = nVarLevel - nReadLevel;
	if (nPointer < 0) {
		return;
	}

	WriteIndent(nReadLevel + 1);
	m_pFs->Write("if (fread(");
	if (!nPointer) {
		m_pFs->Write("&");
	}
	WriteVariable(lpszVariable, nReadLevel);
	m_pFs->Write(", ");
	if (lpszSize != NULL) {
		m_pFs->Write(lpszSize);
		m_pFs->Write(" * ");
	}
	m_pFs->Write("sizeof(");
	m_pFs->Write(GetTypeString(nType));
	m_pFs->Write("), 1, fp) != 1) {");
	WriteEOL(1);

	WriteIndent(nReadLevel + 1);
	m_pFs->Write(m_szIndent);
	m_pFs->Write("return -1;");
	WriteEOL(1);

	WriteIndent(nReadLevel + 1);
	m_pFs->Write("}");
	WriteEOL(1);
}
*/
// s
void CodeWriterForC::WriteRead(Variable& variable,
							   int nLoopLevel, LPCTSTR lpszSize)
{
	int nPointer = variable.GetLoopLevel() - nLoopLevel;
	if (nPointer < 0) {
		return;
	}

	WriteIndent(nLoopLevel + 1);
	m_pFs->Write("if (fread(");
	if (!nPointer) {
		m_pFs->Write("&");
	}
//	WriteVariable(variable.GetName(), nLoopLevel);
	WriteVariable(variable, nLoopLevel);
	m_pFs->Write(", ");
	if (lpszSize != NULL) {
		m_pFs->Write(lpszSize);
		m_pFs->Write(" * ");
	}
	m_pFs->Write("sizeof(");
	m_pFs->Write(variable.GetDataType().GetTypeString());
	m_pFs->Write("), 1, fp) != 1) {");
	WriteEOL(1);

	WriteIndent(nLoopLevel + 1);
	m_pFs->Write(m_szIndent);
	m_pFs->Write("return -1;");
	WriteEOL(1);

	WriteIndent(nLoopLevel + 1);
	m_pFs->Write("}");
	WriteEOL(1);
}
// e

/*
void CodeWriterForC::WriteDeclareVariable(DataType1 nType, int nPointer,
									  LPCTSTR lpszVariable)
{
	WriteIndent(1);
	m_pFs->Write(GetTypeString(nType));
	m_pFs->Write(" ");
	volatile int i;
	for (i = 0; i < nPointer; i++) {
		m_pFs->Write("*");
	}
	m_pFs->Write(lpszVariable);
	m_pFs->Write(";");
	WriteEOL(1);
}
*/

// s
void CodeWriterForC::WriteDeclareVariable(Variable& variable)
{
	WriteIndent(1);
	m_pFs->Write(variable.GetDataType().GetTypeStringAndBlank());
	volatile int i;
	for (i = 0; i < variable.GetLoopLevel(); i++) {
		m_pFs->Write("*");
	}
	m_pFs->Write(variable.GetName());
	m_pFs->Write(";");
	WriteEOL(1);
}
// e

void CodeWriterForC::WriteDeclareFileDesc()
{
	WriteIndent(1);
	m_pFs->Write("FILE *fp;");
	WriteEOL(1);
}
