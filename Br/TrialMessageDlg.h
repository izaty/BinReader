#pragma once


// CTrialMessageDlg �_�C�A���O

class CTrialMessageDlg : public CDialog
{
	DECLARE_DYNAMIC(CTrialMessageDlg)

public:
	CTrialMessageDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CTrialMessageDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_TRIAL_MESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
