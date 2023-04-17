// SetLicenseDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "Br.h"
#include "SetLicenseDialog.h"
#include "LicManager.h"


// CSetLicenseDialog �_�C�A���O

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


// CSetLicenseDialog ���b�Z�[�W �n���h��

void CSetLicenseDialog::OnOK()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
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
