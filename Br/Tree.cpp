#include "StdAfx.h"
#include "Tree.h"
#include "RootDef.h"
#include "TypeDef.h"
#include "LoopDef.h"
#include "UndoList.h"
#include "CodeWriter.h"
#include "LoopIndexManager.h"


// Constructor
Tree::Tree(void)
{
	// Root Node (just access point)
	m_pRoot = new RootDef();//new Node(NT_INNER);
}

// Destructor
Tree::~Tree(void)
{
	// Delete All Nodes
	DeleteAllNodes();
	// Delete Root Node
	delete m_pRoot;
}

// Debug
void Tree::Display()
{
	AssignLevels();

	Node *p = m_pRoot->m_pC;
	while (p) {
		p->Display(0);
		p = p->m_pY;
	}
}

// Get Total Number of Nodes in Tree
int Tree::GetNodeCount()
{
	return (m_pRoot->GetNodeCount() - 1);
}

// Find Oldest Sibling of Specified Node
Node *Tree::FindTopSibling(Node *p)
{
	while (p->m_pE) {
		p = p->m_pE;
	}
	return p;
}

// Find Youngest Sibling of Specified Node
Node *Tree::FindLastSibling(Node *p)
{
	while (p->m_pY) {
		p = p->m_pY;
	}
	return p;
}

// Can Remove Node
BOOL Tree::CanRemoveNode(Node *p)
{
	return ((p->m_pE != NULL) || (p->m_pP != NULL));
}

// Remove Node from Tree
BOOL Tree::RemoveNode(Node *p)
{
	Node *pP = p->m_pP;
	Node *pE = p->m_pE;
	Node *pY = p->m_pY;

	if (pE != NULL) {		// has elder
		pE->m_pY = pY;			// connect elder to younger
	}
	else if (pP != NULL) {	// has parent
		pP->m_pC = pY;			// connect parent to younger
	}
	else {					// no elder and no parent
		return FALSE;			// no connection
	}

	if (pY != NULL) {		// has younger
		pY->m_pE = pE;			// connect younger to elder
	}

	return TRUE;
}

// Can Delete Node
BOOL Tree::CanDeleteNode(Node *p)
{
	return CanRemoveNode(p);
}

// Delete Node from Tree
void Tree::DeleteNode(Node *p, UndoList *U)
{
	Node *pTempP = p->m_pP;
	Node *pTempE = p->m_pE;

	if (RemoveNode(p)) {
		// Regsiter Undo
		if (U != NULL) {
			UndoData *obj = new UndoData;
			obj->type = UndoData::U_DEL;
			obj->p = p;
			obj->pP = pTempP;
			obj->pE = pTempE;
			U->Register(this, (void *)obj);
		}
		// Do Delete Node
		else {
			delete p;
		}
	}
}

// Delete All Nodes under Root
void Tree::DeleteAllNodes()
{
	m_pRoot->DeleteAllChildNodes();
	m_pRoot->m_pC = NULL;
}

// Insert Node into Tree
Node *Tree::InsertNode(Node *p,				// new node
					   Node *pParent,		// parent
					   Node *pInsertAfter,	// insert after this node
					   UndoList *U)
{
	//
	// Set Child ---> unnecessary
	//

	//	p->m_pC = NULL;	// child

	//
	// Set Parent
	//

	// Under root
	if (pParent == NULL) {
		p->m_pP = m_pRoot;	// parent

		// No node
		if (m_pRoot->m_pC == NULL) {
			p->m_pE = NULL;		// elder
			p->m_pY = NULL;		// younger
			m_pRoot->m_pC = p;	// add to root
			goto RET_INS;
			//return p;
		}
	}
	// Under specific parent
	else {
		p->m_pP = pParent;	// parent
	}

	//
	// Set Siblings
	//

	// At top sibling
	if (pInsertAfter == NULL) {
		p->m_pE = NULL;			// elder
		p->m_pY = pParent->m_pC;// younger
	}

	// After last sibling
	else if (pInsertAfter == (Node *)LastNode) {
		// No child
		if (p->m_pP->m_pC == NULL) {
			p->m_pE = NULL;	// elder
			p->m_pY = NULL;	// younger
		}
		// At last sibling
		else {
			p->m_pE = p->m_pP->m_pC->FindLastSibling();//FindLastSibling(p->m_pP->m_pC);	// elder
			p->m_pY = NULL;								// younger
		}
	}

	// After specified sibling
	else {
		p->m_pE = pInsertAfter;			// elder
		p->m_pY = pInsertAfter->m_pY;	// younger
	}

	//
	// Set Neighbor Nodes
	//

	// Elder sibling node
	if (p->m_pE != NULL) {	// elder exists
		p->m_pE->m_pY = p;		// elder's younger
	}
	// Parent node
	else {					// top sibling
		p->m_pP->m_pC = p;		// parent's child
	}
	// Younger sibling node
	if (p->m_pY != NULL) {	// younger exists
		p->m_pY->m_pE = p;		// younger's elder
	}

RET_INS:
	if (U != NULL) {
		UndoData *obj = new UndoData;
		obj->type = UndoData::U_INS;
		obj->p = p;
		obj->pP = obj->pE = NULL;
		U->Register(this, (void *)obj);
	}

	//AssignLevels();

	return p;
}

// Can Move Left This Node?
BOOL Tree::CanMoveLeft(Node *p)
{
	if (p->m_pP == NULL) {
		return FALSE;
	}
	return (p->m_pP != m_pRoot);	// parent is not root
}

// Move Left This Node
BOOL Tree::MoveLeft(Node *p, UndoList *U)
{
	//
	// pPP-+-pP-+-pE		pPP-+-pP-+-pE
	//     |    +-p			    |    +-pY
	//     |    +-pY		    +-p
	//     +-pPY			    +-pY
	//
	BOOL bRet = CanMoveLeft(p);
	if (bRet) {
		PlaceAfterParent(p, U);
		AssignLevels();
	}
	return bRet;
}

// Can Move Right This Node?
BOOL Tree::CanMoveRight(Node *p)
{
	if (p->m_pE == NULL) {
		return FALSE;
	}
	return (p->m_pE->m_nNodeType == Node::NT_INNER);	// elder is NT_INNER type
}

// Move Right This Node
BOOL Tree::MoveRight(Node *p, UndoList *U)
{
	//
	// +-pE-+-pEC		+-pE-+-pEC
	// |    +-...		|    +-...
	// |    +-pECL		|    +-pECL
	// +-p				|    +-p
	// +-pY				+-pY
	//
	BOOL bRet = CanMoveRight(p);
	if (bRet) {
		MakeEldersChild(p, U);
		AssignLevels();
	}
	return bRet;
}

// Can Move Up This Node?
BOOL Tree::CanMoveUp(Node *p)
{
	if (p->m_pE == NULL) {
		if ((p->m_pP == m_pRoot) || (p->m_pP == NULL)) {
			return FALSE;
		}
	}
	return TRUE;	// elder exists or parent is not root
}

// Move Up This Node
BOOL Tree::MoveUp(Node *p, UndoList *U)
{
	//
	// pP-+-pE		pP-+-p			pPP-+-pPE			pPP-+-pPE
	//    +-p	->	   +-pE			    +-pP -+-p	->	    +-p
	//    +-pY		   +-pY			          +-pY		    +-pP
	//
	BOOL bRet = CanMoveUp(p);
	if (bRet) {
		if (p->m_pE != NULL) {
			SwapThisAndPrev(p, U);
		}
		else {	// top sibling
			PlaceBeforeParent(p, U);
		}
		AssignLevels();
	}
	return bRet;
}

// Can Move Down This Node?
BOOL Tree::CanMoveDown(Node *p)
{
	if (p->m_pY == NULL) {
		if ((p->m_pP == m_pRoot) || (p->m_pP == NULL)) {
			return FALSE;
		}
	}
	return TRUE;	// younger exists or parent is not root
}

// Move Down This Node
BOOL Tree::MoveDown(Node *p, UndoList *U)
{
	BOOL bRet = CanMoveDown(p);
	if (bRet) {
		if (p->m_pY != NULL) {
			SwapThisAndNext(p, U);
		}
		else {	// last sibling
			PlaceAfterParent(p, U);
		}
		AssignLevels();
	}
	return bRet;
}

// Move Specified Node to Specified Place
BOOL Tree::MoveNode(Node *p,			// new node
					Node *pParent,		// parent
					Node *pInsertAfter,	// insert after this node
					UndoList *U)
{
	// Remove Node
	BOOL bRet = RemoveNode(p);
	if (bRet) {
		Node *pTempP = p->m_pP;
		Node *pTempE = p->m_pE;
		// Insert Node
		InsertNode(p, pParent, pInsertAfter);
		// Regsiter Undo
		if (U != NULL) {
			UndoData *obj = new UndoData;
			obj->type = UndoData::U_MOV;
			obj->p = p;
			obj->pP = pTempP;
			obj->pE = pTempE;
			U->Register(this, (void *)obj);
		}
	}
	return bRet;
}

// swap this node and elder (previous) node
void Tree::SwapThisAndPrev(Node *p, UndoList *U)
{
	//
	//	pP-pEE		pP-pEE
	//	   pE		   p
	//	   p	->	   pE
	//	   pY		   pY
	//
	Node *pEE = p->m_pE->m_pE;	// elder's elder
	Node *pP  = p->m_pP;		// parent
	MoveNode(p, pP, pEE, U);
}

// swap this node and younger (next) node
void Tree::SwapThisAndNext(Node *p, UndoList *U)
{
	SwapThisAndPrev(p->m_pY, U);
}

// place this node before parent node
void Tree::PlaceBeforeParent(Node *p, UndoList *U)
{
	Node *pPP = p->m_pP->m_pP;	// parent's parent
	Node *pPE = p->m_pP->m_pE;	// parent's elder
	MoveNode(p, pPP, pPE, U);
}

// place this node after parent node
void Tree::PlaceAfterParent(Node *p, UndoList *U)
{
	Node *pPP = p->m_pP->m_pP;	// parent's parent
	Node *pP  = p->m_pP;		// parent
	MoveNode(p, pPP, pP, U);
}

// make this node elder's child
void Tree::MakeEldersChild(Node *p, UndoList *U)
{
	Node *pE   = p->m_pE;			// elder
	Node *pEC  = p->m_pE->m_pC;		// elder's child
	Node *pECL = (pEC != NULL) ? pEC->FindLastSibling() : NULL;//FindLastSibling(pEC) : NULL;
									// elder's child's last sibling
	MoveNode(p, pE, pECL, U);
}

// Assign Loop Levels
int Tree::AssignLevels()
{
	return m_pRoot->SetLoopLevel(-1);
}

// Write code
void Tree::Write(CodeWriter *R)
{
	Node *p;

	// Start
	R->WriteStart();

	// Declare Variables
	p = m_pRoot->m_pC;
	while (p) {
		p->WriteDeclare(R);
		p = p->m_pY;
	}
	R->WriteEOL(1);

	// Function Starts
	R->WriteFuncStart();

	// Declare Loop Indices
	int nLevel = AssignLevels();
	R->WriteDeclareLoopIndices(nLevel);
	R->WriteEOL(1);

	// Declare File Descriptor
	R->WriteDeclareFileDesc();
	R->WriteEOL(1);

	// Open File
	R->WriteFileOpen();
	R->WriteEOL(1);

	// Read File (with Allocation)
	p = m_pRoot->m_pC;
	while (p) {
		p->WriteRead(R, 0, NULL);
		p = p->m_pY;
	}
	R->WriteEOL(1);

	// Close File
	R->WriteFileClose();
	R->WriteEOL(1);

	// Function Ends
	R->WriteFuncEnd();

	// Free All
	if (R->IsClearRequired()) {
		R->WriteEOL(1);
		R->WriteClearFuncStart();
		R->WriteDeclareLoopIndices(nLevel);
		R->WriteEOL(1);
		if (m_pRoot->m_pC) {
			p = m_pRoot->m_pC->FindLastSibling();//FindLastSibling(m_pRoot->m_pC);
			while (p) {
				p->WriteClear(R);
				p = p->m_pE;
			}
//			R->WriteEOL(1);
		}
		//p = m_pRoot->m_pC;
		//while (p) {
		//	p->WriteClear(R);
		//	p = p->m_pY;
		//}
		//R->WriteEOL(1);
		R->WriteClearFuncEnd();
	}

	// Appended on Mar.21,'16
	// start
	// Write Function
	if (R->IsWriteFuncEnabled()) {
		R->WriteEOL(1);

		// Function Starts
		R->WriteWFuncStart();

		// Declare Loop Indices
//		int nLevel = AssignLevels();
		R->WriteDeclareLoopIndices(nLevel);
		R->WriteEOL(1);

		// Declare File Descriptor
		R->WriteWDeclareFileDesc();
		R->WriteEOL(1);

		// Open File
		R->WriteWFileOpen();
		R->WriteEOL(1);

		// Read File (with Allocation)
		p = m_pRoot->m_pC;
		while (p) {
			p->WriteWrite(R, 0, NULL);
			p = p->m_pY;
		}
		R->WriteEOL(1);

		// Close File
		R->WriteWFileClose();
		R->WriteEOL(1);

		// Function Ends
		R->WriteWFuncEnd();
	}
	// end

	// Driver
	if (R->IsDriverEnabled()) {
		R->WriteEOL(1);
		R->WriteDriver();
	}

	// End
	R->WriteEnd();

	/*
	R->WriteClearFuncStart();
		if (m_pRoot->m_pC) {
			p = m_pRoot->m_pC->FindLastSibling();//FindLastSibling(m_pRoot->m_pC);
			while (p) {
				p->WriteClear(R);
				p = p->m_pE;
			}
			R->WriteEOL(1);
		}
	R->WriteClearFuncEnd();
	*/
}

// Load data from File
void Tree::Load(FileStream *F)
{
	DeleteAllNodes();

	m_pRoot->SetLoopLevel(-1);

	Node *pPrev = m_pRoot;
	int nPrev = pPrev->GetLoopLevel();

	try {
		while (F->ReadLine() != NULL) {
			char szTemp[100];
			*F >> szTemp;

			if (szTemp[0] == 'T') {
				TypeDef *pCurr = new TypeDef();
				pCurr->Load(F);
				int nCurr = pCurr->GetLoopLevel();
				if (nCurr > nPrev) {
					InsertNode(pCurr, pPrev);
				}
				else if (nCurr == nPrev) {
					InsertNode(pCurr, pPrev->m_pP);
				}
				else {
					Node *p = pPrev->m_pP;
					while (p) {
						if (p->GetLoopLevel() == nCurr) {
							InsertNode(pCurr, p->m_pP);
						}
						p = p->m_pP;
					}
				}
				nPrev = nCurr;
				pPrev = pCurr;
			}
			else if (szTemp[0] == 'L') {
				LoopDef *pCurr = new LoopDef();
				pCurr->Load(F);
				int nCurr = pCurr->GetLoopLevel();
				if (nCurr > nPrev) {
					InsertNode(pCurr, pPrev);
				}
				else if (nCurr == nPrev) {
					InsertNode(pCurr, pPrev->m_pP);
				}
				else {
					Node *p = pPrev->m_pP;
					while (p) {
						if (p->GetLoopLevel() == nCurr) {
							InsertNode(pCurr, p->m_pP);
						}
						p = p->m_pP;
					}
				}
				nPrev = nCurr;
				pPrev = pCurr;
			}
		}
	}
	catch (FsException&) {
	}

	AssignLevels();
}

// Save data to File
void Tree::Save(FileStream *F)
{
	AssignLevels();

	Node *p = m_pRoot->m_pC;
	while (p) {
		p->Save(F);
		p = p->m_pY;
	}
}

Node *Tree::GetHeadNode()
{
	return GetNextNode(m_pRoot);
}

Node *Tree::GetNextNode(Node *p)
{
	Node *pNext = NULL;

	if (p->m_pC != NULL) {
		pNext = p->m_pC;
	}
	else if (p->m_pY != NULL) {
		pNext = p->m_pY;
	}
	else {
		Node *q = p->m_pP;
		while (q) {
			if (q->m_pY != NULL) {
				pNext = q->m_pY;
				break;
			}
			q = q->m_pP;
		}
	}

	return pNext;
}

Node *Tree::GetNextNode(Node *p, Node::NodeType nType)
{
	Node *pNext = NULL;

	Node *q;
	while ((q = GetNextNode(p)) != NULL) {
		if (q->m_nNodeType == nType) {
			pNext = q;
			break;
		}
		p = q;
	}

	return pNext;
}

Node *Tree::GetHeadLeaf()
{
	return GetNextLeaf(m_pRoot);
}

Node *Tree::GetNextLeaf(Node *p)
{
	/*
	Node *pNext = NULL;

	Node *q;
	while ((q = GetNextNode(p)) != NULL) {
		if (q->m_nNodeType == Node::NT_LEAF) {
			pNext = q;
			break;
		}
		p = q;
	}

	return pNext;
	*/
	return GetNextNode(p, Node::NT_LEAF);
}

Node *Tree::GetHeadInner()
{
	return GetNextInner(m_pRoot);
}

Node *Tree::GetNextInner(Node *p)
{
	return GetNextNode(p, Node::NT_INNER);
}

BOOL Tree::VariableExists(LPCTSTR lpszVariable)
{
	/*
	Node *pNode = m_pRoot->m_pC;
	while (pNode != NULL) {
		if (pNode->m_nNodeType == Node::NT_LEAF) {
			if (!lstrcmp(lpszVariable, pNode->GetVariable().GetName())) {
				return TRUE;
			}
		}
		pNode = GetNextNode(pNode);
	}

	return FALSE;
	*/
	return (FindVariable(lpszVariable) != NULL);
}

Node *Tree::FindVariable(LPCTSTR lpszVariable)
{
	Node *pNode = m_pRoot->m_pC;
	while (pNode != NULL) {
		if (pNode->m_nNodeType == Node::NT_LEAF) {
			if (!lstrcmp(lpszVariable, pNode->GetVariable().GetName())) {
				return pNode;
			}
		}
		pNode = GetNextNode(pNode);
	}

	return NULL;
}

/*
// Restore Node into Tree
BOOL Tree::RestoreNode(Node *p)
{
	Node *pP = p->m_pP;
	Node *pE = p->m_pE;
	Node *pY = p->m_pY;

	if (pE != NULL) {		// has elder
		pE->m_pY = p;			// connect elder to myself
	}
	else if (pP != NULL) {	// has parent
		pP->m_pC = p;			// connect parent to myself (as top brother)
	}
	else {					// no elder and no parent
		return FALSE;			// no connection
	}

	if (pY != NULL) {		// has younger
		pY->m_pE = p;			// connect younger to myself
	}

	return TRUE;
}
*/
/*
// connect node to neighbor nodes (parent and elder and younger siblings)
void Tree::ConnectToParentAndSiblings(Node *p)
{
	// elder exists
	if (p->m_pE != NULL) {
		p->m_pE->m_pY = p;	// elder's younger = p
	}
	// elder not exist (p is top sibling)
	else {
		p->m_pP->m_pC = p;	// parent's child = p
	}

	// younger exists
	if (p->m_pY != NULL) {
		p->m_pY->m_pE = p;	// younger's elder = p
	}
}
*/

//
// for Undo
//
void Tree::ExeUndo(void *pPara)
{
	UndoData *obj = (UndoData *)pPara;

	if (obj->type == UndoData::U_INS) {
		DeleteNode(obj->p);
	}
	else if (obj->type == UndoData::U_DEL) {
		InsertNode(obj->p, obj->pP, obj->pE);
	}
	else if (obj->type == UndoData::U_MOV) {
		MoveNode(obj->p, obj->pP, obj->pE);
	}
	AssignLevels();

	delete obj;
}

void Tree::DelUndo(void *pPara)
{
	UndoData *obj = (UndoData *)pPara;
	if (obj->type == UndoData::U_DEL) {
		delete obj->p;
	}
	delete obj;
}

void Tree::CorrectLoopIndices(LoopIndexManager *pLM)
{
	Node *p = GetHeadInner();
	while (p != NULL) {
		p->GetVariable().CorrectLoopIndices(pLM);
		p = GetNextInner(p);
	}
}