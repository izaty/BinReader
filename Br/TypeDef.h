#pragma once
#include "Node.h"

class TypeDef :	public Node
{
public:
	TypeDef(DataType::Type nType = DataType::TypeInt,
		LPCTSTR lpszVariable = NULL);
	virtual ~TypeDef(void);

public:
	// Debug
	virtual void Display(int nLevel);

	// Write code for "Declare"
	virtual void WriteDeclare(class CodeWriter *R);

	// Write code for "Allocate"
	virtual void WriteAllocate(class CodeWriter *R, int nLoopLevel,
		LPCTSTR lpszSize);

	// Write code for "Free"
	virtual void WriteFree(class CodeWriter *R, int nLoopLevel);

	// Write code for "Read"
	virtual void WriteRead(class CodeWriter *R, int nReadLevel,
		LPCTSTR lpszSize);

	// Appended on Mar.21,'16
	// start
	// Write code for "Write"
	virtual void WriteWrite(class CodeWriter *R,
		int nWriteLevel, LPCTSTR lpszSize);
	// end

	// Load data from File
	virtual void Load(class FileStream *F);

	// Save data to File
	virtual void Save(class FileStream *F);
};
