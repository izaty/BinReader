#include "StdAfx.h"
#include "CodeWriterForCplus.h"

CodeWriterForCplus::CodeWriterForCplus(FileStream *pFs,
									   LoopIndexManager *pLim) : CodeWriter(pFs, pLim)
{
}

CodeWriterForCplus::~CodeWriterForCplus(void)
{
}

void CodeWriterForCplus::WriteStart()
{
	WriteLine(0, 1, "#include <iostream>");
	WriteLine(0, 1, "#include <fstream>");
	WriteLine(0, 1, "#include <new>");
	WriteLine(0, 2, "using namespace std;");

	WriteLine(0, 1, "class MyBinaryReader");
	WriteLine(0, 1, "{");
	WriteLine(0, 1, "public:");
}

void CodeWriterForCplus::WriteEnd()
{
}

void CodeWriterForCplus::WriteFuncStart()
{
	WriteLine(0, 1, "protected:");
	WriteLine(1, 2,     "bool emptyContents;");

	WriteLine(0, 1, "public:");
	WriteLine(1, 1,		"MyBinaryReader() {emptyContents = true;}");
	WriteLine(1, 2,		"~MyBinaryReader() {deleteContents();}");

	WriteLine(1, 1,		"int read(char *filePath);");

	// Appended on Mar.21,'16
	// start
	if (IsWriteFuncEnabled()) {
		WriteLine(1, 1,	"int write(char *filePath);");
	}
	// end

	// Endian
	if (IsEndianConvEnabled()) {
		WriteLine(1, 1,	"void endianConvert(void *ptr, size_t size, size_t n);");
	}

	// Clear
	WriteLine(1, 1,     "void deleteContents();");

	WriteLine(0, 2, "};");

	WriteLine(0, 1, "int MyBinaryReader::read(char *filePath)");
	WriteLine(0, 1, "{");
}

void CodeWriterForCplus::WriteFuncEnd()
{
	WriteLine(1, 2,		"emptyContents = false;");

	WriteLine(1, 1,		"return 0;");
	WriteLine(0, 1, "}");

	// Endian
	if (IsEndianConvEnabled()) {
		WriteEOL(1);
		WriteEndianConv();
	}
}

void CodeWriterForCplus::WriteFileOpen()
{	
	WriteLine(2, 1,			"fin.open(filePath, ios::in | ios::binary);");
	WriteLine(2, 1,			"if (!fin) {");
	WriteLine(3, 1,				"return -3;");
	WriteLine(2, 1,			"}");
}

void CodeWriterForCplus::WriteFileClose()
{
	WriteLine(2, 1,			"fin.close();");
	// try-catch
	WriteLine(1, 1,		"}");
	WriteLine(1, 1,		"catch (bad_alloc) {");
	WriteLine(2, 1,			"return -2;");
	WriteLine(1, 1,		"}");
	//
}

void CodeWriterForCplus::WriteLoopStart(int nLoopLevel, LPCTSTR lpszCount)
{
	LPTSTR lpszVariable = m_pLim->GetVariableString(nLoopLevel);
	WriteIndent(nLoopLevel + 2);
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

void CodeWriterForCplus::WriteLoopEnd(int nLoopLevel, LPCTSTR lpszCount)
{
	WriteLine(nLoopLevel + 2, 1, "}");
}

void CodeWriterForCplus::WriteAllocate(Variable& variable,
									   int nLoopLevel, LPCTSTR lpszSize)
{
	int nPointer = variable.GetLoopLevel() - nLoopLevel;
	if (nPointer < 0) {
		return;
	}

	volatile int i;

	WriteIndent(nLoopLevel + 2);
	WriteVariable(variable, nLoopLevel);
	m_pFs->Write(" = new ");
	m_pFs->Write(variable.GetDataType().GetTypeString());
	for (i = 1; i < nPointer; i++) {
		m_pFs->Write("*");
	}
	m_pFs->Write("[");
	m_pFs->Write(lpszSize);
	m_pFs->Write("];");
	WriteEOL(1);

	// try-catch
	/*
	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("if (");
	WriteVariable(variable, nLoopLevel);
	m_pFs->Write(" == NULL) {");
	WriteEOL(1);

	WriteIndent(nLoopLevel + 3);
	m_pFs->Write("return -2;");
	WriteEOL(1);

	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("}");
	WriteEOL(1);
	*/
	//
}

void CodeWriterForCplus::WriteFree(Variable& variable, int nLoopLevel)
{
	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("delete [] ");
	WriteVariable(variable, nLoopLevel);
	m_pFs->Write(";");
	WriteEOL(1);
}

void CodeWriterForCplus::WriteRead(Variable& variable,
								   int nLoopLevel, LPCTSTR lpszSize)
{
	int nPointer = variable.GetLoopLevel() - nLoopLevel;
	if (nPointer < 0) {
		return;
	}

	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("fin.read((char *)");
	if (!nPointer) {
		m_pFs->Write("&");
	}
	WriteVariable(variable, nLoopLevel);
	m_pFs->Write(", ");
	if (lpszSize != NULL) {
		m_pFs->Write(lpszSize);
		m_pFs->Write(" * ");
	}
	m_pFs->Write("sizeof(");
	m_pFs->Write(variable.GetDataType().GetTypeString());
	m_pFs->Write("));");
	WriteEOL(1);

	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("if (!fin) {");
	WriteEOL(1);
	WriteIndent(nLoopLevel + 3);
	m_pFs->Write("return -1;");
	WriteEOL(1);
	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("}");
	WriteEOL(1);

	// Endian
	if (IsEndianConvEnabled()) {
		// Modified on Mar.21,'16
		// start
		ConvEndian(variable, nPointer, nLoopLevel, lpszSize);
//		if (!variable.GetDataType().IsOneByte()) {
//			WriteIndent(nLoopLevel + 2);
//			m_pFs->Write("endianConvert(");
//			if (!nPointer) {
//				m_pFs->Write("&");
//			}
//			WriteVariable(variable, nLoopLevel);
//			m_pFs->Write(", ");
//			m_pFs->Write("sizeof(");
//			m_pFs->Write(variable.GetDataType().GetTypeString());
//			m_pFs->Write("), ");
//			if (lpszSize != NULL) {
//				m_pFs->Write(lpszSize);
//			}
//			else {
//				m_pFs->Write("1");
//			}
//			m_pFs->Write(");");
//			WriteEOL(1);
//		}
		// end
	}
}

void CodeWriterForCplus::WriteDeclareVariable(Variable& variable)
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

void CodeWriterForCplus::WriteDeclareFileDesc()
{
	// try-catch
	WriteLine(1, 1, "try {");
	WriteLine(2, 1,		"ifstream fin;");
}

void CodeWriterForCplus::WriteDriver()
{
	WriteLine(0, 1, "int main(int argc, char **argv)");
	WriteLine(0, 1, "{");
	// Modified on Mar.21,'16
	// start
	//WriteLine(1, 1,		"if (argc != 2) {");
	//WriteLine(2, 1,			"cerr << \"Usage: \" << argv[0] << \" filename\" << endl;");
	if (IsWriteFuncEnabled()) {
		WriteLine(1, 1,	"if (argc != 3) {");
		WriteLine(2, 1,		"cerr << \"Usage: \" << argv[0] << \" inputfilename outputfilename\" << endl;");
	}
	else {
		WriteLine(1, 1,	"if (argc != 2) {");
		WriteLine(2, 1,		"cerr << \"Usage: \" << argv[0] << \" filename\" << endl;");
	}
	// end
	WriteLine(2, 1,			"return -999;");
	WriteLine(1, 2,		"}");

	WriteLine(1, 2,		"MyBinaryReader br;");

	WriteLine(1, 1,		"int err_code = br.read(argv[1]);");
	WriteLine(1, 1,		"if (err_code == -1) {");
	WriteLine(2, 1,			"cerr << \"read error\" << endl;");
	WriteLine(2, 1,			"return err_code;");
	WriteLine(1, 1,		"}");
	WriteLine(1, 1,		"if (err_code == -2) {");
	WriteLine(2, 1,			"cerr << \"allocation error\" << endl;");
	WriteLine(2, 1,			"return err_code;");
	WriteLine(1, 1,		"}");
	WriteLine(1, 1,		"if (err_code == -3) {");
	WriteLine(2, 1,			"cerr << \"open error\" << endl;");
	WriteLine(2, 1,			"return err_code;");
	WriteLine(1, 2,		"}");

	// Appended on Mar.21,'16
	// start
	if (IsWriteFuncEnabled()) {
		WriteLine(1, 1,	"err_code = br.write(argv[2]);");
		WriteLine(1, 1,	"if (err_code == -4) {");
		WriteLine(2, 1,		"cerr << \"write error\" << endl;");
		WriteLine(2, 1,		"return err_code;");
		WriteLine(1, 1,	"}");
		WriteLine(1, 1,	"if (err_code == -5) {");
		WriteLine(2, 1,		"cerr << \"open error\" << endl;");
		WriteLine(2, 1,		"return err_code;");
		WriteLine(1, 2,	"}");
	}
	// end

	WriteLine(1, 1,		"return 0;");
	WriteLine(0, 1, "}");
}

void CodeWriterForCplus::WriteEndianConv()
{
	WriteLine(0, 1, "void MyBinaryReader::endianConvert(void *ptr, size_t size, size_t n)");
	WriteLine(0, 1, "{");
	WriteLine(1, 1,		"if (size > 1) {");
	WriteLine(2, 1,			"int i, j;");
	// Modified on Mar.21,'16
	// start
	//WriteLine(2, 1,			"unsigned char ic[64];");
	WriteLine(2, 1,			"unsigned char ic[16];");
	// end
	WriteLine(2, 2,			"unsigned char *oc = (unsigned char *)ptr;");

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
	WriteLine(0, 1, "}");
}

void CodeWriterForCplus::WriteClearFuncStart()
{
	WriteLine(0, 1, "void MyBinaryReader::deleteContents()");
	WriteLine(0, 1, "{");
	WriteLine(1, 1,     "if (!emptyContents) {");
}

void CodeWriterForCplus::WriteClearFuncEnd()
{
	WriteEOL(1);
	WriteLine(2, 1,         "emptyContents = true;");
	WriteLine(1, 1,     "}");
	WriteLine(0, 1, "}");
}

// Appended on Mar.21,'16
// start
void CodeWriterForCplus::WriteWFuncStart()
{
	WriteLine(0, 1, "int MyBinaryReader::write(char *filePath)");
	WriteLine(0, 1, "{");
}

void CodeWriterForCplus::WriteWFuncEnd()
{
	WriteLine(1, 1,		"return 0;");
	WriteLine(0, 1, "}");
}

void CodeWriterForCplus::WriteWFileOpen()
{	
	WriteLine(2, 1,			"fout.open(filePath, ios::out | ios::binary);");
	WriteLine(2, 1,			"if (!fout) {");
	WriteLine(3, 1,				"return -5;");
	WriteLine(2, 1,			"}");
}

void CodeWriterForCplus::WriteWFileClose()
{
	WriteLine(2, 1,			"fout.close();");
	WriteLine(1, 1,		"}");
}

void CodeWriterForCplus::WriteWrite(Variable& variable,
									int nLoopLevel, LPCTSTR lpszSize)
{
	int nPointer = variable.GetLoopLevel() - nLoopLevel;
	if (nPointer < 0) {
		return;
	}

	// Endian
	if (IsEndianConvEnabled()) {
		ConvEndian(variable, nPointer, nLoopLevel, lpszSize);
	}

	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("fout.write((char *)");
	if (!nPointer) {
		m_pFs->Write("&");
	}
	WriteVariable(variable, nLoopLevel);
	m_pFs->Write(", ");
	if (lpszSize != NULL) {
		m_pFs->Write(lpszSize);
		m_pFs->Write(" * ");
	}
	m_pFs->Write("sizeof(");
	m_pFs->Write(variable.GetDataType().GetTypeString());
	m_pFs->Write("));");
	WriteEOL(1);

	// Endian
	if (IsEndianConvEnabled()) {
		ConvEndian(variable, nPointer, nLoopLevel, lpszSize);
	}

	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("if (!fout) {");
	WriteEOL(1);
	WriteIndent(nLoopLevel + 3);
	m_pFs->Write("return -4;");
	WriteEOL(1);
	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("}");
	WriteEOL(1);
}

void CodeWriterForCplus::WriteWDeclareFileDesc()
{
	WriteLine(1, 1,		"{");
	WriteLine(2, 1,			"ofstream fout;");
}

void CodeWriterForCplus::ConvEndian(Variable& variable, int nPointer,
									int nLoopLevel, LPCTSTR lpszSize)
{
	if (!variable.GetDataType().IsOneByte()) {
		WriteIndent(nLoopLevel + 2);
		m_pFs->Write("endianConvert(");
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
		}
		else {
			m_pFs->Write("1");
		}
		m_pFs->Write(");");
		WriteEOL(1);
	}
}
// end