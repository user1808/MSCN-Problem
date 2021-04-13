#pragma once
#include "pch.h"
#include "utils.h"
#include "CMscnProblem.h"
#include "CRandom.h"
#include "COptimizer.h"

template<typename T> class CDiffEvol : public COptimizer<T>
{
public:
	CDiffEvol();
	CDiffEvol(int iPopulation, double dDiffWeight, double dCrossProb, int iNumberOfIteration);
	~CDiffEvol();

	bool bSolveProblem(CProblem<T> * problem);
private:
	CSolution<T> ** population;
	int iNumOfPopulation;
	int iNumOfFitnessCall;
	double dDiffWeight;
	double dCrossProb;
	int iNumberOfIteration;

	CProblem<T> * problem;

	void vSetDiffWeight(double dNewDiffWeight) { dDiffWeight = dNewDiffWeight; }
	void vSetCrossProb(double dNewCrossProb) { dCrossProb = dNewCrossProb; }
	void vSetNumOfIteration(int iNewNumOfIteration) { iNumberOfIteration = iNewNumOfIteration; }

	bool bStartProgram();

	bool bInitPopulation(CRandom * randomGenerator);

	bool bIndividulasAreDifferent(CSolution<T> * first, CSolution<T> * second, CSolution<T> * third, CSolution<T> * fourth);

	void vShowPopuation();

	void vFitness(CSolution<T> * indNew, CSolution<T> * ind);
};


template<typename T>
CDiffEvol<T>::CDiffEvol()
{
	iNumOfPopulation = DEFAULT_POPULATION;
	iNumOfFitnessCall = 0;
	dDiffWeight = MIN_DIFF_WEIGHT;
	dCrossProb = CROSS_PROB;
	iNumberOfIteration = NUMBER_OF_ITERATION;
}

template<typename T>
CDiffEvol<T>::CDiffEvol(int iPopulation, double dDiffWeight, double dCrossProb, int iNumberOfIteration)
{
	if (iPopulation > MIN_POPULATION) {
		iNumOfPopulation = iPopulation;
	}
	else {
		iNumOfPopulation = DEFAULT_POPULATION;
	}

	iNumOfFitnessCall = 0;

	if (dDiffWeight >= MIN_DIFF_WEIGHT && dDiffWeight <= MAX_DIFF_WEIGHT) {
		vSetDiffWeight(dDiffWeight);
	}
	else {
		vSetDiffWeight(MIN_DIFF_WEIGHT);
	}

	if (dCrossProb > 0 && dCrossProb < 1) {
		vSetCrossProb(dCrossProb);
	}
	else {
		vSetCrossProb(CROSS_PROB);
	}

	if (iNumberOfIteration > 0) {
		vSetNumOfIteration(iNumberOfIteration);
	}
	else {
		vSetNumOfIteration(NUMBER_OF_ITERATION);
	}
}

template<typename T>
CDiffEvol<T>::~CDiffEvol()
{
	for (int i = 0; i < iNumOfPopulation; i++) {
		delete population[i];
	}
	delete population;
}

template<typename T>
bool CDiffEvol<T>::bSolveProblem(CProblem<T> * cpProblem)
{
	problem = cpProblem;

	population = new CSolution<T>*[iNumOfPopulation];

	for (int i = 0; i < iNumOfPopulation; i++) {
		population[i] = problem->csCreateSolution();
	}

	return bStartProgram();
}

template<typename T>
bool CDiffEvol<T>::bStartProgram()
{
	CRandom * randomGenerator = new CRandom(time(NULL));

	if (bInitPopulation(randomGenerator) == MYERROR)
		return MYERROR;

	CSolution<T> * baseInd;
	CSolution<T> * addInd0;
	CSolution<T> * addInd1;
	CSolution<T> * indNew = problem->csCreateSolution();

	int i = 0;
	bool error;
	while (iNumOfFitnessCall <= iNumberOfIteration) {
		for (int j = 0; j < iNumOfPopulation; j++) {
			*indNew = *population[j];
			baseInd = population[randomGenerator->iGenerateRandomPositiveInt(0, iNumOfPopulation)];
			addInd0 = population[randomGenerator->iGenerateRandomPositiveInt(0, iNumOfPopulation)];
			addInd1 = population[randomGenerator->iGenerateRandomPositiveInt(0, iNumOfPopulation)];

			if (bIndividulasAreDifferent(population[j], baseInd, addInd0, addInd1) == MYNOERROR) {
				for (int geneOffset = 0; geneOffset < indNew->iGetSizeSolution(); geneOffset++) {
					if (randomGenerator->dGenerateRandomPositiveDouble(0, 1) < dCrossProb) {
						indNew->pcGetPDSolution()->bSetValue(geneOffset,
							baseInd->pcGetPDSolution()->dGetValue(geneOffset) +
							dDiffWeight *
							(addInd0->pcGetPDSolution()->dGetValue(geneOffset) - addInd1->pcGetPDSolution()->dGetValue(geneOffset)));
					}
				}

				vFitness(indNew, population[j]);
			}
		}
		//cout << iNumOfFitnessCall << "\n";
	}

	delete indNew;

	delete randomGenerator;

	vShowPopuation();

	return MYNOERROR;
}

template<typename T>
bool CDiffEvol<T>::bInitPopulation(CRandom * randomGenerator)
{
	int i = 0;
	bool error;
	while (i != iNumOfPopulation) {

		if (problem->bGenerateInstanceSolution(population[i], randomGenerator) == MYERROR)
			return MYERROR;

		i++;
	}

	return MYNOERROR;
}

template<typename T>
bool CDiffEvol<T>::bIndividulasAreDifferent(CSolution<T> * first, CSolution<T> * second, CSolution<T> * third, CSolution<T> * fourth)
{
	if (first != second && first != third && first != fourth && second != third && second != fourth && third != fourth)
		return MYNOERROR;

	return MYERROR;
}

template<typename T>
void CDiffEvol<T>::vShowPopuation()
{
	bool error;
	double dBestProfit = 0;
	double profit = 0;
	int indexOfBestSolution = 0;
	for (int i = 0; i < iNumOfPopulation; i++) {
		profit = problem->dQetQuality(population[i], error);
		cout << i << " " << profit << "\n";
		if (profit > dBestProfit) {
			dBestProfit = profit;
			indexOfBestSolution = i;
		}
	}

	cout << "Najlepsze rozwiazanie: " << indexOfBestSolution << " " << dBestProfit << "\n";

	if (population[indexOfBestSolution]->bSaveToFile("bestsolution.txt") == MYERROR)
		cout << "Zapis sie nie udal\n";
}

template<typename T>
void CDiffEvol<T>::vFitness(CSolution<T> * indNew, CSolution<T> * ind)
{
	iNumOfFitnessCall++;
	bool error;
	if (problem->dQetQuality(indNew, error) >= problem->dQetQuality(ind, error)) {
		*ind = *indNew;
	}
}

