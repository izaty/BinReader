// MainFrm.cpp : CMainFrame クラスの実装
//

#include "stdafx.h"
#include "Br.h"

#include "MainFrm.h"
#include "BrDoc.h"
#include "BrView.h"
#include "BrEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_SAVE_SRC, &CMainFrame::OnSaveSrc)
	ON_COMMAND(ID_SRC_OPTIONS, &CMainFrame::OnSrcOptions)
	ON_UPDATE_COMMAND_UI(ID_SAVE_SRC, &CMainFrame::OnUpdateSaveSrc)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ステータス ライン インジケータ
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame コンストラクション/デストラクション

CMainFrame::CMainFrame()
{
	// TODO: メンバ初期化コードをここに追加してください。
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("ツール バーの作成に失敗しました。\n");
		return -1;      // 作成できませんでした。
	}

	// 256色のツールバー対応
	// start
	CImageList *pImgList = m_wndToolBar.GetToolBarCtrl().GetImageList();
	pImgList->DeleteImageList();
	//CImageList *pImgList = &m_imgToolBar;
	CBitmap bitmapToolbar;
	bitmapToolbar.LoadBitmap(IDR_MAINFRAME);
	pImgList->Create(24, 24, ILC_COLOR32 | ILC_MASK, 15, 15);
	pImgList->Add(&bitmapToolbar, RGB(192,192,192));
	m_wndToolBar.GetToolBarCtrl().SetImageList(pImgList);
	// end

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("ステータス バーの作成に失敗しました。\n");
		return -1;      // 作成できませんでした。
	}

	// TODO: ツール バーをドッキング可能にしない場合は、これらの 3 行を削除してください。
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	/*
	m_wndToolBar.SetButtonText(0, "新規作成");
	CRect rcButton;
	m_wndToolBar.GetItemRect(0, rcButton);
	m_wndToolBar.SetSizes(CSize(rcButton.Width(), rcButton.Height()), CSize(24, 13));
	ShowControlBar(&m_wndToolBar, TRUE, FALSE);
	*/
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
//	BOOL bRet = 
//		m_wndSplitter.Create(this,
//		1, 2,               // TODO: 行と列の数を調整してください。
//		CSize(10, 10),      // TODO: 最小ペインのサイズを変更します。
//		pContext);
	BOOL bRet = m_wndSplitter.CreateStatic(this, 1, 2);

	if (bRet) {
		if (bRet = m_wndSplitter.CreateView(0, 0,
			RUNTIME_CLASS(CBrView), CSize(400, 400), pContext)) {
		}
		if (bRet) {
			if (bRet = m_wndSplitter.CreateView(0, 1,
				RUNTIME_CLASS(CBrEditView), CSize(400, 400), pContext)) {
			}
		}
	}

	return bRet;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return TRUE;
}


// CMainFrame 診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame メッセージ ハンドラ
CBrView *CMainFrame::GetTreeView()
{
	return (CBrView *)m_wndSplitter.GetPane(0, 0);
}

CBrEditView *CMainFrame::GetEditView()
{
	return (CBrEditView *)m_wndSplitter.GetPane(0, 1);
}

void CMainFrame::OnSaveSrc()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	CFileDialog dlg(FALSE, "*.*");
	dlg.m_ofn.lpstrFilter = "All Files (*.*)\0*.*\0\0";

	if (dlg.DoModal() == IDOK) {
		CString strBuf;
		GetEditView()->GetEditCtrl().GetWindowText(strBuf);
		strBuf.Remove(_T('\r'));
		TRY {
			CStdioFile sf(dlg.GetPathName(), CFile::modeWrite | CFile::modeCreate);
			sf.WriteString(strBuf);
		}
		CATCH (CFileException, e) {
			AfxMessageBox(IDS_ERR_OUT_SRC);
		}
		END_CATCH
	}
}

void CMainFrame::OnSrcOptions()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	GetTreeView()->DoSrcOptions();
}

void CMainFrame::OnUpdateSaveSrc(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	CBrApp *pApp = (CBrApp *)AfxGetApp();
	pCmdUI->Enable(!pApp->IsTrial());
}

//
// HTMLヘルプ
//
#include <htmlhelp.h>
void CMainFrame::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	// 最初に CWin::WinHelp 関数内の必要な処理をコピーしました。

	CWinApp* pApp = AfxGetApp();
	ASSERT_VALID(pApp);
	ASSERT(pApp->m_pszHelpFilePath != NULL);

	CWaitCursor wait;
	if (IsFrameWnd())
	{
		// CFrameWnd windows should be allowed to exit help mode first
		CFrameWnd* pFrameWnd = (CFrameWnd*)this;
		pFrameWnd->ExitHelpMode();
	}

	// cancel any tracking modes
	SendMessage(WM_CANCELMODE);
	SendMessageToDescendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);

	// need to use top level parent (for the case where m_hWnd is in DLL)
	CWnd* pWnd = GetTopLevelParent();
	pWnd->SendMessage(WM_CANCELMODE);
	pWnd->SendMessageToDescendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);

	// attempt to cancel capture
	HWND hWndCapture = ::GetCapture();
	if (hWndCapture != NULL)
		::SendMessage(hWndCapture, WM_CANCELMODE, 0, 0);


	// ここから HTML ヘルプ用に書き足したものです。

	// HTML Help ファイルの存在をチェック
	CString hp = pApp->m_pszHelpFilePath;
	CFileStatus st;
	if ( !CFile::GetStatus(hp,st) )
	{
		CString str;
		str.Format( "Not Exist Html Help File\n\n   File Path [ %s ]", hp );
		AfxMessageBox(str);
		return;
	}

	// ヘルプを表示
	switch( nCmd )
	{
	case HELP_INDEX:// ヘルプの目次
		::HtmlHelp(m_hWnd, hp, HH_DISPLAY_TOC, NULL);
		break;
	case HELP_HELPONHELP:// ヘルプの検索
		{
			HH_FTS_QUERY q ;
			q.cbStruct = sizeof (HH_FTS_QUERY);
			q.fUniCodeStrings = FALSE;
			q.pszSearchQuery = "";
			q.iProximity = 0;
			q.fStemmedSearch = FALSE;
			q.fTitleOnly = FALSE; 
			q.fExecute = FALSE;
			q.pszWindow = "";   
			::HtmlHelp(m_hWnd, hp, HH_DISPLAY_SEARCH, (DWORD)&q);
		}
		break;
	case HELP_FINDER:// キーワードで検索
		::HtmlHelp(m_hWnd, hp, HH_DISPLAY_INDEX , NULL);
		break;
	case HELP_CONTEXT:// コンテキストヘルプ (F1/Shift+F1/HelpButton/?Button)
		{
			// すぐにカーソル位置のウィンドウを取得しないとカーソルが動いちゃう。
			POINT   point;
			GetCursorPos(&point);
			CWnd*pCallWnd = WindowFromPoint( point );

			// ヘルプコンテキストID dwData を別の ID に変更したい場合などは
			// ここに式を書きます。dwData は既に加算された値なので注意。
		
			// 例 ID_EDIT_REDO の場合 ID_EDIT_UNDO にする（つまり同じページ表示)
			// if ( dwData == ID_EDIT_REDO | 0x10000 ) dwData = ID_EDIT_UNDO | 0x10000;
			
			// 状況依存型のヘルプだと、ヘルプ作成時にVCのリソースに対応した
			// 各HTMLファイルを関連付けてある必要があります。しかし、ツール
			// バーのボタン１つ１つに１ページの html ファイルを関連付けるの
			// ではなく、１つのツールバーで１ページ分を関連付けたい時などが
			// あります。ダイアログバーなどでも、コントロールやボタンのの１
			// つ１つに １ページを割り当てるのではなく、ダイアログバー自体で
			// １つのページを表示させたい場合などがあります。

			// そこで、ここでは、まず最初に dwDataのコンテキストIDのページが
			// あれば表示し、無ければ、親ウィンドウのIDから作成したコンテキス
			// トID なければさらに親ウィンドウのID・・・。とトライしてみて、
			// 結局何も無い場合は、エラーメッセージを表示するような、仕様で
			// 書いてみました。各自好みに合わせて書き換えて使用してください。

			// HTML Help を表示
			HWND hWnd = NULL;
			DWORD dwID = dwData;
			while( dwID>0 && (hWnd=::HtmlHelp(m_hWnd,hp,HH_HELP_CONTEXT,dwID))==NULL && pCallWnd )
			{
				pCallWnd = pCallWnd->GetParent();
				dwID = (pCallWnd)? (pCallWnd->GetDlgCtrlID()|0x50000):0;
			}
			
			// この方法だと、メニュー項目のコンテキストIDのヘルプが無い場合に
			// その下のウィンドウのコンテキストがあるとそれを表示してしまうと
			// いう難点がある。しかし、メニュー項目のコンテキストIDのヘルプを
			// ちゃんと用意しておけば問題も起きない。

			// エラーチェック
			if ( hWnd == NULL )
			{
				CString str;
				DWORD dwIdOrg = 0x0000ffff & dwData, dwIdAdd = 0xffff0000 & dwData;
				str.Format( "Error Context ID\n\n   File Path [ %s ]\n  ContextID [0x%x + 0x%04x(%d)]", hp , dwIdAdd, dwIdOrg, dwIdOrg );
				AfxMessageBox(str);
			}
		}
		break;
	}
}