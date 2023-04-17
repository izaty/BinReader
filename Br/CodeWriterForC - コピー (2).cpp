#include "StdAfx.h"
#include "CodeWriterForC.h"

CodeWriterForC::CodeWriterForC(FileStream *pFs,
							   LoopIndexManager *pLim) : CodeWriter(pFs, pLim)
{
}

CodeWriterForC::~CodeWriterForC(void)
{
}

void CodeWriterForC::WriteStart()
{
	WriteLine(0, 1, "#include <stdio.h>");
	WriteLine(0, 2, "#include <stdlib.h>");
}

void CodeWriterForC::WriteEnd()
{
}

void CodeWriterForC::WriteFuncStart()
{
	// Endian
	if (IsEndianConvEnabled()) {
		WriteEndianConv();
		WriteEOL(1);
	}

	WriteLine(0, 1, "int readBinary(char *filePath)");
	WriteLine(0, 1, "{");
}

void CodeWriterForC::WriteFuncEnd()
{
	WriteLine(1, 1,		"return 0;");
	WriteLine(0, 1, "}");
}

void CodeWriterForC::WriteFileOpen()
{
	WriteLine(1, 1,		"if ((fp = fopen(filePath, \"rb\")) == NULL) {");
	WriteLine(2, 1,			"return -3;");
	WriteLine(1, 1,		"}");
}

void CodeWriterForC::WriteFileClose()
{
	WriteLine(1, 1,		"fclose(fp);");
}

void CodeWriterForC::WriteLoopStart(int nLoopLevel, LPCTSTR lpszCount)
{
	LPTSTR lpszVariable = m_pLim->GetVariableString(nLoopLevel);
	WriteIndent(nLoopLevel + 1);
	m_pFs->Write("for (");
	m_pFs->Write(lpszVariable);
	m_pFs->Write(" = 0; ");
	m_pFs->Write(lpszVariable);
	m_pFs->Write(" < ");
	m_pFs->Write(lpszCount);
	m_pFs->Write("; ");
	m_pFs->Write(lpszVariable);
	m_pFs->Write("++) {");
	WriteEOL(1);
}

void CodeWriterForC::WriteLoopEnd(int nLoopLevel, LPCTSTR lpszCount)
{
	WriteLine(nLoopLevel + 1, 1, "}");
}

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

	WriteLine(nLoopLevel + 2, 1, "return -2;");
	WriteLine(nLoopLevel + 1, 1, "}");
}

void CodeWriterForC::WriteFree(Variable& variable, int nLoopLevel)
{
	WriteIndent(nLoopLevel + 1);
	m_pFs->Write("free(");
	WriteVariable(variable, nLoopLevel);
	m_pFs->Write(");");
	WriteEOL(1);
}

void CodeWriterForC::WriteRead(Variable& variable,
							   int nLoopLevel, LPCTSTR lpszSize)
{
	int nPointer = variable.GetLoopLevel() - nLoopLevel;
	if (nPointer < 0) {
		return;
	}

	WriteIndent(nLoopLevel + 1);
	if (IsEndianConvEnabled()) {
		m_pFs->Write("if (eread(");
	}
	else {
		m_pFs->Write("if (fread(");
	}
	if (!nPointer) {
		m_pFs->Write("&");
	}
	WriteVariable(variable, nLoopLevel);
	m_pFs->Write(", ");

	m_pFs->Write("sizeof(");
	m_pFs->Write(variable.GetDataType().GetTypeString());
	m_pFs->Write("), ");

	if (lpszSize != NULL) {
		m_pFs->Write(lpszSize);
		m_pFs->Write(", ");
	}
	else {
		m_pFs->Write("1, ");
	}

	m_pFs->Write("fp) != ");

	if (lpszSize != NULL) {
		m_pFs->Write(lpszSize);
	}
	else {
		m_pFs->Write("1");
	}

	m_pFs->Write(") {");

	WriteEOL(1);

	WriteLine(nLoopLevel + 2, 1, "return -1;");
	WriteLine(nLoopLevel + 1, 1, "}");
}

void CodeWriterForC::WriteDeclareVariable(Variable& variable)
{
	if (m_bUseLocal) {
		WriteIndent(1);
	}
	m_pFs->Write(variable.GetDataType().GetTypeStringAndBlank());
	volatile int i;
	for (i = 0; i < variable.GetLoopLevel(); i++) {
		m_pFs->Write("*");
	}
	m_pFs->Write(variable.GetName());
	m_pFs->Write(";");
	WriteEOL(1);
}

void CodeWriterForC::WriteDeclareFileDesc()
{
	WriteLine(1, 1,		"FILE *fp;");
}

void CodeWriterForC::WriteDriver()
{
	WriteLine(0, 1,	"int main(int argc, char **argv)");
	WriteLine(0, 1,	"{");
	WriteLine(1, 2,		"int err_code;");

	WriteLine(1, 1,		"if (argc != 2) {");
	WriteLine(2, 1,			"fprintf(stderr, \"Usage: %%s filename\\n\", argv[0]);");
	WriteLine(2, 1,			"return -999;");
	WriteLine(1, 2,		"}");

	WriteLine(1, 2,		"err_code = readBinary(argv[1]);");

	WriteLine(1, 1,		"if (err_code == -1) {");
	WriteLine(2, 1,			"fprintf(stderr, \"read error\\n\");");
	WriteLine(2, 1,			"return err_code;");
	WriteLine(1, 1,		"}");
	WriteLine(1, 1,		"if (err_code == -2) {");
	WriteLine(2, 1,			"fprintf(stderr, \"allocation error\\n\");");
	WriteLine(2, 1,			"return err_code;");
	WriteLine(1, 1,		"}");
	WriteLine(1, 1,		"if (err_code == -3) {");
	WriteLine(2, 1,			"fprintf(stderr, \"open error\\n\");");
	WriteLine(2, 1,			"return err_code;");
	WriteLine(1, 2,		"}");

	WriteLine(1, 1,		"return 0;");
	WriteLine(0, 1,	"}");
}

void CodeWriterForC::WriteEndianConv()
{
	WriteLine(0, 1, "size_t eread(void *ptr, size_t size, size_t n, FILE *stream)");
	WriteLine(0, 1, "{");
	WriteLine(1, 1,		"size_t ret_code;");
	WriteLine(1, 1,		"if (size > 1) {");
	WriteLine(2, 1,			"int i, j;");
	WriteLine(2, 1,			"unsigned char ic[64];");
	WriteLine(2, 2,			"unsigned char *oc = (unsigned char *)ptr;");

	WriteLine(2, 2,			"ret_code = fread(oc, size, n, stream);");

	WriteLine(2, 1,			"for (i = 0; i < n; i++) {");
	WriteLine(3, 1,				"int base = i * size;");
	WriteLine(3, 1,				"for (j = 0; j < size; j++) {");
	WriteLine(4, 1,					"ic[size-j-1] = oc[base+j];");
	WriteLine(3, 1,				"}");
	WriteLine(3, 1,				"for (j = 0; j < size; j++) {");
	WriteLine(4, 1,					"oc[base+j] = ic[j];");
	WriteLine(3, 1,				"}");
	WriteLine(2, 1,			"}");
	WriteLine(1, 1,		"}");
	WriteLine(1, 1,		"else {");
	WriteLine(2, 1,			"ret_code = fread(ptr, size, n, stream);");
	WriteLine(1, 2,		"}");

	WriteLine(1, 1,		"return ret_code;");
	WriteLine(0, 1, "}");
}