#include "StdAfx.h"
#include "LoopIndexManager.h"

LoopIndexManager::LoopIndexManager(VariableType nVarType,
								   NumericalType nNumType)
	: m_nVarType(nVarType), m_nNumType(nNumType)
{

}

LPTSTR LoopIndexManager::GetIndexName(int nLevel) const
{
	static TCHAR szTemp[30];
	::ZeroMemory(szTemp, sizeof(szTemp));

	if (0 <= nLevel && nLevel < (int)MaxLoopCount) {
		if (m_nVarType == Index_i) {
			_stprintf_s(szTemp, "i%d", nLevel);
		}
		else if (m_nVarType == Index_ijk) {
			_stprintf_s(szTemp, "%c", 'i' + nLevel);
		}
	}
	return szTemp;
}

LPTSTR LoopIndexManager::GetNumericalType() const
{
	static TCHAR szTemp[30];
	::ZeroMemory(szTemp, sizeof(szTemp));

	if (m_nNumType == Num_Int) {
		_tcscpy_s(szTemp, _T("int "));
	}
	if (m_nNumType == Num_RegInt) {
		_tcscpy_s(szTemp, _T("register int "));
	}
	if (m_nNumType == Num_VolInt) {
		_tcscpy_s(szTemp, _T("volatile int "));
	}
	if (m_nNumType == Num_UInt) {
		_tcscpy_s(szTemp, _T("unsigned int "));
	}
	if (m_nNumType == Num_RegUInt) {
		_tcscpy_s(szTemp, _T("register unsigned int "));
	}
	if (m_nNumType == Num_VolUInt) {
		_tcscpy_s(szTemp, _T("volatile unsigned int "));
	}
	return szTemp;
}
