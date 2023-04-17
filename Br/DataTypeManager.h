#pragma once

#include "DataType.h"

class DataTypeManager
{
protected:
	struct {
		int size;
		LPTSTR name;
		LPTSTR name2;
	} m_dataType[DataType::TypeCount];

public:
	DataTypeManager(void);
	virtual ~DataTypeManager(void);

};
