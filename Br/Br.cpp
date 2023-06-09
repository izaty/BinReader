// Br.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "Br.h"
#include "MainFrm.h"

#include "BrDoc.h"
#include "BrView.h"

#include "SetLicenseDialog.h"

#include "TrialMessageDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBrApp

BEGIN_MESSAGE_MAP(CBrApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CBrApp::OnAppAbout)
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
	ON_COMMAND(ID_DEFAULT_HELP, &CWinApp::OnHelpIndex)
	ON_COMMAND(ID_HELP_INDEX, &CWinApp::OnHelpIndex)
	ON_COMMAND(ID_HELP_USING, &CWinApp::OnHelpUsing)
	ON_COMMAND(ID_HELP_FINDER, &CWinApp::OnHelpFinder)
	ON_COMMAND(ID_SET_LICENSE, &CBrApp::OnSetLicense)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CBrApp::OnUpdateFileOpen)
END_MESSAGE_MAP()


// CBrApp コンストラクション

CBrApp::CBrApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。

}


// 唯一の CBrApp オブジェクトです。

CBrApp theApp;


// CBrApp 初期化

BOOL CBrApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// 標準初期化

	// ヘルプファイルの拡張子を変更 (hlp -> chm)
	CString strHelpPath = m_pszHelpFilePath;
	free((void*)m_pszHelpFilePath);
	int len = strHelpPath.GetLength();
	strHelpPath.SetAt(len-3, 'c');
	strHelpPath.SetAt(len-2, 'h');
	strHelpPath.SetAt(len-1, 'm');
	m_pszHelpFilePath = _tcsdup(strHelpPath);

	if (IsTrial()) {
		CString strMsg; strMsg.LoadString(IDS_TRIAL_MESSAGE);
		CString strTtl; strTtl.LoadString(IDS_TRIAL_VERSION);
		::MessageBox(NULL, strMsg, strTtl, MB_OK);
		//AfxMessageBox(IDS_TRIAL_MESSAGE, MB_ICONINFORMATION | MB_OK);
		OnSetLicense();
	}
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));
	LoadStdProfileSettings(8);  // 標準の INI ファイルのオプションをロードします (MRU を含む)
	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBrDoc),
		RUNTIME_CLASS(CMainFrame),       // メイン SDI フレーム ウィンドウ
		RUNTIME_CLASS(CBrView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// DDE Execute open を使用可能にします。
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// DDE、file open など標準のシェル コマンドのコマンド ラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// コマンド ラインで指定されたディスパッチ コマンドです。アプリケーションが
	// /RegServer、/Register、/Unregserver または /Unregister で起動された場合、False を返します。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 接尾辞が存在する場合にのみ DragAcceptFiles を呼び出してください。
	//  SDI アプリケーションでは、ProcessShellCommand の直後にこの呼び出しが発生しなければなりません。
	// ドラッグ/ドロップ オープンを許可します。
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// ダイアログを実行するためのアプリケーション コマンド
void CBrApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CBrApp メッセージ ハンドラ


BOOL CBrApp::IsTrial(void) const
{
	return m_lm.IsTrial();
}

void CBrApp::OnSetLicense()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	CSetLicenseDialog dlg(&m_lm);
	dlg.DoModal();
}

void CBrApp::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	pCmdUI->Enable(!IsTrial());
}