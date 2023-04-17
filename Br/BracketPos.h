#pragma once

class BracketPos
{
public:
	struct Var {
		int level;
		int start;
		int length;
		LPTSTR lpsz;
		Var *next;
	} m_var, *m_pCurrVar;

	BOOL m_bError;

	BracketPos(LPCTSTR lpsz);
	virtual ~BracketPos(void);

	BOOL IsError() const {return m_bError;}
};
