#pragma once
#include "afxwin.h"

#include "Tree.h"

// CAddDataDialog ダイアログ

class CAddDataDialog : public CDialog
{
	DECLARE_DYNAMIC(CAddDataDialog)

public:
	CAddDataDialog(UINT nStrTitleID, Tree *pTree,
		CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CAddDataDialog();

// ダイアログ データ
	enum { IDD = IDD_ADD_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
protected:
	UINT m_nStrTitleID;
	Tree *m_pTree;

public:
	int m_nType;
	CString m_strVariable;
	CEdit m_edVariable;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CComboBox m_cbType;
};
