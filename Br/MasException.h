#pragma once

class MasException  
{
public:
	MasException();
	virtual ~MasException();
	virtual BOOL GetErrorMessage(LPTSTR lpszError, UINT nMaxError);
	virtual int ReportError(UINT nType = MB_OK, UINT nMessageId = 0);
};
