#pragma once
#include "afxwin.h"


// CAddLoopDialog �_�C�A���O

class CAddLoopDialog : public CDialog
{
	DECLARE_DYNAMIC(CAddLoopDialog)

	class LoopIndexManager *m_pLM;

public:
	CAddLoopDialog(class LoopIndexManager *pLM, UINT nStrTitleID,
		CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CAddLoopDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ADD_LOOP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	UINT m_nStrTitleID;
	CString m_strVariable;
	CEdit m_edVariable;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
