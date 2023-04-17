#pragma once
#include "afxwin.h"


// CSetLicenseDialog ダイアログ

class CSetLicenseDialog : public CDialog
{
	DECLARE_DYNAMIC(CSetLicenseDialog)

private:
	class LicManager *m_pLM;

public:
	CSetLicenseDialog(LicManager *pLM,
		CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSetLicenseDialog();

// ダイアログ データ
	enum { IDD = IDD_SET_LICENSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CEdit m_edVariable;
};
