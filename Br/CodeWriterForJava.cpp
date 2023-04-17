#include "StdAfx.h"
#include "CodeWriterForJava.h"

CodeWriterForJava::CodeWriterForJava(FileStream *pFs,
									 LoopIndexManager *pLim) : CodeWriter(pFs, pLim)
{
	m_bClearRequired = FALSE;
}

CodeWriterForJava::~CodeWriterForJava(void)
{
}

void CodeWriterForJava::WriteStart()
{
	WriteLine(0, 1, "import java.io.DataInputStream;");
	// Appended on Mar.21,'16
	// start
	if (IsWriteFuncEnabled()) {
		WriteLine(0, 1, "import java.io.DataOutputStream;");
	}
	// end
	WriteLine(0, 1, "import java.io.FileInputStream;");
	// Appended on Mar.21,'16
	// start
	if (IsWriteFuncEnabled()) {
		WriteLine(0, 1, "import java.io.FileOutputStream;");
	}
	// end
	WriteLine(0, 2, "import java.io.IOException;");

	if (IsEndianConvEnabled()) {
		WriteLine(0, 1, "import java.nio.ByteBuffer;");
		WriteLine(0, 2, "import java.nio.ByteOrder;");
	}

	WriteLine(0, 1, "public class MyBinaryReader {");
}

void CodeWriterForJava::WriteEnd()
{
	WriteLine(0, 1, "}");
}

void CodeWriterForJava::WriteFuncStart()
{
	WriteLine(1, 2, "public MyBinaryReader() {}");
	WriteLine(1, 1, "public void read(String filePath) throws IOException {");
}

void CodeWriterForJava::WriteFuncEnd()
{
	WriteLine(1, 1, "}");

	// Deleted on Mar.21,'16
	// start
	// Endian
//	if (IsEndianConvEnabled()) {
//		WriteEOL(1);
//		WriteEndianConv();
//	}
	// end
}

void CodeWriterForJava::WriteFileOpen()
{
	WriteLine(2, 1, "DataInputStream dis = new DataInputStream(fis);");

	if (IsEndianConvEnabled()) {
		WriteIndent(2);
		m_pFs->Write("ByteOrder bo = ByteOrder.");
		if (IsLittleEndian()) {
			m_pFs->Write("LITTLE_ENDIAN;");
		}
		else {
			m_pFs->Write("BIG_ENDIAN;");
		}
		WriteEOL(1);
		// Appended on Mar.21,'16
		// start
		WriteLine(2, 1, "byte bytes[] = new byte[16];");
		// end
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
		if (variable.GetDataType().IsOneByte()) {
			WriteIndent(nLoopLevel + 2);
			m_pFs->Write("dis.read(");
			WriteVariable(variable, nLoopLevel);
			m_pFs->Write(");");
			WriteEOL(1);
		}
		else {
			WriteLoopStart(nLoopLevel, lpszSize);
			WriteIndent(nLoopLevel + 3);
			// Deleted on Mar.21,'16
			// start
			//WriteVariable(variable, nLoopLevel + 1);
			// end
			if (IsEndianConvEnabled()) {
				// Modified on Mar.21,'16
				//m_pFs->Write(" = readBuf(dis, bo, %d).get",
				//	variable.GetDataType().GetSize());
				m_pFs->Write("dis.read(bytes, 0, %d);",
					variable.GetDataType().GetSize());
				WriteEOL(1);
				WriteIndent(nLoopLevel + 3);
				WriteVariable(variable, nLoopLevel + 1);
				m_pFs->Write(" = ByteBuffer.wrap(bytes).order(bo).get");
				// end
			}
			else {
				// Appended on Mar.21,'16
				// start
				WriteVariable(variable, nLoopLevel + 1);
				// end
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
	}
	else {
		WriteIndent(nLoopLevel + 2);
		// Deleted on Mar.21,'16
		// start
		//WriteVariable(variable, nLoopLevel);
		// end
		if (IsEndianConvEnabled() &&
			!variable.GetDataType().IsOneByte()) {
//			m_pFs->Write(" = readBuf(dis, bo, sizeof(");
//			m_pFs->Write(variable.GetDataType().GetTypeString());
//			m_pFs->Write(")).get");
			// Modified on Mar.21,'16
			// start
			//m_pFs->Write(" = readBuf(dis, bo, %d).get",
			//	variable.GetDataType().GetSize());
			m_pFs->Write("dis.read(bytes, 0, %d);",
				variable.GetDataType().GetSize());
			WriteEOL(1);
			WriteIndent(nLoopLevel + 2);
			WriteVariable(variable, nLoopLevel);
			m_pFs->Write(" = ByteBuffer.wrap(bytes).order(bo).get");
			// end
		}
		else {
			// Appended on Mar.21,'16
			// start
			WriteVariable(variable, nLoopLevel);
			// end
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
	WriteIndent(1);
	m_pFs->Write("public ");
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
	// Modified on Mar.21,'16
	// start
	//WriteLine(2, 1,		"if (args.length != 1) {");
	//WriteLine(3, 1,			"System.err.println(\"Usage: java MyBinaryReader filename\");");
	if (IsWriteFuncEnabled()) {
		WriteLine(2, 1,	"if (args.length != 2) {");
		WriteLine(3, 1,		"System.err.println(\"Usage: java MyBinaryReader inputfilename outputfilename\");");
	}
	else {
		WriteLine(2, 1,	"if (args.length != 1) {");
		WriteLine(3, 1,		"System.err.println(\"Usage: java MyBinaryReader filename\");");
	}
	// end
	WriteLine(3, 1,			"System.exit(-999);");
	WriteLine(2, 1,		"}");
	WriteLine(2, 1,		"try {");
	WriteLine(3, 1,			"MyBinaryReader br = new MyBinaryReader();");
	WriteLine(3, 1,			"br.read(args[0]);");
	// Appended on Mar.21,'16
	// start
	if (IsWriteFuncEnabled()) {
		WriteLine(3, 1,		"br.write(args[1]);");
	}
	// end
	WriteLine(2, 1,		"} catch (IOException e) {");
	WriteLine(3, 1,			"throw new RuntimeException(e.toString());");// e.printStackTrace();
	WriteLine(2, 1,		"}");
	WriteLine(1, 1, "}");
}

void CodeWriterForJava::WriteEndianConv()
{
	// Deleted on Mar.21,'16
	// start
	/*
	WriteLine(1, 1, "public static ByteBuffer readBuf(DataInputStream dis, ByteOrder bo, int size) throws IOException {");
	WriteLine(2, 1,		"byte[] buf = new byte[size];");
	WriteLine(2, 1,		"int nbytes = dis.read(buf);");
	WriteLine(2, 1,		"if (nbytes != size) {");
	WriteLine(3, 1,			"throw new IOException(\"Unexpected End of Stream\");");
	WriteLine(2, 1,		"}");
	WriteLine(2, 1,		"return ByteBuffer.wrap(buf).order(bo);");
	WriteLine(1, 1, "}");
	*/
	// end
}

// Appended on Mar.21,'16
// start
void CodeWriterForJava::WriteWFuncStart()
{
	WriteLine(1, 1, "public void write(String filePath) throws IOException {");
}

void CodeWriterForJava::WriteWFuncEnd()
{
	WriteLine(1, 1, "}");
}

void CodeWriterForJava::WriteWFileOpen()
{
	WriteLine(2, 1, "DataOutputStream dos = new DataOutputStream(fos);");

	if (IsEndianConvEnabled()) {
		WriteIndent(2);
		m_pFs->Write("ByteOrder bo = ByteOrder.");
		if (IsLittleEndian()) {
			m_pFs->Write("LITTLE_ENDIAN;");
		}
		else {
			m_pFs->Write("BIG_ENDIAN;");
		}
		WriteEOL(1);
		WriteLine(2, 1, "byte bytes[] = new byte[16];");
	}
}

void CodeWriterForJava::WriteWFileClose()
{
	WriteLine(2, 1, "dos.close();");
	WriteLine(2, 1, "fos.close();");
}

void CodeWriterForJava::WriteWDeclareFileDesc()
{
	WriteIndent(2);
	m_pFs->Write("FileOutputStream fos = new FileOutputStream(filePath);");
}

void CodeWriterForJava::WriteWrite(Variable& variable,
								   int nLoopLevel, LPCTSTR lpszSize)
{
	int nPointer = variable.GetLoopLevel() - nLoopLevel;
	if (nPointer < 0) {
		return;
	}

	if (lpszSize != NULL) {
		if (variable.GetDataType().IsOneByte()) {
			WriteIndent(nLoopLevel + 2);
			m_pFs->Write("dos.write(");
			WriteVariable(variable, nLoopLevel);
			m_pFs->Write(", 0, %s);", lpszSize);
			WriteEOL(1);
		}
		else {
			WriteLoopStart(nLoopLevel, lpszSize);
			WriteIndent(nLoopLevel + 3);
			if (IsEndianConvEnabled()) {
				m_pFs->Write("ByteBuffer.wrap(bytes).order(bo).put");
			}
			else {
				m_pFs->Write("dos.write");
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

			m_pFs->Write("(");
			WriteVariable(variable, nLoopLevel + 1);
			m_pFs->Write(");");

			if (IsEndianConvEnabled()) {
				WriteEOL(1);
				WriteIndent(nLoopLevel + 3);
				m_pFs->Write("dos.write(bytes, 0, %d);",
					variable.GetDataType().GetSize());
			}

			WriteEOL(1);
			WriteLoopEnd(nLoopLevel, lpszSize);
		}
	}
	else {
		WriteIndent(nLoopLevel + 2);
		if (IsEndianConvEnabled() &&
			!variable.GetDataType().IsOneByte()) {
			m_pFs->Write("ByteBuffer.wrap(bytes).order(bo).put");
		}
		else {
			m_pFs->Write("dos.write");
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

		m_pFs->Write("(");
		WriteVariable(variable, nLoopLevel);
		m_pFs->Write(");");

		if (IsEndianConvEnabled() &&
			!variable.GetDataType().IsOneByte()) {
			WriteEOL(1);
			WriteIndent(nLoopLevel + 2);
			m_pFs->Write("dos.write(bytes, 0, %d);",
				variable.GetDataType().GetSize());
		}
		WriteEOL(1);
	}
}
// end