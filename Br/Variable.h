#pragma once

#include "UndoObject.h"
#include "DataType.h"

class Variable : public UndoObject
{
public:
	// Maximum Length of Variable Name
	enum {MaxStrLen = 50};

private:
	DataType m_dataType;	// Data Type
	LPTSTR m_lpszName;		// Variable Name
	int m_nLoopLevel;		// Loop Level

public:
	// Constructor
	Variable(DataType::Type nType = DataType::TypeInt,
		LPCTSTR lpszName = NULL, int nLoopLevel = 0);
	// Destructor
	virtual ~Variable(void);

	// Get Data Type
	DataType& GetDataType() const {return (DataType&)m_dataType;}

	// Set Variable Name
	void SetName(LPCTSTR lpszName, class UndoList *U = NULL);
	// Get Variable Name
	LPTSTR GetName() const {return m_lpszName;}

	// Set Loop Level
	void SetLoopLevel(int nLoopLevel) {m_nLoopLevel = nLoopLevel;}
	// Get Loop Level
	int GetLoopLevel() const {return m_nLoopLevel;}

	// Is Integer
	BOOL IsIntegerType() const;
	BOOL IsIntegerValue(int nIndexLevel) const;

public:
	// Error Code
	enum ErrorCode {
		ErrNull,
		ErrEmpty,
		ErrTooLong,
		ErrInvalidChar,
		ErrInvalid1st,
		ErrInvalidUscore
	};

	// Check Variable Name
	static void CheckName(LPCTSTR lpszName, DataType::Type nType) throw(...);
	static void CheckDataName(LPCTSTR lpszName) throw(...);
	static void CheckLoopName(LPCTSTR lpszName, class BracketPos **ppBp) throw(...);
	void CorrectLoopIndices(class LoopIndexManager *pLM);

	// Check Character
	static BOOL IsNumeric(TCHAR c);
	static BOOL IsLowerCase(TCHAR c);
	static BOOL IsUpperCase(TCHAR c);
	static BOOL IsAlphabet(TCHAR c);
	static BOOL IsUnderscore(TCHAR c);
	static BOOL IsBracketBegin(TCHAR c);
	static BOOL IsBracketEnd(TCHAR c);
	static BOOL IsAlphaNumeric(TCHAR c);

protected:
	// Undo Data
	struct UndoData {
		LPTSTR name;
	};

public:
	// Execute Undo
	virtual void ExeUndo(void *pPara);
	// Delete Undo
	virtual void DelUndo(void *pPara);
};
