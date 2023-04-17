// ToolsOptionsDialog.cpp : �����t�@�C��
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


// CToolsOptionsDialog ���b�Z�[�W �n���h��

BOOL CToolsOptionsDialog::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  �����ɓ���ȃR�[�h��ǉ����Ă��������B

	return bResult;
}
