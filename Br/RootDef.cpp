#include "StdAfx.h"
#include "resource.h"
#include "RootDef.h"

RootDef::RootDef(void) : Node(NT_INNER)
{
	TCHAR sz[100];
	::LoadString(NULL, IDS_TREE_ROOT, sz, 100);
	m_variable.SetName(sz);
}

RootDef::~RootDef(void)
{
}
