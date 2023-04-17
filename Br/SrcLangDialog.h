#pragma once


// CSrcLangDialog ダイアログ

class CSrcLangDialog : public CDialog
{
	DECLARE_DYNAMIC(CSrcLangDialog)

public:
	CSrcLangDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSrcLangDialog();

// ダイアログ データ
	enum { IDD = IDD_SRC_LANG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

public:
	int m_nLang;
	BOOL m_bNodisp;
};
