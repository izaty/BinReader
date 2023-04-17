#pragma once

#include "ToolsOptGenPage.h"


// CToolsOptionsDialog

class CToolsOptionsDialog : public CPropertySheet
{
	DECLARE_DYNAMIC(CToolsOptionsDialog)

public:
	CToolsOptionsDialog(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CToolsOptionsDialog(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CToolsOptionsDialog();

	CToolsOptGenPage *m_pGen;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};


