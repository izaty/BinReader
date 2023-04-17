#include "StdAfx.h"
#include "Tree.h"
#include "CodeWriter.h"
#include "RootDef.h"
#include "TypeDef.h"
#include "LoopDef.h"

//
// Tree::Node class
//

// Constructor
Tree::Node::Node(NodeType nNodeType)
{
//	::ZeroMemory(m_szVariable, sizeof(m_szVariable));
	m_nNodeType = nNodeType;
	m_pP = m_pC = m_pE = m_pY = NULL;
//	m_nLoopLevel = 0;
}

// Destructor
Tree::Node::~Node()
{
	DeleteAllChildNodes();
}

// Debug
void Tree::Node::Display(int nLevel)
{
	Tree::Node *p = m_pC;
	while (p) {
		p->Display(nLevel + 1);
		p = p->m_pY;
	}
}

// Delete All Child Nodes
void Tree::Node::DeleteAllChildNodes()
{
	Node *p = m_pC;	// child
	while (p) {
		Node *q = p->m_pY;	// keep next sibling
		delete p;			// delete current sibling
		p = q;				// go to next sibling
	}
}

// Get Total Number of Nodes (including myself)
int Tree::Node::GetNodeCount()
{
	int nCount = 1;	// including myself

	Node *p = m_pC;	// child
	while (p) {
		nCount += p->GetNodeCount();// add number of nodes within current sibling
		p = p->m_pY;				// go to next sibling
	}

	return nCount;
}

// Set Loop Level to myself and descendants
// (Return Maximum Level under this node)
int Tree::Node::SetLoopLevel(int nLevel)
{
	// Loop level of myself
//	m_nLoopLevel = nLevel;
	m_variable.SetLoopLevel(nLevel);

	// Maximum level under this node
//	int nMaxLevel = m_nLoopLevel;
	int nMaxLevel = m_variable.GetLoopLevel();

	nLevel++;
	Tree::Node *p = m_pC;
	while (p) {
		// Maximum level under this node's child
		int nRetLevel = p->SetLoopLevel(nLevel);
		if (nRetLevel > nMaxLevel) {
			nMaxLevel = nRetLevel;
		}
		p = p->m_pY;
	}

	// Return Maximum Level
	return nMaxLevel;
}

//// Set Variable Name
//void Tree::Node::SetVariable(LPCTSTR lpszVariable)
//{
//	lstrcpy(m_szVariable, lpszVariable);
//	m_variable.SetName(lpszVariable);
//}

//
// Tree class
//

// Constructor
Tree::Tree(void)
{
	// Root Node (just access point)
	m_pRoot = new RootDef();//new Node(NT_INNER);
	// Temprarily
	//m_pTemp = m_pTempPrevP = m_pTempPrevE = m_pTempPrevY = NULL;
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
Tree::Node *Tree::FindTopSibling(Node *p)
{
	while (p->m_pE) {
		p = p->m_pE;
	}
	return p;
}

// Find Youngest Sibling of Specified Node
Tree::Node *Tree::FindLastSibling(Node *p)
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
void Tree::DeleteNode(Node *p)
{
	if (RemoveNode(p)) {
		delete p;
	}
}

// Delete All Nodes under Root
void Tree::DeleteAllNodes()
{
	m_pRoot->DeleteAllChildNodes();
	m_pRoot->m_pC = NULL;
}

// Insert Node into Tree
Tree::Node *Tree::InsertNode(Node *p,				// new node
							 Node *pParent,			// parent
							 Node *pInsertAfter)	// insert after this node
{
	//
	// Set Child
	//

	p->m_pC = NULL;	// child

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
			return p;
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
			p->m_pE = FindLastSibling(p->m_pP->m_pC);	// elder
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
BOOL Tree::MoveLeft(Node *p)
{
	//
	// pPP-+-pP-+-pE		pPP-+-pP-+-pE
	//     |    +-p			    |    +-pY
	//     |    +-pY		    +-p
	//     +-pPY			    +-pY
	//
	BOOL bRet = CanMoveLeft(p);
	if (bRet) {
		Node *pP  = p->m_pP;		// parent
		Node *pE  = p->m_pE;		// elder
		Node *pY  = p->m_pY;		// younger
		Node *pPP = p->m_pP->m_pP;	// parent's parent
		Node *pPY = p->m_pP->m_pY;	// parent's younger

		// new place
		p->m_pP = pPP;		// p's parent	= parent's parent
		p->m_pE = pP;		// p's elder	= parent
		p->m_pY = pPY;		// p's younger	= parent's younger
		ConnectToParentAndSiblings(p);	// connect to neighbors

		// old place
		if (pE != NULL) {	// if old p's elder exists
			pE->m_pY = pY;		// old p's elder's younger = old younger
		}
		else {				// if old p's elder not exist
			pP->m_pC = pY;		// old p's child = old younger
		}
		if (pY != NULL) {	// if old p's younger exists
			pY->m_pE = pE;		// old p's younger's elder = old elder
		}

		// assign levels
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
	return (p->m_pE->m_nNodeType == NT_INNER);	// elder is NT_INNER type
}

// Move Right This Node
BOOL Tree::MoveRight(Node *p)
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
		/*
		Node *pE   = p->m_pE;			// elder
		Node *pY   = p->m_pY;			// younger
		Node *pEC  = p->m_pE->m_pC;		// elder's child
		Node *pECL = (pEC != NULL) ? FindLastSibling(pEC) : NULL;
										// elder's child's last sibling
		// new place
		p->m_pP = pE;		// p's parent	= elder
		p->m_pE = pECL;		// p's elder	= elder's child's last sibling
		p->m_pY = NULL;		// p's younger	= (none)
		ConnectToParentAndSiblings(p);	// connect to neighbors

		// old place
		pE->m_pY = pY;			// old p's elder's younger = old younger
		if (pY != NULL) {	// if old p's younger exists
			pY->m_pE = pE;		// old p's younger's elder = old elder
		}
		*/
		RemoveNode(p);
		Node *pE   = p->m_pE;			// elder
		Node *pEC  = p->m_pE->m_pC;		// elder's child
		Node *pECL = (pEC != NULL) ? FindLastSibling(pEC) : NULL;
										// elder's child's last sibling
		p->m_pP = pE;		// p's parent	= elder
		p->m_pE = pECL;		// p's elder	= elder's child's last sibling
		p->m_pY = NULL;		// p's younger	= (none)
		ConnectToParentAndSiblings(p);	// connect to neighbors

		// assign levels
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
BOOL Tree::MoveUp(Node *p)
{
	//
	// pP-+-pE		pP-+-p			pPP-+-pPE			pPP-+-pPE
	//    +-p	->	   +-pE			    +-pP -+-p	->	    +-p
	//    +-pY		   +-pY			          +-pY		    +-pP
	//
	BOOL bRet = CanMoveUp(p);
	if (bRet) {
		if (p->m_pE != NULL) {
			SwapThisAndPrev(p);
		}
		// top sibling
		else {
			/*
			Node *pPP = p->m_pP->m_pP;	// parent's parent
			Node *pPE = p->m_pP->m_pE;	// parent's elder
			Node *pP  = p->m_pP;		// parent
			Node *pY  = p->m_pY;		// younger

			// new place
			p->m_pP = pPP;		// p's parent	= parent's parent
			p->m_pE = pPE;		// p's elder	= parent's elder
			p->m_pY = pP;		// p's younger	= parent
			ConnectToParentAndSiblings(p);	// connect to neighbors

			// old place
			pP->m_pC = pY;			// old p's parent's child = old younger
			if (pY != NULL) {	// if old p's younger exists
				pY->m_pE = NULL;	// old p's younger = (none)
			}
			*/
			Node *pPP = p->m_pP->m_pP;	// parent's parent
			Node *pPE = p->m_pP->m_pE;	// parent's elder
			MoveNode(p, pPP, pPE);
		}

		// assign levels
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
BOOL Tree::MoveDown(Node *p)
{
	BOOL bRet = CanMoveDown(p);
	if (bRet) {
		if (p->m_pY != NULL) {
			SwapThisAndNext(p);
		}
		// last sibling
		else {
			Node *pPP = p->m_pP->m_pP;	// parent's parent
			Node *pPY = p->m_pP->m_pY;	// parent's younger
			Node *pP  = p->m_pP;		// parent
			Node *pE  = p->m_pE;		// elder

			// new place
			p->m_pP = pPP;		// p's parent	= parent's parent
			p->m_pE = pP;		// p's elder	= parent
			p->m_pY = pPY;		// p's younger	= parent's younger
			ConnectToParentAndSiblings(p);	// connect to neighbors

			// old place
			if (pE != NULL) {	// if old p's elder exists
				pE->m_pY = NULL;	// old p's elder's younger	= (none)
			}
			else {				// if old p's elder not exist
				pP->m_pC = NULL;	// old p's parent's child	= (none)
			}
		}

		// assign levels
		AssignLevels();
	}
	return bRet;
}

// Move Specified Node to Specified Place
BOOL Tree::MoveNode(Node *p,			// new node
					Node *pParent,		// parent
					Node *pInsertAfter)	// insert after this node
{
	// Remove Node
	BOOL bRet = RemoveNode(p);
	if (bRet) {
		// Insert Node
		InsertNode(p, pParent, pInsertAfter);
	}
	return bRet;
	/*
	p->m_pP = pP;
	p->m_pE = pE;
	p->m_pY = pY;
	ConnectToParentAndSiblings(p);	// connect to neighbors
	*/
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

// swap this node and elder (previous) node
void Tree::SwapThisAndPrev(Node *p)
{
	//
	//	pP-pEE		pP-pEE
	//	   pE		   p
	//	   p	->	   pE
	//	   pY		   pY
	//
	Node *pEE = p->m_pE->m_pE;	// elder's elder
	Node *pE  = p->m_pE;		// elder
	Node *pY  = p->m_pY;		// younger
	Node *pP  = p->m_pP;		// parent

	// p
	p->m_pE = pEE;	// p's elder	= elder's elder
	p->m_pY = pE;	// p's younger	= elder

	// pE
	pE->m_pE = p;	// pE's elder	= p
	pE->m_pY = pY;	// pE's younger	= p's younger

	// pEE/pP

	// pEE exists
	if (pEE != NULL) {
		pEE->m_pY = p;	// pEE's younger	= p
	}
	// pEE not exist
	else {
		pP->m_pC = p;	// pP's child		= p
	}

	// pY

	// pY exists
	if (pY != NULL) {
		pY->m_pE = pE;	// pY's elder		= p
	}
}

// swap this node and younger (next) node
void Tree::SwapThisAndNext(Node *p)
{
	SwapThisAndPrev(p->m_pY);
}

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

// Assign Loop Levels
int Tree::AssignLevels()
{
	return m_pRoot->SetLoopLevel(-1);
}

// Write code
void Tree::Write(CodeWriter *R)
{
	// Start
	R->WriteFuncStart();

	// Declare Loop Indices
	int nLevel = AssignLevels();
	R->WriteDeclareLoopIndices(nLevel);
	R->WriteEOL(1);

	Node *p;

	// Declare Variables
	p = m_pRoot->m_pC;
	while (p) {
		p->WriteDeclare(R);
		p = p->m_pY;
	}
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

	// Free All
	p = m_pRoot->m_pC;
	while (p) {
		p->WriteClear(R);
		p = p->m_pY;
	}
	R->WriteEOL(1);

	// Close File
	R->WriteFileClose();
	R->WriteEOL(1);

	// End
	R->WriteFuncEnd();
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

Tree::Node *Tree::GetHeadNode()
{
	return GetNextNode(m_pRoot);
}

Tree::Node *Tree::GetNextNode(Node *p)
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

Tree::Node *Tree::GetHeadLeaf()
{
	return GetNextLeaf(m_pRoot);
}

Tree::Node *Tree::GetNextLeaf(Node *p)
{
	Node *pNext = NULL;

	Node *q;
	while ((q = GetNextNode(p)) != NULL) {
		if (q->m_nNodeType == NT_LEAF) {
			pNext = q;
			break;
		}
		p = q;
	}

	return pNext;
}

BOOL Tree::VariableExists(LPCTSTR lpszVariable)
{
	Node *pNode = m_pRoot->m_pC;
	while (pNode != NULL) {
		if (pNode->m_nNodeType == NT_LEAF) {
//			if (!lstrcmp(lpszVariable, pNode->GetVariable())) {
			if (!lstrcmp(lpszVariable, 
				pNode->GetVariable().GetName())) {
				return TRUE;
			}
		}
		pNode = GetNextNode(pNode);
	}

	return FALSE;
}
