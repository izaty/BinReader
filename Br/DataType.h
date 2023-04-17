#pragma once

#include "UndoObject.h"

class DataType : public UndoObject
{
public:
	enum Type {
		TypeInt = 0,
		TypeFloat,
		TypeDouble,
		TypeChar,
		TypeLong,
		TypeShort,
		TypeByte,
		TypeCount
	};
protected:
	Type m_nType;

	static struct TypeInfo {
		int size;
		LPTSTR phpsize;
		LPTSTR name;
		LPTSTR name2;
		LPTSTR name3;
	} m_stInfo[TypeCount];

public:
	DataType(Type nType = TypeInt);
	virtual ~DataType(void);

	void SetType(Type nType, class UndoList *U = NULL);
	Type GetType() const {return m_nType;}

	int GetSize() const;

	LPTSTR GetPHPSizeString() const;

	LPTSTR GetTypeString() const;
	LPTSTR GetTypeStringAndBlank() const;

	LPTSTR GetTypeString2() const;
	LPTSTR GetTypeStringAndBlank2() const;

	LPTSTR GetTypeString3() const;

	//BOOL IsOneByte() const
	//	{return ((m_nType == TypeChar) || (m_nType == TypeByte));}
	BOOL IsOneByte() const {return (GetSize(m_nType) == 1);}

	static Type GetType(int nIndex);
	static int GetSize(Type nType);
	static LPTSTR GetPHPSizeString(Type nType);
	static LPTSTR GetTypeString(Type nType);
	static LPTSTR GetTypeStringAndBlank(Type nType);
	static LPTSTR GetTypeString2(Type nType);
	static LPTSTR GetTypeStringAndBlank2(Type nType);
	static LPTSTR GetTypeString3(Type nType);

	static void SetSize(Type nType, int nSize);

protected:
	struct UndoData {
		Type type;
	};

public:
	virtual void ExeUndo(void *pPara);
	virtual void DelUndo(void *pPara);
};
