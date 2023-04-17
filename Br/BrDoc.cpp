// BrDoc.cpp : CBrDoc クラスの実装
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


// CBrDoc コンストラクション/デストラクション

CBrDoc::CBrDoc()
{
	// TODO: この位置に 1 度だけ呼ばれる構築用のコードを追加してください。

}

CBrDoc::~CBrDoc()
{
}

BOOL CBrDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}




// CBrDoc シリアル化

void CBrDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 格納するコードをここに追加してください。
//		CString strPath = ar.GetFile()->GetFilePath();
		//ar.Close();
//		FileStream fs(strPath, _T("w"));
//		m_T.Save(&fs);
	}
	else
	{
		// TODO: 読み込むコードをここに追加してください。
		CString strPath = ar.GetFile()->GetFilePath();
		FileStream fs(strPath, _T("r"));
		m_T.Load(&fs);
	}
}


// CBrDoc 診断

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


// CBrDoc コマンド

void CBrDoc::DeleteContents()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	m_U.ClearList();
	m_T.DeleteAllNodes();

	CDocument::DeleteContents();
}

BOOL CBrDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	FileStream fs(lpszPathName, _T("w"));
	m_T.Save(&fs);
	SetModifiedFlag(FALSE);
	return TRUE;

//	return CDocument::OnSaveDocument(lpszPathName);
}

BOOL CBrDoc::SaveModified()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
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
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	CBrApp *pApp = (CBrApp *)AfxGetApp();
	pCmdUI->Enable(!pApp->IsTrial());
}

void CBrDoc::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	CBrApp *pApp = (CBrApp *)AfxGetApp();
	pCmdUI->Enable(!pApp->IsTrial());
}
