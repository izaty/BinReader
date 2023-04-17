#pragma once
#include "Node.h"

class LoopDef :	public Node
{
public:
	LoopDef(LPCTSTR lpszCount = NULL);
	virtual ~LoopDef(void);

public:
	// Debug
	virtual void Display(int nLevel);

	// Set Count
	void SetCount(LPCTSTR lpszCount);

	// Get Count
	LPCTSTR GetCount() const {return m_variable.GetName();}

	// Write code for "Declare"
	virtual void WriteDeclare(class CodeWriter *R);

	// Write code for "Allocate"
	virtual void WriteAllocate(class CodeWriter *R, int nLoopLevel,
		LPCTSTR lpszSize);

	// Write code for "Free"
	virtual void WriteFree(class CodeWriter *R, int nLoopLevel);

	// Write code for "Read" (with Allocate)
	virtual void WriteRead(class CodeWriter *R, int nReadLevel,
		LPCTSTR lpszSize);

	// Write code for "Loop Start"
	virtual void WriteLoopStart(class CodeWriter *R);

	// Write code for "Loop End"
	virtual void WriteLoopEnd(class CodeWriter *R);

	// Write code for "Free All"
	virtual void WriteClear(class CodeWriter *R);

	// Appended on Mar.21,'16
	// start
	// Write code for "Write" (without Allocate)
	virtual void WriteWrite(class CodeWriter *R,
		int nWriteLevel, LPCTSTR lpszSize);
	// end

	// Load data from File
	virtual void Load(class FileStream *F);

	// Save data to File
	virtual void Save(class FileStream *F);
};
