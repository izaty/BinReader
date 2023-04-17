// SrcLangDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "Br.h"
#include "SrcLangDialog.h"


// CSrcLangDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CSrcLangDialog, CDialog)

CSrcLangDialog::CSrcLangDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSrcLangDialog::IDD, pParent)
	, m_nLang(0)
	, m_bNodisp(FALSE)
{

}

CSrcLangDialog::~CSrcLangDialog()
{
}

void CSrcLangDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_LANG_C, m_nLang);
	DDX_Check(pDX, IDC_NODISP, m_bNodisp);
}


BEGIN_MESSAGE_MAP(CSrcLangDialog, CDialog)
END_MESSAGE_MAP()


// CSrcLangDialog ���b�Z�[�W �n���h��
