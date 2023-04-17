// SetLicenseDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "Br.h"
#include "SetLicenseDialog.h"
#include "LicManager.h"


// CSetLicenseDialog ダイアログ

IMPLEMENT_DYNAMIC(CSetLicenseDialog, CDialog)

CSetLicenseDialog::CSetLicenseDialog(LicManager *pLM,
									 CWnd* pParent /*=NULL*/)
	: CDialog(CSetLicenseDialog::IDD, pParent)
{
	m_pLM = pLM;
}

CSetLicenseDialog::~CSetLicenseDialog()
{
}

void CSetLicenseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VARIABLE, m_edVariable);
}


BEGIN_MESSAGE_MAP(CSetLicenseDialog, CDialog)
END_MESSAGE_MAP()


// CSetLicenseDialog メッセージ ハンドラ

void CSetLicenseDialog::OnOK()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CString strVariable;
	m_edVariable.GetWindowText(strVariable);

	if (!m_pLM->SetKey(strVariable)) {
		AfxMessageBox(IDS_ERR_INVALID_KEY);
	}
	else {
		AfxMessageBox(IDS_INF_VALID_KEY, MB_ICONINFORMATION | MB_OK);
		CDialog::OnOK();
	}
}
