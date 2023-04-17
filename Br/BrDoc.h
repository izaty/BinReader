// BrDoc.h : CBrDoc クラスのインターフェイス
//


#pragma once

#include "Tree.h"
#include "UndoList.h"

class CBrDoc : public CDocument
{
protected: // シリアル化からのみ作成します。
	CBrDoc();
	DECLARE_DYNCREATE(CBrDoc)

// 属性
public:
	Tree m_T;
	UndoList m_U;

// 操作

// オーバーライド
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 実装
public:
	virtual ~CBrDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
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


