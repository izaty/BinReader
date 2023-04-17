#include "StdAfx.h"
#include "CodeWriterForPHP.h"

CodeWriterForPHP::CodeWriterForPHP(FileStream *pFs,
								   LoopIndexManager *pLim) : CodeWriter(pFs, pLim)
{
	m_bClearRequired = FALSE;
}

CodeWriterForPHP::~CodeWriterForPHP(void)
{
}

void CodeWriterForPHP::WriteStart()
{
	WriteLine(0, 1, "<?php");

	WriteEndianConv();
	WriteEOL(1);

	WriteUnpack();
	WriteEOL(1);

	WriteLine(1, 1, "function readBinary($filePath) {");

	WriteIndent(2);
	m_pFs->Write(DataType::GetPHPSizeString(DataType::TypeInt));
	m_pFs->Write(" = PHP_INT_SIZE;");
	WriteEOL(1);

	WriteLine(2, 1,     "$php_size_check = 1.0;");

	WriteIndent(2);
	m_pFs->Write(DataType::GetPHPSizeString(DataType::TypeFloat));
	m_pFs->Write(" = strlen(pack(\"f\", $php_size_check));");
	WriteEOL(1);

	WriteIndent(2);
	m_pFs->Write(DataType::GetPHPSizeString(DataType::TypeDouble));
	m_pFs->Write(" = strlen(pack(\"d\", $php_size_check));");
	WriteEOL(1);

	WriteIndent(2);
	m_pFs->Write(DataType::GetPHPSizeString(DataType::TypeChar));
	m_pFs->Write(" = 1;");
	WriteEOL(1);

	WriteIndent(2);
	m_pFs->Write(DataType::GetPHPSizeString(DataType::TypeLong));
	m_pFs->Write(" = 4;");
	WriteEOL(1);

	WriteIndent(2);
	m_pFs->Write(DataType::GetPHPSizeString(DataType::TypeShort));
	m_pFs->Write(" = 2;");
	WriteEOL(2);

	WriteIndent(2);
	m_pFs->Write(DataType::GetPHPSizeString(DataType::TypeByte));
	m_pFs->Write(" = 1;");
	WriteEOL(1);
}

void CodeWriterForPHP::WriteEnd()
{
	WriteLine(0, 1,	"?>");
}

void CodeWriterForPHP::WriteFuncStart()
{
}

void CodeWriterForPHP::WriteFuncEnd()
{
	WriteLine(2, 1,		"return 0;");
	WriteLine(1, 1, "}");
}

void CodeWriterForPHP::WriteFileOpen()
{
	WriteLine(2, 1,		"$fp = fopen($filePath, \"rb\");");
	WriteLine(2, 1,		"if ($fp == FALSE) {");
	WriteLine(3, 1,			"return -3;");
	WriteLine(2, 1,		"}");
}

void CodeWriterForPHP::WriteFileClose()
{
	WriteLine(2, 1,		"fclose($fp);");
}

void CodeWriterForPHP::WriteLoopStart(int nLoopLevel, LPCTSTR lpszCount)
{
	LPTSTR lpszVariable = m_pLim->GetVariableString(nLoopLevel);
	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("for ($");
	m_pFs->Write(lpszVariable);
	m_pFs->Write(" = 0; $");
	m_pFs->Write(lpszVariable);
	m_pFs->Write(" < ");
	WriteSize(lpszCount);
	m_pFs->Write("; $");
	m_pFs->Write(lpszVariable);
	m_pFs->Write("++) {");
	WriteEOL(1);
}

void CodeWriterForPHP::WriteLoopEnd(int nLoopLevel, LPCTSTR lpszCount)
{
	WriteLine(nLoopLevel + 2, 1, "}");
}

void CodeWriterForPHP::WriteAllocate(Variable& variable,
								   int nLoopLevel, LPCTSTR lpszSize)
{
	int nPointer = variable.GetLoopLevel() - nLoopLevel;
	if (nPointer < 0) {
		return;
	}
	WriteIndent(nLoopLevel + 2);
	WriteVariable(variable, nLoopLevel);
	m_pFs->Write(" = array_fill(0, ");
	WriteSize(lpszSize);
	m_pFs->Write(", NULL);");
	WriteEOL(1);
}

void CodeWriterForPHP::WriteFree(Variable& variable, int nLoopLevel)
{
}

void CodeWriterForPHP::WriteRead(Variable& variable,
								 int nLoopLevel, LPCTSTR lpszSize)
{
	int nPointer = variable.GetLoopLevel() - nLoopLevel;
	if (nPointer < 0) {
		return;
	}

	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("$php_contents = eread($fp, ");
	m_pFs->Write(variable.GetDataType().GetPHPSizeString());
	m_pFs->Write(", ");

	if (lpszSize != NULL) {
		WriteSize(lpszSize);
		m_pFs->Write(");");
	}
	else {
		m_pFs->Write("1);");
	}

	WriteEOL(1);

	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("if ($php_contents == FALSE) {");
	WriteEOL(1);
	WriteLine(nLoopLevel + 3, 1,	"return -1;");
	WriteLine(nLoopLevel + 2, 1, "}");

	WriteIndent(nLoopLevel + 2);
	WriteVariable(variable, nLoopLevel);
	if (variable.GetDataType().GetType() == DataType::TypeChar) {
		m_pFs->Write(" = $php_contents;");
	}
	else {
		if (lpszSize != NULL) {
			m_pFs->Write(" = unpack_array(\"");
			m_pFs->Write(variable.GetDataType().GetTypeString3());
			m_pFs->Write("*\", $php_contents);");
		}
		else {
			m_pFs->Write(" = unpack_single(\"");
			m_pFs->Write(variable.GetDataType().GetTypeString3());
			m_pFs->Write("\", $php_contents);");
		}
	}
	WriteEOL(1);
}

void CodeWriterForPHP::WriteDeclareLoopIndices(int nLoopLevel)
{
}

void CodeWriterForPHP::WriteDeclareVariable(Variable& variable)
{
	WriteIndent(2);
	m_pFs->Write("global $");
	m_pFs->Write(variable.GetName());
	m_pFs->Write(";");
	WriteEOL(1);
}

void CodeWriterForPHP::WriteDeclareFileDesc()
{
}

void CodeWriterForPHP::WriteVariable(Variable& variable, int nLoopLevel)
{
	m_pFs->Write("$");
//	m_pFs->Write("$GLOBALS['");
	m_pFs->Write(variable.GetName());
	for (volatile int i = 0; i < nLoopLevel; i++) {
		m_pFs->Write("[$%s]", m_pLim->GetVariableString(i));
	}
//	m_pFs->Write("']");
}

void CodeWriterForPHP::WriteDriver()
{
	// Modified on Mar.23,'16
	// start
	//WriteLine(1, 1,		"if (!isset($_GET['ifname'])) {");
	if (IsWriteFuncEnabled()) {
		WriteLine(1, 1,	"if (!isset($_GET['ifname']) || !isset($_GET['ofname'])) {");
	}
	else {
		WriteLine(1, 1,	"if (!isset($_GET['ifname'])) {");
	}
	// end
	WriteLine(2, 1,			"print(\"Usage : http://\");");
	WriteLine(2, 1,			"print($_SERVER['HTTP_HOST'] . $_SERVER['SCRIPT_NAME']);");
	// Modified on Mar.22,'16
	// start
	//WriteLine(2, 1,			"print(\"?ifname=BinaryFilePath<br />\");");
	if (IsWriteFuncEnabled()) {
		WriteLine(2, 1,		"print(\"?ifname=InputBinaryFilePath\");");
		WriteLine(2, 1,		"print(\"&ofname=OutputBinaryFilePath<br />\");");
	}
	else {
		WriteLine(2, 1,		"print(\"?ifname=BinaryFilePath<br />\");");
	}
	// end
	WriteLine(2, 1,			"exit;");
	WriteLine(1, 2,		"}");

	WriteLine(1, 2,		"$err_code = readBinary($_GET['ifname']);");

	WriteLine(1, 1,		"if ($err_code == -1) {");
	WriteLine(2, 1,			"print(\"read error<br />\");");
	WriteLine(1, 1,		"}");
	WriteLine(1, 1,		"else if ($err_code == -2) {");
	WriteLine(2, 1,			"print(\"allocation error<br />\");");
	WriteLine(1, 1,		"}");
	WriteLine(1, 1,		"else if ($err_code == -3) {");
	WriteLine(2, 1,			"print(\"open error<br />\");");
	WriteLine(1, 1,		"}");
	WriteLine(1, 1,		"else {");
	WriteLine(2, 1,			"print(\"reading binary file succeeded<br />\");");
	WriteLine(1, 2,		"}");

	// Appended on Mar.22,'16
	// start
	if (IsWriteFuncEnabled()) {
		WriteLine(1, 2,	"$err_code = writeBinary($_GET['ofname']);");

		WriteLine(1, 1,	"if ($err_code == -4) {");
		WriteLine(2, 1,		"print(\"write error<br />\");");
		WriteLine(1, 1,	"}");
		WriteLine(1, 1,	"else if ($err_code == -5) {");
		WriteLine(2, 1,		"print(\"open error<br />\");");
		WriteLine(1, 1,	"}");
		WriteLine(1, 1,	"else {");
		WriteLine(2, 1,		"print(\"writing binary file succeeded<br />\");");
		WriteLine(1, 2,	"}");
	}
	// end
}

void CodeWriterForPHP::WriteEndianConv()
{
	WriteLine(1, 1, "function eread($fp, $size, $n) {");
	WriteLine(2, 1,		"$buffer = fread($fp, $size * $n);");
	if (IsEndianConvEnabled()) {
		WriteLine(2, 1,	"if ($buffer == FALSE) {");
		WriteLine(3, 1,		"return FALSE;");
		WriteLine(2, 1,	"}");
		WriteLine(2, 1, "if ($size > 1) {");
		WriteLine(3, 1,		"$temp = $buffer;");
		WriteLine(3, 1,		"for ($i = 0; $i < $n; $i++) {");
		WriteLine(4, 1,			"$base = $i * $size;");
		WriteLine(4, 1,			"for ($j = 0; $j < $size; $j++) {");
		WriteLine(5, 1,				"$buffer[$base+$j] = $temp[$base+$size-$j-1];");
		WriteLine(4, 1,			"}");
		WriteLine(3, 1,		"}");
		WriteLine(2, 1, "}");
	}
	WriteLine(2, 1,		"return $buffer;");
	WriteLine(1, 1, "}");

	// Appended on Mar.21,'16
	// start
	if (IsWriteFuncEnabled()) {
		WriteEOL(1);
		WriteLine(1, 1, "function ewrite($fp, $buffer) {");
		if (IsEndianConvEnabled()) {
			WriteLine(2, 1, "if ($size > 1) {");
			WriteLine(3, 1,		"$temp = $buffer;");
			WriteLine(3, 1,		"for ($i = 0; $i < $n; $i++) {");
			WriteLine(4, 1,			"$base = $i * $size;");
			WriteLine(4, 1,			"for ($j = 0; $j < $size; $j++) {");
			WriteLine(5, 1,				"$buffer[$base+$j] = $temp[$base+$size-$j-1];");
			WriteLine(4, 1,			"}");
			WriteLine(3, 1,		"}");
			WriteLine(2, 1, "}");
		}
		WriteLine(2, 1,		"return fwrite($fp, $buffer);");
		WriteLine(1, 1, "}");
	}
	// end
}

void CodeWriterForPHP::WriteUnpack()
{
	WriteLine(1, 1, "function unpack_single($format, $data) {");
	WriteLine(2, 1,		"$value = unpack($format, $data);");
	WriteLine(2, 1,		"return $value[1];");
	WriteLine(1, 1, "}");
	WriteEOL(1);
	WriteLine(1, 1, "function unpack_array($format, $data) {");
	WriteLine(2, 1,		"return array_merge(unpack($format, $data));");
	WriteLine(1, 1, "}");

	// Appended on Mar.22,'16
	// start
	if (IsWriteFuncEnabled()) {
		WriteLine(1, 1, "function pack_single($format, $value) {");
		WriteLine(2, 1,		"return pack($format, $value);");
		WriteLine(1, 1, "}");
		WriteEOL(1);
		WriteLine(1, 1, "function pack_array($format, $arr) {");
		WriteLine(2, 1,		"return call_user_func_array(\"pack\", array_merge(array($format), $arr));");
		WriteLine(1, 1, "}");
	}
	// end
}

void CodeWriterForPHP::WriteSize(LPCTSTR lpszSize)
{
	int nLen = lstrlen(lpszSize);
	LPTSTR lpszTemp = new TCHAR[nLen+1];

	int nCopyStart = 0, nCopyLen;
	BOOL bWriteDollar = TRUE;

	for (volatile int i = 0; i < nLen; i++) {
		if (Variable::IsAlphabet(lpszSize[i])) {
			if (bWriteDollar == TRUE) {
				m_pFs->Write("$");
				nCopyStart = i;
				bWriteDollar = FALSE;
			}
		}
		else if (Variable::IsNumeric(lpszSize[i])) {
			if (bWriteDollar == TRUE) {
				nCopyStart = i;
				bWriteDollar = FALSE;
			}
		}
		else {
			nCopyLen = i - nCopyStart + 1;
			if (nCopyLen > 0) {
				lstrcpyn(lpszTemp, &lpszSize[nCopyStart], nCopyLen + 1);
				m_pFs->Write(lpszTemp);
			}
			nCopyStart = i + 1;
			bWriteDollar = TRUE;
		}
	}
	nCopyLen = nLen - nCopyStart;
	if (nCopyLen > 0) {
		lstrcpyn(lpszTemp, &lpszSize[nCopyStart], nCopyLen + 1);
		m_pFs->Write(lpszTemp);
	}

	delete [] lpszTemp;
}

// Appended on Mar.22,'16
// start
void CodeWriterForPHP::WriteWFuncStart()
{
	WriteLine(1, 1, "function writeBinary($filePath) {");
}

void CodeWriterForPHP::WriteWFuncEnd()
{
	WriteLine(2, 1,		"return 0;");
	WriteLine(1, 1, "}");
}

void CodeWriterForPHP::WriteWFileOpen()
{
	WriteLine(2, 1,		"$fp = fopen($filePath, \"wb\");");
	WriteLine(2, 1,		"if ($fp == FALSE) {");
	WriteLine(3, 1,			"return -5;");
	WriteLine(2, 1,		"}");
}

void CodeWriterForPHP::WriteWFileClose()
{
	WriteLine(2, 1,		"fclose($fp);");
}

void CodeWriterForPHP::WriteWrite(Variable& variable,
								  int nLoopLevel, LPCTSTR lpszSize)
{
	int nPointer = variable.GetLoopLevel() - nLoopLevel;
	if (nPointer < 0) {
		return;
	}

	WriteIndent(nLoopLevel + 2);
	m_pFs->Write("$php_contents = ");

	if (variable.GetDataType().GetType() == DataType::TypeChar) {
		WriteVariable(variable, nLoopLevel);
		m_pFs->Write(";");
	}
	else {
		if (lpszSize != NULL) {
			m_pFs->Write("pack_array(\"");
			m_pFs->Write(variable.GetDataType().GetTypeString3());
			m_pFs->Write("*\", ");
		}
		else {
			m_pFs->Write("pack_single(\"");
			m_pFs->Write(variable.GetDataType().GetTypeString3());
			m_pFs->Write("\", ");
		}
		WriteVariable(variable, nLoopLevel);
		m_pFs->Write(");");
	}
	WriteEOL(1);

	WriteLine(nLoopLevel + 2, 1, "$rcode = ewrite($fp, $php_contents);");
	WriteLine(nLoopLevel + 2, 1, "if ($rcode == FALSE) {");
	WriteLine(nLoopLevel + 3, 1,	"return -4;");
	WriteLine(nLoopLevel + 2, 1, "}");
}

void CodeWriterForPHP::WriteWDeclareFileDesc()
{
}
// end