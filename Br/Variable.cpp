#include "StdAfx.h"
#include "Variable.h"
#include "UndoList.h"
#include "BracketPos.h"
#include "LoopIndexManager.h"

Variable::Variable(DataType::Type nType,
				   LPCTSTR lpszName, int nLoopLevel)
{
	m_dataType.SetType(nType);
	m_lpszName = new TCHAR[MaxStrLen+11];
	SetName(lpszName);
	SetLoopLevel(nLoopLevel);
}

Variable::~Variable(void)
{
	delete [] m_lpszName; 
}

void Variable::SetName(LPCTSTR lpszName, UndoList *U)
{
	if (U != NULL) {
		UndoData *obj = new UndoData;
		obj->name = new TCHAR[MaxStrLen+11];
		::ZeroMemory(obj->name, MaxStrLen + 11);
		lstrcpyn(obj->name, m_lpszName, MaxStrLen + 11);
		U->Register(this, (void *)obj);
	}
	::ZeroMemory(m_lpszName, MaxStrLen + 11);
	lstrcpyn(m_lpszName, lpszName, MaxStrLen + 11);
}

void Variable::CheckDataName(LPCTSTR lpszName) throw(...)
{
	// null
	if (lpszName == NULL) {
		throw ErrNull;
	}

	// length of name
	int nStrLen = lstrlen(lpszName);
	if (nStrLen <= 0) {			// empty
		throw ErrEmpty;
	}
	if (nStrLen > MaxStrLen) {	// over max
		throw ErrTooLong;
	}

	// numerical 1st character
	if (IsNumeric(lpszName[0])) {
		throw ErrInvalid1st;
	}

	// unacceptable characters
	BOOL bAllUnderscored = TRUE;
	volatile int i;
	for (i = 0; i < nStrLen; i++) {
		if (IsAlphaNumeric(lpszName[i])) {
			bAllUnderscored = FALSE;
		}
		else if (IsUnderscore(lpszName[i])) {
		}
		else {
			throw ErrInvalidChar;
		}
	}

	// all underscored
	if (bAllUnderscored) {
		throw ErrInvalidUscore;
	}

}

void Variable::CheckName(LPCTSTR lpszName, DataType::Type nType) throw(...)
{
	// null
	if (lpszName == NULL) {
		throw ErrNull;
	}

	// length of name
	int nStrLen = lstrlen(lpszName);
	if (nStrLen <= 0) {			// empty
		throw ErrEmpty;
	}
	if (nStrLen > MaxStrLen) {	// over max
		throw ErrTooLong;
		//if (IsNumeric(lpszName[0])) {
		//	throw ErrInvalid1st;
		//}
	}

	// characters
	volatile int i;
	if (nType == DataType::TypeCount) {	// loop variable
		// numerical value
		if (IsNumeric(lpszName[0])) {
			for (i = 1; i < nStrLen; i++) {
				if (!IsNumeric(lpszName[i])) {
					throw ErrInvalid1st;
				}
			}
			return;
		}
		// brackets used
		if (IsBracketEnd(lpszName[nStrLen-1])) {
			BracketPos bp(lpszName);
			if (bp.IsError()) {
				throw ErrInvalidChar;
			}
			return;
			/*
			i = nStrLen - 2;
			int nBgnPos = 0;
			int nEndPos = i;
			int nEndCount = 1;
			while (1) {
				if (IsBracketEnd(lpszName[i])) {
					nEndPos = i;
					nEndCount++;
				}
				if (IsBracketBegin(lpszName[i])) {
					nBgnPos = i;

					if (nEndCount <= 0) {
						throw ErrInvalidChar;
					}

					if (!nBgnPos) {
						throw ErrInvalidChar;
					}

					// variable part characters
					int nVarPartLen;
					TCHAR *lpszVar;

					nVarPartLen = nEndPos - nBgnPos - 1;
					if (nVarPartLen <= 0) {
						throw ErrInvalidChar;
					}

					lpszVar = new TCHAR[nVarPartLen+1];
					LPCTSTR lpszTest = &lpszName[nBgnPos+1];
					lstrcpyn(lpszVar, lpszTest, nVarPartLen + 1);
					lpszVar[nVarPartLen] = _T('\0');
					try {
						CheckName(lpszVar, DataType::TypeInt);
					}
					catch (ErrorCode e) {
						throw;
					}
					delete [] lpszVar;

					nEndCount--;
					nEndPos = nBgnPos;
				}
				if (i == 0) {
					if (nEndCount > 0) {
						throw ErrInvalidChar;
					}

					// variable part characters
					int nVarPartLen;
					TCHAR *lpszVar;

					nVarPartLen = nBgnPos;
					if (nVarPartLen <= 0) {
						throw ErrInvalidChar;
					}

					lpszVar = new TCHAR[nVarPartLen+1];
					lstrcpyn(lpszVar, lpszName, nVarPartLen + 1);
					lpszVar[nVarPartLen] = _T('\0');
					try {
						CheckName(lpszVar, DataType::TypeInt);
					}
					catch (ErrorCode e) {
						throw;
					}
					delete [] lpszVar;
					return;
				}
				i--;
			}
			*/
		}

		/*
		if (IsBracketEnd(lpszName[nStrLen-1])) {
			// find bracket-begin
			int nBracketBegin = 0;
			for (i = 1; i < nStrLen - 2; i++) {
				if (IsBracketBegin(lpszName[i])) {
					nBracketBegin = i;
				}
			}
			if (!nBracketBegin) {
				throw ErrInvalidChar;
			}
			// variable part characters
			int nVarPartLen;
			TCHAR *lpszVar;

			nVarPartLen = nBracketBegin;
			lpszVar = new TCHAR[nVarPartLen+1];
			lstrcpyn(lpszVar, lpszName, nVarPartLen + 1);
			//lpszVar[nVarPartLen] = _T('\0');
			try {
				CheckName(lpszVar, DataType::TypeInt);
			}
			catch (ErrorCode e) {
				throw;
			}
			delete [] lpszVar;

			// index part characters
			nVarPartLen = nStrLen - nBracketBegin - 2;
			lpszVar = new TCHAR[nVarPartLen+1];
			lstrcpyn(lpszVar, &lpszName[nBracketBegin+1], nVarPartLen + 1);
			//lpszVar[nVarPartLen] = _T('\0');
			try {
				CheckName(lpszVar, DataType::TypeInt);
			}
			catch (ErrorCode e1) {
				try {
					CheckName(lpszVar, DataType::TypeCount);
				}
				catch (ErrorCode e2) {
					throw;
				}
			}
			delete [] lpszVar;

			return;
		}
		*/
	}
	else {
		// numerical 1st character
		if (IsNumeric(lpszName[0])) {
			throw ErrInvalid1st;
		}
	}

	// unacceptable characters
	BOOL bAllUnderscored = TRUE;
	for (i = 0; i < nStrLen; i++) {
		if (IsAlphaNumeric(lpszName[i])) {
			bAllUnderscored = FALSE;
		}
		else if (IsUnderscore(lpszName[i])) {
		}
		else {
			throw ErrInvalidChar;
		}
	}

	// all underscored
	if (bAllUnderscored) {
		throw ErrInvalidUscore;
	}
}

void Variable::CheckLoopName(LPCTSTR lpszName, BracketPos **ppBp) throw(...)
{
	// null
	if (lpszName == NULL) {
		throw ErrNull;
	}

	// length of name
	int nStrLen = lstrlen(lpszName);
	if (nStrLen <= 0) {			// empty
		throw ErrEmpty;
	}
	if (nStrLen > MaxStrLen) {	// over max
		throw ErrTooLong;
	}

	// numerical value
	volatile int i;
	if (IsNumeric(lpszName[0])) {
		volatile int i;
		for (i = 1; i < nStrLen; i++) {
			if (!IsNumeric(lpszName[i])) {
				throw ErrInvalid1st;
			}
		}
		return;
	}

	// brackets used
	if (IsBracketEnd(lpszName[nStrLen-1])) {
		BracketPos *pBp = new BracketPos(lpszName);
		*ppBp = pBp;
		if (pBp->IsError()) {
			throw ErrInvalidChar;
		}
		BracketPos::Var *p = pBp->m_var.next;
		while (p) {
			try {
				if (p->level > 0) {
					CheckDataName(p->lpsz);
				}
			}
			catch (ErrorCode e) {
				throw;
			}
			p = p->next;
		}
		return;
	}

	// unacceptable characters
	BOOL bAllUnderscored = TRUE;
	for (i = 0; i < nStrLen; i++) {
		if (IsAlphaNumeric(lpszName[i])) {
			bAllUnderscored = FALSE;
		}
		else if (IsUnderscore(lpszName[i])) {
		}
		else {
			throw ErrInvalidChar;
		}
	}

	// all underscored
	if (bAllUnderscored) {
		throw ErrInvalidUscore;
	}
}

void Variable::CorrectLoopIndices(LoopIndexManager *pLM)
{
	int nStrLen = lstrlen(m_lpszName);

	if (!IsBracketEnd(m_lpszName[nStrLen-1])) {
		return;
	}

	BracketPos *pBp = new BracketPos(m_lpszName);
	if (pBp == NULL) {
		return;
	}

	LPTSTR lpszTemp = new TCHAR[MaxStrLen+11];
	::ZeroMemory(lpszTemp, MaxStrLen + 11);
	BracketPos::Var *p = pBp->m_var.next;
	while (p) {
		int nLevel = pLM->GetVariableLevel(p->lpsz);
		if (nLevel >= 0) {
			lstrcpyn(lpszTemp, m_lpszName, p->start + 1);
			lstrcat(lpszTemp, pLM->GetVariableString(nLevel));
			lstrcat(lpszTemp, &m_lpszName[p->start+p->length]);
			lstrcpy(m_lpszName, lpszTemp);
		}
		p = p->next;
	}
	delete [] lpszTemp;
	delete pBp;
}

BOOL Variable::IsNumeric(TCHAR c)
{
	return (_T('0') <= c && c <= _T('9'));
}

BOOL Variable::IsUpperCase(TCHAR c)
{
	return (_T('A') <= c && c <= _T('Z'));
}

BOOL Variable::IsLowerCase(TCHAR c)
{
	return (_T('a') <= c && c <= _T('z'));
}

BOOL Variable::IsAlphabet(TCHAR c)
{
	return (IsUpperCase(c) || IsLowerCase(c));
}

BOOL Variable::IsUnderscore(TCHAR c)
{
	return (c == _T('_'));
}

BOOL Variable::IsBracketBegin(TCHAR c)
{
	return (c == _T('['));
}

BOOL Variable::IsBracketEnd(TCHAR c)
{
	return (c == _T(']'));
}

BOOL Variable::IsAlphaNumeric(TCHAR c)
{
	return (IsAlphabet(c) || IsNumeric(c));
}

BOOL Variable::IsIntegerType() const
{
	DataType::Type nType = m_dataType.GetType();
	return (nType == DataType::TypeInt ||
			nType == DataType::TypeLong ||
			nType == DataType::TypeShort);
}

BOOL Variable::IsIntegerValue(int nIndexLevel) const
{
	return (IsIntegerType() && nIndexLevel == m_nLoopLevel);
}


// Execute Undo
void Variable::ExeUndo(void *pPara)
{
	UndoData *obj = (UndoData *)pPara;
	SetName(obj->name);
	delete obj->name;
	delete obj;
}

// Delete Undo Data
void Variable::DelUndo(void *pPara)
{
	UndoData *obj = (UndoData *)pPara;
	delete obj->name;
	delete obj;
}