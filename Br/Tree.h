#pragma once

#include "UndoObject.h"
#include "Node.h"

class Tree : public UndoObject
{
public:
	enum {LastNode = -1};

protected:
	Node *m_pRoot;

public:
	// Constructor
	Tree(void);
	// Destructor
	virtual ~Tree(void);

public:
	// Delete Specified Node
	BOOL CanDeleteNode(Node *p);
	void DeleteNode(Node *p, class UndoList *U = NULL);

	// Delete All Nodes
	void DeleteAllNodes();

	// Insert Specified Node
	Node *InsertNode(Node *p,
		Node *pParent = NULL, Node *pInsertAfter = (Node *)LastNode,
		class UndoList *U = NULL);

	// Move Specified Node
	BOOL CanMoveLeft(Node *p);
	BOOL CanMoveRight(Node *p);
	BOOL CanMoveUp(Node *p);
	BOOL CanMoveDown(Node *p);

	BOOL MoveLeft(Node *p, class UndoList *U = NULL);
	BOOL MoveRight(Node *p, class UndoList *U = NULL);
	BOOL MoveUp(Node *p, class UndoList *U = NULL);
	BOOL MoveDown(Node *p, class UndoList *U = NULL);

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

	// Find Variable
	Node *FindVariable(LPCTSTR lpszVariable);

	// Assign Loop Levels
	int AssignLevels();

	// Correct Loop Indices
	void CorrectLoopIndices(class LoopIndexManager *pLM);

protected:
	// Remove Specified Node
	BOOL CanRemoveNode(Node *p);
	BOOL RemoveNode(Node *p);

	// Move Specified Node
	BOOL MoveNode(Node *p, Node *pParent, Node *pInsertAfter,
		class UndoList *U = NULL);

	// Restore Specified Node
	//BOOL RestoreNode(Node *p);

protected:
	void SwapThisAndPrev(Node *p, class UndoList *U = NULL);
	void SwapThisAndNext(Node *p, class UndoList *U = NULL);
	void PlaceBeforeParent(Node *p, class UndoList *U = NULL);
	void PlaceAfterParent(Node *p, class UndoList *U = NULL);
	void MakeEldersChild(Node *p, class UndoList *U = NULL);
	//void ConnectToParentAndSiblings(Node *p);

	Node *FindTopSibling(Node *p);
	Node *FindLastSibling(Node *p);

	Node *GetHeadNode();
	Node *GetNextNode(Node *p);
	Node *GetNextNode(Node *p, Node::NodeType nType);

	Node *GetHeadLeaf();
	Node *GetNextLeaf(Node *p);

	Node *GetHeadInner();
	Node *GetNextInner(Node *p);

protected:
	struct UndoData {
		enum UndoType {U_INS, U_DEL, U_MOV};
		UndoType type;
		Node *p;
		Node *pP;
		Node *pE;
	};

public:
	virtual void ExeUndo(void *pPara);
	virtual void DelUndo(void *pPara);
};
