// BrEditView.cpp : 実装ファイル
//

#include "stdafx.h"
#include "Br.h"
#include "BrEditView.h"
#include "RegManager.h"


// CBrEditView

IMPLEMENT_DYNCREATE(CBrEditView, CEditView)

CBrEditView::CBrEditView()
{

}

CBrEditView::~CBrEditView()
{
}

BEGIN_MESSAGE_MAP(CBrEditView, CEditView)
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, &CBrEditView::OnUpdateEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CBrEditView::OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_FONT, &CBrEditView::OnEditFont)
END_MESSAGE_MAP()


// CBrEditView 診断

#ifdef _DEBUG
void CBrEditView::AssertValid() const
{
	CEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CBrEditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBrEditView メッセージ ハンドラ

void CBrEditView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
}

static BOOL bInitUpdateDone = FALSE;

void CBrEditView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	if (!bInitUpdateDone) {
		LOGFONT logfont;
		GetLogFont(logfont);
		m_font.CreateFontIndirect(&logfont);
		SetFont(&m_font);
		bInitUpdateDone = TRUE;
	}
}

BOOL CBrEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	cs.style |= ES_READONLY | ES_MULTILINE | WS_VSCROLL;

	return CEditView::PreCreateWindow(cs);
}

void CBrEditView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加します。
	CBrApp *pApp = (CBrApp *)AfxGetApp();
//	if (pApp->IsTrial()) {
//		return;
//	}

	CMenu menu;
	menu.LoadMenu(IDR_EDIT_CONTEXT);
	
	CMenu* pPopup = menu.GetSubMenu(0);
	if (point.x < 0 || point.y < 0) {
		CRect rc; GetWindowRect(&rc);
		point = rc.TopLeft();
	}
	ASSERT(pPopup != NULL);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
}

void CBrEditView::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	CBrApp *pApp = (CBrApp *)AfxGetApp();
	pCmdUI->Enable(!pApp->IsTrial());
}

void CBrEditView::OnUpdateEditSelectAll(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	CBrApp *pApp = (CBrApp *)AfxGetApp();
	pCmdUI->Enable(!pApp->IsTrial());
}

void CBrEditView::OnEditFont()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	LOGFONT logfont;

	GetLogFont(logfont);
	CFontDialog dlg(&logfont);
	if (dlg.DoModal() == IDOK) {
		m_font.Detach();
		m_font.CreateFontIndirect(&logfont);
		SetLogFont(logfont);
		SetFont(&m_font);
	}
}

void CBrEditView::SetLogFont(LOGFONT& lf)
{
	CRegManager rm;
	rm.WriteProfileDword("", "FontHeight",	lf.lfHeight);
	rm.WriteProfileDword("", "FontWidth",	lf.lfWidth);
	rm.WriteProfileDword("", "FontEscape",	lf.lfEscapement);
	rm.WriteProfileDword("", "FontOrient",	lf.lfOrientation);
	rm.WriteProfileDword("", "FontWeight",	lf.lfWeight);
	rm.WriteProfileDword("", "FontItalic",	lf.lfItalic);
	rm.WriteProfileDword("", "FontUL",		lf.lfUnderline);
	rm.WriteProfileDword("", "FontKO",		lf.lfStrikeOut);
	rm.WriteProfileDword("", "FontCharSet",	lf.lfCharSet);
	rm.WriteProfileDword("", "FontOutPrec",	lf.lfOutPrecision);
	rm.WriteProfileDword("", "FontClipPrec",lf.lfClipPrecision);
	rm.WriteProfileDword("", "FontQuality",	lf.lfQuality);
	rm.WriteProfileString("", "FontFace",	lf.lfFaceName);
}

void CBrEditView::GetLogFont(LOGFONT& lf)
{
	CRegManager rm;
	lf.lfHeight			= (long)rm.GetProfileDword("", "FontHeight",   15);
	lf.lfWidth			= (long)rm.GetProfileDword("", "FontWidth",    0);
	lf.lfEscapement		= (long)rm.GetProfileDword("", "FontEscape",   0);
	lf.lfOrientation	= (long)rm.GetProfileDword("", "FontOrient",   0);
	lf.lfWeight			= (long)rm.GetProfileDword("", "FontWeight",   FW_DONTCARE);
	lf.lfItalic			= (BYTE)rm.GetProfileDword("", "FontItalic",   FALSE);
	lf.lfUnderline		= (BYTE)rm.GetProfileDword("", "FontUL",       FALSE);
	lf.lfStrikeOut		= (BYTE)rm.GetProfileDword("", "FontKO",       FALSE);
	lf.lfCharSet		= (BYTE)rm.GetProfileDword("", "FontCharSet",  DEFAULT_CHARSET);
	lf.lfOutPrecision	= (BYTE)rm.GetProfileDword("", "FontOutPrec",  OUT_DEFAULT_PRECIS);
	lf.lfClipPrecision	= (BYTE)rm.GetProfileDword("", "FontClipPrec", CLIP_DEFAULT_PRECIS);
	lf.lfQuality		= (BYTE)rm.GetProfileDword("", "FontQuality",  DRAFT_QUALITY);
	lf.lfPitchAndFamily	= (BYTE)rm.GetProfileDword("", "FontPitch",    DEFAULT_PITCH);
	lstrcpy(lf.lfFaceName, rm.GetProfileString("", "FontFace", "Courier New"));
}