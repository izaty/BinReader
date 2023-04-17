// SrcOptions.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "Br.h"
#include "SrcOptionsDialog.h"
#include "LoopIndexManager.h"


// CSrcOptionsDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CSrcOptionsDialog, CDialog)

CSrcOptionsDialog::CSrcOptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSrcOptionsDialog::IDD, pParent)
	, m_nLang(0)
	, m_nIndent(0)
	, m_nLoopIndex(0)
	, m_nLoopType(0)
	, m_nNewLine(0)
	, m_bDriver(FALSE)
	, m_bEndian(FALSE)
	, m_nEndType(0)
	, m_bWrite(TRUE)
{

}

CSrcOptionsDialog::~CSrcOptionsDialog()
{
}

void CSrcOptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_LANG_C, m_nLang);
	DDX_CBIndex(pDX, IDC_INDENT, m_nIndent);
	DDX_CBIndex(pDX, IDC_LOOP_INDEX, m_nLoopIndex);
	DDX_CBIndex(pDX, IDC_LOOP_TYPE, m_nLoopType);
	DDX_Control(pDX, IDC_LOOP_INDEX, m_cbLoopIndex);
	DDX_Control(pDX, IDC_LOOP_TYPE, m_cbLoopType);
	DDX_CBIndex(pDX, IDC_NEWLINE, m_nNewLine);
	DDX_Check(pDX, IDC_DRIVER, m_bDriver);
	DDX_Check(pDX, IDC_ENDIAN, m_bEndian);
	DDX_Check(pDX, IDC_WRITE, m_bWrite);
	DDX_Control(pDX, IDC_END_TYPE, m_cbEndType);
	DDX_CBIndex(pDX, IDC_END_TYPE, m_nEndType);
	DDX_Control(pDX, IDC_ENDIAN, m_btEndian);
	DDX_Control(pDX, IDC_DRIVER, m_btDriver);
}


BEGIN_MESSAGE_MAP(CSrcOptionsDialog, CDialog)
	ON_BN_CLICKED(IDC_LANG_C, &CSrcOptionsDialog::OnBnClickedLangC)
	ON_BN_CLICKED(IDC_LANG_CPL, &CSrcOptionsDialog::OnBnClickedLangCpl)
	ON_BN_CLICKED(IDC_LANG_CSH, &CSrcOptionsDialog::OnBnClickedLangCsh)
	ON_BN_CLICKED(IDC_LANG_JAVA, &CSrcOptionsDialog::OnBnClickedLangJava)
	ON_BN_CLICKED(IDC_LANG_PHP, &CSrcOptionsDialog::OnBnClickedLangPHP)
	ON_BN_CLICKED(IDC_LANG_RUBY, &CSrcOptionsDialog::OnBnClickedLangRuby)
	ON_BN_CLICKED(IDC_ENDIAN, &CSrcOptionsDialog::OnBnClickedEndian)
END_MESSAGE_MAP()


// CSrcOptionsDialog ���b�Z�[�W �n���h��

BOOL CSrcOptionsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �����ɏ�������ǉ����Ă�������
	switch (m_nLang) {
	case 0:
		OnBnClickedLangC();
		break;
	case 1:
		OnBnClickedLangCpl();
		break;
	case 2:
		OnBnClickedLangCsh();
		break;
	case 3:
		OnBnClickedLangJava();
		break;
	case 4:
		OnBnClickedLangPHP();
		break;
	case 5:
		OnBnClickedLangRuby();
		break;
	}

	CBrApp *pApp = (CBrApp *)AfxGetApp();
	if (pApp->IsTrial()) {
		m_btDriver.SetCheck(BST_UNCHECKED);
		m_btDriver.EnableWindow(FALSE);
		m_btEndian.SetCheck(BST_UNCHECKED);
		m_btEndian.EnableWindow(FALSE);
		m_cbEndType.EnableWindow(FALSE);
		// Appended on Mar.24,'16
		// start
		m_btWrite.EnableWindow(FALSE);
		// end
	}

	GetDlgItem(IDC_NEWLINE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NEWLINE_FR)->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CSrcOptionsDialog::OnBnClickedLangC()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	SwitchLang(IDS_DECL_EXT, FALSE);
}

void CSrcOptionsDialog::OnBnClickedLangCpl()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	SwitchLang(IDS_DECL_MEM, FALSE);
}

void CSrcOptionsDialog::OnBnClickedLangCsh()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	SwitchLang(IDS_DECL_MEM, FALSE);
}

void CSrcOptionsDialog::OnBnClickedLangJava()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	SwitchLang(IDS_DECL_MEM, TRUE);
}

void CSrcOptionsDialog::OnBnClickedLangPHP()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	SwitchLang(IDS_DECL_MEM, FALSE);
}

void CSrcOptionsDialog::OnBnClickedLangRuby()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	SwitchLang(IDS_DECL_MEM, FALSE);
}

void CSrcOptionsDialog::SwitchLang(UINT nStringID, BOOL bEndTypeFlag)
{
	CString strText; strText.LoadString(nStringID);
	m_cbEndType.SetCurSel((bEndTypeFlag) ? m_nEndType : -1);
	bEndTypeFlag &= (m_btEndian.GetCheck() == BST_CHECKED);
	m_cbEndType.EnableWindow(bEndTypeFlag);
}

void CSrcOptionsDialog::OnBnClickedEndian()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	BOOL bFlag = (m_btEndian.GetCheck() == BST_CHECKED);
	bFlag &= (((CButton *)GetDlgItem(IDC_LANG_JAVA))->GetCheck() == BST_CHECKED);
	m_cbEndType.EnableWindow(bFlag);
}

