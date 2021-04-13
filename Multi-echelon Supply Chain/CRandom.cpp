#include "pch.h"
#include <stdlib.h>
#include "CRandom.h"

int CRandom::iGenerateRandomPositiveInt(int iMin, int iMax)
{
	if (iMin <= iMax && iMin >= 0) {
		return iMin + rand() % iMax;
	}
	else {
		return -1;
	}
}

double CRandom::dGenerateRandomPositiveDouble(double dMin, double dMax)
{
	if (dMin <= dMax && dMin >= 0) {
		double number = (double)rand() / RAND_MAX;
		return dMin + number * (dMax - dMin);
	}
	else {
		return -1;
	}
}
