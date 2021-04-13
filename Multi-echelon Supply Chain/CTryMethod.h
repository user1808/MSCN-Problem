#pragma once
#include "pch.h"
#include "COptimizer.h"

template<typename T> class CTryMethod : public COptimizer<T>
{
public:
	CTryMethod();
	~CTryMethod();

	bool bSolveProblem(CProblem<T> * cpProblem);
private:
	CProblem<T> * problem;
	CSolution<T> * solution;
};

template<typename T>
CTryMethod<T>::CTryMethod()
{
}

template<typename T>
CTryMethod<T>::~CTryMethod()
{
	delete solution;
}

template<typename T>
bool CTryMethod<T>::bSolveProblem(CProblem<T> * cpProblem)
{
	problem = cpProblem;
	solution = problem->csCreateSolution();

	for (int i = 0; i < solution->iGetSizeSolution(); i++) {
		if (solution->pcGetPDSolution()->bSetValue(i, i) == MYERROR)
			return MYERROR;
	}

	return solution->bSaveToFile("123solution.txt");
}