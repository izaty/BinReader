// BrDoc.h : CBrDoc �N���X�̃C���^�[�t�F�C�X
//


#pragma once

#include "Tree.h"
#include "UndoList.h"

class CBrDoc : public CDocument
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CBrDoc();
	DECLARE_DYNCREATE(CBrDoc)

// ����
public:
	Tree m_T;
	UndoList m_U;

// ����

// �I�[�o�[���C�h
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ����
public:
	virtual ~CBrDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DeleteContents();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
protected:
	virtual BOOL SaveModified();
public:
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI *pCmdUI);
};


