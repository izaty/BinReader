#pragma once


// CToolsOptGenPage �_�C�A���O

class CToolsOptGenPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CToolsOptGenPage)

public:
	CToolsOptGenPage();
	virtual ~CToolsOptGenPage();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_TOOLS_OPT_GEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
