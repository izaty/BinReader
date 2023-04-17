#include "StdAfx.h"
#include "TypeDef.h"
#include "CodeWriter.h"
#include "FileStream.h"


TypeDef::TypeDef(DataType::Type nType,
				 LPCTSTR lpszVariable) : Node(NT_LEAF)
{
	m_variable.GetDataType().SetType(nType);
	m_variable.SetName(lpszVariable);
}

TypeDef::~TypeDef(void)
{
}

void TypeDef::Display(int nLevel)
{
	volatile int i;

	for (i = 0; i < nLevel; i++) {
		TRACE("    ");
	}

	TRACE("TYPE ");

	DataType::Type nDataType = m_variable.GetDataType().GetType();
	if (nDataType == DataType::TypeInt) {
		TRACE("int : ");
	}
	else if (nDataType == DataType::TypeFloat) {
		TRACE("float : ");
	}
	else if (nDataType == DataType::TypeDouble) {
		TRACE("double : ");
	}
	else if (nDataType == DataType::TypeChar) {
		TRACE("char : ");
	}


	TRACE(m_variable.GetName());
	for (i = 0; i < nLevel; i++) {
		TRACE("[i%d]", i);
	}
	TRACE("\n");

	Node::Display(nLevel);
}

// Write code for "Declare"
void TypeDef::WriteDeclare(CodeWriter *R)
{
//	R->WriteDeclareVariable(m_nDataType, m_nLoopLevel, m_szVariable);
//	R->WriteDeclareVariable(m_nDataType, 
//		m_variable.GetLoopLevel(),
//		m_variable.GetName());
	R->WriteDeclareVariable(m_variable);
}

// Write code for "Allocate"
void TypeDef::WriteAllocate(CodeWriter *R, int nLoopLevel, LPCTSTR lpszSize)
{
//	R->WriteAllocate(m_nDataType, nLoopLevel, m_nLoopLevel, m_szVariable, lpszSize);
//	R->WriteAllocate(m_nDataType, 
//		nLoopLevel, m_variable.GetLoopLevel(), 
//		m_variable.GetName(), lpszSize);
	R->WriteAllocate(m_variable, nLoopLevel, lpszSize);
}

// Write code for "Free"
void TypeDef::WriteFree(CodeWriter *R, int nLoopLevel)
{
//	if (nLoopLevel < m_nLoopLevel) {
//		R->WriteFree(nLoopLevel, m_szVariable);
//		R->WriteFree(nLoopLevel, m_variable.GetName());
		R->WriteFree(m_variable, nLoopLevel);
//	}
}

// Write code for "Read"
void TypeDef::WriteRead(CodeWriter *R, int nReadLevel, LPCTSTR lpszSize)
{
//	R->WriteRead(m_nDataType, nReadLevel, m_nLoopLevel, m_szVariable, lpszSize);
//	R->WriteRead(m_nDataType, nReadLevel, m_variable.GetLoopLevel(), 
//		m_variable.GetName(), lpszSize);
	R->WriteRead(m_variable, nReadLevel, lpszSize);
}

// Added on Mar.21,'16
// start
// Write code for "Write"
void TypeDef::WriteWrite(CodeWriter *R, int nWriteLevel, LPCTSTR lpszSize)
{
	R->WriteWrite(m_variable, nWriteLevel, lpszSize);
}
// end

// Load data from File
void TypeDef::Load(FileStream *F)
{
	int nLoopLevel;
	*F >> nLoopLevel;
	m_variable.SetLoopLevel(nLoopLevel);

	int nDataType;
	*F >> nDataType;
	m_variable.GetDataType().SetType((DataType::Type)nDataType);

	TCHAR szTemp[Variable::MaxStrLen+101];
	*F >> szTemp;
	m_variable.SetName(szTemp);
}

// Save data to File
void TypeDef::Save(FileStream *F)
{
	F->WriteLine("T %d %d %s", m_variable.GetLoopLevel(),
		(int)m_variable.GetDataType().GetType(),
		m_variable.GetName());
}
