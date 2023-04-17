#pragma once

class LoopIndexManager
{
public:
	enum {MaxLoopCount = 10};
	enum VariableType {Index_i, Index_ijk};
	enum NumericalType {
		Num_Int,
		Num_RegInt,
		Num_VolInt,
		Num_UInt,
		Num_RegUInt,
		Num_VolUInt
	};

protected:
	VariableType m_nVarType;
	NumericalType m_nNumType;

public:
	LoopIndexManager(VariableType nVarType, NumericalType nNumType = Num_VolInt);
	virtual ~LoopIndexManager(void) {}

	void SetVariableType(VariableType nVarType) {m_nVarType = nVarType;}
	LPTSTR GetIndexName(int nLevel) const;

	void SetNumericalType(NumericalType nNumType) {m_nNumType = nNumType;}
	LPTSTR GetNumericalType() const;
};
