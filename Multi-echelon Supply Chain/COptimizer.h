#pragma once
#include "utils.h"
#include "CProblem.h"
template<typename T> class COptimizer
{
public:
	COptimizer() {};
	virtual ~COptimizer() {};

	virtual bool bSolveProblem(CProblem<T> * problem)=0;
};

