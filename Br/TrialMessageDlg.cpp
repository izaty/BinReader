// TrialMessageDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "Br.h"
#include "TrialMessageDlg.h"


// CTrialMessageDlg ダイアログ

IMPLEMENT_DYNAMIC(CTrialMessageDlg, CDialog)

CTrialMessageDlg::CTrialMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrialMessageDlg::IDD, pParent)
{

}

CTrialMessageDlg::~CTrialMessageDlg()
{
}

void CTrialMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTrialMessageDlg, CDialog)
END_MESSAGE_MAP()


// CTrialMessageDlg メッセージ ハンドラ

BOOL CTrialMessageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ここに初期化を追加してください
	CString strText;
	strText.LoadString(IDS_TRIAL_MESSAGE);
	AfxMessageBox(strText);
	GetDlgItem(IDC_MESSAGE)->SetWindowText(strText);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
