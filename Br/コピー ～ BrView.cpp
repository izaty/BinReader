// BrView.cpp : CBrView クラスの実装
//

#include "stdafx.h"
#include <strstream>
#include "Br.h"

#include "BrDoc.h"
#include "BrView.h"
#include "BrEditView.h"

#include "CodeWriterForC.h"
#include "CodeWriterForCplus.h"
#include "TypeDef.h"
#include "LoopDef.h"

#include "MainFrm.h"

#include "AddDataDialog.h"
#include "AddLoopDialog.h"

#include "TreeManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBrView

IMPLEMENT_DYNCREATE(CBrView, CTreeViewEx)

BEGIN_MESSAGE_MAP(CBrView, CTreeViewEx)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MOV_DOWN,  &CBrView::OnMovDown)
	ON_COMMAND(ID_MOV_UP,    &CBrView::OnMovUp)
	ON_COMMAND(ID_MOV_LEFT,  &CBrView::OnMovLeft)
	ON_COMMAND(ID_MOV_RIGHT, &CBrView::OnMovRight)
	ON_COMMAND(ID_DEL_NODE, &CBrView::OnDelNode)
	ON_COMMAND(ID_ADD_DATA, &CBrView::OnAddData)
	ON_COMMAND(ID_ADD_LOOP, &CBrView::OnAddLoop)
	ON_COMMAND(ID_EDIT_PROP, &CBrView::OnEditProp)
END_MESSAGE_MAP()

// CBrView コンストラクション/デストラクション

CBrView::CBrView()
{
	// TODO: 構築コードをここに追加します。
	BOOL bFlag = m_imageList.Create(16, 16, ILC_COLOR4 | ILC_MASK, 2, 1);
	if (bFlag) {
		CWinApp *pApp = AfxGetApp();
		m_imageList.Add(pApp->LoadIcon(IDI_SQUARE));
		m_imageList.Add(pApp->LoadIcon(IDI_LOOP));
	}
	m_pCodeWriter = NULL;
	m_pTM = NULL;
}

CBrView::~CBrView()
{
	if (m_pCodeWriter != NULL) {
		delete m_pCodeWriter;
	}
	if (m_pTM != NULL) {
		delete m_pTM;
	}
}

BOOL CBrView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CTreeViewEx::PreCreateWindow(cs);
}

void CBrView::OnInitialUpdate()
{
	CTreeViewEx::OnInitialUpdate();

	GetTreeCtrl().SetImageList(&m_imageList, LVSIL_NORMAL);
}


// CBrView 診断

#ifdef _DEBUG
void CBrView::AssertValid() const
{
	CTreeViewEx::AssertValid();
}

void CBrView::Dump(CDumpContext& dc) const
{
	CTreeViewEx::Dump(dc);
}

CBrDoc* CBrView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBrDoc)));
	return (CBrDoc*)m_pDocument;
}
#endif //_DEBUG


// CBrView メッセージ ハンドラ

void CBrView::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: ここにメッセージ ハンドラ コードを追加します。

}

void CBrView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	CMenu menu;
	menu.LoadMenu(IDR_TREE_CONTEXT);
	CMenu *pmnCont= menu.GetSubMenu(0);

//	pmnCont->EnableMenuItem(ID_A_ADD, MF_BYCOMMAND | MF_GRAYED);
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Tree& T = pDoc->m_tree;

	UINT nP, nU, nD, nL, nR, nDel;
	nP = nU = nD = nL = nR = nDel = MF_GRAYED;

	Tree::Node *pSelect = GetTreeManager()->GetSelectedNode();
	if (pSelect != NULL) {
		nP = MF_ENABLED;
		if (T.CanMoveUp(pSelect)) {
			nU = MF_ENABLED;
		}
		if (T.CanMoveDown(pSelect)) {
			nD = MF_ENABLED;
		}
		if (T.CanMoveLeft(pSelect)) {
			nL = MF_ENABLED;
		}
		if (T.CanMoveRight(pSelect)) {
			nR = MF_ENABLED;
		}
		if (T.CanRemoveNode(pSelect)) {
			nDel = MF_ENABLED;
		}
	}

	pmnCont->EnableMenuItem(ID_EDIT_PROP, MF_BYCOMMAND | nP);
	pmnCont->EnableMenuItem(ID_MOV_UP,    MF_BYCOMMAND | nU);
	pmnCont->EnableMenuItem(ID_MOV_DOWN,  MF_BYCOMMAND | nD);
	pmnCont->EnableMenuItem(ID_MOV_LEFT,  MF_BYCOMMAND | nL);
	pmnCont->EnableMenuItem(ID_MOV_RIGHT, MF_BYCOMMAND | nR);
	pmnCont->EnableMenuItem(ID_DEL_NODE,  MF_BYCOMMAND | nDel);

	ClientToScreen(&point);
	pmnCont->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, this);

	CTreeViewEx::OnRButtonUp(nFlags, point);
}

BOOL CBrView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	dwStyle |= TVS_HASBUTTONS;
	dwStyle |= TVS_HASLINES;

	return CTreeViewEx::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CBrView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	// Document
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// Tree Control/Tree
	CTreeCtrl& tc = GetTreeCtrl();
	Tree& T = pDoc->m_tree;

	TreeManager *pTM = GetTreeManager();

	// Make tree in Tree Control
	T.AssignLevels();
	tc.DeleteAllItems();
	pTM->CreateTree(m_pCodeWriter);
	ExpandAll();
	UpdatePreview();
}

void CBrView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	HTREEITEM hItem = GetTreeCtrl().HitTest(point);
	GetTreeManager()->SelectItem(hItem);
}

// Move Up
void CBrView::OnMovUp()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	TreeManager *pTM = GetTreeManager();
	Tree::Node *pItem  = pTM->GetSelectedNode();
	if (pItem != NULL) {
		pTM->DoMoveUp(pItem, m_pCodeWriter);
		pTM->SelectNode(pItem);
		UpdatePreview();
	}
}

// Move Down
void CBrView::OnMovDown()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	TreeManager *pTM = GetTreeManager();
	Tree::Node *pItem  = pTM->GetSelectedNode();
	if (pItem != NULL) {
		pTM->DoMoveDown(pItem, m_pCodeWriter);
		pTM->SelectNode(pItem);
		UpdatePreview();
	}
}

// Move Left
void CBrView::OnMovLeft()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	TreeManager *pTM = GetTreeManager();
	Tree::Node *pItem  = pTM->GetSelectedNode();
	if (pItem != NULL) {
		pTM->DoMoveLeft(pItem, m_pCodeWriter);
		pTM->SelectNode(pItem);
		UpdatePreview();
	}
}

// Move Right
void CBrView::OnMovRight()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	TreeManager *pTM = GetTreeManager();
	Tree::Node *pItem  = pTM->GetSelectedNode();
	if (pItem != NULL) {
		pTM->DoMoveRight(pItem, m_pCodeWriter);
		pTM->SelectNode(pItem);
		UpdatePreview();
	}
}

// Delete
void CBrView::OnDelNode()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	TreeManager *pTM = GetTreeManager();
	Tree::Node *pItem  = pTM->GetSelectedNode();
	if (pItem != NULL) {
		pTM->DoDelete(pItem);
		UpdatePreview();
	}
}


/*
// Update tree view with specified nodes selected and first visible
void CBrView::UpdateTree(Tree::Node *pSelect, Tree::Node *pFirstVisible)
{
	// Document
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// Tree Control/Tree
	CTreeCtrl& tc = GetTreeCtrl();
	Tree& T = pDoc->m_tree;

	TreeManager *pTM = GetTreeManager();

	// Make tree in Tree Control
	T.AssignLevels();
	tc.DeleteAllItems();
	pTM->MakeTree(m_pCodeWriter);
	ExpandAll();
	UpdatePreview();

	// Display code
	CString strBuf;
//	LPTSTR lpszText = strBuf.GetBuffer(10000);
	TCHAR lpszText[30001];
	::ZeroMemory(lpszText, 30001);
	strstream ss(lpszText, 30000, ios::out);
	FileStream fs(&ss);
	// code writer
	if (m_pCodeWriter != NULL) {
		delete m_pCodeWriter;
	}
	m_pCodeWriter = new CodeWriterForC(&fs);
	T.Write(m_pCodeWriter);

//	strBuf.ReleaseBuffer(10000);
	strBuf = lpszText;
	((CMainFrame *)AfxGetApp()->m_pMainWnd)->GetEditView()->GetEditCtrl().SetWindowText(strBuf);
}
*/


void CBrView::OnAddData()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	Tree::Node *pSelect = GetTreeManager()->GetSelectedNode();
	if (pSelect == NULL) {
		return;
	}

	CAddDataDialog dlg(IDS_ADD_DATA);
	if (dlg.DoModal() == IDOK) {
		CBrDoc *pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		Tree& T = pDoc->m_tree;
		TypeDef *pNew = 
			new TypeDef((TypeDef::DataType)dlg.m_nType, dlg.m_strVariable);
		if (pSelect->m_nNodeType == Common::NT_INNER) {
			T.InsertNode(pNew, pSelect);			
		}
		else {
			Tree::Node *pParent = pSelect->m_pP;
			T.InsertNode(pNew, pParent, pSelect);
		}
		UpdateAll();
	}
}

void CBrView::OnAddLoop()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	Tree::Node *pSelect = GetTreeManager()->GetSelectedNode();
	if (pSelect == NULL) {
		return;
	}

	CAddLoopDialog dlg(IDS_ADD_LOOP);
	if (dlg.DoModal() == IDOK) {
		CBrDoc *pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		Tree& T = pDoc->m_tree;
		LoopDef *pNew = 
			new LoopDef(dlg.m_strVariable);
		if (pSelect->m_nNodeType == Common::NT_INNER) {
			T.InsertNode(pNew, pSelect);
		}
		else {
			Tree::Node *pParent = pSelect->m_pP;
			T.InsertNode(pNew, pParent, pSelect);
		}
		UpdateAll();
	}
}

void CBrView::OnEditProp()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	Tree::Node *pSelect = GetTreeManager()->GetSelectedNode();
	if (pSelect == NULL) {
		return;
	}

	if (pSelect->m_nNodeType == Common::NT_INNER) {
		CAddLoopDialog dlg(IDS_MOD_LOOP);
		dlg.m_strVariable = pSelect->GetVariable();
		if (dlg.DoModal() == IDOK) {
			pSelect->SetVariable(dlg.m_strVariable);
			UpdateAll();
		}
	}
	else {
		TypeDef *pProp = (TypeDef *)pSelect;
		CAddDataDialog dlg(IDS_MOD_DATA);
		dlg.m_nType = (int)pProp->GetDataType();
		dlg.m_strVariable = pProp->GetVariable();
		if (dlg.DoModal() == IDOK) {
			pProp->SetDataType((TypeDef::DataType)dlg.m_nType);
			pProp->SetVariable(dlg.m_strVariable);
			UpdateAll();
		}
	}
}

TreeManager *CBrView::GetTreeManager()
{
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CTreeCtrl& tc = GetTreeCtrl();
	
	if (m_pTM != NULL) {
		delete m_pTM;
	}

	m_pTM = new TreeManager(&pDoc->m_tree, &tc);

	return m_pTM;
}

void CBrView::UpdateAll()
{
	UpdateTree();
	UpdatePreview();
}

void CBrView::UpdateTree()
{
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	TreeManager *pTM = GetTreeManager();

	pDoc->m_tree.AssignLevels();
	pTM->CreateTree(m_pCodeWriter);
	ExpandAll();
	HTREEITEM hRoot = pTM->GetRootItem();
	pTM->SelectItem(hRoot);
}

void CBrView::UpdatePreview()
{
	// Tree
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Tree& T = pDoc->m_tree;

	int nSize = T.GetNodeCount();
	if (nSize > 0) {
		// string
		nSize *= 150;
		TCHAR *lpszText = new TCHAR[nSize];
		::ZeroMemory(lpszText, nSize);
		// stream
		strstream ss(lpszText, nSize, ios::out);
		FileStream fs(&ss);
		// code writer
		if (m_pCodeWriter != NULL) {
			delete m_pCodeWriter;
		}
		m_pCodeWriter = new CodeWriterForC(&fs);
		// write
		T.Write(m_pCodeWriter);
		// preview
		CString strBuf(lpszText);
		CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
		pFrame->GetEditView()->GetEditCtrl().SetWindowText(strBuf);
		// free string
		delete [] lpszText;
	}
}