#include "StdAfx.h"
#include "LoopIndexManager.h"

LoopIndexManager::LoopIndexManager(VarType nVarType,
								   NumType nNumType)
	: m_nVarType(nVarType), m_nNumType(nNumType)
{

}

LPTSTR LoopIndexManager::GetTypeString() const
{
	static LPTSTR lpszInt		= _T("int");
	static LPTSTR lpszVolInt	= _T("volatile int");
	static LPTSTR lpszRegInt	= _T("register int");

	switch (m_nNumType) {
	case NumInt:
		return lpszInt;
	case NumVolInt:
		return lpszVolInt;
	case NumRegInt:
		return lpszRegInt;
	}

	return lpszInt;
}

LPTSTR LoopIndexManager::GetTypeStringAndBlank() const
{
	static TCHAR szType[30];
	lstrcpy(szType, GetTypeString());
	lstrcat(szType, _T(" "));
	return szType;
}

LPTSTR LoopIndexManager::GetVariableString(int nLevel) const
{
	return GetVariableString(nLevel, m_nVarType);
}

LPTSTR LoopIndexManager::GetVariableString(int nLevel, VarType nVarType)
{
	static TCHAR szTemp[100];
	::ZeroMemory(szTemp, sizeof(szTemp));

	if (0 <= nLevel && nLevel < (int)MaxLoopCount) {
		if (nVarType == Var_i) {
			_stprintf_s(szTemp, "i%d", nLevel);
		}
		else if (nVarType == Var_ijk) {
			_stprintf_s(szTemp, "%c", 'i' + nLevel);
		}
		else if (nVarType == Var_Index) {
			_stprintf_s(szTemp, "Index_%c", 'i' + nLevel);
		}
	}

	return szTemp;
}

int LoopIndexManager::GetVariableLevel(LPCTSTR lpszVariable)
{
	int nLevel = -1;
	for (volatile int i = 0; i < (int)VarTypeCount; i++) {
		for (volatile int j = 0; j < (int)MaxLoopCount; j++) {
			LPTSTR lpsz = GetVariableString(j, (VarType)i);
			if (_tcscmp(lpsz, lpszVariable) == 0) {
				nLevel = j;
			}
		}
	}
	return nLevel;
}

BOOL LoopIndexManager::IsPossibleVariableString(LPCTSTR lpszVariable)
{
	for (volatile int i = 0; i < (int)VarTypeCount; i++) {
		for (volatile int j = 0; j < (int)MaxLoopCount; j++) {
			LPTSTR lpsz = GetVariableString(j, (VarType)i);
			if (_tcscmp(lpsz, lpszVariable) == 0) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

LPTSTR LoopIndexManager::GetAllVariableStrings(int nCount) const
{
	static TCHAR szTemp[40];
	::ZeroMemory(szTemp, sizeof(szTemp));

	if (0 < nCount && nCount < (int)MaxLoopCount) {
		// loop index varaibles (i0, i1, i2, ....)
		volatile int i;
		for (i = 0; i < nCount; i++) {
			_tcscat(szTemp, GetVariableString(i));
			if (i < nCount - 1) {	// to be continued
				_tcscat(szTemp, ", ");
			}
		}
	}

	return szTemp;
}