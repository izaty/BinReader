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
	WriteLine(0, 1, "}");
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
}

void CodeWriterForCSharp::WriteFileOpen()
{
	WriteLine(2, 1,		"using (FileStream fis = new FileStream(filePath,");
	WriteLine(3, 2,			"FileMode.Open, FileAccess.Read)) {");

	WriteLine(3, 1,			"byte[] bytes = new byte[fis.Length];");
}

void CodeWriterForCSharp::WriteFileClose()
{
	WriteLine(2, 1,		"}");
//	WriteLine(2, 1, "fis.Close();");
}

void CodeWriterForCSharp::WriteLoopStart(int nLoopLevel, LPCTSTR lpszCount)
{
	LPTSTR lpszVariable = m_pLim->GetVariableString(nLoopLevel);
	WriteIndent(nLoopLevel + 3);
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
	WriteLine(nLoopLevel + 3, 1, "}");
}

void CodeWriterForCSharp::WriteAllocate(Variable& variable,
									  int nLoopLevel, LPCTSTR lpszSize)
{
	int nPointer = variable.GetLoopLevel() - nLoopLevel;
	if (nPointer < 0) {
		return;
	}

	volatile int i;

	WriteIndent(nLoopLevel + 3);
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
		if (variable.GetDataType().IsOneByte()) {
			WriteIndent(nLoopLevel + 3);
			m_pFs->Write("fis.Read(");
			WriteVariable(variable, nLoopLevel);
			m_pFs->Write(", 0, ");
			m_pFs->Write(lpszSize);
			m_pFs->Write(");");
			WriteEOL(1);
		}
		else {
			WriteLoopStart(nLoopLevel, lpszSize);
			WriteIndent(nLoopLevel + 4);
			m_pFs->Write("fis.Read(bytes, 0, sizeof(");
			m_pFs->Write(variable.GetDataType().GetTypeString());
			m_pFs->Write("));");
			WriteEOL(1);

			if (IsEndianConvEnabled()) {
				WriteIndent(nLoopLevel + 4);
				m_pFs->Write("Array.Reverse(bytes, 0, sizeof(");
				m_pFs->Write(variable.GetDataType().GetTypeString());
				m_pFs->Write("));");
				WriteEOL(1);
			}

			WriteIndent(nLoopLevel + 4);
			WriteVariable(variable, nLoopLevel + 1);
			m_pFs->Write(" = BitConverter.To");
			m_pFs->Write(variable.GetDataType().GetTypeString2());
			m_pFs->Write("(bytes, 0);");
			WriteEOL(1);

			WriteLoopEnd(nLoopLevel, lpszSize);
		}
	}
	else {
		WriteIndent(nLoopLevel + 3);
		if (variable.GetDataType().IsOneByte()) {
			WriteVariable(variable, nLoopLevel);
			m_pFs->Write(" = fis.ReadByte();");
			WriteEOL(1);
		}
		else {
			m_pFs->Write("fis.Read(bytes, 0, sizeof(");
			m_pFs->Write(variable.GetDataType().GetTypeString());
			m_pFs->Write("));");
			WriteEOL(1);

			if (IsEndianConvEnabled()) {
				WriteIndent(nLoopLevel + 3);
				m_pFs->Write("Array.Reverse(bytes, 0, sizeof(");
				m_pFs->Write(variable.GetDataType().GetTypeString());
				m_pFs->Write("));");
				WriteEOL(1);
			}

			WriteIndent(nLoopLevel + 3);
			WriteVariable(variable, nLoopLevel);
			m_pFs->Write(" = BitConverter.To");
			m_pFs->Write(variable.GetDataType().GetTypeString2());
			m_pFs->Write("(bytes, 0);");
			WriteEOL(1);
		}
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
	WriteLine(1, 1, "static int Main() {");
	WriteLine(2, 1,		"string[] args = Environment.GetCommandLineArgs();");
	WriteLine(2, 1,		"if (args.Length != 2) {");
	WriteLine(3, 1,			"Console.WriteLine(\"Usage: {0} filename\", args[0]);");
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