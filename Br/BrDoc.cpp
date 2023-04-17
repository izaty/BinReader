// BrDoc.cpp : CBrDoc �N���X�̎���
//

#include "stdafx.h"
#include "Br.h"

#include "BrDoc.h"

#include "FileStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBrDoc

IMPLEMENT_DYNCREATE(CBrDoc, CDocument)

BEGIN_MESSAGE_MAP(CBrDoc, CDocument)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CBrDoc::OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CBrDoc::OnUpdateFileSaveAs)
END_MESSAGE_MAP()


// CBrDoc �R���X�g���N�V����/�f�X�g���N�V����

CBrDoc::CBrDoc()
{
	// TODO: ���̈ʒu�� 1 �x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CBrDoc::~CBrDoc()
{
}

BOOL CBrDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}




// CBrDoc �V���A����

void CBrDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �i�[����R�[�h�������ɒǉ����Ă��������B
//		CString strPath = ar.GetFile()->GetFilePath();
		//ar.Close();
//		FileStream fs(strPath, _T("w"));
//		m_T.Save(&fs);
	}
	else
	{
		// TODO: �ǂݍ��ރR�[�h�������ɒǉ����Ă��������B
		CString strPath = ar.GetFile()->GetFilePath();
		FileStream fs(strPath, _T("r"));
		m_T.Load(&fs);
	}
}


// CBrDoc �f�f

#ifdef _DEBUG
void CBrDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBrDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBrDoc �R�}���h

void CBrDoc::DeleteContents()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	m_U.ClearList();
	m_T.DeleteAllNodes();

	CDocument::DeleteContents();
}

BOOL CBrDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	FileStream fs(lpszPathName, _T("w"));
	m_T.Save(&fs);
	SetModifiedFlag(FALSE);
	return TRUE;

//	return CDocument::OnSaveDocument(lpszPathName);
}

BOOL CBrDoc::SaveModified()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	if (IsModified()) {
		int nID = AfxMessageBox(IDS_QST_SAVE_MOD, MB_YESNOCANCEL);
		if (nID == IDCANCEL) {
			return FALSE;
		}
		else if (nID == IDYES) {
			if (!DoSave(m_strPathName)) {
				return FALSE;
			}
		}
		else if (nID == IDNO) {
//			SetModifiedFlag(FALSE);
		}
	}
	return TRUE;
}

void CBrDoc::OnUpdateFileSave(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h�� �R�[�h��ǉ����܂��B
	CBrApp *pApp = (CBrApp *)AfxGetApp();
	pCmdUI->Enable(!pApp->IsTrial());
}

void CBrDoc::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h�� �R�[�h��ǉ����܂��B
	CBrApp *pApp = (CBrApp *)AfxGetApp();
	pCmdUI->Enable(!pApp->IsTrial());
}
