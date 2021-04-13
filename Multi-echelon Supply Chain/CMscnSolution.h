#pragma once
#include "pch.h"
#include "CMatrix.h"
#include "CTable.h"
#include "CRandom.h"
#include "CSolution.h"
#include "utils.h"

template<typename T> class CMscnSolution : public CSolution<T>
{
public:
	CMscnSolution();
	CMscnSolution(CMscnSolution & other);
	~CMscnSolution();

	int iGetDelivery() { return iDelivery; }
	int iGetFactory() { return iFactory; }
	int iGetWarehouse() { return iWarehouse; }
	int iGetShop() { return iShop; }

	int iGetSizeSolution() { return size_solution; }

	CMatrix<T> * pcGetXDValue() { return xdValues; }
	CMatrix<T> * pcGetXFValue() { return xfValues; }
	CMatrix<T> * pcGetXMValue() { return xmValues; }

	double dGetXDValue(int iD, int iF) { return xdValues->dGetValue(iD, iF); }
	double dGetXFValue(int iF, int iM) { return xfValues->dGetValue(iF, iM); }
	double dGetXMValue(int iM, int iS) { return xmValues->dGetValue(iM, iS); }

	bool bSetDelivery(int newD);
	bool bSetFactory(int newF);
	bool bSetWarehouse(int newW);
	bool bSetShop(int newS);

	CTable<T> * pcGetPDSolution() { return pdSolution; }

	bool bLoadFromFile(string fileName);
	bool bSaveToFile(string fileName);

	void vCreatePdSolution();

	void operator=(CSolution<T> & other);
private:
	int iDelivery;
	int iFactory;
	int iWarehouse;
	int iShop;

	CMatrix<T> *xdValues;
	CMatrix<T> *xfValues;
	CMatrix<T> *xmValues;

	CTable<T> *pdSolution;
	int size_solution;

	bool bSetXDValue(int iD, int iF, double newValue) { return xdValues->bSetValue(iD, iF, newValue); }
	bool bSetXFValue(int iF, int iM, double newValue) { return xfValues->bSetValue(iF, iM, newValue); }
	bool bSetXMValue(int iM, int iS, double newValue) { return xmValues->bSetValue(iM, iS, newValue); }

	bool bReadParameters(FILE * file);
	bool bSaveParameters(FILE * file);

	void vAllocMatrix();
};

template<typename T>
CMscnSolution<T>::CMscnSolution()
{
}

template<typename T>
CMscnSolution<T>::CMscnSolution(CMscnSolution & other)
{
	bSetDelivery(other.iGetDelivery());
	bSetFactory(other.iGetFactory());
	bSetWarehouse(other.iGetWarehouse());
	bSetShop(other.iGetShop());

	vCreatePdSolution();
}

template<typename T>
CMscnSolution<T>::~CMscnSolution()
{
	delete xdValues;
	delete xfValues;
	delete xmValues;

	delete pdSolution;
}

template<typename T>
bool CMscnSolution<T>::bSetDelivery(int newD)
{
	if (newD > 0) {
		iDelivery = newD;
		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<typename T>
bool CMscnSolution<T>::bSetFactory(int newF)
{
	if (newF > 0) {
		iFactory = newF;
		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<typename T>
bool CMscnSolution<T>::bSetWarehouse(int newW)
{
	if (newW > 0) {
		iWarehouse = newW;
		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<typename T>
bool CMscnSolution<T>::bSetShop(int newS)
{
	if (newS > 0) {
		iShop = newS;
		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<typename T>
void CMscnSolution<T>::vCreatePdSolution()
{
	if (pdSolution != NULL) {
		delete pdSolution;
		delete xdValues;
		delete xfValues;
		delete xmValues;
	}

	size_solution = iDelivery * iFactory + iFactory * iWarehouse + iWarehouse * iShop;
	pdSolution = new CTable<T>(size_solution, "solution");

	vAllocMatrix();
}

template<typename T>
void CMscnSolution<T>::operator=(CSolution<T> & other)
{
	CMscnSolution * solution = dynamic_cast<CMscnSolution *>(&other);

	bSetDelivery(solution->iGetDelivery());
	bSetFactory(solution->iGetFactory());
	bSetWarehouse(solution->iGetWarehouse());
	bSetShop(solution->iGetShop());

	vCreatePdSolution();

	pdSolution->bCopy(other.pcGetPDSolution());
}

template<typename T>
bool CMscnSolution<T>::bReadParameters(FILE * file)
{
	char line[LINE_LENGTH];

	if (file == NULL) {
		return MYERROR;
	}
	else {
		if (fgets(line, LINE_LENGTH, file) != NULL) {
			char* subtab = strtok(line, " \n");
			subtab = strtok(NULL, " \n");
			if (subtab == NULL || bSetDelivery(subtab[0] - '0') == MYERROR) {
				return MYERROR;
			}
		}
		else {
			return MYERROR;
		}
		if (fgets(line, LINE_LENGTH, file) != NULL) {
			char* subtab = strtok(line, " \n");
			subtab = strtok(NULL, " \n");
			if (subtab == NULL || bSetFactory(subtab[0] - '0') == MYERROR) {
				return MYERROR;
			}
		}
		else {
			return MYERROR;
		}
		if (fgets(line, LINE_LENGTH, file) != NULL) {
			char* subtab = strtok(line, " \n");
			subtab = strtok(NULL, " \n");
			if (subtab == NULL || bSetWarehouse(subtab[0] - '0') == MYERROR) {
				return MYERROR;
			}
		}
		else {
			return MYERROR;
		}
		if (fgets(line, LINE_LENGTH, file) != NULL) {
			char* subtab = strtok(line, " \n");
			subtab = strtok(NULL, " \n");
			return subtab != NULL && bSetShop(subtab[0] - '0');
		}
		else {
			return MYERROR;
		}
	}
}

template<typename T>
bool CMscnSolution<T>::bSaveParameters(FILE * file)
{
	if (file == NULL) {
		return MYERROR;
	}
	else {
		if (fprintf(file, "D %d\n", iDelivery) == 0)
			return MYERROR;
		if (fprintf(file, "F %d\n", iFactory) == 0)
			return MYERROR;
		if (fprintf(file, "M %d\n", iWarehouse) == 0)
			return MYERROR;
		if (fprintf(file, "S %d\n", iShop) == 0)
			return MYERROR;

		return MYNOERROR;
	}
}

template<typename T>
void CMscnSolution<T>::vAllocMatrix()
{
	xdValues = new CMatrix<T>(*pdSolution, iDelivery, iFactory, 0, "xd");
	xfValues = new CMatrix<T>(*pdSolution, iFactory, iWarehouse, iDelivery * iFactory, "xf");
	xmValues = new CMatrix<T>(*pdSolution, iWarehouse, iShop, iDelivery * iFactory + iFactory * iWarehouse, "xm");
}

template<typename T>
bool CMscnSolution<T>::bLoadFromFile(string fileName)
{
	FILE * pd_file;

	pd_file = fopen(fileName.c_str(), "r");

	if (pd_file == NULL) {
		return MYERROR;
	}
	else {
		if (bReadParameters(pd_file) == MYERROR)
			return MYERROR;

		vCreatePdSolution();

		if (xdValues->bLoadFromFile(pd_file) == MYERROR)
			return MYERROR;
		if (xfValues->bLoadFromFile(pd_file) == MYERROR)
			return MYERROR;
		if (xmValues->bLoadFromFile(pd_file) == MYERROR)
			return MYERROR;

		if (fclose(pd_file) == 0) {
			return MYNOERROR;
		}
		else {
			return MYERROR;
		}
	}
}

template<typename T>
bool CMscnSolution<T>::bSaveToFile(string fileName)
{
	FILE * pd_file;

	pd_file = fopen(fileName.c_str(), "w");

	if (pd_file == NULL) {
		return MYERROR;
	}
	else {
		if (bSaveParameters(pd_file) == MYERROR)
			return MYERROR;

		if (xdValues->bSaveToFile(pd_file) == MYERROR)
			return MYERROR;
		if (xfValues->bSaveToFile(pd_file) == MYERROR)
			return MYERROR;
		if (xmValues->bSaveToFile(pd_file) == MYERROR)
			return MYERROR;

		if (fclose(pd_file) == 0)
			return MYNOERROR;
		else
			return MYERROR;
	}
}