#include "StdAfx.h"
#include "DataType.h"
#include "UndoList.h"

DataType::TypeInfo DataType::m_stInfo[] = {
	{4, _T("$php_int_size"),	_T("int"),		_T("Int32"),	_T("i")},
	{4, _T("$php_float_size"),	_T("float"),	_T("Single"),	_T("f")},
	{8, _T("$php_double_size"),	_T("double"),	_T("Double"),	_T("d")},
	{1, _T("$php_char_size"),	_T("char"),		_T("Char"),		_T("c")},
	{8, _T("$php_long_size"),	_T("long"),		_T("Int64"),	_T("l")},
	{2, _T("$php_short_size"),	_T("short"),	_T("Int16"),	_T("s")},
	{1, _T("$php_byte_size"),	_T("byte"),		_T("Byte"),		_T("C")},
};


DataType::DataType(Type nType) : m_nType(nType)
{
}

DataType::~DataType(void)
{
}

DataType::Type DataType::GetType(int nIndex)
{
	return (Type)nIndex;
}

int DataType::GetSize(Type nType)
{
	return (nType < TypeCount) ? m_stInfo[nType].size : 0;
}

LPTSTR DataType::GetPHPSizeString(Type nType)
{
	return (nType < TypeCount) ? m_stInfo[nType].phpsize : _T("no_size");
}

LPTSTR DataType::GetTypeString(Type nType)
{
	return (nType < TypeCount) ? m_stInfo[nType].name : _T("no_type");
}

LPTSTR DataType::GetTypeStringAndBlank(Type nType)
{
	static TCHAR szType[30];
	lstrcpy(szType, GetTypeString(nType));
	lstrcat(szType, _T(" "));
	return szType;
}

int DataType::GetSize() const
{
	return GetSize(m_nType);
}
	
LPTSTR DataType::GetPHPSizeString() const
{
	return GetPHPSizeString(m_nType);
}
	
LPTSTR DataType::GetTypeString() const
{
	return GetTypeString(m_nType);
}

LPTSTR DataType::GetTypeStringAndBlank() const
{
	return GetTypeStringAndBlank(m_nType);
}

LPTSTR DataType::GetTypeString2(Type nType)
{
	return (nType < TypeCount) ? m_stInfo[nType].name2 : _T("no_type");
}

LPTSTR DataType::GetTypeStringAndBlank2(Type nType)
{
	static TCHAR szType[30];
	lstrcpy(szType, GetTypeString2(nType));
	lstrcat(szType, _T(" "));
	return szType;
}
	
LPTSTR DataType::GetTypeString2() const
{
	return GetTypeString2(m_nType);
}

LPTSTR DataType::GetTypeStringAndBlank2() const
{
	return GetTypeStringAndBlank2(m_nType);
}

LPTSTR DataType::GetTypeString3(Type nType)
{
	return (nType < TypeCount) ? m_stInfo[nType].name3 : _T("x");
}
	
LPTSTR DataType::GetTypeString3() const
{
	return GetTypeString3(m_nType);
}

void DataType::SetSize(Type nType, int nSize)
{
	if (nType < TypeCount) {
		m_stInfo[nType].size = nSize;
	}
}

void DataType::SetType(Type nType, UndoList *U)
{
	if (U != NULL) {
		UndoData *obj = new UndoData;
		obj->type = m_nType;
		U->Register(this, (void *)obj);
	}
	m_nType = nType;
}

void DataType::ExeUndo(void *pPara)
{
	UndoData *obj = (UndoData *)pPara;
	SetType(obj->type);
	delete obj;
}

void DataType::DelUndo(void *pPara)
{
	UndoData *obj = (UndoData *)pPara;
	delete obj;
}