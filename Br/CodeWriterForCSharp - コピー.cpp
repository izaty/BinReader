#include "StdAfx.h"
#include "CodeWriterForCSharp.h"

CodeWriterForCSharp::CodeWriterForCSharp(FileStream *pFs,
										 LoopIndexManager *pLim) : CodeWriter(pFs, pLim)
{
	m_bFreeRequired = FALSE;
}

CodeWriterForCSharp::~CodeWriterForCSharp(void)
{
}

void CodeWriterForCSharp::WriteStart()
{
	WriteLine(0, 1, "using System;");
	WriteLine(0, 2, "using System.IO;");

	WriteLine(0, 1, "class MyBinaryReader {");
}

void CodeWriterForCSharp::WriteEnd()
{
}

void CodeWriterForCSharp::WriteFuncStart()
{
	WriteLine(1, 2, "public MyBinaryReader() {}");
	WriteLine(1, 1, "public void read(String filePath) {");
}

void CodeWriterForCSharp::WriteFuncEnd()
{
	WriteLine(1, 1, "}");

	// Endian
	if (IsEndianConvEnabled()) {
		WriteEOL(1);
		WriteEndianConv();
	}

	// Driver
	if (IsDriverEnabled()) {
		WriteEOL(1);
		WriteDriver();
	}

	WriteLine(0, 1, "}");
}

void CodeWriterForCSharp::WriteFileOpen()
{
	WriteLine(2, 1,		"using (FileStream fis = new FileStream(filePath,");
	WriteLine(3, 2,			"FileMode.Open, FileAccess.Read)) {");

	WriteLine(3, 1,			"byte[] bytes = new byte[fis.Length];");
	WriteLine(3, 1,			"int numBytesToRead = (int)fis.Length;");
	WriteLine(3, 1,			"int numBytesRead = 0;");
	WriteLine(3, 2,			"int numBytesRet;");

	WriteLine(3, 1,			"while (numBytesToRead > 0) {");
}

void CodeWriterForCSharp::WriteFileClose()
{
	WriteLine(4, 1,				"if (numBytesRet == 0) {");
	WriteLine(5, 1,					"break;");
	WriteLine(4, 1,				"}");
	WriteLine(4, 1,				"numBytesRead += numBytesRet;");
	WriteLine(4, 1,				"numBytesToRead -= numBytesRet;");
	WriteLine(3, 1,			"}");
	WriteLine(2, 1,		"}");
//	WriteLine(2, 1, "fis.Close();");
}

void CodeWriterForCSharp::WriteLoopStart(int nLoopLevel, LPCTSTR lpszCount)
{
	LPTSTR lpszVariable = m_pLim->GetVariableString(nLoopLevel);
	WriteIndent(nLoopLevel + 4);
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

void CodeWriterForCSharp::WriteLoopEnd(int nLoopLevel, LPCTSTR lpszCount)
{
	WriteLine(nLoopLevel + 4, 1, "}");
}

void CodeWriterForCSharp::WriteAllocate(Variable& variable,
									  int nLoopLevel, LPCTSTR lpszSize)
{
	int nPointer = variable.GetLoopLevel() - nLoopLevel;
	if (nPointer < 0) {
		return;
	}

	volatile int i;

	WriteIndent(nLoopLevel + 4);
	WriteVariable(variable, nLoopLevel);
	m_pFs->Write(" = new ");
	m_pFs->Write(variable.GetDataType().GetTypeString());
	m_pFs->Write("[");
	m_pFs->Write(lpszSize);
	m_pFs->Write("]");
	for (i = 1; i < nPointer; i++) {
		m_pFs->Write("[]");
	}
	m_pFs->Write(";");
	WriteEOL(1);
}

void CodeWriterForCSharp::WriteFree(Variable& variable, int nLoopLevel)
{
//	WriteIndent(nLoopLevel + 2);
//	WriteVariable(variable, nLoopLevel);
//	m_pFs->Write(" = null;");
//	WriteEOL(1);
}

void CodeWriterForCSharp::WriteRead(Variable& variable,
									int nLoopLevel, LPCTSTR lpszSize)
{
	int nPointer = variable.GetLoopLevel() - nLoopLevel;
	if (nPointer < 0) {
		return;
	}

	if (lpszSize != NULL) {
		WriteLoopStart(nLoopLevel, lpszSize);
		WriteIndent(nLoopLevel + 5);
		m_pFs->Write("numBytesRet = fis.Read(bytes, 0, sizeof(");
		m_pFs->Write(variable.GetDataType().GetTypeString());
		m_pFs->Write("));");
		WriteEOL(1);

		WriteIndent(nLoopLevel + 5);
		WriteVariable(variable, nLoopLevel + 1);
		m_pFs->Write(" = BitConverter.To");

		m_pFs->Write(variable.GetDataType().GetTypeString2());

		m_pFs->Write("(bytes");
		if (IsEndianConvEnabled()) {
			if (!variable.GetDataType().IsOneByte()) {
				m_pFs->Write(".Reverse().ToArray()");
			}
		}
		m_pFs->Write(", 0);");
		WriteEOL(1);

		WriteLoopEnd(nLoopLevel, lpszSize);
	}
	else {
		WriteIndent(nLoopLevel + 4);
		m_pFs->Write("numBytesRet = fis.Read(bytes, 0, sizeof(");
		m_pFs->Write(variable.GetDataType().GetTypeString());
		m_pFs->Write("));");
		WriteEOL(1);

		WriteIndent(nLoopLevel + 4);
		WriteVariable(variable, nLoopLevel);
		m_pFs->Write(" = BitConverter.To");

		m_pFs->Write(variable.GetDataType().GetTypeString2());

		m_pFs->Write("(bytes");
		if (IsEndianConvEnabled()) {
			if (!variable.GetDataType().IsOneByte()) {
				m_pFs->Write(".Reverse().ToArray()");
			}
		}
		m_pFs->Write(", 0);");
		WriteEOL(1);
	}
}

void CodeWriterForCSharp::WriteDeclareVariable(Variable& variable)
{
	if (m_bUseLocal) {
		WriteIndent(2);
	}
	else {
		WriteIndent(1);
		m_pFs->Write("public ");
	}
	m_pFs->Write(variable.GetDataType().GetTypeString());
	volatile int i;
	for (i = 0; i < variable.GetLoopLevel(); i++) {
		m_pFs->Write("[]");
	}
	m_pFs->Write(" ");
	m_pFs->Write(variable.GetName());
	m_pFs->Write(";");
	WriteEOL(1);
}

void CodeWriterForCSharp::WriteDeclareFileDesc()
{
//	WriteIndent(2);
//	m_pFs->Write("using (FileStream fis = new FileStream(filePath, FileMode.Open)) {");
}

void CodeWriterForCSharp::WriteDeclareLoopIndices(int nLoopLevel)
{
	WriteIndent(1);
	CodeWriter::WriteDeclareLoopIndices(nLoopLevel);
}

void CodeWriterForCSharp::WriteDriver()
{
	WriteLine(1, 1, "static int Main(String[] args) {");
	WriteLine(2, 1,		"if (args.Length != 1) {");
	WriteLine(3, 1,			"Console.WriteLine(\"Usage: MyBinaryReader filename\");");
	WriteLine(3, 1,			"return -999;");
	WriteLine(2, 1,		"}");
	WriteLine(2, 1,		"try {");
	WriteLine(3, 1,			"MyBinaryReader br = new MyBinaryReader();");
	WriteLine(3, 1,			"br.read(args[0]);");
	WriteLine(2, 1,		"} catch (IOException) {");
	WriteLine(3, 1,			"return -1;");
	WriteLine(2, 2,		"}");
	WriteLine(2, 1,		"return 0;");
	WriteLine(1, 1, "}");
}

void CodeWriterForCSharp::WriteEndianConv()
{
}