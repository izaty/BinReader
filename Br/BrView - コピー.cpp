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
#include "CodeWriterForCSharp.h"
#include "CodeWriterForJava.h"
#include "CodeWriterForPHP.h"
#include "TypeDef.h"
#include "LoopDef.h"

#include "MainFrm.h"

#include "AddDataDialog.h"
#include "AddLoopDialog.h"
#include "SrcOptionsDialog.h"
#include "SrcLangDialog.h"

#include "RegManager.h"

#include "TreeManager.h"
#include "UndoList.h"

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
	ON_UPDATE_COMMAND_UI(ID_EDIT_PROP, &CBrView::OnUpdateEditProp)
	ON_UPDATE_COMMAND_UI(ID_MOV_UP, &CBrView::OnUpdateMovUp)
	ON_UPDATE_COMMAND_UI(ID_MOV_DOWN, &CBrView::OnUpdateMovDown)
	ON_UPDATE_COMMAND_UI(ID_MOV_LEFT, &CBrView::OnUpdateMovLeft)
	ON_UPDATE_COMMAND_UI(ID_MOV_RIGHT, &CBrView::OnUpdateMovRight)
	ON_UPDATE_COMMAND_UI(ID_DEL_NODE, &CBrView::OnUpdateDelNode)
	ON_COMMAND(ID_EDIT_UNDO, &CBrView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CBrView::OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(ID_ADD_DATA, &CBrView::OnUpdateAddData)
	ON_UPDATE_COMMAND_UI(ID_ADD_LOOP, &CBrView::OnUpdateAddLoop)
END_MESSAGE_MAP()

// CBrView コンストラクション/デストラクション

CBrView::CBrView()
{
	// TODO: 構築コードをここに追加します。
	BOOL bFlag = m_imageList.Create(16, 16, ILC_COLOR4 | ILC_MASK, 2, 1);
	if (bFlag) {
		CWinApp *pApp = AfxGetApp();
		m_imageList.Add(pApp->LoadIcon(IDI_DATA));
		m_imageList.Add(pApp->LoadIcon(IDI_LOOP));
		m_imageList.Add(pApp->LoadIcon(IDI_ROOT));
	}

	m_pTM = NULL;
	m_pLM = new LoopIndexManager(LoopIndexManager::Var_i);

	m_pCodeWriterForC		= new CodeWriterForC(NULL, m_pLM);
	m_pCodeWriterForCplus	= new CodeWriterForCplus(NULL, m_pLM);
	m_pCodeWriterForCSharp	= new CodeWriterForCSharp(NULL, m_pLM);
	m_pCodeWriterForJava	= new CodeWriterForJava(NULL, m_pLM);
	m_pCodeWriterForPHP 	= new CodeWriterForPHP(NULL, m_pLM);

	CRegManager rm;
	{
		int nVarType, nNumType;
		GetLoopIndexManager(nVarType, nNumType);
		SetLoopIndexManager(nVarType, nNumType);
	}
	{
		int nCodeWriter, nIndType, nNlType, nDefType, nDriver,
			nEndian, nEndType;
		GetCodeWriter(nCodeWriter, nIndType, nNlType, nDefType, nDriver,
			nEndian, nEndType);
		SetCodeWriter(nCodeWriter, nIndType, nNlType, nDefType, nDriver,
			nEndian, nEndType);
	}

	m_nType = DataType::TypeInt;

	/**/
	int nNoDispSrcLang = (int)rm.GetProfileDword("", "NoDispSrcLang", 0);
	if (!nNoDispSrcLang) {
		DoSrcLang();
	}
	/**/
}

void CBrView::GetLoopIndexManager(int& nVarType, int& nNumType)
{
	CRegManager rm;
	nVarType = (int)rm.GetProfileDword("", "LoopIndexVarType", 0);
	nNumType = (int)rm.GetProfileDword("", "LoopIndexNumType", 0);
}

void CBrView::SetLoopIndexManager(int nVarType, int nNumType)
{
	m_pLM->SetVariableType((LoopIndexManager::VarType)nVarType);
	m_pLM->SetNumericalType((LoopIndexManager::NumType)nNumType);

	CRegManager rm;
	rm.WriteProfileDword("", "LoopIndexVarType", nVarType);
	rm.WriteProfileDword("", "LoopIndexNumType", nNumType);
}

void CBrView::GetCodeWriter(int& nCodeType,
							int& nIndType, int& nNlType, int& nDefType,
							int& nDriver, int& nEndian, int& nEndType)
{
	CRegManager rm;
	nCodeType = (int)rm.GetProfileDword("", "CodeWriter", 3);
	nIndType  = (int)rm.GetProfileDword("", "IndentType", 0);
	nNlType   = (int)rm.GetProfileDword("", "NewLineType", 1);
	nDefType  = (int)rm.GetProfileDword("", "DataDefType", 1);
	nDriver   = (int)rm.GetProfileDword("", "Driver", 0);
	nEndian   = (int)rm.GetProfileDword("", "Endian", 0);
	nEndType  = (int)rm.GetProfileDword("", "EndianType", 0);
}

void CBrView::SetCodeWriter(int nCodeType)
{
	if (nCodeType == 1) {
		m_pCodeWriter = m_pCodeWriterForCplus;	DataType::SetSize(DataType::TypeChar, 1);
	}
	else if (nCodeType == 2) {
		m_pCodeWriter = m_pCodeWriterForCSharp;	DataType::SetSize(DataType::TypeChar, 2);
	}
	else if (nCodeType == 3) {
		m_pCodeWriter = m_pCodeWriterForJava;	DataType::SetSize(DataType::TypeChar, 2);
	}
	else if (nCodeType == 4) {
		m_pCodeWriter = m_pCodeWriterForPHP;	DataType::SetSize(DataType::TypeChar, 1);
	}
	else {
		m_pCodeWriter = m_pCodeWriterForC;		DataType::SetSize(DataType::TypeChar, 1);
	}
	CRegManager rm;
	rm.WriteProfileDword("", "CodeWriter", nCodeType);
}

void CBrView::SetCodeWriter(int nCodeType, int nIndType, int nNlType, int nDefType,
							int nDriver, int nEndian, int nEndType)
{
	SetCodeWriter(nCodeType);

	m_pCodeWriter->SetIndent((CodeWriter::IndentType)nIndType);
	m_pCodeWriter->SetNewLine((CodeWriter::NewLineType)nNlType);
	m_pCodeWriter->MakeVariableLocal(nDefType == 0);

	CBrApp *pApp = (CBrApp *)AfxGetApp();

	if (pApp->IsTrial()) {
		m_pCodeWriter->EnableDriver(FALSE);
	}
	else {
		m_pCodeWriter->EnableDriver(nDriver == 1);
	}

	if (pApp->IsTrial()) {
		m_pCodeWriter->EnableEndianConv(FALSE);
	}
	else {
		m_pCodeWriter->EnableEndianConv(nEndian == 1);
	}
	m_pCodeWriter->SetLittleEndian(nEndType == 1);

	CRegManager rm;
	rm.WriteProfileDword("", "IndentType", nIndType);
	rm.WriteProfileDword("", "NewLineType", nNlType);
	rm.WriteProfileDword("", "DataDefType", nDefType);
	rm.WriteProfileDword("", "Driver", nDriver);
	rm.WriteProfileDword("", "Endian", nEndian);
	rm.WriteProfileDword("", "EndianType", nEndType);
}

CBrView::~CBrView()
{
	if (m_pCodeWriterForC != NULL) {
		delete m_pCodeWriterForC;
	}
	if (m_pCodeWriterForCplus != NULL) {
		delete m_pCodeWriterForCplus;
	}
	if (m_pCodeWriterForCSharp != NULL) {
		delete m_pCodeWriterForCSharp;
	}
	if (m_pCodeWriterForJava != NULL) {
		delete m_pCodeWriterForJava;
	}
	if (m_pCodeWriterForPHP != NULL) {
		delete m_pCodeWriterForPHP;
	}
	if (m_pTM != NULL) {
		delete m_pTM;
	}
	if (m_pLM != NULL) {
		delete m_pLM;
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
	Tree& T = pDoc->m_T;

	UINT nP, nU, nD, nL, nR, nDel;
	nP = nU = nD = nL = nR = nDel = MF_GRAYED;

	Node *pSelect = GetTreeManager()->GetSelectedNode();
	if (pSelect != NULL) {
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
		if (T.CanDeleteNode(pSelect)) {
			nDel = MF_ENABLED;
			nP = MF_ENABLED;
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

TreeManager *CBrView::GetTreeManager()
{
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CTreeCtrl& tc = GetTreeCtrl();
	
	if (m_pTM != NULL) {
		delete m_pTM;
	}

	m_pTM = new TreeManager(&pDoc->m_T, &tc, m_pLM, &pDoc->m_U);

	return m_pTM;
}

void CBrView::UpdateAll(BOOL bSetVScrollPos, Node *pSelect)
{
	UpdateTree(bSetVScrollPos, pSelect);
	UpdateLoopIndices();
	UpdatePreview();
}

void CBrView::UpdateTree(BOOL bSetVScrollPos, Node *pSelect)
{
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	TreeManager *pTM = GetTreeManager();
	CTreeCtrl& tc = GetTreeCtrl();

	int nPos = -1;
	if (bSetVScrollPos) {
		nPos = tc.GetScrollPos(SB_VERT);
	}

	pDoc->m_T.AssignLevels();
	pTM->CreateTree();
	ExpandAll();

	if (pSelect != NULL) {
		pTM->SelectNode(pSelect);
	}
	else {
		pTM->SelectRoot();
	}

	if (nPos >= 0) {
		tc.SetScrollPos(SB_VERT, nPos);
	}
}

void CBrView::UpdateLoopIndices()
{
	m_pTM->CorrectLoopIndices();
}

void CBrView::UpdatePreview()
{
	// Tree
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Tree& T = pDoc->m_T;

	int nSize = T.GetNodeCount();
	if (nSize > 0) {
		// string
		nSize *= 250;
		nSize += 5000;
		TCHAR *lpszText = new TCHAR[nSize];
		::ZeroMemory(lpszText, nSize);
		// stream
		strstream ss(lpszText, nSize, ios::out);
		FileStream fs(&ss);
		// code writer
		m_pCodeWriter->SetFileStream(&fs);
		// write
		CodeWriter::NewLineType nNlType = m_pCodeWriter->GetNewLineType();
		m_pCodeWriter->SetNewLine(CodeWriter::NewLineType::NL_RN);
		T.Write(m_pCodeWriter);
		m_pCodeWriter->SetNewLine(nNlType);
		// preview
		CString strBuf(lpszText);
		CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
		pFrame->GetEditView()->GetEditCtrl().SetWindowText(strBuf);
		// free string
		delete [] lpszText;
	}
	else {
		CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
		pFrame->GetEditView()->GetEditCtrl().SetWindowText("");
	}
}

#include "DataType.h"

void CBrView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	UpdateAll();
}

// Select Tree Item
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
	Node *pItem  = pTM->GetSelectedNode();
	if (pItem != NULL) {
		pTM->DoMoveUp(pItem);
		pTM->SelectNode(pItem);
		UpdatePreview();
		SetModified();
	}
}

// Move Down
void CBrView::OnMovDown()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	TreeManager *pTM = GetTreeManager();
	Node *pItem  = pTM->GetSelectedNode();
	if (pItem != NULL) {
		pTM->DoMoveDown(pItem);
		pTM->SelectNode(pItem);
		UpdatePreview();
		SetModified();
	}
}

// Move Left
void CBrView::OnMovLeft()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	TreeManager *pTM = GetTreeManager();
	Node *pItem  = pTM->GetSelectedNode();
	if (pItem != NULL) {
		pTM->DoMoveLeft(pItem);
		pTM->SelectNode(pItem);
		UpdatePreview();
		SetModified();
	}
}

// Move Right
void CBrView::OnMovRight()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	TreeManager *pTM = GetTreeManager();
	Node *pItem  = pTM->GetSelectedNode();
	if (pItem != NULL) {
		pTM->DoMoveRight(pItem);
		pTM->SelectNode(pItem);
		UpdatePreview();
		SetModified();
	}
}

// Delete
void CBrView::OnDelNode()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	TreeManager *pTM = GetTreeManager();
	Node *pItem  = pTM->GetSelectedNode();
	if (pItem != NULL) {
		pTM->DoDelete(pItem);
		UpdatePreview();
		SetModified();
	}
}

// Add Data
void CBrView::OnAddData()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	CBrDoc *pDoc = GetDocument();
	Tree& T = pDoc->m_T;
	TreeManager *pTM = GetTreeManager();

	Node *pSelect = pTM->GetSelectedNode();
	if (pSelect == NULL) {
		return;
	}

	CAddDataDialog dlg(IDS_ADD_DATA, &T);
	dlg.m_nType = (int)m_nType;
	if (dlg.DoModal() == IDOK) {
		TypeDef *pNew = 
			new TypeDef((DataType::Type)dlg.m_nType, dlg.m_strVariable);
		if (pSelect->m_nNodeType == Node::NT_INNER) {
			pTM->DoInsert(pNew, pSelect, NULL);
		}
		else {
			Node *pParent = pSelect->m_pP;
			pTM->DoInsert(pNew, pParent, pSelect);
		}
		m_nType = (DataType::Type)dlg.m_nType;
		UpdateAll(TRUE, pNew);
		SetModified();
	}
}

// Add Loop
void CBrView::OnAddLoop()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	TreeManager *pTM = GetTreeManager();

	Node *pSelect = pTM->GetSelectedNode();
	if (pSelect == NULL) {
		return;
	}

	CAddLoopDialog dlg(m_pLM, IDS_ADD_LOOP);
	if (dlg.DoModal() == IDOK) {
		LoopDef *pNew = new LoopDef(dlg.m_strVariable);
		if (pSelect->m_nNodeType == Node::NT_INNER) {
			pTM->DoInsert(pNew, pSelect, NULL);
		}
		else {
			Node *pParent = pSelect->m_pP;
			pTM->DoInsert(pNew, pParent, pSelect);
		}
		UpdateAll(TRUE, pNew);
		SetModified();
	}
}

void CBrView::OnUpdateAddData(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	BOOL bEnable = TRUE;

	CBrApp *pApp = (CBrApp *)AfxGetApp();
	if (pApp->IsTrial()) {
		CBrDoc *pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		Tree& T = pDoc->m_T;
		if (T.GetNodeCount() >= 5) {
			bEnable = FALSE;
		}
	}
	pCmdUI->Enable(bEnable);
	/*
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Tree& T = pDoc->m_T;
	Node *pSelect = GetTreeManager()->GetSelectedNode();

	BOOL bEnable = FALSE;
	if (pSelect != NULL) {
		if (pSelect->GetMaxLoopLevel() <= LoopIndexManager::MaxLoopCount) {
			bEnable = TRUE;
		}
	}
	pCmdUI->Enable(bEnable);
	*/
}

void CBrView::OnUpdateAddLoop(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	BOOL bEnable = TRUE;

	CBrApp *pApp = (CBrApp *)AfxGetApp();
	if (pApp->IsTrial()) {
		CBrDoc *pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		Tree& T = pDoc->m_T;
		if (T.GetNodeCount() >= 5) {
			bEnable = FALSE;
		}
	}
	pCmdUI->Enable(bEnable);
	/*
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Tree& T = pDoc->m_T;
	Node *pSelect = GetTreeManager()->GetSelectedNode();

	BOOL bEnable = FALSE;
	if (pSelect != NULL) {
		if (pSelect->GetMaxLoopLevel() < LoopIndexManager::MaxLoopCount) {
			bEnable = TRUE;
		}
	}
	pCmdUI->Enable(bEnable);
	*/
}

void CBrView::OnEditProp()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	CBrDoc *pDoc = GetDocument();
	Tree& T = pDoc->m_T;
	TreeManager *pTM = GetTreeManager();

	Node *pSelect = pTM->GetSelectedNode();
	if (pSelect == NULL) {
		return;
	}

	if (pSelect->m_nNodeType == Node::NT_INNER) {
		CAddLoopDialog dlg(m_pLM, IDS_MOD_LOOP);
		dlg.m_strVariable = pSelect->GetVariable().GetName();
		if (dlg.DoModal() == IDOK) {
			pTM->DoSetLoop(pSelect, dlg.m_strVariable);
			UpdateLoopIndices();
			UpdatePreview();
			SetModified();
		}
	}
	else {
		TypeDef *pProp = (TypeDef *)pSelect;
		CAddDataDialog dlg(IDS_MOD_DATA, &T);
		dlg.m_nType = (int)pProp->GetVariable().GetDataType().GetType();
		dlg.m_strVariable = pProp->GetVariable().GetName();
		if (dlg.DoModal() == IDOK) {
			pTM->DoSetData(pSelect,
				(DataType::Type)dlg.m_nType, dlg.m_strVariable);
			UpdatePreview();
			SetModified();
		}
	}
}

void CBrView::OnUpdateEditProp(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Tree& T = pDoc->m_T;
	Node *pSelect = GetTreeManager()->GetSelectedNode();
	pCmdUI->Enable(pSelect != NULL && T.CanDeleteNode(pSelect));
}

void CBrView::OnUpdateMovUp(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Tree& T = pDoc->m_T;
	Node *pSelect = GetTreeManager()->GetSelectedNode();
	pCmdUI->Enable(pSelect != NULL && T.CanMoveUp(pSelect));
}

void CBrView::OnUpdateMovDown(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Tree& T = pDoc->m_T;
	Node *pSelect = GetTreeManager()->GetSelectedNode();
	pCmdUI->Enable(pSelect != NULL && T.CanMoveDown(pSelect));
}

void CBrView::OnUpdateMovLeft(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Tree& T = pDoc->m_T;
	Node *pSelect = GetTreeManager()->GetSelectedNode();
	pCmdUI->Enable(pSelect != NULL && T.CanMoveLeft(pSelect));
}

void CBrView::OnUpdateMovRight(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Tree& T = pDoc->m_T;
	Node *pSelect = GetTreeManager()->GetSelectedNode();
	pCmdUI->Enable(pSelect != NULL && T.CanMoveRight(pSelect));
}

void CBrView::OnUpdateDelNode(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Tree& T = pDoc->m_T;
	Node *pSelect = GetTreeManager()->GetSelectedNode();
	pCmdUI->Enable(pSelect != NULL && T.CanDeleteNode(pSelect));
}

void CBrView::OnEditUndo()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_U.Undo();
	UpdateAll();
	SetModified();
}

void CBrView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pCmdUI->Enable(pDoc->m_U.IsUndoable());
}

void CBrView::DoSrcOptions()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	CSrcOptionsDialog dlg;

	{
		dlg.m_nLang = 0;
		if (m_pCodeWriter == m_pCodeWriterForCplus) {
			dlg.m_nLang = 1;
		}
		else if (m_pCodeWriter == m_pCodeWriterForCSharp) {
			dlg.m_nLang = 2;
		}
		else if (m_pCodeWriter == m_pCodeWriterForJava) {
			dlg.m_nLang = 3;
		}
		else if (m_pCodeWriter == m_pCodeWriterForPHP) {
			dlg.m_nLang = 4;
		}
	}
	{
		int nPos = m_pCodeWriter->IsVariableLocal() ? 0 : 1;
		dlg.m_nVarPos = nPos;
	}
	dlg.m_nIndent = (int)m_pCodeWriter->GetIndentType();
	dlg.m_nNewLine = (int)m_pCodeWriter->GetNewLineType();
	dlg.m_nLoopIndex = (int)m_pLM->GetVariableType();
	dlg.m_nLoopType = (int)m_pLM->GetNumericalType();
	dlg.m_bDriver = m_pCodeWriter->IsDriverEnabled();
	dlg.m_bEndian = m_pCodeWriter->IsEndianConvEnabled();
	dlg.m_nEndType = m_pCodeWriter->IsLittleEndian() ? 1 : 0;
	
	if (dlg.DoModal() == IDOK) {
		SetCodeWriter(dlg.m_nLang,
			dlg.m_nIndent, dlg.m_nNewLine, dlg.m_nVarPos,
			((dlg.m_bDriver) ? 1 : 0),
			((dlg.m_bEndian) ? 1 : 0),
			((dlg.m_nEndType == 1) ? 1 : 0));
		SetLoopIndexManager(dlg.m_nLoopIndex, dlg.m_nLoopType);

		Node *pSelect = GetTreeManager()->GetSelectedNode();
		UpdateAll(TRUE, pSelect);
	}
}

void CBrView::DoSrcLang()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	CSrcLangDialog dlg;

	{
		dlg.m_nLang = 0;
		if (m_pCodeWriter == m_pCodeWriterForCplus) {
			dlg.m_nLang = 1;
		}
		else if (m_pCodeWriter == m_pCodeWriterForCSharp) {
			dlg.m_nLang = 2;
		}
		else if (m_pCodeWriter == m_pCodeWriterForJava) {
			dlg.m_nLang = 3;
		}
		else if (m_pCodeWriter == m_pCodeWriterForPHP) {
			dlg.m_nLang = 4;
		}
	}

	if (dlg.DoModal() == IDOK) {
//		SetCodeWriter(dlg.m_nLang);
		CRegManager rm;
		rm.WriteProfileDword("", "NoDispSrcLang", dlg.m_bNodisp);
	}
}

void CBrView::SetModified()
{
	CBrDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CBrApp *pApp = (CBrApp *)AfxGetApp();
	pDoc->SetModifiedFlag(!pApp->IsTrial());
}
