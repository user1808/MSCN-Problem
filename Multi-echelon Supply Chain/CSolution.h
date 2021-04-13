#pragma once
#include "CTable.h"
template<typename T> class CSolution
{
public:
	CSolution() {};
	virtual ~CSolution() {};

	virtual bool bLoadFromFile(string fileName)=0;
	virtual bool bSaveToFile(string fileName)=0;

	virtual void vCreatePdSolution() = 0;
	virtual CTable<T> * pcGetPDSolution() = 0;
	virtual int iGetSizeSolution() = 0;

	virtual void operator=(CSolution<T> & other) = 0;
};

