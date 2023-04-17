#pragma once

#include "Common.h"
#include "Variable.h"

class Tree : public Common
{
public:
	enum {LastNode = -1};

public:
	class Node : public Common
	{
	protected:
		Variable m_variable;

//		TCHAR m_szVariable[_MAX_VARNAME+1];	// Variable Name
	public:
		NodeType m_nNodeType;	// Node Type (INNER or LEAF)
		Node *m_pP;				// Parent Node
		Node *m_pC;				// (Top) Child Node
		Node *m_pE;				// Elderly Brother
		Node *m_pY;				// Younger Brother
//		int m_nLoopLevel;
	protected:
		// Constructor
		Node(NodeType nNodeType);
	public:
		// Destructor
		virtual ~Node();

		// Delete All Child Nodes
		void DeleteAllChildNodes();

		// Get Total Number of Nodes including Myself and All Child Nodes
		int GetNodeCount();

		// Get Variable Name
		Variable& GetVariable() const {return (Variable&)m_variable;}

		// Set & Get Loop Levels
		int SetLoopLevel(int nLevel);
		int GetLoopLevel() {return m_variable.GetLoopLevel();}

		virtual void Display(int nLevel);

		virtual void WriteDeclare(class CodeWriter *R) {}

		virtual void WriteAllocate(class CodeWriter *R, int nLoopLevel,
			LPCTSTR lpszSize) {}
		virtual void WriteFree(class CodeWriter *R, int nLoopLevel) {}

		virtual void WriteRead(class CodeWriter *R, int nReadLevel,
			LPCTSTR lpszSize) {}

		virtual void WriteClear(class CodeWriter *R) {}

		virtual void WriteLoopStart(class CodeWriter *R) {}
		virtual void WriteLoopEnd(class CodeWriter *R) {}

		virtual void WriteEnd(class CodeWriter *R) {}

		virtual void Load(class FileStream *F) {}
		virtual void Save(class FileStream *F) {}
	};

protected:
	Node *m_pRoot;

public:
	// Constructor
	Tree(void);
	// Destructor
	virtual ~Tree(void);

protected:
	// Remove Specified Node
	BOOL CanRemoveNode(Node *p);
	BOOL RemoveNode(Node *p);

	// Move Specified Node
	BOOL MoveNode(Node *p, Node *pParent, Node *pInsertAfter);

public:
	// Delete Specified Node
	BOOL CanDeleteNode(Node *p);
	void DeleteNode(Node *p);

	// Delete All Nodes
	void DeleteAllNodes();

	// Insert Specified Node
	Node *InsertNode(Node *p,
		Node *pParent = NULL, Node *pInsertAfter = (Node *)LastNode);

	// Move Specified Node
	BOOL CanMoveLeft(Node *p);
	BOOL CanMoveRight(Node *p);
	BOOL CanMoveUp(Node *p);
	BOOL CanMoveDown(Node *p);

	BOOL MoveLeft(Node *p);
	BOOL MoveRight(Node *p);
	BOOL MoveUp(Node *p);
	BOOL MoveDown(Node *p);

	// Restore Specified Node
	//BOOL RestoreNode(Node *p);

	// Get Root Node
	Node *GetRootNode() const {return m_pRoot;}

	// Get Total Number of Nodes
	int GetNodeCount();

	// Write Code
	void Write(class CodeWriter *R);

	// TRACE command
	void Display();

	// Read and Write Specified File
	void Load(class FileStream *F);
	void Save(class FileStream *F);

	// If Variable Exists
	BOOL VariableExists(LPCTSTR lpszVariable);

	// Assign Loop Levels
	int AssignLevels();

protected:
	void SwapThisAndPrev(Node *p);
	void SwapThisAndNext(Node *p);
	void ConnectToParentAndSiblings(Node *p);

	Node *FindTopSibling(Node *p);
	Node *FindLastSibling(Node *p);

	Node *GetHeadNode();
	Node *GetNextNode(Node *p);

	Node *GetHeadLeaf();
	Node *GetNextLeaf(Node *p);
};
