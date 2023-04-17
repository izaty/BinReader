#include "StdAfx.h"
#include "Node.h"

// Constructor
Node::Node(NodeType nNodeType)
{
	m_nNodeType = nNodeType;
	m_pP = m_pC = m_pE = m_pY = NULL;
}

// Destructor
Node::~Node()
{
	DeleteAllChildNodes();
}

// Debug
void Node::Display(int nLevel)
{
	Node *p = m_pC;
	while (p) {
		p->Display(nLevel + 1);
		p = p->m_pY;
	}
}

// Delete All Child Nodes
void Node::DeleteAllChildNodes()
{
	Node *p = m_pC;	// child
	while (p) {
		Node *q = p->m_pY;	// keep next sibling
		delete p;			// delete current sibling
		p = q;				// go to next sibling
	}
}

// Get Total Number of Nodes (including myself)
int Node::GetNodeCount() const
{
	int nCount = 1;	// including myself

	Node *p = m_pC;	// child
	while (p) {
		nCount += p->GetNodeCount();// add number of nodes within current sibling
		p = p->m_pY;				// go to next sibling
	}

	return nCount;
}

// Get Max Loop Level Number of Nodes (including myself)
int Node::GetMaxLoopLevel() const
{
	int nMaxLoopLevel = m_variable.GetLoopLevel();

	Node *p = m_pC;	// child
	while (p) {
		int nLoopLevel = p->GetVariable().GetLoopLevel();
		if (nLoopLevel > nMaxLoopLevel) {
			nMaxLoopLevel = nLoopLevel;
		}
		p = p->m_pY;				// go to next sibling
	}

	return nMaxLoopLevel;
}

// Set Loop Level to myself and descendants
//
// (return value: Maximum Level under this node)
//
int Node::SetLoopLevel(int nLevel)
{
	// Loop level of myself
	m_variable.SetLoopLevel(nLevel);

	// Maximum level under this node
	int nMaxLevel = m_variable.GetLoopLevel();

	nLevel++;
	Node *p = m_pC;
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

Node *Node::FindTopSibling()
{
	Node *r = this;
	Node *p = m_pE;
	while (p) {
		r = p;
		p = p->m_pE;
	}
	return r;
}

Node *Node::FindLastSibling()
{
	Node *r = this;
	Node *p = m_pY;
	while (p) {
		r = p;
		p = p->m_pY;
	}
	return r;
}