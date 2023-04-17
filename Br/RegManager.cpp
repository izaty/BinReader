// RegManager.cpp: CRegManager クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RegManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CRegManager::CRegManager()
{
	m_hTopKey = HKEY_CURRENT_USER;
	m_strSoftwareKey = _T("Software");
	m_strCompanyName = _T("IZA-B");
	m_strProductName = _T("BinReader");
	// Appended by izaty on Aug.4,'06
	// start
	m_bCreate = TRUE;
	// end
}

CRegManager::~CRegManager()
{

}

HKEY CRegManager::GetProductKey()
{
	HKEY hSoftKey = NULL;
	HKEY hCompanyKey = NULL;
	HKEY hProductKey = NULL;

	// Modified by izaty on Aug.4,'06
	// start
	REGSAM regSam = (m_bCreate) ? KEY_WRITE | KEY_READ : KEY_READ;

	if (RegOpenKeyEx(m_hTopKey, m_strSoftwareKey, 0, regSam, &hSoftKey) 
		== ERROR_SUCCESS) {
	//if (RegOpenKeyEx(m_hTopKey, m_strSoftwareKey, 0, KEY_WRITE | KEY_READ,
	//	&hSoftKey) == ERROR_SUCCESS) {
	// end
		DWORD dw;
		// Modified by izaty on Aug.4,'06
		// start
		if (m_bCreate) {
			if (RegCreateKeyEx(hSoftKey, m_strCompanyName, 0, REG_NONE,
				REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL,
				&hCompanyKey, &dw) == ERROR_SUCCESS) {
				RegCreateKeyEx(hCompanyKey, m_strProductName, 0, REG_NONE,
					REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL,
					&hProductKey, &dw);
			}
		}
		else {
			if (RegOpenKeyEx(hSoftKey, m_strCompanyName, 0, KEY_READ, 
				&hCompanyKey) == ERROR_SUCCESS) {
				RegOpenKeyEx(hCompanyKey, m_strProductName, 0, KEY_READ,
					&hProductKey);
			}
		}
		/*
		if (RegCreateKeyEx(hSoftKey, m_strCompanyName, 0, REG_NONE,
			REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL,
			&hCompanyKey, &dw) == ERROR_SUCCESS) {
			RegCreateKeyEx(hCompanyKey, m_strProductName, 0, REG_NONE,
				REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
				&hProductKey, &dw);
		}
		*/
		// end
	}
	if (hSoftKey != NULL)
		RegCloseKey(hSoftKey);
	if (hCompanyKey != NULL)
		RegCloseKey(hCompanyKey);

	return hProductKey;
}

HKEY CRegManager::GetSectionKey(LPCTSTR lpszSection)
{
	HKEY hSectionKey = NULL;
	HKEY hProductKey = GetProductKey();
	if (hProductKey == NULL)
		return NULL;

	DWORD dw;
	// Modified by izaty on Aug.4,'06
	// start
	if (m_bCreate) {
		RegCreateKeyEx(hProductKey, lpszSection, 0, REG_NONE,
			REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL,
			&hSectionKey, &dw);
	}
	else {
		RegOpenKeyEx(hProductKey, lpszSection, 0, KEY_READ,
			&hSectionKey);
	}
	/*
	RegCreateKeyEx(hProductKey, lpszSection, 0, REG_NONE,
		REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
		&hSectionKey, &dw);
	*/
	// end
	RegCloseKey(hProductKey);
	return hSectionKey;
}

CString CRegManager::GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry,
	LPCTSTR lpszDefault)
{
	HKEY hSecKey = GetSectionKey(lpszSection);
	if (hSecKey == NULL)
		return lpszDefault;
	CString strValue;
	DWORD dwType, dwCount;
	LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
		NULL, &dwCount);
	if (lResult == ERROR_SUCCESS) {
		lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
			(LPBYTE)strValue.GetBuffer(dwCount/sizeof(TCHAR)), &dwCount);
		strValue.ReleaseBuffer();
	}
	RegCloseKey(hSecKey);
	if (lResult == ERROR_SUCCESS) {
		return strValue;
	}
	return lpszDefault;
}

BOOL CRegManager::WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry,
			LPCTSTR lpszValue)
{
	LONG lResult;
	if (lpszEntry == NULL) { //delete whole section
		HKEY hAppKey = GetProductKey();
		if (hAppKey == NULL)
			return FALSE;
		lResult = ::RegDeleteKey(hAppKey, lpszSection);
		RegCloseKey(hAppKey);
	}
	else if (lpszValue == NULL) {
		HKEY hSecKey = GetSectionKey(lpszSection);
		if (hSecKey == NULL)
			return FALSE;
		// necessary to cast away const below
		lResult = ::RegDeleteValue(hSecKey, (LPTSTR)lpszEntry);
		RegCloseKey(hSecKey);
	}
	else {
		HKEY hSecKey = GetSectionKey(lpszSection);
		if (hSecKey == NULL)
			return FALSE;
		lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_SZ,
			(LPBYTE)lpszValue, (lstrlen(lpszValue)+1)*sizeof(TCHAR));
		RegCloseKey(hSecKey);
	}
	return lResult == ERROR_SUCCESS;
}

DWORD CRegManager::GetProfileDword(LPCTSTR lpszSection, LPCTSTR lpszEntry,
								   DWORD dwDefault)
{
	HKEY hSecKey = GetSectionKey(lpszSection);
	if (hSecKey == NULL)
		return dwDefault;
	DWORD dwValue;
	DWORD dwType;
	DWORD dwCount = sizeof(DWORD);
	LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
		(LPBYTE)&dwValue, &dwCount);
	RegCloseKey(hSecKey);
	if (lResult == ERROR_SUCCESS) {
		return dwValue;
	}
	return dwDefault;
}

BOOL CRegManager::WriteProfileDword(LPCTSTR lpszSection, LPCTSTR lpszEntry,
									DWORD dwValue)
{
	LONG lResult;
	if (lpszEntry == NULL) { //delete whole section
		HKEY hAppKey = GetProductKey();
		if (hAppKey == NULL)
			return FALSE;
		lResult = ::RegDeleteKey(hAppKey, lpszSection);
		RegCloseKey(hAppKey);
	}
	else {
		HKEY hSecKey = GetSectionKey(lpszSection);
		if (hSecKey == NULL)
			return FALSE;
		lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_DWORD,
			(LPBYTE)&dwValue, sizeof(DWORD));
		RegCloseKey(hSecKey);
	}
	return lResult == ERROR_SUCCESS;
}

CString CRegManager::GetWinAppRegistryKey() const
{
	CString strTmp;
	strTmp.Format("%s\\%s", GetCompanyName(), GetProductName());
	return strTmp;
}
