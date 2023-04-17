// BrView.h : CBrView クラスのインターフェイス
//


#pragma once

#include "TreeViewEx.h"
#include "CodeWriter.h"

#include "TreeManager.h"
#include "LoopIndexManager.h"
#include "DataType.h"


class CBrView : public CTreeViewEx
{
private:
	TreeManager *m_pTM;
	TreeManager *GetTreeManager();

	LoopIndexManager *m_pLM;

	void GetLoopIndexManager(int& nVarType, int& nNumType);
	void SetLoopIndexManager(int nVarType, int nNumType);
	void GetCodeWriter(int& nCodeType,
		int& nIndType, int& nNlType, int& nDriver,
		// Modified on Mar.24,'16
		// start
		int& nEndian, int& nEndType, int& nWrite);
		//int& nEndian, int& nEndType);
		// end
	void SetCodeWriter(int nCodeType,
		int nIndType, int nNlType, int nDriver,
		// Modified on Mar.24,'16
		// start
		int nEndian, int nEndType, int nWrite);
		//int nEndian, int nEndType);
		// end

	void SetModified();

public:
	LoopIndexManager *GetLoopIndexManager() const {return m_pLM;}


protected: // シリアル化からのみ作成します。
	CBrView();
	DECLARE_DYNCREATE(CBrView)

// 属性
public:
	CBrDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 構築後に初めて呼び出されます。

// 実装
public:
	virtual ~CBrView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CImageList m_imageList;
	FileStream *m_pFs;
	CodeWriter *m_pCodeWriter;
	CodeWriter *m_pCodeWriterForC;
	CodeWriter *m_pCodeWriterForCplus;
	CodeWriter *m_pCodeWriterForCSharp;
	CodeWriter *m_pCodeWriterForJava;
	CodeWriter *m_pCodeWriterForPHP;

	DataType::Type m_nType;

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMovDown();
	afx_msg void OnMovUp();
	afx_msg void OnMovLeft();
	afx_msg void OnMovRight();

	afx_msg void OnDelNode();
	afx_msg void OnAddData();
	afx_msg void OnAddLoop();
	afx_msg void OnEditProp();

	void UpdateAll(BOOL bSetVScrollPos = FALSE, Node *pSelect = NULL);
	void UpdateTree(BOOL bSetVScrollPos = FALSE, Node *pSelect = NULL);
	void UpdateLoopIndices();
	void UpdatePreview();
	void DoSrcOptions();
	void DoSrcLang();

	afx_msg void OnUpdateEditProp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMovUp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMovDown(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMovLeft(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMovRight(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDelNode(CCmdUI *pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAddData(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAddLoop(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // BrView.cpp のデバッグ バージョン
inline CBrDoc* CBrView::GetDocument() const
   { return reinterpret_cast<CBrDoc*>(m_pDocument); }
#endif

