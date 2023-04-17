#pragma once


// CTrialMessageDlg ダイアログ

class CTrialMessageDlg : public CDialog
{
	DECLARE_DYNAMIC(CTrialMessageDlg)

public:
	CTrialMessageDlg(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CTrialMessageDlg();

// ダイアログ データ
	enum { IDD = IDD_TRIAL_MESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
