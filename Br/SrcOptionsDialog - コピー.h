#pragma once
#include "afxwin.h"


// CSrcOptionsDialog ダイアログ

class CSrcOptionsDialog : public CDialog
{
	DECLARE_DYNAMIC(CSrcOptionsDialog)

public:
	CSrcOptionsDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSrcOptionsDialog();

// ダイアログ データ
	enum { IDD = IDD_SRC_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	int m_nLang;
	int m_nIndent;
	int m_nLoopIndex;
	int m_nLoopType;
	BOOL m_nVarPos;
	BOOL m_bDriver;
	BOOL m_bEndian;
	virtual BOOL OnInitDialog();
	CComboBox m_cbLoopIndex;
	CComboBox m_cbLoopType;
	int m_nNewLine;
	afx_msg void OnBnClickedLangC();
	afx_msg void OnBnClickedLangCpl();
	afx_msg void OnBnClickedLangCsh();
	afx_msg void OnBnClickedLangJava();
	afx_msg void OnBnClickedLangPHP();
	afx_msg void OnBnClickedLangRuby();

protected:
	void SwitchLang(UINT nStringID, BOOL bEndTypeFlag, BOOL bVarTypeFlag);
public:
	CComboBox m_cbEndType;
	int m_nEndType;
	CButton m_btEndian;
	CButton m_btDriver;
	afx_msg void OnBnClickedEndian();
};
