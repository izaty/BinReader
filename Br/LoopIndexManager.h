#pragma once

class LoopIndexManager
{
public:
	enum {MaxLoopCount = 10};
	enum VarType {
		Var_i = 0,
		Var_ijk,
		Var_Index,
		VarTypeCount
	};
	enum NumType {
		NumInt = 0,
		NumVolInt,
		NumRegInt,
		NumTypeCount
	};

protected:
	VarType m_nVarType;
	NumType m_nNumType;

public:
	LoopIndexManager(VarType nVarType, NumType nNumType = NumVolInt);
	virtual ~LoopIndexManager(void) {}

	void SetVariableType(VarType nVarType) {m_nVarType = nVarType;}
	VarType GetVariableType() const {return m_nVarType;}

	void SetNumericalType(NumType nNumType) {m_nNumType = nNumType;}
	NumType GetNumericalType() const {return m_nNumType;}

	LPTSTR GetVariableString(int nLevel) const;
	LPTSTR GetAllVariableStrings(int nCount) const;
	LPTSTR GetTypeString() const;
	LPTSTR GetTypeStringAndBlank() const;

	static LPTSTR GetVariableString(int nLevel, VarType nVarType);
	int GetVariableLevel(LPCTSTR lpszVariable);
	static BOOL IsPossibleVariableString(LPCTSTR lpszVariable);
};
