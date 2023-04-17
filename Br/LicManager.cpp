#include "StdAfx.h"
#include "LicManager.h"
#include "FileStream.h"

//LPCTSTR LicManager::m_lpszLicKey = _T("1326-A45E-0B8A-1060-22FA-12C2-19ED");

LicManager::LicManager(void)
{
	m_bTrial = TRUE;

	TCHAR szModFilePath[_MAX_PATH+1];
	::GetModuleFileName(AfxGetInstanceHandle(), szModFilePath, _MAX_PATH);
	CString strModFilePath = _T(szModFilePath);
	int nPos = strModFilePath.ReverseFind(_T('\\'));
	m_strSetFilePath = strModFilePath.Left(nPos + 1);
	m_strSetFilePath += _T("Br.set");

	m_strLicKey.Format("%04x-%04x-%04x-%04x-%04x-%04x-%04x",
		0x1326, 0xa45e, 0x0b8a, 0x1060, 0x22fa, 0x12c2, 0x19ed);
	m_strLicKey.MakeUpper();

	try {
		FileStream fs(m_strSetFilePath, _T("r"));
		char *p = fs.ReadLine();

		if (p != NULL) {
			if (!strcmp(p, m_strLicKey)) {
				m_bTrial = FALSE;
			}
		}
	}
	catch (FsException) {
	}
}

LicManager::~LicManager(void)
{
}

BOOL LicManager::SetKey(LPCTSTR lpszKey)
{
	if (strcmp(lpszKey, m_strLicKey)) {
		return FALSE;
	}

	FileStream fs(m_strSetFilePath, _T("w"));
	fs.Write(m_strLicKey);
	
	m_bTrial = FALSE;

	return TRUE;
}