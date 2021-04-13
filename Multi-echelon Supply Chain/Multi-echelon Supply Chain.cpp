#include "pch.h"
#include "CMscnProblem.h"
#include "CRandom.h"
#include "CMscnSolution.h"
#include "CRandomSearch.h"
#include "CDiffEvol.h"
#include "CTryMethod.h" 
#include <iostream>

void test() {
	bool error;
	CMscnProblem<double> problem;
	CMscnSolution<double> solution;
	if (problem.bLoadFromFile("readyproblem.txt") && solution.bLoadFromFile("bestsolution.txt")) {
		//problem.bSaveToFile("saveFileProblem.txt");
		//solution.bSaveToFile("saveFileSolution.txt");
		cout << "Czy rozwiazanie spelnia ograniczenia? ";
		if (problem.bConstraintsSatisfied(&solution, error)) {
			cout << "Tak/true\n";
		}
		else {
			cout << "Nie/false\n";
		}
		if (error == MYERROR) {
			cout << "Rozwiazanie jest technicznie zle!!!\n";
		}
		else {
			cout << "Zysk/Strata: " << problem.dQetQuality(&solution, error) << "\n";
		}
	}
	else {
		cout << "Niezgodnosc w plikach wejsciowych. Dane wejsciowe sa niepoprawne\n\n";
	}
}

void test1() {
	CProblem<double> * problem = new CMscnProblem<double>();
	problem->bLoadFromFile("readyproblem.txt");

	COptimizer<double> * evol = new CDiffEvol<double>(20, 0.5, 0.7, 50000);
	evol->bSolveProblem(problem);

	COptimizer<double> * search = new CRandomSearch<double>(5);
	search->bSolveProblem(problem);

	COptimizer<double> * random = new CTryMethod<double>();
	random->bSolveProblem(problem);

	delete evol;
	delete search;
	delete random;
	delete problem;
}

int main() {
	test1();
}
