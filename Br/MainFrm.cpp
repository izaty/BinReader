// MainFrm.cpp : CMainFrame �N���X�̎���
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
	ID_SEPARATOR,           // �X�e�[�^�X ���C�� �C���W�P�[�^
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame �R���X�g���N�V����/�f�X�g���N�V����

CMainFrame::CMainFrame()
{
	// TODO: �����o�������R�[�h�������ɒǉ����Ă��������B
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
		TRACE0("�c�[�� �o�[�̍쐬�Ɏ��s���܂����B\n");
		return -1;      // �쐬�ł��܂���ł����B
	}

	// 256�F�̃c�[���o�[�Ή�
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
		TRACE0("�X�e�[�^�X �o�[�̍쐬�Ɏ��s���܂����B\n");
		return -1;      // �쐬�ł��܂���ł����B
	}

	// TODO: �c�[�� �o�[���h�b�L���O�\�ɂ��Ȃ��ꍇ�́A������ 3 �s���폜���Ă��������B
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	/*
	m_wndToolBar.SetButtonText(0, "�V�K�쐬");
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
//		1, 2,               // TODO: �s�Ɨ�̐��𒲐����Ă��������B
//		CSize(10, 10),      // TODO: �ŏ��y�C���̃T�C�Y��ύX���܂��B
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
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return TRUE;
}


// CMainFrame �f�f

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


// CMainFrame ���b�Z�[�W �n���h��
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
	// TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
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
	// TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
	GetTreeView()->DoSrcOptions();
}

void CMainFrame::OnUpdateSaveSrc(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h�� �R�[�h��ǉ����܂��B
	CBrApp *pApp = (CBrApp *)AfxGetApp();
	pCmdUI->Enable(!pApp->IsTrial());
}

//
// HTML�w���v
//
#include <htmlhelp.h>
void CMainFrame::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	// �ŏ��� CWin::WinHelp �֐����̕K�v�ȏ������R�s�[���܂����B

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


	// �������� HTML �w���v�p�ɏ������������̂ł��B

	// HTML Help �t�@�C���̑��݂��`�F�b�N
	CString hp = pApp->m_pszHelpFilePath;
	CFileStatus st;
	if ( !CFile::GetStatus(hp,st) )
	{
		CString str;
		str.Format( "Not Exist Html Help File\n\n   File Path [ %s ]", hp );
		AfxMessageBox(str);
		return;
	}

	// �w���v��\��
	switch( nCmd )
	{
	case HELP_INDEX:// �w���v�̖ڎ�
		::HtmlHelp(m_hWnd, hp, HH_DISPLAY_TOC, NULL);
		break;
	case HELP_HELPONHELP:// �w���v�̌���
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
	case HELP_FINDER:// �L�[���[�h�Ō���
		::HtmlHelp(m_hWnd, hp, HH_DISPLAY_INDEX , NULL);
		break;
	case HELP_CONTEXT:// �R���e�L�X�g�w���v (F1/Shift+F1/HelpButton/?Button)
		{
			// �����ɃJ�[�\���ʒu�̃E�B���h�E���擾���Ȃ��ƃJ�[�\�����������Ⴄ�B
			POINT   point;
			GetCursorPos(&point);
			CWnd*pCallWnd = WindowFromPoint( point );

			// �w���v�R���e�L�X�gID dwData ��ʂ� ID �ɕύX�������ꍇ�Ȃǂ�
			// �����Ɏ��������܂��BdwData �͊��ɉ��Z���ꂽ�l�Ȃ̂Œ��ӁB
		
			// �� ID_EDIT_REDO �̏ꍇ ID_EDIT_UNDO �ɂ���i�܂蓯���y�[�W�\��)
			// if ( dwData == ID_EDIT_REDO | 0x10000 ) dwData = ID_EDIT_UNDO | 0x10000;
			
			// �󋵈ˑ��^�̃w���v���ƁA�w���v�쐬����VC�̃��\�[�X�ɑΉ�����
			// �eHTML�t�@�C�����֘A�t���Ă���K�v������܂��B�������A�c�[��
			// �o�[�̃{�^���P�P�ɂP�y�[�W�� html �t�@�C�����֘A�t�����
			// �ł͂Ȃ��A�P�̃c�[���o�[�łP�y�[�W�����֘A�t���������Ȃǂ�
			// ����܂��B�_�C�A���O�o�[�Ȃǂł��A�R���g���[����{�^���̂̂P
			// �P�� �P�y�[�W�����蓖�Ă�̂ł͂Ȃ��A�_�C�A���O�o�[���̂�
			// �P�̃y�[�W��\�����������ꍇ�Ȃǂ�����܂��B

			// �����ŁA�����ł́A�܂��ŏ��� dwData�̃R���e�L�X�gID�̃y�[�W��
			// ����Ε\�����A������΁A�e�E�B���h�E��ID����쐬�����R���e�L�X
			// �gID �Ȃ���΂���ɐe�E�B���h�E��ID�E�E�E�B�ƃg���C���Ă݂āA
			// ���ǉ��������ꍇ�́A�G���[���b�Z�[�W��\������悤�ȁA�d�l��
			// �����Ă݂܂����B�e���D�݂ɍ��킹�ď��������Ďg�p���Ă��������B

			// HTML Help ��\��
			HWND hWnd = NULL;
			DWORD dwID = dwData;
			while( dwID>0 && (hWnd=::HtmlHelp(m_hWnd,hp,HH_HELP_CONTEXT,dwID))==NULL && pCallWnd )
			{
				pCallWnd = pCallWnd->GetParent();
				dwID = (pCallWnd)? (pCallWnd->GetDlgCtrlID()|0x50000):0;
			}
			
			// ���̕��@���ƁA���j���[���ڂ̃R���e�L�X�gID�̃w���v�������ꍇ��
			// ���̉��̃E�B���h�E�̃R���e�L�X�g������Ƃ����\�����Ă��܂���
			// ������_������B�������A���j���[���ڂ̃R���e�L�X�gID�̃w���v��
			// �����Ɨp�ӂ��Ă����Ζ����N���Ȃ��B

			// �G���[�`�F�b�N
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