// ToolsOptGenPage.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "Br.h"
#include "ToolsOptGenPage.h"


// CToolsOptGenPage �_�C�A���O

IMPLEMENT_DYNAMIC(CToolsOptGenPage, CPropertyPage)

CToolsOptGenPage::CToolsOptGenPage()
	: CPropertyPage(CToolsOptGenPage::IDD)
{

}

CToolsOptGenPage::~CToolsOptGenPage()
{
}

void CToolsOptGenPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolsOptGenPage, CPropertyPage)
END_MESSAGE_MAP()


// CToolsOptGenPage ���b�Z�[�W �n���h��

BOOL CToolsOptGenPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �����ɏ�������ǉ����Ă�������

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}
