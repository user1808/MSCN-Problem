#pragma once
#include "pch.h"
#include "CSolution.h"
#include "CRandom.h"
template <typename T> class CProblem
{
public:
	CProblem() {};
	virtual ~CProblem() {};

	virtual bool bLoadFromFile(string fileName)=0;
	virtual bool bSaveToFile(string fileName)=0;

	virtual CSolution<T> * csCreateSolution()=0;
	virtual bool bGenerateInstanceSolution(CSolution<T> * solution, CRandom * randomGenerator)=0;
	virtual bool bConstraintsSatisfied(CSolution<T> * solution, bool & error)=0;
	virtual T dQetQuality(CSolution<T> * solution, bool & error)=0;
	virtual void vRepairSolution(CSolution<T> * solution, CRandom * randomGenerator)=0;
};

