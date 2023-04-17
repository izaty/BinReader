// AddDataDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "Br.h"
#include "AddDataDialog.h"
#include "Variable.h"
#include "LoopIndexManager.h"


// CAddDataDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CAddDataDialog, CDialog)

CAddDataDialog::CAddDataDialog(UINT nStrTitleID, Tree *pTree,
							   CWnd* pParent /*=NULL*/)
	: CDialog(CAddDataDialog::IDD, pParent)
	, m_nStrTitleID(nStrTitleID)
	, m_pTree(pTree)
	, m_nType(0)
	, m_strVariable(_T(""))
{

}

CAddDataDialog::~CAddDataDialog()
{
}

void CAddDataDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_TYPE, m_nType);
	DDX_Text(pDX, IDC_VARIABLE, m_strVariable);
	DDX_Control(pDX, IDC_VARIABLE, m_edVariable);
	DDX_Control(pDX, IDC_TYPE, m_cbType);
}


BEGIN_MESSAGE_MAP(CAddDataDialog, CDialog)
END_MESSAGE_MAP()


// CAddDataDialog ���b�Z�[�W �n���h��

BOOL CAddDataDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �����ɏ�������ǉ����Ă�������

	// Set dialog title
	CString strTitle;
	strTitle.LoadString(m_nStrTitleID);
	SetWindowText(strTitle);

	// Add data types
	for (volatile int i = 0; i < DataType::TypeCount; i++) {
		DataType::Type nType = DataType::GetType(i);
		m_cbType.InsertString(i, DataType::GetTypeString(nType));
	}
	m_cbType.SetCurSel(m_nType);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CAddDataDialog::OnOK()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CString strVariable;
	m_edVariable.GetWindowText(strVariable);

	// Check Variable Name
	try {
		Variable::CheckDataName(strVariable);
		if (LoopIndexManager::IsPossibleVariableString(strVariable)) {
			AfxMessageBox(IDS_ERR_VAR_RESERVED);
			return;
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

	// Check Duplicated Variable
	if (strVariable != m_strVariable) {		// Differnt variable specified
		if (m_pTree->VariableExists(strVariable)) {
			AfxMessageBox(IDS_ERR_DUP_VAR);
			return;
		}
	}

	CDialog::OnOK();
}
