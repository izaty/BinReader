// RegManager.h: CRegManager クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGMANAGER_H__B4F92A30_68EB_4D82_AF15_BF154C5AC4C3__INCLUDED_)
#define AFX_REGMANAGER_H__B4F92A30_68EB_4D82_AF15_BF154C5AC4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRegManager  
{
public:
	CRegManager();
	virtual ~CRegManager();

	CString GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry,
		LPCTSTR lpszDefault);
	BOOL WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry,
		LPCTSTR lpszValue);
	DWORD GetProfileDword(LPCTSTR lpszSection, LPCTSTR lpszEntry,
		DWORD dwDefault);
	BOOL WriteProfileDword(LPCTSTR lpszSection, LPCTSTR lpszEntry,
		DWORD dwValue);

protected:
	HKEY m_hTopKey;
	CString m_strSoftwareKey;
	CString m_strCompanyName;
	CString m_strProductName;
	// Appended by izaty on Aug.4,'06
	// start
	BOOL m_bCreate;
	// end

public:
	HKEY GetProductKey();
	HKEY GetSectionKey(LPCTSTR lpszSection);

	void SetTopKey(HKEY hKey) {m_hTopKey = hKey;}
	void SetSoftwareKey(LPCTSTR lpszKey) {m_strSoftwareKey = lpszKey;}
	void SetCompanyName(LPCTSTR lpszKey) {m_strCompanyName = lpszKey;}
	void SetProductName(LPCTSTR lpszKey) {m_strProductName = lpszKey;}
	HKEY GetTopKey() const {return m_hTopKey;}
	CString GetSoftwareKey() const {return m_strSoftwareKey;}
	CString GetCompanyName() const {return m_strCompanyName;}
	CString GetProductName() const {return m_strProductName;}
	CString GetWinAppRegistryKey() const;

	// Appended by izaty on Aug.4,'06
	// start
	void SetReadWrite() {m_bCreate = TRUE;}
	void SetReadOnly() {m_bCreate = FALSE;}
	// end
};

#endif // !defined(AFX_REGMANAGER_H__B4F92A30_68EB_4D82_AF15_BF154C5AC4C3__INCLUDED_)
