// Br.h : Br �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��


// CBrApp:
// ���̃N���X�̎����ɂ��ẮABr.cpp ���Q�Ƃ��Ă��������B
//

#include "LicManager.h"

class CBrApp : public CWinApp
{
public:
	CBrApp();


// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����
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