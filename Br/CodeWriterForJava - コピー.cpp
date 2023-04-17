#include "StdAfx.h"
#include "CodeWriterForJava.h"

CodeWriterForJava::CodeWriterForJava(FileStream *pFs,
									 LoopIndexManager *pLim) : CodeWriter(pFs, pLim)
{
	m_bFreeRequired = FALSE;
}

CodeWriterForJava::~CodeWriterForJava(void)
{
}

void CodeWriterForJava::WriteTop()
{
	WriteLine(0, 1, "import java.io.DataInputStream;");
	WriteLine(0, 1, "import java.io.FileInputStream;");
	WriteLine(0, 2, "import java.io.IOException;");

	if (m_bEndian) {
		WriteLine(0, 1, "import java.nio.ByteBuffer;");
		WriteLine(0, 2, "import java.nio.ByteOrder;");
	}

	WriteLine(0, 1, "public class MyBinaryReader {");
}

void CodeWriterForJava::WriteFuncStart()
{
	WriteLine(1, 2, "public MyBinaryReader() {}");
	WriteLine(1, 1, "public void read(String filePath) throws IOException {");
}

void CodeWriterForJava::WriteFuncEnd()
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

void CodeWriterForJava::WriteFileOpen()
{
	WriteLine(2, 1, "DataInputStream dis = new DataInputStream(fis);");

	if (m_bEndian) {
		WriteIndent(2);
		m_pFs->Write("ByteOrder bo = ByteOrder.");
		if (m_bLittleEndian) {
			m_pFs->Write("LITTLE_ENDIAN;");
		}
		else {
			m_pFs->Write("BIG_ENDIAN;");
		}
		WriteEOL(1);
	}
}

void CodeWriterForJava::WriteFileClose()
{
	WriteLine(2, 1, "dis.close();");
	WriteLine(2, 1, "fis.close();");
}

void CodeWriterForJava::WriteLoopStart(int nLoopLevel, LPCTSTR lpszCount)
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

void CodeWriterForJava::WriteLoopEnd(int nLoopLevel, LPCTSTR lpszCount)
{
	WriteLine(nLoopLevel + 2, 1, "}");
}

void CodeWriterForJava::WriteAllocate(Variable& variable,
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
	m_pFs->Write("[");
	m_pFs->Write(lpszSize);
	m_pFs->Write("]");
	for (i = 1; i < nPointer; i++) {
		m_pFs->Write("[]");
	}
	m_pFs->Write(";");
	WriteEOL(1);
}

void CodeWriterForJava::WriteFree(Variable& variable, int nLoopLevel)
{
	WriteIndent(nLoopLevel + 2);
	WriteVariable(variable, nLoopLevel);
	m_pFs->Write(" = null;");
	WriteEOL(1);
}

void CodeWriterForJava::WriteRead(Variable& variable,
								  int nLoopLevel, LPCTSTR lpszSize)
{
	int nPointer = variable.GetLoopLevel() - nLoopLevel;
	if (nPointer < 0) {
		return;
	}

	if (lpszSize != NULL) {
		WriteLoopStart(nLoopLevel, lpszSize);
		WriteIndent(nLoopLevel + 3);
		WriteVariable(variable, nLoopLevel + 1);
		if (m_bEndian && !variable.GetDataType().IsOneByte()) {
//			m_pFs->Write(" = readBuf(dis, bo, sizeof(");
//			m_pFs->Write(variable.GetDataType().GetTypeString());
//			m_pFs->Write(")).get");
			m_pFs->Write(" = readBuf(dis, bo, %d).get",
				variable.GetDataType().GetSize());
		}
		else {
			m_pFs->Write(" = dis.read");
		}

		{
			LPTSTR lpszOrg = variable.GetDataType().GetTypeString();
			LPTSTR lpszNew = new TCHAR[_tcslen(lpszOrg)+1];
			_tcscpy(lpszNew, lpszOrg);
			if (lpszNew[0] != _T('\0')) {
				lpszNew[0] -= 32;
				m_pFs->Write(lpszNew);
			}
			delete [] lpszNew;
		}

		m_pFs->Write("();");
		WriteEOL(1);
		WriteLoopEnd(nLoopLevel, lpszSize);
	}
	else {
		WriteIndent(nLoopLevel + 2);
		WriteVariable(variable, nLoopLevel);
		if (m_bEndian && !variable.GetDataType().IsOneByte()) {
//			m_pFs->Write(" = readBuf(dis, bo, sizeof(");
//			m_pFs->Write(variable.GetDataType().GetTypeString());
//			m_pFs->Write(")).get");
			m_pFs->Write(" = readBuf(dis, bo, %d).get",
				variable.GetDataType().GetSize());
		}
		else {
			m_pFs->Write(" = dis.read");
		}

		{
			LPTSTR lpszOrg = variable.GetDataType().GetTypeString();
			LPTSTR lpszNew = new TCHAR[_tcslen(lpszOrg)+1];
			_tcscpy(lpszNew, lpszOrg);
			if (lpszNew[0] != _T('\0')) {
				lpszNew[0] -= 32;
				m_pFs->Write(lpszNew);
			}
			delete [] lpszNew;
		}

		m_pFs->Write("();");
		WriteEOL(1);
	}
}

void CodeWriterForJava::WriteDeclareVariable(Variable& variable)
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

void CodeWriterForJava::WriteDeclareFileDesc()
{
	WriteIndent(2);
	m_pFs->Write("FileInputStream fis = new FileInputStream(filePath);");
}

void CodeWriterForJava::WriteDeclareLoopIndices(int nLoopLevel)
{
	WriteIndent(1);
	CodeWriter::WriteDeclareLoopIndices(nLoopLevel);
}

void CodeWriterForJava::WriteDriver()
{
	WriteLine(1, 1, "public static void main(String[] args) {");
	WriteLine(2, 1,		"if (args.length != 1) {");
	WriteLine(3, 1,			"System.err.println(\"Usage: java MyBinaryReader filename\");");
	WriteLine(3, 1,			"System.exit(-999);");
	WriteLine(2, 1,		"}");
	WriteLine(2, 1,		"try {");
	WriteLine(3, 1,			"MyBinaryReader br = new MyBinaryReader();");
	WriteLine(3, 1,			"br.read(args[0]);");
	WriteLine(2, 1,		"} catch (IOException e) {");
	WriteLine(3, 1,			"throw new RuntimeException(e.toString());");// e.printStackTrace();
	WriteLine(2, 1,		"}");
	WriteLine(1, 1, "}");
}

void CodeWriterForJava::WriteEndianConv()
{
	WriteLine(1, 1, "public static ByteBuffer readBuf(DataInputStream dis, ByteOrder bo, int size) throws IOException {");
	WriteLine(2, 1,		"byte[] buf = new byte[size];");
	WriteLine(2, 1,		"int nbytes = dis.read(buf);");
	WriteLine(2, 1,		"if (nbytes != size) {");
	WriteLine(3, 1,			"throw new IOException(\"Unexpected End of Stream\");");
	WriteLine(2, 1,		"}");
	WriteLine(2, 1,		"return ByteBuffer.wrap(buf).order(bo);");
	WriteLine(1, 1, "}");
}