#pragma once

class LicManager
{
protected:
//	static LPCTSTR m_lpszLicKey;
	BOOL m_bTrial;
	CString m_strSetFilePath;
	CString m_strLicKey;

public:
	LicManager(void);
	virtual ~LicManager(void);

	BOOL IsTrial() const {return m_bTrial;}

	BOOL SetKey(LPCTSTR lpszKey);
};
