#include "StdAfx.h"
#include "LoopDef.h"
#include "CodeWriter.h"
#include "FileStream.h"

LoopDef::LoopDef(LPCTSTR lpszCount) : Node(NT_INNER)
{
	m_variable.GetDataType().SetType(DataType::TypeCount);
	if (lpszCount != NULL) {
		SetCount(lpszCount);
	}
}

LoopDef::~LoopDef(void)
{
}

// Set
void LoopDef::SetCount(LPCTSTR lpszCount)
{
	m_variable.SetName(lpszCount);
}

// Debug
void LoopDef::Display(int nLevel)
{
	volatile int i;

	for (i = 0; i < nLevel; i++) {
		TRACE("    ");
	}

	TRACE("LOOP i%d : %ls\n", nLevel, m_variable.GetName());

	Node::Display(nLevel);
}

// Write code for "Declare"
void LoopDef::WriteDeclare(CodeWriter *R)
{
	Node *p = m_pC;
	while (p) {
		p->WriteDeclare(R);
		p = p->m_pY;
	}
}

// Write code for "Allocate"
void LoopDef::WriteAllocate(CodeWriter *R, int nLoopLevel, LPCTSTR lpszSize)
{
	Node *p = m_pC;
	while (p) {
		p->WriteAllocate(R, nLoopLevel, lpszSize);
		p = p->m_pY;
	}
}

// Write code for "Free"
void LoopDef::WriteFree(CodeWriter *R, int nLoopLevel)
{
	if (m_pC) {
		Node *p = m_pC->FindLastSibling();
		while (p) {
			p->WriteFree(R, nLoopLevel);
			p = p->m_pE;
		}
	}

	//Node *p = m_pC;
	//while (p) {
	//	p->WriteFree(R, nLoopLevel);
	//	p = p->m_pY;
	//}
}

// Write code for "Read" (with Allocate)
void LoopDef::WriteRead(CodeWriter *R, int nReadLevel, LPCTSTR lpszSize)
{
	WriteAllocate(R, m_variable.GetLoopLevel(), m_variable.GetName());

	if (m_pC) {
		if (m_pC->m_nNodeType == Node::NT_LEAF && m_pC->m_pY == NULL) {
			m_pC->WriteRead(R, m_variable.GetLoopLevel(), m_variable.GetName());
			return;
		}
	}

	WriteLoopStart(R);

	Node *p = m_pC;
	while (p) {
		p->WriteRead(R, p->GetLoopLevel(), lpszSize);
		p = p->m_pY;
	}

	WriteLoopEnd(R);
}

// Write code for "Loop Start"
void LoopDef::WriteLoopStart(CodeWriter *R)
{
	R->WriteLoopStart(m_variable.GetLoopLevel(), m_variable.GetName());
}

// Write code for "Loop End"
void LoopDef::WriteLoopEnd(CodeWriter *R)
{
	R->WriteLoopEnd(m_variable.GetLoopLevel(), m_variable.GetName());
}

// Write code for "Free All"
void LoopDef::WriteClear(CodeWriter *R)
{
	Node *p;

	// Contains loop?
	p = m_pC;
	while (p) {
		if (p->m_nNodeType == NT_INNER) {
			break;
		}
		p = p->m_pY;
	}

	if (p != NULL) {	// contains loop
		WriteLoopStart(R);

		p = m_pC->FindLastSibling();
		while (p) {
			p->WriteClear(R);
			p = p->m_pE;
		}
		//p = m_pC;
		//while (p) {
		//	p->WriteClear(R);
		//	p = p->m_pY;
		//}

		WriteLoopEnd(R);
	}

	WriteFree(R, m_variable.GetLoopLevel());
}

// Appended on Mar.21,'16
// start
// Write code for "Write" (without Allocate)
void LoopDef::WriteWrite(CodeWriter *R, int nWriteLevel, LPCTSTR lpszSize)
{
	if (m_pC) {
		if (m_pC->m_nNodeType == Node::NT_LEAF && m_pC->m_pY == NULL) {
			m_pC->WriteWrite(R, m_variable.GetLoopLevel(), m_variable.GetName());
			return;
		}
	}

	WriteLoopStart(R);

	Node *p = m_pC;
	while (p) {
		p->WriteWrite(R, p->GetLoopLevel(), lpszSize);
		p = p->m_pY;
	}

	WriteLoopEnd(R);
}
// end

// Load data from File
void LoopDef::Load(FileStream *F)
{
	int nLoopLevel;
	*F >> nLoopLevel;
	m_variable.SetLoopLevel(nLoopLevel);

	TCHAR szTemp[Variable::MaxStrLen+101];
	*F >> szTemp;
	m_variable.SetName(szTemp);
}

// Save data to File
void LoopDef::Save(FileStream *F)
{
	F->WriteLine("L %d %s", m_variable.GetLoopLevel(), m_variable.GetName());
	Node *p = m_pC;
	while (p) {
		p->Save(F);
		p = p->m_pY;
	}
}
