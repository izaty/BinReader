// MainFrm.h : CMainFrame クラスのインターフェイス
//


#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // シリアル化からのみ作成します。
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 属性
protected:
	CSplitterWnd m_wndSplitter;
public:
	class CBrView *GetTreeView();
	class CBrEditView *GetEditView();


// 操作
public:

// オーバーライド
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);

// 実装
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // コントロール バー用メンバ
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CImageList	m_imgToolBar;

// 生成された、メッセージ割り当て関数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSaveSrc();
	afx_msg void OnSrcOptions();
	afx_msg void OnUpdateSaveSrc(CCmdUI *pCmdUI);
};


