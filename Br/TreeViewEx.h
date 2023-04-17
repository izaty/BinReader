#pragma once


// CTreeViewEx �r���[

class CTreeViewEx : public CTreeView
{
	DECLARE_DYNCREATE(CTreeViewEx)

protected:
	CTreeViewEx();           // ���I�����Ŏg�p����� protected �R���X�g���N�^
	virtual ~CTreeViewEx();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

	// Expand Specified Branch
	void ExpandBranch(HTREEITEM hItem);

	// Expand All Branches
	void ExpandAll();
};


