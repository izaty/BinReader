// SrcOptions.cpp : 実装ファイル
//

#include "stdafx.h"
#include "Br.h"
#include "SrcOptionsDialog.h"
#include "LoopIndexManager.h"


// CSrcOptionsDialog ダイアログ

IMPLEMENT_DYNAMIC(CSrcOptionsDialog, CDialog)

CSrcOptionsDialog::CSrcOptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSrcOptionsDialog::IDD, pParent)
	, m_nLang(0)
	, m_nIndent(0)
	, m_nLoopIndex(0)
	, m_nLoopType(0)
	, m_nVarPos(FALSE)
	, m_nNewLine(0)
	, m_bDriver(FALSE)
	, m_bEndian(FALSE)
	, m_nEndType(0)
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
	DDX_Radio(pDX, IDC_VAR_LOCAL, m_nVarPos);
	DDX_Control(pDX, IDC_LOOP_INDEX, m_cbLoopIndex);
	DDX_Control(pDX, IDC_LOOP_TYPE, m_cbLoopType);
	DDX_CBIndex(pDX, IDC_NEWLINE, m_nNewLine);
	DDX_Check(pDX, IDC_DRIVER, m_bDriver);
	DDX_Check(pDX, IDC_ENDIAN, m_bEndian);
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


// CSrcOptionsDialog メッセージ ハンドラ

BOOL CSrcOptionsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ここに初期化を追加してください
//	for (volatile int i = 0; i < LoopIndexManager::VarTypeCount; i++) {
//		m_cbLoopIndex.InsertString(i, 
//	}
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
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CSrcOptionsDialog::OnBnClickedLangC()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	SwitchLang(IDS_DECL_EXT, FALSE, TRUE);
}

void CSrcOptionsDialog::OnBnClickedLangCpl()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	SwitchLang(IDS_DECL_MEM, FALSE, TRUE);
}

void CSrcOptionsDialog::OnBnClickedLangCsh()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	SwitchLang(IDS_DECL_MEM, FALSE, TRUE);
}

void CSrcOptionsDialog::OnBnClickedLangJava()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	SwitchLang(IDS_DECL_MEM, TRUE, TRUE);
}

void CSrcOptionsDialog::OnBnClickedLangPHP()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	SwitchLang(IDS_DECL_MEM, FALSE, FALSE);
}

void CSrcOptionsDialog::OnBnClickedLangRuby()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	SwitchLang(IDS_DECL_MEM, FALSE, FALSE);
}

void CSrcOptionsDialog::SwitchLang(UINT nStringID, BOOL bEndTypeFlag, BOOL bVarTypeFlag)
{
	CString strText; strText.LoadString(nStringID);
	GetDlgItem(IDC_VAR_MEMBER)->SetWindowText(strText);
	m_cbEndType.SetCurSel((bEndTypeFlag) ? m_nEndType : -1);
	bEndTypeFlag &= (m_btEndian.GetCheck() == BST_CHECKED);
	m_cbEndType.EnableWindow(bEndTypeFlag);
	GetDlgItem(IDC_VAR_STATIC)->EnableWindow(bVarTypeFlag);
	GetDlgItem(IDC_VAR_LOCAL)->EnableWindow(bVarTypeFlag);
	GetDlgItem(IDC_VAR_MEMBER)->EnableWindow(bVarTypeFlag);
}

void CSrcOptionsDialog::OnBnClickedEndian()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	BOOL bFlag = (m_btEndian.GetCheck() == BST_CHECKED);
	bFlag &= (((CButton *)GetDlgItem(IDC_LANG_JAVA))->GetCheck() == BST_CHECKED);
	m_cbEndType.EnableWindow(bFlag);
}

