// Br.h : Br アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// CBrApp:
// このクラスの実装については、Br.cpp を参照してください。
//

#include "LicManager.h"

class CBrApp : public CWinApp
{
public:
	CBrApp();


// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
protected:
	LicManager m_lm;

public:
	BOOL IsTrial(void) const;
	afx_msg void OnSetLicense();
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
};

extern CBrApp theApp;