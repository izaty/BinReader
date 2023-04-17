// MasException.cpp: MasException クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MasException.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

MasException::MasException()
{
}

MasException::~MasException()
{

}

BOOL MasException::GetErrorMessage(LPTSTR lpszError, UINT nMaxError)
{
	if (nMaxError != 0 && lpszError != NULL)
		*lpszError = '\0';

	return FALSE;
}

int MasException::ReportError(UINT nType, UINT nMessageId)
{
	/*
	TCHAR szErrorMessage[512];
	int nDisposition;

	if (GetErrorMessage(szErrorMessage, sizeof(szErrorMessage)))
		nDisposition = AfxMessageBox(szErrorMessage, nType);
	else {
		if (nMessageId == 0)
			nMessageId = AFX_IDP_NO_ERROR_AVAILABLE;
		nDisposition = AfxMessageBox(nMessageId, nType);
	}
	return nDisposition;
	*/
	return 0;
}
