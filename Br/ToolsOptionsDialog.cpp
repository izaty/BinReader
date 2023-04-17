// ToolsOptionsDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "Br.h"
#include "ToolsOptionsDialog.h"


// CToolsOptionsDialog

IMPLEMENT_DYNAMIC(CToolsOptionsDialog, CPropertySheet)

CToolsOptionsDialog::CToolsOptionsDialog(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pGen = new CToolsOptGenPage();
	AddPage(m_pGen);
}

CToolsOptionsDialog::CToolsOptionsDialog(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pGen = new CToolsOptGenPage();
	AddPage(m_pGen);
}

CToolsOptionsDialog::~CToolsOptionsDialog()
{
	delete m_pGen;
}


BEGIN_MESSAGE_MAP(CToolsOptionsDialog, CPropertySheet)
END_MESSAGE_MAP()


// CToolsOptionsDialog メッセージ ハンドラ

BOOL CToolsOptionsDialog::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  ここに特定なコードを追加してください。

	return bResult;
}
