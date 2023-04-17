#include "StdAfx.h"
#include "CodeWriter.h"

CodeWriter::CodeWriter(FileStream *pFs, LoopIndexManager *pLim)
{
	SetIndent(IT_SPACE4);
	SetNewLine(NL_RN);
	m_bDriver = FALSE;
	m_bEndian = FALSE;
	m_bLittleEndian = FALSE;
	// Added on Mar.21,'16
	// start
	m_bWriteFunc = TRUE;
	// end
	m_pFs = pFs;
	m_pLim = pLim;

	m_bClearRequired = TRUE;
}

CodeWriter::~CodeWriter(void)
{
}

static LPCTSTR _lpszTab1	= _T("\t");
static LPCTSTR _lpszTab2	= _T("\t\t");
static LPCTSTR _lpszSpace4	= _T("    ");
static LPCTSTR _lpszSpace8	= _T("        ");

void CodeWriter::SetIndent(IndentType nType)
{
	if (nType == IT_TAB1) {
		SetIndent(_lpszTab1);
	}
	else if (nType == IT_TAB2) {
		SetIndent(_lpszTab2);
	}
	else if (nType == IT_SPACE4) {
		SetIndent(_lpszSpace4);
	}
	else if (nType == IT_SPACE8) {
		SetIndent(_lpszSpace8);
	}
}

void CodeWriter::SetIndent(LPCTSTR lpsz)
{
	int nLen = (int)_tcslen(lpsz);
	if (nLen < _MAX_INDENT) {
		lstrcpy(m_szIndent, lpsz);
	}
	else {
		_tcsncpy_s(m_szIndent, lpsz, _MAX_INDENT - 1);
		m_szIndent[_MAX_INDENT-1] = _T('\0');
	}
}

static LPCTSTR _lpszN	= _T("\n");
static LPCTSTR _lpszRN	= _T("\r\n");

void CodeWriter::SetNewLine(NewLineType nType)
{
	if (nType == NL_N) {
		SetNewLine(_lpszN);
	}
	if (nType == NL_RN) {
		SetNewLine(_lpszRN);
	}
}

void CodeWriter::SetNewLine(LPCTSTR lpsz)
{
	int nLen = (int)_tcslen(lpsz);
	if (nLen < _MAX_NEW_LINE) {
		lstrcpy(m_szNewLine, lpsz);
	}
	else {
		_tcsncpy_s(m_szIndent, lpsz, _MAX_NEW_LINE - 1);
		m_szNewLine[_MAX_NEW_LINE-1] = _T('\0');
	}

}

CodeWriter::IndentType CodeWriter::GetIndentType()
{
	IndentType nType = IT_OTHER;
	if (!_tcscmp(m_szIndent, _lpszTab1)) {
		nType = IT_TAB1;
	}
	if (!_tcscmp(m_szIndent, _lpszTab2)) {
		nType = IT_TAB2;
	}
	else if (!_tcscmp(m_szIndent, _lpszSpace4)) {
		nType = IT_SPACE4;
	}
	else if (!_tcscmp(m_szIndent, _lpszSpace8)) {
		nType = IT_SPACE8;
	}
	return nType;
}

CodeWriter::NewLineType CodeWriter::GetNewLineType()
{
	NewLineType nType = NL_N;
//	if (!_tcscmp(m_szNewLine, _lpszN)) {
//		nType = NL_N;
//	}
	if (!_tcscmp(m_szNewLine, _lpszRN)) {
		nType = NL_RN;
	}
	return nType;
}

void CodeWriter::WriteIndent(int nCount)
{
	volatile int i;
	for (i = 0; i < nCount; i++) {
		m_pFs->Write(m_szIndent);
	}
}

void CodeWriter::WriteEOL(int nCount)
{
	volatile int i;
	for (i = 0; i < nCount; i++) {
		m_pFs->Write(m_szNewLine);
	}
}

void CodeWriter::WriteLine(int nIndent, int nEOL, LPCTSTR lpsz)
{
	WriteIndent(nIndent);
	m_pFs->Write(lpsz);
	WriteEOL(nEOL);
}

void CodeWriter::WriteImplPart()
{
	WriteLine(0, 1, "/*");
	WriteLine(0, 1, " *");
	WriteLine(0, 1, " * To be implemented here");
	WriteLine(0, 1, " *");
	WriteLine(0, 1, " */");
}

void CodeWriter::WriteDeclareLoopIndices(int nLoopLevel)
{
	m_pFs->Write(m_szIndent);
	// numerical type (volatile int, int, ....)
	m_pFs->Write(m_pLim->GetTypeStringAndBlank());
	// loop index varaibles (i0, i1, i2, ....)
	volatile int i;
	for (i = 0; i <= nLoopLevel; i++) {
		m_pFs->Write(m_pLim->GetVariableString(i));
		if (i == nLoopLevel) {	// last index
			m_pFs->Write(";");
			WriteEOL(1);
		}
		else {					// to be continued
			m_pFs->Write(", ");
		}
	}
}

void CodeWriter::WriteVariable(Variable& variable, int nLoopLevel)
{
	m_pFs->Write(variable.GetName());
	for (volatile int i = 0; i < nLoopLevel; i++) {
		m_pFs->Write("[%s]", m_pLim->GetVariableString(i));
	}
}

void CodeWriter::WriteClearFuncStart()
{
}

void CodeWriter::WriteClearFuncEnd()
{
}