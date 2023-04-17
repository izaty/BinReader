#pragma once
#include "Variable.h"

class Node
{
public:
	// Node Type
	enum NodeType {
		NT_LEAF,	// leaf node
		NT_INNER	// inter node
	};

protected:
	Variable m_variable;

public:
	NodeType m_nNodeType;	// Node Type (INNER or LEAF)
	Node *m_pP;				// Parent Node
	Node *m_pC;				// Top Child Node
	Node *m_pE;				// Elderly Brother
	Node *m_pY;				// Younger Brother

public:
	// Constructor
	Node(NodeType nNodeType);
	// Destructor
	virtual ~Node();

	// Debug
	virtual void Display(int nLevel);

	// Delete All Child Nodes
	void DeleteAllChildNodes();

	// Get Total Number of Nodes including Myself and All Child Nodes
	int GetNodeCount() const;

	// Get Variable
	Variable& GetVariable() const {return (Variable&)m_variable;}

	// Set & Get Loop Levels
	int SetLoopLevel(int nLevel);
	int GetLoopLevel() const {return m_variable.GetLoopLevel();}

	// Get Max Loop Level from Myself and All Child Nodes
	int GetMaxLoopLevel() const;

	// Find Top & Last Sibling Nodes
	Node *FindTopSibling();
	Node *FindLastSibling();

	//
	// Write functions
	//

	virtual void WriteDeclare(class CodeWriter *R) {}

	virtual void WriteAllocate(class CodeWriter *R,
		int nLoopLevel, LPCTSTR lpszSize) {}
	virtual void WriteFree(class CodeWriter *R, int nLoopLevel) {}

	virtual void WriteRead(class CodeWriter *R,
		int nReadLevel, LPCTSTR lpszSize) {}

	virtual void WriteClear(class CodeWriter *R) {}

	virtual void WriteLoopStart(class CodeWriter *R) {}
	virtual void WriteLoopEnd(class CodeWriter *R) {}

	// Appended on Mar.21,'16
	// start
	virtual void WriteWrite(class CodeWriter *R,
		int nWriteLevel, LPCTSTR lpszSize) {}
	// end

	// Deleted on Mar.21,'16
	// start
	//virtual void WriteEnd(class CodeWriter *R) {}
	// end

	// Load File
	virtual void Load(class FileStream *F) {}
	// Save File
	virtual void Save(class FileStream *F) {}
};
