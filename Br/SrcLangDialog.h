#pragma once


// CSrcLangDialog �_�C�A���O

class CSrcLangDialog : public CDialog
{
	DECLARE_DYNAMIC(CSrcLangDialog)

public:
	CSrcLangDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CSrcLangDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SRC_LANG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()

public:
	int m_nLang;
	BOOL m_bNodisp;
};
