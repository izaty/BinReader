#pragma once
#include "afxwin.h"


// CSetLicenseDialog �_�C�A���O

class CSetLicenseDialog : public CDialog
{
	DECLARE_DYNAMIC(CSetLicenseDialog)

private:
	class LicManager *m_pLM;

public:
	CSetLicenseDialog(LicManager *pLM,
		CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CSetLicenseDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SET_LICENSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CEdit m_edVariable;
};
