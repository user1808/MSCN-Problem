#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "CTable.h"
#include "CMatrix.h"
#include "CMscnSolution.h"
#include "CRandom.h"
#include "CProblem.h"
#include "utils.h"

template <typename T> class CMscnProblem : public CProblem<T>
{
public:
	CMscnProblem();
	~CMscnProblem();

	int iGetDelivery() { return i_Delivery; }
	int iGetFactory() { return i_Factory; }
	int iGetWarehouse() { return i_Warehouse; }
	int iGetShop() { return i_Shop; }
	CMatrix<T> * pdGetCDCost() { return cdCost; }
	CMatrix<T> * pdGetCFCost() { return cfCost; }
	CMatrix<T> * pdGetCMCost() { return cmCost; }
	CTable<T> * pdGetSDCapacity() { return sdCapacity; }
	CTable<T> * pdGetSFCapacity() { return sfCapacity; }
	CTable<T> * pdGetSMCapacity() { return smCapacity; }
	CTable<T> * pdGetSSCapacity() { return ssCapacity; }
	CMatrix<T> * pdGetXDMin() { return xdMin; }
	CMatrix<T> * pdGetXDMax() { return xdMax; }
	CMatrix<T> * pdGetXFMin() { return xfMin; }
	CMatrix<T> * pdGetXFMax() { return xfMax; }
	CMatrix<T> * pdGetXMMin() { return xmMin; }
	CMatrix<T> * pdGetXMMax() { return xmMax; }

	bool bSetDelivery(int newD);
	bool bSetFactory(int newF);
	bool bSetWarehouse(int newW);
	bool bSetShop(int newS);

	bool bLoadFromFile(string fileName);
	bool bSaveToFile(string fileName);

	bool bConstraintsSatisfied(CSolution<T> * solution, bool & error);
	T dQetQuality(CSolution<T> * solution, bool & error);

	bool bGenerateRandomProblem(int iDelivery, int iFactory, int iWarehouse, int iShop);
	bool bGenerateInstance(int iInstanceSeed);

	CSolution<T> * csCreateSolution();
	bool bGenerateInstanceSolution(CSolution<T> * solution, CRandom * randomGenerator);
	void vRepairSolution(CSolution<T> * solution, CRandom * randomGenerator);
private:
	int i_Delivery, i_Factory, i_Warehouse, i_Shop; //ilosc dostawcow, fabryk, magazynow i sklepow
	CTable<T> *sdCapacity, *sfCapacity, *smCapacity, *ssCapacity; //moce produkcyjne w tablicy
	CMatrix<T> *cdCost, *cfCost, *cmCost; //koszty produkcji i dostawy w macierzach
	CTable<T> *udCost, *ufCost, *umCost; //koszty umowy w tablicy
	CTable<T> *pProfit; //zysk ze sklepu w tablicy
	CMatrix<T> *xdMin, *xdMax, *xfMin, *xfMax, *xmMin, *xmMax; //min i max z solution

	/*bool bSetDelivery(int newD);
	bool bSetFactory(int newF);
	bool bSetWarehouse(int newW);
	bool bSetShop(int newS);*/

	bool bSetCDCost(int iD, int iF, T dNewValue);
	bool bSetCFCost(int iF, int iM, T dNewValue);
	bool bSetCMCost(int iM, int iS, T dNewValue);

	bool bSetSDCapacity(int iD, T dNewValue);
	bool bSetSFCapacity(int iF, T dNewValue);
	bool bSetSMCapacity(int iW, T dNewValue);
	bool bSetSSCapacity(int iS, T dNewValue);

	bool bSetUDCost(int iD, T dNewValue);
	bool bSetUFCost(int iF, T dNewValue);
	bool bSetUMCost(int iM, T dNewValue);
	bool bSetPProfit(int iS, T dNewValue);

	bool bSetXDMin(int iD, int iF, T dNewValue);
	bool bSetXDMax(int iD, int iF, T dNewValue);
	bool bSetXFMin(int iF, int iM, T dNewValue);
	bool bSetXFMax(int iF, int iM, T dNewValue);
	bool bSetXMMin(int iM, int iS, T dNewValue);
	bool bSetXMMax(int iM, int iS, T dNewValue);

	bool bReadParameters(FILE * file);
	bool bSaveParameters(FILE * file);

	bool bCheckMinMax(CMatrix<T> * xxValues, CMatrix<T> * xxMin, CMatrix<T> * xxMax);

	bool bCheckProCap(CMatrix<T> * matrix, CTable<T> * table, int sizeX, int sizeY);
	bool bCheckMarkDemand(CMatrix<T> * matrix, CTable<T> * table, int sizeX, int sizeY);
	bool bCheckInOut(CMatrix<T> * matrix1, CMatrix<T> * matrix2);
	bool bCheckParameters(CMscnSolution<T> * solution);

	T dCalculateIncome(CMscnSolution<T> * pdSolution);
	T dCalculateKT(CMscnSolution<T> * pdSolution);
	T dCalculateKU(CMscnSolution<T> * pdSolution);

	T dCalculatePartOfCostKT(CMatrix<T> * matrix1, CMatrix<T> * matrix2);
	T dCalculatePartOfCostKU(CMatrix<T> * matrix, CTable<T> * table);

	bool bCheckMinMaxSolution(CMscnSolution<T> * solution);

	void vRepairMinMaxInMatrix(CMatrix<T> * matrixToRepair, CMatrix<T> * minMatrix, CMatrix<T> * maxMatrix);
	void vRepairProCap(CMatrix<T> * matrix, CTable<T> * table, int sizeX, int sizeY, CRandom * randomGenerator);
	void vRepairInOut(CMatrix<T> * matrix1, CMatrix<T> * matrix2, CRandom * randomGenerator);
	void vRepairMarkDemand(CMatrix<T> * matrix, CTable<T> * table, int sizeX, int sizeY, CRandom * randomGenerator);
};


template<typename T>
CMscnProblem<T>::CMscnProblem()
{
	sdCapacity = new CTable<T>("sd");
	sfCapacity = new CTable<T>("sf");
	smCapacity = new CTable<T>("sm");
	ssCapacity = new CTable<T>("ss");

	cdCost = new CMatrix<T>("cd");
	cfCost = new CMatrix<T>("cf");
	cmCost = new CMatrix<T>("cm");

	udCost = new CTable<T>("ud");
	ufCost = new CTable<T>("uf");
	umCost = new CTable<T>("um");

	pProfit = new CTable<T>("p");

	xdMin = new CMatrix<T>("xdMin");
	xdMax = new CMatrix<T>("xdMax");
	xfMin = new CMatrix<T>("xfMin");
	xfMax = new CMatrix<T>("xfMax");
	xmMin = new CMatrix<T>("xmMin");
	xmMax = new CMatrix<T>("xmMax");
}

template<typename T>
CMscnProblem<T>::~CMscnProblem()
{
	delete sdCapacity;
	delete sfCapacity;
	delete smCapacity;
	delete ssCapacity;

	delete cdCost;
	delete cfCost;
	delete cmCost;

	delete udCost;
	delete ufCost;
	delete umCost;

	delete pProfit;

	delete xdMin;
	delete xdMax;
	delete xfMin;
	delete xfMax;
	delete xmMin;
	delete xmMax;
}

template<typename T>
bool CMscnProblem<T>::bSetDelivery(int newD)
{
	if (newD > 0) {
		if (cdCost->bCreateNewMatrix(newD, cdCost->iGetSizeY(), cdCost->sGetName()) == MYERROR)
			return MYERROR;

		if (xdMin->bCreateNewMatrix(newD, xdMin->iGetSizeY(), xdMin->sGetName()) == MYERROR)
			return MYERROR;

		if (xdMax->bCreateNewMatrix(newD, xdMax->iGetSizeY(), xdMax->sGetName()) == MYERROR)
			return MYERROR;

		if (sdCapacity->bCreateNewTable(newD, sdCapacity->sGetName()) == MYERROR)
			return MYERROR;

		if (udCost->bCreateNewTable(newD, udCost->sGetName()) == MYERROR)
			return MYERROR;

		i_Delivery = newD;
		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<typename T>
bool CMscnProblem<T>::bSetFactory(int newF)
{
	if (newF > 0) {
		if (cdCost->bCreateNewMatrix(cdCost->iGetSizeX(), newF, cdCost->sGetName()) == MYERROR)
			return MYERROR;

		if (xdMin->bCreateNewMatrix(xdMin->iGetSizeX(), newF, xdMin->sGetName()) == MYERROR)
			return MYERROR;

		if (xdMax->bCreateNewMatrix(xdMax->iGetSizeX(), newF, xdMax->sGetName()) == MYERROR)
			return MYERROR;

		if (cfCost->bCreateNewMatrix(newF, cfCost->iGetSizeY(), cfCost->sGetName()) == MYERROR)
			return MYERROR;

		if (xfMin->bCreateNewMatrix(newF, xfMin->iGetSizeY(), xfMin->sGetName()) == MYERROR)
			return MYERROR;

		if (xfMax->bCreateNewMatrix(newF, xfMax->iGetSizeY(), xfMax->sGetName()) == MYERROR)
			return MYERROR;

		if (sfCapacity->bCreateNewTable(newF, sfCapacity->sGetName()) == MYERROR)
			return MYERROR;

		if (ufCost->bCreateNewTable(newF, ufCost->sGetName()) == MYERROR)
			return MYERROR;

		i_Factory = newF;

		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<typename T>
bool CMscnProblem<T>::bSetWarehouse(int newW)//Zmiana, ma zmieniaæ na bie¿¹co min i max
{
	if (newW > 0) {
		if (cfCost->bCreateNewMatrix(cfCost->iGetSizeX(), newW, cfCost->sGetName()) == MYERROR)
			return MYERROR;

		if (xfMin->bCreateNewMatrix(xfMin->iGetSizeX(), newW, xfMin->sGetName()) == MYERROR)
			return MYERROR;

		if (xfMax->bCreateNewMatrix(xfMax->iGetSizeX(), newW, xfMax->sGetName()) == MYERROR)
			return MYERROR;

		if (cmCost->bCreateNewMatrix(newW, cmCost->iGetSizeY(), cmCost->sGetName()) == MYERROR)
			return MYERROR;

		if (xmMin->bCreateNewMatrix(newW, xmMin->iGetSizeY(), xmMin->sGetName()) == MYERROR)
			return MYERROR;

		if (xmMax->bCreateNewMatrix(newW, xmMax->iGetSizeY(), xmMax->sGetName()) == MYERROR)
			return MYERROR;

		if (smCapacity->bCreateNewTable(newW, smCapacity->sGetName()) == MYERROR)
			return MYERROR;

		if (umCost->bCreateNewTable(newW, umCost->sGetName()) == MYERROR)
			return MYERROR;

		i_Warehouse = newW;

		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<typename T>
bool CMscnProblem<T>::bSetShop(int newS)//Zmiana, ma zmieniaæ na bie¿¹co min i max
{
	if (newS > 0) {
		if (cmCost->bCreateNewMatrix(cmCost->iGetSizeX(), newS, cmCost->sGetName()) == MYERROR)
			return MYERROR;

		if (xmMin->bCreateNewMatrix(xmMin->iGetSizeX(), newS, xmMin->sGetName()) == MYERROR)
			return MYERROR;

		if (xmMax->bCreateNewMatrix(xmMax->iGetSizeX(), newS, xmMax->sGetName()) == MYERROR)
			return MYERROR;

		if (ssCapacity->bCreateNewTable(newS, ssCapacity->sGetName()) == MYERROR)
			return MYERROR;

		if (pProfit->bCreateNewTable(newS, pProfit->sGetName()) == MYERROR)
			return MYERROR;

		i_Shop = newS;

		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<>
bool CMscnProblem<double>::bSetCDCost(int iD, int iF, double dNewValue)
{
	return cdCost->bSetValue(iD, iF, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetCDCost(int iD, int iF, int dNewValue)
{
	return cdCost->bSetValue(iD, iF, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetCDCost(int iD, int iF, T dNewValue)
{
	return cdCost->bSetValue(iD, iF, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetCFCost(int iF, int iM, double dNewValue)
{
	return cfCost->bSetValue(iF, iM, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetCFCost(int iF, int iM, int dNewValue)
{
	return cfCost->bSetValue(iF, iM, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetCFCost(int iF, int iM, T dNewValue)
{
	return cfCost->bSetValue(iF, iM, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetCMCost(int iM, int iS, double dNewValue)
{
	return cmCost->bSetValue(iM, iS, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetCMCost(int iM, int iS, int dNewValue)
{
	return cmCost->bSetValue(iM, iS, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetCMCost(int iM, int iS, T dNewValue)
{
	return cmCost->bSetValue(iM, iS, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetSDCapacity(int iD, double dNewValue)
{
	return sdCapacity->bSetValue(iD, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetSDCapacity(int iD, int dNewValue)
{
	return sdCapacity->bSetValue(iD, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetSDCapacity(int iD, T dNewValue)
{
	return sdCapacity->bSetValue(iD, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetSFCapacity(int iF, double dNewValue)
{
	return sfCapacity->bSetValue(iF, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetSFCapacity(int iF, int dNewValue)
{
	return sfCapacity->bSetValue(iF, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetSFCapacity(int iF, T dNewValue)
{
	return sfCapacity->bSetValue(iF, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetSMCapacity(int iW, double dNewValue)
{
	return smCapacity->bSetValue(iW, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetSMCapacity(int iW, int dNewValue)
{
	return smCapacity->bSetValue(iW, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetSMCapacity(int iW, T dNewValue)
{
	return smCapacity->bSetValue(iW, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetSSCapacity(int iS, double dNewValue)
{
	return ssCapacity->bSetValue(iS, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetSSCapacity(int iS, int dNewValue)
{
	return ssCapacity->bSetValue(iS, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetSSCapacity(int iS, T dNewValue)
{
	return ssCapacity->bSetValue(iS, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetUDCost(int iD, double dNewValue)
{
	return udCost->bSetValue(iD, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetUDCost(int iD, int dNewValue)
{
	return udCost->bSetValue(iD, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetUDCost(int iD, T dNewValue)
{
	return udCost->bSetValue(iD, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetUFCost(int iF, double dNewValue)
{
	return ufCost->bSetValue(iF, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetUFCost(int iF, int dNewValue)
{
	return ufCost->bSetValue(iF, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetUFCost(int iF, T dNewValue)
{
	return ufCost->bSetValue(iF, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetUMCost(int iM, double dNewValue)
{
	return umCost->bSetValue(iM, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetUMCost(int iM, int dNewValue)
{
	return umCost->bSetValue(iM, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetUMCost(int iM, T dNewValue)
{
	return umCost->bSetValue(iM, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetPProfit(int iS, double dNewValue)
{
	return pProfit->bSetValue(iS, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetPProfit(int iS, int dNewValue)
{
	return pProfit->bSetValue(iS, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetPProfit(int iS, T dNewValue)
{
	return pProfit->bSetValue(iS, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetXDMin(int iD, int iF, double dNewValue)
{
	return xdMin->bSetValue(iD, iF, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetXDMin(int iD, int iF, int dNewValue)
{
	return xdMin->bSetValue(iD, iF, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetXDMin(int iD, int iF, T dNewValue)
{
	return xdMin->bSetValue(iD, iF, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetXDMax(int iD, int iF, double dNewValue)
{
	return xdMax->bSetValue(iD, iF, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetXDMax(int iD, int iF, int dNewValue)
{
	return xdMax->bSetValue(iD, iF, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetXDMax(int iD, int iF, T dNewValue)
{
	return xdMax->bSetValue(iD, iF, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetXFMin(int iF, int iM, double dNewValue)
{
	return xfMin->bSetValue(iF, iM, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetXFMin(int iF, int iM, int dNewValue)
{
	return xfMin->bSetValue(iF, iM, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetXFMin(int iF, int iM, T dNewValue)
{
	return xfMin->bSetValue(iF, iM, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetXFMax(int iF, int iM, double dNewValue)
{
	return xfMax->bSetValue(iF, iM, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetXFMax(int iF, int iM, int dNewValue)
{
	return xfMax->bSetValue(iF, iM, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetXFMax(int iF, int iM, T dNewValue)
{
	return xfMax->bSetValue(iF, iM, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetXMMin(int iM, int iS, double dNewValue)
{
	return xmMin->bSetValue(iM, iS, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetXMMin(int iM, int iS, int dNewValue)
{
	return xmMin->bSetValue(iM, iS, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetXMMin(int iM, int iS, T dNewValue)
{
	return xmMin->bSetValue(iM, iS, dNewValue);
}

template<>
bool CMscnProblem<double>::bSetXMMax(int iM, int iS, double dNewValue)
{
	return xmMax->bSetValue(iM, iS, dNewValue);
}

template<>
bool CMscnProblem<int>::bSetXMMax(int iM, int iS, int dNewValue)
{
	return xmMax->bSetValue(iM, iS, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bSetXMMax(int iM, int iS, T dNewValue)
{
	return xmMax->bSetValue(iM, iS, dNewValue);
}

template<typename T>
bool CMscnProblem<T>::bLoadFromFile(string fileName)
{
	FILE * pd_file;

	pd_file = fopen(fileName.c_str(), "r");

	if (pd_file == NULL) {
		return MYERROR;
	}
	else {
		if (bReadParameters(pd_file) == MYERROR)
			return MYERROR;

		if (sdCapacity->bLoadFromFile(pd_file) == MYERROR)
			return MYERROR;
		if (sfCapacity->bLoadFromFile(pd_file) == MYERROR)
			return MYERROR;
		if (smCapacity->bLoadFromFile(pd_file) == MYERROR)
			return MYERROR;
		if (ssCapacity->bLoadFromFile(pd_file) == MYERROR)
			return MYERROR;

		if (cdCost->bLoadFromFile(pd_file) == MYERROR)
			return MYERROR;
		if (cfCost->bLoadFromFile(pd_file) == MYERROR)
			return MYERROR;
		if (cmCost->bLoadFromFile(pd_file) == MYERROR)
			return MYERROR;

		if (udCost->bLoadFromFile(pd_file) == MYERROR)
			return MYERROR;
		if (ufCost->bLoadFromFile(pd_file) == MYERROR)
			return MYERROR;
		if (umCost->bLoadFromFile(pd_file) == MYERROR)
			return MYERROR;
		if (pProfit->bLoadFromFile(pd_file) == MYERROR)
			return MYERROR;
		if (xdMin->bLoadFromFileForMinMax(pd_file, xdMax) == MYERROR)
			return MYERROR;
		if (xfMin->bLoadFromFileForMinMax(pd_file, xfMax) == MYERROR)
			return MYERROR;
		if (xmMin->bLoadFromFileForMinMax(pd_file, xmMax) == MYERROR)
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
bool CMscnProblem<T>::bSaveToFile(string fileName)
{
	FILE * pd_file;

	pd_file = fopen(fileName.c_str(), "w");

	if (pd_file == NULL) {
		return MYERROR;
	}
	else {
		if (bSaveParameters(pd_file) == MYERROR)
			return MYERROR;

		if (sdCapacity->bSaveToFile(pd_file) == MYERROR)
			return MYERROR;
		if (sfCapacity->bSaveToFile(pd_file) == MYERROR)
			return MYERROR;
		if (smCapacity->bSaveToFile(pd_file) == MYERROR)
			return MYERROR;
		if (ssCapacity->bSaveToFile(pd_file) == MYERROR)
			return MYERROR;

		if (cdCost->bSaveToFile(pd_file) == MYERROR)
			return MYERROR;
		if (cfCost->bSaveToFile(pd_file) == MYERROR)
			return MYERROR;
		if (cmCost->bSaveToFile(pd_file) == MYERROR)
			return MYERROR;

		if (udCost->bSaveToFile(pd_file) == MYERROR)
			return MYERROR;
		if (ufCost->bSaveToFile(pd_file) == MYERROR)
			return MYERROR;
		if (umCost->bSaveToFile(pd_file) == MYERROR)
			return MYERROR;
		if (pProfit->bSaveToFile(pd_file) == MYERROR)
			return MYERROR;

		if (xdMin->bSaveToFileForMinMax(pd_file, xdMax) == MYERROR)
			return MYERROR;
		if (xfMin->bSaveToFileForMinMax(pd_file, xfMax) == MYERROR)
			return MYERROR;
		if (xmMin->bSaveToFileForMinMax(pd_file, xmMax) == MYERROR)
			return MYERROR;


		if (fclose(pd_file) == 0)
			return MYNOERROR;
		else
			return MYERROR;
	}
}

template<typename T>
bool CMscnProblem<T>::bCheckMinMaxSolution(CMscnSolution<T> * pdSolution)
{
	return bCheckMinMax(pdSolution->pcGetXDValue(), xdMin, xdMax) && bCheckMinMax(pdSolution->pcGetXFValue(), xfMin, xfMax)
		&& bCheckMinMax(pdSolution->pcGetXMValue(), xmMin, xmMax);
}

template<typename T>
bool CMscnProblem<T>::bConstraintsSatisfied(CSolution<T> * solution, bool & error)
{
	CMscnSolution<T> * pdSolution = dynamic_cast<CMscnSolution<T> *>(solution);

	if (pdSolution->pcGetPDSolution() == NULL || bCheckParameters(pdSolution) == MYERROR || pdSolution->pcGetPDSolution()->iGetSize() != (i_Delivery * i_Factory + i_Factory * i_Warehouse + i_Warehouse * i_Shop)) {
		error = MYERROR;
		return MYERROR;
	}
	else {
		error = MYNOERROR;

		return bCheckProCap(pdSolution->pcGetXDValue(), sdCapacity, pdSolution->pcGetXDValue()->iGetSizeX(), pdSolution->pcGetXDValue()->iGetSizeY()) &&
			bCheckProCap(pdSolution->pcGetXFValue(), sfCapacity, pdSolution->pcGetXFValue()->iGetSizeX(), pdSolution->pcGetXFValue()->iGetSizeY()) &&
			bCheckProCap(pdSolution->pcGetXMValue(), smCapacity, pdSolution->pcGetXMValue()->iGetSizeX(), pdSolution->pcGetXMValue()->iGetSizeY()) &&
			bCheckMarkDemand(pdSolution->pcGetXMValue(), ssCapacity, pdSolution->pcGetXMValue()->iGetSizeY(), pdSolution->pcGetXMValue()->iGetSizeX()) &&
			bCheckInOut(pdSolution->pcGetXDValue(), pdSolution->pcGetXFValue()) && bCheckInOut(pdSolution->pcGetXFValue(), pdSolution->pcGetXMValue()) &&
			bCheckMinMaxSolution(pdSolution);
	}
}

template<typename T>
T CMscnProblem<T>::dQetQuality(CSolution<T> * solution, bool & error)
{
	CRandom * randomGenerator = new CRandom();
	while (bConstraintsSatisfied(solution, error) == MYERROR) {
		vRepairSolution(solution, randomGenerator);
	}
	delete randomGenerator;

	CMscnSolution<T> * pdSolution = dynamic_cast<CMscnSolution<T> *>(solution);

	double profit = dCalculateIncome(pdSolution) - dCalculateKT(pdSolution) - dCalculateKU(pdSolution);
	return profit;
}

template<typename T>
bool CMscnProblem<T>::bGenerateRandomProblem(int iDelivery, int iFactory, int iWarehouse, int iShop)
{
	if (bSetDelivery(iDelivery) == MYERROR)
		return MYERROR;
	if (bSetFactory(iFactory) == MYERROR)
		return MYERROR;
	if (bSetWarehouse(iWarehouse) == MYERROR)
		return MYERROR;
	if (bSetShop(iShop) == MYERROR)
		return MYERROR;

	return bGenerateInstance(time(NULL));
}

template<typename T>
bool CMscnProblem<T>::bGenerateInstance(int iInstanceSeed)
{
	CRandom * randomGenerator = new CRandom(iInstanceSeed);

	if (i_Factory > 0 && i_Delivery > 0 && i_Warehouse > 0 && i_Shop > 0) {
		if (cdCost->bFillWithRandom(CD_COST_MIN, CD_COST_MAX, randomGenerator) == MYERROR)
			return MYERROR;
		if (cfCost->bFillWithRandom(CF_COST_MIN, CF_COST_MAX, randomGenerator) == MYERROR)
			return MYERROR;
		if (cmCost->bFillWithRandom(CM_COST_MIN, CM_COST_MAX, randomGenerator) == MYERROR)
			return MYERROR;

		if (udCost->bFillWithRandom(UD_COST_MIN, UD_COST_MAX, randomGenerator) == MYERROR)
			return MYERROR;
		if (ufCost->bFillWithRandom(UF_COST_MIN, UF_COST_MAX, randomGenerator) == MYERROR)
			return MYERROR;
		if (umCost->bFillWithRandom(UM_COST_MIN, UM_COST_MAX, randomGenerator) == MYERROR)
			return MYERROR;

		if (sdCapacity->bFillWithRandom(SD_CAPACITY_MIN, SD_CAPACITY_MAX, randomGenerator) == MYERROR)
			return MYERROR;
		if (sfCapacity->bFillWithRandom(SF_CAPACITY_MIN, SF_CAPACITY_MAX, randomGenerator) == MYERROR)
			return MYERROR;
		if (smCapacity->bFillWithRandom(SM_CAPACITY_MIN, SM_CAPACITY_MAX, randomGenerator) == MYERROR)
			return MYERROR;
		if (ssCapacity->bFillWithRandom(SS_CAPACITY_MIN, SS_CAPACITY_MAX, randomGenerator) == MYERROR)
			return MYERROR;

		if (pProfit->bFillWithRandom(PROFIT_MIN, PROFIT_MAX, randomGenerator) == MYERROR)
			return MYERROR;

		if (xdMin->bFillWithRandom(XD_MINRES_MIN, XD_MINRES_MAX, randomGenerator) == MYERROR)
			return MYERROR;
		if (xdMax->bFillWithRandom(XD_MAXRES_MIN, XD_MAXRES_MAX, randomGenerator) == MYERROR)
			return MYERROR;

		if (xfMin->bFillWithRandom(XF_MINRES_MIN, XF_MINRES_MAX, randomGenerator) == MYERROR)
			return MYERROR;
		if (xfMax->bFillWithRandom(XF_MAXRES_MIN, XF_MAXRES_MAX, randomGenerator) == MYERROR)
			return MYERROR;

		if (xmMin->bFillWithRandom(XM_MINRES_MIN, XM_MINRES_MAX, randomGenerator) == MYERROR)
			return MYERROR;
		if (xmMax->bFillWithRandom(XM_MAXRES_MIN, XM_MAXRES_MAX, randomGenerator) == MYERROR)
			return MYERROR;

		delete randomGenerator;

		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<typename T>
CSolution<T> * CMscnProblem<T>::csCreateSolution()
{
	CMscnSolution<T> * tempsolution = new CMscnSolution<T>();

	tempsolution->bSetDelivery(i_Delivery);
	tempsolution->bSetFactory(i_Factory);
	tempsolution->bSetWarehouse(i_Warehouse);
	tempsolution->bSetShop(i_Shop);

	tempsolution->vCreatePdSolution();

	return tempsolution;
}

template<typename T>
bool CMscnProblem<T>::bGenerateInstanceSolution(CSolution<T> * solution, CRandom * randomGenerator)
{
	CMscnSolution<T> * pdSolution = dynamic_cast<CMscnSolution<T> *>(solution);
	if (pdSolution == nullptr) {
		return MYERROR;
	}

	if (i_Factory > 0 && i_Delivery > 0 && i_Warehouse > 0 && i_Shop > 0) {
		if (pdSolution->pcGetXDValue()->bFillWithRestrictions(pdGetXDMin(), pdGetXDMax(), randomGenerator) == MYERROR)
			return MYERROR;
		if (pdSolution->pcGetXFValue()->bFillWithRestrictions(pdGetXFMin(), pdGetXFMax(), randomGenerator) == MYERROR)
			return MYERROR;
		if (pdSolution->pcGetXMValue()->bFillWithRestrictions(pdGetXMMin(), pdGetXMMax(), randomGenerator) == MYERROR)
			return MYERROR;

		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<typename T>
void CMscnProblem<T>::vRepairSolution(CSolution<T> * solution, CRandom * randomGenerator)
{
	CMscnSolution<T> * pdSolution = dynamic_cast<CMscnSolution<T> *>(solution);

	if (bCheckMinMax(pdSolution->pcGetXDValue(), xdMin, xdMax) == MYERROR)
		vRepairMinMaxInMatrix(pdSolution->pcGetXDValue(), xdMin, xdMax);
	if (bCheckMinMax(pdSolution->pcGetXFValue(), xfMin, xfMax) == MYERROR)
		vRepairMinMaxInMatrix(pdSolution->pcGetXFValue(), xfMin, xfMax);
	if (bCheckMinMax(pdSolution->pcGetXMValue(), xmMin, xmMax) == MYERROR)
		vRepairMinMaxInMatrix(pdSolution->pcGetXMValue(), xmMin, xmMax);

	if (bCheckProCap(pdSolution->pcGetXDValue(), sdCapacity, pdSolution->pcGetXDValue()->iGetSizeX(), pdSolution->pcGetXDValue()->iGetSizeY()) == MYERROR) {
		vRepairProCap(pdSolution->pcGetXDValue(), sdCapacity, pdSolution->pcGetXDValue()->iGetSizeX(), pdSolution->pcGetXDValue()->iGetSizeY(), randomGenerator);
	}
	if (bCheckProCap(pdSolution->pcGetXFValue(), sfCapacity, pdSolution->pcGetXFValue()->iGetSizeX(), pdSolution->pcGetXFValue()->iGetSizeY()) == MYERROR) {
		vRepairProCap(pdSolution->pcGetXFValue(), sfCapacity, pdSolution->pcGetXFValue()->iGetSizeX(), pdSolution->pcGetXFValue()->iGetSizeY(), randomGenerator);
	}
	if (bCheckProCap(pdSolution->pcGetXMValue(), smCapacity, pdSolution->pcGetXMValue()->iGetSizeX(), pdSolution->pcGetXMValue()->iGetSizeY()) == MYERROR) {
		vRepairProCap(pdSolution->pcGetXMValue(), smCapacity, pdSolution->pcGetXMValue()->iGetSizeX(), pdSolution->pcGetXMValue()->iGetSizeY(), randomGenerator);
	}
	if (bCheckMarkDemand(pdSolution->pcGetXMValue(), ssCapacity, pdSolution->pcGetXMValue()->iGetSizeY(), pdSolution->pcGetXMValue()->iGetSizeX()) == MYERROR) {
		vRepairMarkDemand(pdSolution->pcGetXMValue(), ssCapacity, pdSolution->pcGetXMValue()->iGetSizeY(), pdSolution->pcGetXMValue()->iGetSizeX(), randomGenerator);
	}
	if (bCheckInOut(pdSolution->pcGetXDValue(), pdSolution->pcGetXFValue()) == MYERROR) {
		vRepairInOut(pdSolution->pcGetXDValue(), pdSolution->pcGetXFValue(), randomGenerator);
	}
	if (bCheckInOut(pdSolution->pcGetXFValue(), pdSolution->pcGetXMValue()) == MYERROR) {
		vRepairInOut(pdSolution->pcGetXFValue(), pdSolution->pcGetXMValue(), randomGenerator);
	}
}

template<typename T>
bool CMscnProblem<T>::bReadParameters(FILE * file)
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
bool CMscnProblem<T>::bSaveParameters(FILE * file)
{
	if (file == NULL) {
		return MYERROR;
	}
	else {
		if (fprintf(file, "D %d\n", i_Delivery) == 0)
			return MYERROR;
		if (fprintf(file, "F %d\n", i_Factory) == 0)
			return MYERROR;
		if (fprintf(file, "M %d\n", i_Warehouse) == 0)
			return MYERROR;
		if (fprintf(file, "S %d\n", i_Shop) == 0)
			return MYERROR;

		return MYNOERROR;
	}
}

template<typename T>
bool CMscnProblem<T>::bCheckMinMax(CMatrix<T> * xxValues, CMatrix<T> * xxMin, CMatrix<T> * xxMax)
{
	double value;
	for (int i = 0; i < xxValues->iGetSizeX(); i++) {
		for (int j = 0; j < xxValues->iGetSizeY(); j++) {
			value = xxValues->dGetValue(i, j);
			if (value > xxMax->dGetValue(i, j) || value < xxMin->dGetValue(i, j))
				return MYERROR;
		}
	}

	return MYNOERROR;
}

template<typename T>
bool CMscnProblem<T>::bCheckProCap(CMatrix<T> * matrix, CTable<T> * table, int sizeX, int sizeY)
{
	double sum;
	for (int i = 0; i < sizeX; i++) {
		sum = 0;
		for (int j = 0; j < sizeY; j++) {
			sum += matrix->dGetValue(i, j);
		}
		if (sum > table->dGetValue(i))
			return MYERROR;
	}
	return MYNOERROR;
}

template<typename T>
bool CMscnProblem<T>::bCheckMarkDemand(CMatrix<T> * matrix, CTable<T> * table, int sizeY, int sizeX)
{
	double sum;
	for (int i = 0; i < sizeY; i++) {
		sum = 0;
		for (int j = 0; j < sizeX; j++) {
			sum += matrix->dGetValue(j, i);
		}
		if (sum > table->dGetValue(i))
			return MYERROR;
	}
	return MYNOERROR;
}

template<typename T>
bool CMscnProblem<T>::bCheckInOut(CMatrix<T> * matrix1, CMatrix<T> * matrix2)
{
	double sumOut;
	double sumIn;

	for (int i = 0; i < matrix1->iGetSizeY(); i++) {
		sumOut = 0;
		sumIn = 0;
		for (int j = 0; j < matrix1->iGetSizeX(); j++) {
			sumOut += matrix1->dGetValue(j, i);
		}
		for (int j = 0; j < matrix2->iGetSizeY(); j++) {
			sumIn += matrix2->dGetValue(i, j);
		}
		if (sumIn > sumOut) {
			return MYERROR;
		}
	}
	return MYNOERROR;
}

template<typename T>
bool CMscnProblem<T>::bCheckParameters(CMscnSolution<T> * pdSolution)
{

	if (i_Delivery == pdSolution->iGetDelivery() && i_Factory == pdSolution->iGetFactory() && i_Warehouse == pdSolution->iGetWarehouse() && i_Shop == pdSolution->iGetShop())
		return MYNOERROR;
	else
		return MYERROR;
}

template<>
double CMscnProblem<double>::dCalculateIncome(CMscnSolution<double> * pdSolution)
{

	double income = 0;
	double elem = 0;
	for (int i = 0; i < pProfit->iGetSize(); i++) {
		for (int j = 0; j < pdSolution->pcGetXMValue()->iGetSizeX(); j++) {
			elem += pdSolution->pcGetXMValue()->dGetValue(j, i);
		}
		elem *= pProfit->dGetValue(i);
		income += elem;
		elem = 0;
	}
	return income;
}

template<>
int CMscnProblem<int>::dCalculateIncome(CMscnSolution<int> * pdSolution)
{

	double income = 0;
	double elem = 0;
	for (int i = 0; i < pProfit->iGetSize(); i++) {
		for (int j = 0; j < pdSolution->pcGetXMValue()->iGetSizeX(); j++) {
			elem += pdSolution->pcGetXMValue()->dGetValue(j, i);
		}
		elem *= pProfit->dGetValue(i);
		income += elem;
		elem = 0;
	}
	return income;
}

template<typename T>
T CMscnProblem<T>::dCalculateIncome(CMscnSolution<T> * pdSolution)
{

	double income = 0;
	double elem = 0;
	for (int i = 0; i < pProfit->iGetSize(); i++) {
		for (int j = 0; j < pdSolution->pcGetXMValue()->iGetSizeX(); j++) {
			elem += pdSolution->pcGetXMValue()->dGetValue(j, i);
		}
		elem *= pProfit->dGetValue(i);
		income += elem;
		elem = 0;
	}
	return income;
}

template<>
double CMscnProblem<double>::dCalculateKT(CMscnSolution<double> * pdSolution)
{
	double cost = 0;
	cost += dCalculatePartOfCostKT(cdCost, pdSolution->pcGetXDValue());
	cost += dCalculatePartOfCostKT(cfCost, pdSolution->pcGetXFValue());
	cost += dCalculatePartOfCostKT(cmCost, pdSolution->pcGetXMValue());
	return cost;
}

template<>
int CMscnProblem<int>::dCalculateKT(CMscnSolution<int> * pdSolution)
{
	double cost = 0;
	cost += dCalculatePartOfCostKT(cdCost, pdSolution->pcGetXDValue());
	cost += dCalculatePartOfCostKT(cfCost, pdSolution->pcGetXFValue());
	cost += dCalculatePartOfCostKT(cmCost, pdSolution->pcGetXMValue());
	return cost;
}

template<typename T>
T CMscnProblem<T>::dCalculateKT(CMscnSolution<T> * pdSolution)
{
	double cost = 0;
	cost += dCalculatePartOfCostKT(cdCost, pdSolution->pcGetXDValue());
	cost += dCalculatePartOfCostKT(cfCost, pdSolution->pcGetXFValue());
	cost += dCalculatePartOfCostKT(cmCost, pdSolution->pcGetXMValue());
	return cost;
}

template<>
double CMscnProblem<double>::dCalculateKU(CMscnSolution<double> * pdSolution)
{
	double cost = 0;

	cost += dCalculatePartOfCostKU(pdSolution->pcGetXDValue(), udCost);
	cost += dCalculatePartOfCostKU(pdSolution->pcGetXFValue(), ufCost);
	cost += dCalculatePartOfCostKU(pdSolution->pcGetXMValue(), umCost);

	return cost;
}

template<>
int CMscnProblem<int>::dCalculateKU(CMscnSolution<int> * pdSolution)
{
	double cost = 0;

	cost += dCalculatePartOfCostKU(pdSolution->pcGetXDValue(), udCost);
	cost += dCalculatePartOfCostKU(pdSolution->pcGetXFValue(), ufCost);
	cost += dCalculatePartOfCostKU(pdSolution->pcGetXMValue(), umCost);

	return cost;
}

template<typename T>
T CMscnProblem<T>::dCalculateKU(CMscnSolution<T> * pdSolution)
{
	double cost = 0;

	cost += dCalculatePartOfCostKU(pdSolution->pcGetXDValue(), udCost);
	cost += dCalculatePartOfCostKU(pdSolution->pcGetXFValue(), ufCost);
	cost += dCalculatePartOfCostKU(pdSolution->pcGetXMValue(), umCost);

	return cost;
}

template<>
double CMscnProblem<double>::dCalculatePartOfCostKT(CMatrix<double> * matrix1, CMatrix<double> * matrix2)
{
	double result = 0;

	for (int i = 0; i < matrix1->iGetSizeX(); i++) {
		for (int j = 0; j < matrix1->iGetSizeY(); j++) {
			result += (matrix1->dGetValue(i, j) * matrix2->dGetValue(i, j));
		}
	}

	return result;
}

template<>
int CMscnProblem<int>::dCalculatePartOfCostKT(CMatrix<int> * matrix1, CMatrix<int> * matrix2)
{
	double result = 0;

	for (int i = 0; i < matrix1->iGetSizeX(); i++) {
		for (int j = 0; j < matrix1->iGetSizeY(); j++) {
			result += (matrix1->dGetValue(i, j) * matrix2->dGetValue(i, j));
		}
	}

	return result;
}

template<typename T>
T CMscnProblem<T>::dCalculatePartOfCostKT(CMatrix<T> * matrix1, CMatrix<T> * matrix2)
{
	double result = 0;

	for (int i = 0; i < matrix1->iGetSizeX(); i++) {
		for (int j = 0; j < matrix1->iGetSizeY(); j++) {
			result += (matrix1->dGetValue(i, j) * matrix2->dGetValue(i, j));
		}
	}

	return result;
}

template<>
double CMscnProblem<double>::dCalculatePartOfCostKU(CMatrix<double> * matrix, CTable<double> * table)
{
	double amount = 0;
	double cost = 0;
	for (int i = 0; i < table->iGetSize(); i++) {
		for (int j = 0; j < matrix->iGetSizeY(); j++) {
			amount += matrix->dGetValue(i, j);
		}
		if (amount > 0) {
			cost += table->dGetValue(i);
		}
		amount = 0;
	}
	return cost;
}

template<>
int CMscnProblem<int>::dCalculatePartOfCostKU(CMatrix<int> * matrix, CTable<int> * table)
{
	double amount = 0;
	double cost = 0;
	for (int i = 0; i < table->iGetSize(); i++) {
		for (int j = 0; j < matrix->iGetSizeY(); j++) {
			amount += matrix->dGetValue(i, j);
		}
		if (amount > 0) {
			cost += table->dGetValue(i);
		}
		amount = 0;
	}
	return cost;
}

template<typename T>
T CMscnProblem<T>::dCalculatePartOfCostKU(CMatrix<T> * matrix, CTable<T> * table)
{
	double amount = 0;
	double cost = 0;
	for (int i = 0; i < table->iGetSize(); i++) {
		for (int j = 0; j < matrix->iGetSizeY(); j++) {
			amount += matrix->dGetValue(i, j);
		}
		if (amount > 0) {
			cost += table->dGetValue(i);
		}
		amount = 0;
	}
	return cost;
}

template<typename T>
void CMscnProblem<T>::vRepairMinMaxInMatrix(CMatrix<T> * matrixToRepair, CMatrix<T> * minMatrix, CMatrix<T> * maxMatrix)
{
	double minimum;
	double maximum;
	double valueToCheck;
	for (int i = 0; i < matrixToRepair->iGetSizeX(); i++) {
		for (int j = 0; j < matrixToRepair->iGetSizeY(); j++) {
			minimum = minMatrix->dGetValue(i, j);
			maximum = maxMatrix->dGetValue(i, j);
			valueToCheck = matrixToRepair->dGetValue(i, j);
			if (valueToCheck > maximum) {
				matrixToRepair->bSetValue(i, j, maximum);
			}
			if (valueToCheck < minimum) {
				matrixToRepair->bSetValue(i, j, minimum);
			}
		}
	}
}

template<>
void CMscnProblem<double>::vRepairProCap(CMatrix<double> * matrix, CTable<double> * table, int sizeX, int sizeY, CRandom * randomGenerator)
{
	double sum;
	double difference;
	double max;
	double minus;
	int y;

	for (int i = 0; i < sizeX; i++) {
		sum = 0;
		for (int j = 0; j < sizeY; j++) {
			sum += matrix->dGetValue(i, j);
		}
		max = table->dGetValue(i);
		if (sum > max) {
			difference = sum - table->dGetValue(i);
			minus = difference / sizeY;
			while (difference > 0) {
				y = randomGenerator->iGenerateRandomPositiveInt(0, sizeY);
				difference -= minus;
				matrix->bSetValue(i, y, matrix->dGetValue(i, y) - minus);
			}
		}
	}
}

template<>
void CMscnProblem<int>::vRepairProCap(CMatrix<int> * matrix, CTable<int> * table, int sizeX, int sizeY, CRandom * randomGenerator)
{
	double sum;
	double difference;
	double max;
	double minus;
	int y;

	for (int i = 0; i < sizeX; i++) {
		sum = 0;
		for (int j = 0; j < sizeY; j++) {
			sum += matrix->dGetValue(i, j);
		}
		max = table->dGetValue(i);
		if (sum > max) {
			difference = sum - table->dGetValue(i);
			minus = 1;
			while (difference > 0) {
				y = randomGenerator->iGenerateRandomPositiveInt(0, sizeY);
				difference -= minus;
				matrix->bSetValue(i, y, matrix->dGetValue(i, y) - minus);
			}
		}
	}
}

template<typename T>
void CMscnProblem<T>::vRepairProCap(CMatrix<T> * matrix, CTable<T> * table, int sizeX, int sizeY, CRandom * randomGenerator)
{
	double sum;
	double difference;
	double max;
	double minus;
	int y;

	for (int i = 0; i < sizeX; i++) {
		sum = 0;
		for (int j = 0; j < sizeY; j++) {
			sum += matrix->dGetValue(i, j);
		}
		max = table->dGetValue(i);
		if (sum > max) {
			difference = sum - table->dGetValue(i);
			minus = difference / sizeY;
			while (difference > 0) {
				y = randomGenerator->iGenerateRandomPositiveInt(0, sizeY);
				difference -= minus;
				matrix->bSetValue(i, y, matrix->dGetValue(i, y) - minus);
			}
		}
	}
}

template<>
void CMscnProblem<double>::vRepairInOut(CMatrix<double> * matrix1, CMatrix<double> * matrix2, CRandom * randomGenerator)
{
	double sumOut;
	double sumIn;
	double difference;
	double minus;
	int y;

	for (int i = 0; i < matrix1->iGetSizeY(); i++) {
		sumOut = 0;
		sumIn = 0;
		for (int j = 0; j < matrix1->iGetSizeX(); j++) {
			sumOut += matrix1->dGetValue(j, i);
		}
		for (int j = 0; j < matrix2->iGetSizeY(); j++) {
			sumIn += matrix2->dGetValue(i, j);
		}
		if (sumIn > sumOut) {
			difference = sumIn - sumOut;
			minus = difference / matrix2->iGetSizeY();
			while (difference > 0) {
				y = randomGenerator->iGenerateRandomPositiveInt(0, matrix2->iGetSizeY());
				difference -= minus;
				matrix2->bSetValue(i, y, matrix2->dGetValue(i, y) - minus);
			}
		}
	}
}

template<>
void CMscnProblem<int>::vRepairInOut(CMatrix<int> * matrix1, CMatrix<int> * matrix2, CRandom * randomGenerator)
{
	double sumOut;
	double sumIn;
	double difference;
	double minus;
	int y;

	for (int i = 0; i < matrix1->iGetSizeY(); i++) {
		sumOut = 0;
		sumIn = 0;
		for (int j = 0; j < matrix1->iGetSizeX(); j++) {
			sumOut += matrix1->dGetValue(j, i);
		}
		for (int j = 0; j < matrix2->iGetSizeY(); j++) {
			sumIn += matrix2->dGetValue(i, j);
		}
		if (sumIn > sumOut) {
			difference = sumIn - sumOut;
			minus = 1;
			while (difference > 0) {
				y = randomGenerator->iGenerateRandomPositiveInt(0, matrix2->iGetSizeY());
				difference -= minus;
				matrix2->bSetValue(i, y, matrix2->dGetValue(i, y) - minus);
			}
		}
	}
}

template<typename T>
void CMscnProblem<T>::vRepairInOut(CMatrix<T> * matrix1, CMatrix<T> * matrix2, CRandom * randomGenerator)
{
	double sumOut;
	double sumIn;
	double difference;
	double minus;
	int y;

	for (int i = 0; i < matrix1->iGetSizeY(); i++) {
		sumOut = 0;
		sumIn = 0;
		for (int j = 0; j < matrix1->iGetSizeX(); j++) {
			sumOut += matrix1->dGetValue(j, i);
		}
		for (int j = 0; j < matrix2->iGetSizeY(); j++) {
			sumIn += matrix2->dGetValue(i, j);
		}
		if (sumIn > sumOut) {
			difference = sumIn - sumOut;
			minus = difference / matrix2->iGetSizeY();
			while (difference > 0) {
				y = randomGenerator->iGenerateRandomPositiveInt(0, matrix2->iGetSizeY());
				difference -= minus;
				matrix2->bSetValue(i, y, matrix2->dGetValue(i, y) - minus);
			}
		}
	}
}

template<>
void CMscnProblem<double>::vRepairMarkDemand(CMatrix<double> * matrix, CTable<double> * table, int sizeY, int sizeX, CRandom * randomGenerator)
{
	double sum;
	double difference;
	double max;
	double minus;
	int x;

	for (int i = 0; i < sizeY; i++) {
		sum = 0;
		for (int j = 0; j < sizeX; j++) {
			sum += matrix->dGetValue(j, i);
		}
		max = table->dGetValue(i);
		if (sum > max) {
			difference = sum - table->dGetValue(i);
			minus = difference / sizeY;
			while (difference > 0) {
				x = randomGenerator->iGenerateRandomPositiveInt(0, sizeX);
				difference -= minus;
				matrix->bSetValue(x, i, matrix->dGetValue(x, i) - minus);
			}
		}
	}
}

template<>
void CMscnProblem<int>::vRepairMarkDemand(CMatrix<int> * matrix, CTable<int> * table, int sizeY, int sizeX, CRandom * randomGenerator)
{
	double sum;
	double difference;
	double max;
	double minus;
	int x;

	for (int i = 0; i < sizeY; i++) {
		sum = 0;
		for (int j = 0; j < sizeX; j++) {
			sum += matrix->dGetValue(j, i);
		}
		max = table->dGetValue(i);
		if (sum > max) {
			difference = sum - table->dGetValue(i);
			minus = difference / sizeY;
			while (difference > 0) {
				x = randomGenerator->iGenerateRandomPositiveInt(0, sizeX);
				difference -= minus;
				matrix->bSetValue(x, i, matrix->dGetValue(x, i) - minus);
			}
		}
	}
}

template<typename T>
void CMscnProblem<T>::vRepairMarkDemand(CMatrix<T> * matrix, CTable<T> * table, int sizeY, int sizeX, CRandom * randomGenerator)
{
	double sum;
	double difference;
	double max;
	double minus;
	int x;

	for (int i = 0; i < sizeY; i++) {
		sum = 0;
		for (int j = 0; j < sizeX; j++) {
			sum += matrix->dGetValue(j, i);
		}
		max = table->dGetValue(i);
		if (sum > max) {
			difference = sum - table->dGetValue(i);
			minus = difference / sizeY;
			while (difference > 0) {
				x = randomGenerator->iGenerateRandomPositiveInt(0, sizeX);
				difference -= minus;
				matrix->bSetValue(x, i, matrix->dGetValue(x, i) - minus);
			}
		}
	}
}