#pragma once


// CBrEditView ビュー

class CBrEditView : public CEditView
{
	DECLARE_DYNCREATE(CBrEditView)

protected:
	CBrEditView();           // 動的生成で使用される protected コンストラクタ
	virtual ~CBrEditView();

	CFont m_font;
	void SetLogFont(LOGFONT& lf);
	void GetLogFont(LOGFONT& lf);

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	virtual void OnInitialUpdate();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnUpdateEditSelectAll(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
	afx_msg void OnEditFont();
};


