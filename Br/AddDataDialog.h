#pragma once
#include "afxwin.h"

#include "Tree.h"

// CAddDataDialog �_�C�A���O

class CAddDataDialog : public CDialog
{
	DECLARE_DYNAMIC(CAddDataDialog)

public:
	CAddDataDialog(UINT nStrTitleID, Tree *pTree,
		CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CAddDataDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ADD_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

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
