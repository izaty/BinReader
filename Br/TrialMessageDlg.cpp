// TrialMessageDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "Br.h"
#include "TrialMessageDlg.h"


// CTrialMessageDlg �_�C�A���O

IMPLEMENT_DYNAMIC(CTrialMessageDlg, CDialog)

CTrialMessageDlg::CTrialMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrialMessageDlg::IDD, pParent)
{

}

CTrialMessageDlg::~CTrialMessageDlg()
{
}

void CTrialMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTrialMessageDlg, CDialog)
END_MESSAGE_MAP()


// CTrialMessageDlg ���b�Z�[�W �n���h��

BOOL CTrialMessageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �����ɏ�������ǉ����Ă�������
	CString strText;
	strText.LoadString(IDS_TRIAL_MESSAGE);
	AfxMessageBox(strText);
	GetDlgItem(IDC_MESSAGE)->SetWindowText(strText);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}
