#pragma once


// CToolsOptGenPage ダイアログ

class CToolsOptGenPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CToolsOptGenPage)

public:
	CToolsOptGenPage();
	virtual ~CToolsOptGenPage();

// ダイアログ データ
	enum { IDD = IDD_TOOLS_OPT_GEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
