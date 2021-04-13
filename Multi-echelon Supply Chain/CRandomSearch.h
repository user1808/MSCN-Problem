#pragma once
#include "pch.h"
#include "utils.h"
#include "CMscnProblem.h"
#include "CTimer.h"
#include "COptimizer.h"

template<typename T> class CRandomSearch : public COptimizer<T>
{
public:
	CRandomSearch();
	CRandomSearch(int iTimeInSeconds);
	~CRandomSearch();

	bool bSolveProblem(CProblem<T> * problem);
private:
	CProblem<T> * problem;
	CSolution<T> * solution;
	int duration;

	bool bStartProgram();
};

template<typename T>
CRandomSearch<T>::CRandomSearch()
{
	duration = TIME;
}

template<typename T>
CRandomSearch<T>::CRandomSearch(int iTimeInSeconds)
{
	if (iTimeInSeconds > 0) {
		duration = iTimeInSeconds;
	}
	else {
		duration = TIME;
	}
}

template<typename T>
CRandomSearch<T>::~CRandomSearch()
{
	delete solution;
}

template<typename T>
bool CRandomSearch<T>::bSolveProblem(CProblem<T> * cpProblem)
{
	problem = cpProblem;
	solution = problem->csCreateSolution();

	return bStartProgram();
}

template<typename T>
bool CRandomSearch<T>::bStartProgram()
{
	CRandom * randomGenerator = new CRandom(time(NULL));
	CTimer timer;

	int i = 0;
	double maxProfit = 0;
	double newProfit = 0;
	bool error;

	timer.vStart(duration);
	while (timer.iTimeisOver() != 0) {

		if (problem->bGenerateInstanceSolution(solution, randomGenerator) == MYERROR)
			return MYERROR;

		newProfit = problem->dQetQuality(solution, error);
		if (newProfit > maxProfit) {
			if (solution->bSaveToFile("randomsolution.txt") == MYERROR)
				return MYERROR;

			maxProfit = newProfit;
			i++;
			cout << i << " " << maxProfit << "\n";
		}
	}

	delete randomGenerator;

	return MYNOERROR;
}