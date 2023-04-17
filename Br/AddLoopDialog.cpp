// AddLoopDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "Br.h"
#include "BrDoc.h"
#include "BrView.h"
#include "AddLoopDialog.h"
#include "Variable.h"
#include "BracketPos.h"
#include "LoopIndexManager.h"


// CAddLoopDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CAddLoopDialog, CDialog)

CAddLoopDialog::CAddLoopDialog(LoopIndexManager *pLM,
							   UINT nStrTitleID,
							   CWnd* pParent /*=NULL*/)
	: CDialog(CAddLoopDialog::IDD, pParent)
	, m_nStrTitleID(nStrTitleID)
	, m_strVariable(_T(""))
{
	m_pLM = pLM;
}

CAddLoopDialog::~CAddLoopDialog()
{
}

void CAddLoopDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VARIABLE, m_strVariable);
	DDX_Control(pDX, IDC_VARIABLE, m_edVariable);
}


BEGIN_MESSAGE_MAP(CAddLoopDialog, CDialog)
END_MESSAGE_MAP()


// CAddLoopDialog ���b�Z�[�W �n���h��

BOOL CAddLoopDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �����ɏ�������ǉ����Ă�������
	CString strTitle;
	strTitle.LoadString(m_nStrTitleID);
	SetWindowText(strTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CAddLoopDialog::OnOK()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CString strVariable;
	m_edVariable.GetWindowText(strVariable);

	// Check Variable Name
	try {
		BracketPos *pBp = NULL;
		Variable::CheckLoopName(strVariable, &pBp);

		if (pBp != NULL) {
			BracketPos::Var *p = pBp->m_var.next;
			while (p) {
				int nLevel = m_pLM->GetVariableLevel(p->lpsz);
				if (nLevel >= 0) {
//					if (p->level > 0) {
//						delete pBp;
//						throw Variable::ErrInvalidChar;
//					}
					CString strM(m_pLM->GetVariableString(nLevel));
					CString strF = strVariable.Left(p->start);
					CString strE = strVariable.Mid(p->start + p->length);
					strVariable = strF + strM + strE;
//AfxMessageBox(strVariable);
				}
				p = p->next;
			}
			delete pBp;
			m_edVariable.SetWindowText(strVariable);
		}
	}
	catch (Variable::ErrorCode e) {
		if (e == Variable::ErrEmpty) {
			AfxMessageBox(IDS_ERR_VAR_EMPTY);
		}
		else if (e == Variable::ErrTooLong) {
			AfxMessageBox(IDS_ERR_VAR_SIZE);
		}
		else {
			AfxMessageBox(IDS_ERR_INVALID_VAR);
		}
		return;
	}

//	if (!UpdateData(TRUE)) {
//		return;
//	}
//	EndDialog(IDOK);
	CDialog::OnOK();
}
