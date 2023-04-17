#pragma once
#include "afxwin.h"


// CAddLoopDialog ダイアログ

class CAddLoopDialog : public CDialog
{
	DECLARE_DYNAMIC(CAddLoopDialog)

	class LoopIndexManager *m_pLM;

public:
	CAddLoopDialog(class LoopIndexManager *pLM, UINT nStrTitleID,
		CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CAddLoopDialog();

// ダイアログ データ
	enum { IDD = IDD_ADD_LOOP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	UINT m_nStrTitleID;
	CString m_strVariable;
	CEdit m_edVariable;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
