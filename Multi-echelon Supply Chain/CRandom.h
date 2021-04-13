#pragma once
#include "pch.h"
#include <time.h>
class CRandom
{
public:
	CRandom() {};
	CRandom(int iSeed) { srand(iSeed); }
	~CRandom() {};

	int iGenerateRandomPositiveInt(int iMin, int iMax);
	double dGenerateRandomPositiveDouble(double iMin, double iMax);
};

