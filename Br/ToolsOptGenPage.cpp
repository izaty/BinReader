// ToolsOptGenPage.cpp : 実装ファイル
//

#include "stdafx.h"
#include "Br.h"
#include "ToolsOptGenPage.h"


// CToolsOptGenPage ダイアログ

IMPLEMENT_DYNAMIC(CToolsOptGenPage, CPropertyPage)

CToolsOptGenPage::CToolsOptGenPage()
	: CPropertyPage(CToolsOptGenPage::IDD)
{

}

CToolsOptGenPage::~CToolsOptGenPage()
{
}

void CToolsOptGenPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolsOptGenPage, CPropertyPage)
END_MESSAGE_MAP()


// CToolsOptGenPage メッセージ ハンドラ

BOOL CToolsOptGenPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ここに初期化を追加してください

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
