#include "StdAfx.h"
#include "BracketPos.h"
#include "Variable.h"

BracketPos::BracketPos(LPCTSTR lpsz)
{
	m_var.next = NULL;
	m_pCurrVar = &m_var;
	m_bError = TRUE;

	if (lpsz == NULL) {
		return;
	}
	int nStrLen = lstrlen(lpsz);
	if (nStrLen < 4) {
		return;
	}

	BOOL bError = FALSE;
	int nPos = nStrLen - 1;
	int nBgnCount = 0, nEndCount = 0;
	int nAryPos = 0;
	int nEndPos = nStrLen;
	int nFlag = -1;
	while (nPos >= 0) {
		if (Variable::IsBracketEnd(lpsz[nPos])) {
			nEndCount++;
			if (nFlag == 0) {		// Variable
				bError = TRUE;
				break;
			}
			//nAryPos = 0;
			nEndPos = nPos;
			nFlag = 2;
		}
		else if (Variable::IsBracketBegin(lpsz[nPos])) {
			nBgnCount++;
			if (nBgnCount > nEndCount) {
				bError = TRUE;
				break;
			}
			if (nFlag != 0) {	// Not Variable
				bError = TRUE;
				break;
			}

			int nVarLen = nEndPos - nPos - 1;
			Var *p = new Var;
			p->lpsz = new TCHAR[nVarLen+1];
			lstrcpyn(p->lpsz, &lpsz[nPos+1], nVarLen + 1);
			p->lpsz[nVarLen] = _T('\0');
			p->start = nPos + 1;
			p->length = nVarLen;
			p->level = nAryPos;
			p->next = NULL;
			m_pCurrVar->next = p;
			m_pCurrVar = p;

			nAryPos++;
			nEndPos = nPos;
			nFlag = 1;
		}
		else if (Variable::IsAlphaNumeric(lpsz[nPos])) {
			nFlag = 0;
		}
		else if (Variable::IsUnderscore(lpsz[nPos])) {
			nFlag = 0;
		}
		else {
			bError = TRUE;
			break;
		}
		nPos--;
	}

	if (bError) {
		return;
	}

	if (nFlag == 0) {
		int nVarLen = nEndPos;
		Var *p = new Var;
		p->lpsz = new TCHAR[nVarLen+1];
		lstrcpyn(p->lpsz, lpsz, nVarLen + 1);
		p->lpsz[nVarLen] = _T('\0');
		p->start = 0;
		p->length = nVarLen;
		p->level = nAryPos;
		p->next = NULL;
		m_pCurrVar->next = p;
		m_pCurrVar = p;
		m_bError = FALSE;
	}
}

BracketPos::~BracketPos(void)
{
	Var *pVar = m_var.next;
	while (pVar != NULL) {
		Var *pWork = pVar->next;
		if (pVar->lpsz != NULL) {
			delete pVar->lpsz;
		}
		delete pVar;
		pVar = pWork;
	}
}
