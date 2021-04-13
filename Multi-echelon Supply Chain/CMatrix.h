#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include <string>
#include <iostream>
#include "CRandom.h"
#include "CTable.h"
#include "pch.h"
using namespace std;

template<typename T> class CMatrix
{
public:
	CMatrix();
	CMatrix(string sNewName);
	CMatrix(int x, int y, string sNewName);
	CMatrix(CTable<T> & pdTable, int x, int y, int iOffset, string sNewName);
	~CMatrix();

	bool bSetValue(int x, int y, T newValue);
	T dGetValue(int x, int y);
	bool bCreateNewMatrix(int x, int y, string sNewName);

	int iGetSizeX() { return i_size_x; }
	int iGetSizeY() { return i_size_y; }
	string sGetName() { return s_name; }

	bool bLoadFromFile(FILE * file);
	bool bLoadFromFileForMinMax(FILE * file, CMatrix * maxMatrix);
	bool bSaveToFile(FILE * file);
	bool bSaveToFileForMinMax(FILE * file, CMatrix * maxMatrix);

	bool bFillWithRandom(T dMin, T dMax, CRandom * randomGenerator);
	bool bFillWithRestrictions(CMatrix * minRestrictions, CMatrix * maxRestrictions, CRandom * randomGenerator);

	bool bCopy(CMatrix * other);
private:
	string s_name;
	int i_size_x;
	int i_size_y;
	bool bMatrixFillingTable;

	T **d_matrix;
};

template<typename T>
CMatrix<T>::CMatrix()
{
	i_size_x = 0;
	i_size_y = 0;
	bMatrixFillingTable = false;
}

template<typename T>
CMatrix<T>::CMatrix(string sNewName)
{
	s_name = sNewName;
	i_size_x = 0;
	i_size_y = 0;
	bMatrixFillingTable = false;
}

template<typename T>
CMatrix<T>::CMatrix(int x, int y, string sNewName)
{
	bCreateNewMatrix(x, y, s_name);
	bMatrixFillingTable = false;
}

template<>
CMatrix<double>::CMatrix(CTable<double> & pdTable, int x, int y, int iOffset, string sNewName)
{
	s_name = sNewName;
	i_size_x = x;
	i_size_y = y;
	bMatrixFillingTable = true;
	d_matrix = new double*[x];
	d_matrix[0] = pdTable.pdGetTable() + iOffset;
	for (int i = 1; i < x; i++) {
		d_matrix[i] = d_matrix[i - 1] + y;
	}
}

template<>
CMatrix<int>::CMatrix(CTable<int> & piTable, int x, int y, int iOffset, string sNewName)
{
	s_name = sNewName;
	i_size_x = x;
	i_size_y = y;
	bMatrixFillingTable = true;
	d_matrix = new int*[x];
	d_matrix[0] = piTable.pdGetTable() + iOffset;
	for (int i = 1; i < x; i++) {
		d_matrix[i] = d_matrix[i - 1] + y;
	}
}

template<typename T>
CMatrix<T>::CMatrix(CTable<T> & ptTable, int x, int y, int iOffset, string sNewName)
{
	s_name = sNewName;
	i_size_x = x;
	i_size_y = y;
	bMatrixFillingTable = true;
	d_matrix = new T*[x];
	d_matrix[0] = ptTable.pdGetTable() + iOffset;
	for (int i = 1; i < x; i++) {
		d_matrix[i] = d_matrix[i - 1] + y;
	}
}

template<typename T>
CMatrix<T>::~CMatrix()
{
	if (bMatrixFillingTable) {
		delete d_matrix;
	}
	else {
		for (int i = 0; i < i_size_x; i++) {
			delete d_matrix[i];
		}
		delete d_matrix;
	}
}

template<>
bool CMatrix<double>::bSetValue(int x, int y, double d_newValue)
{
	if (x < i_size_x && x >= 0 && y < i_size_y && y >= 0 && d_newValue >= 0) {
		d_matrix[x][y] = d_newValue;
		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<>
bool CMatrix<int>::bSetValue(int x, int y, int i_newValue)
{
	if (x < i_size_x && x >= 0 && y < i_size_y && y >= 0 && i_newValue >= 0) {
		d_matrix[x][y] = i_newValue;
		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<typename T>
bool CMatrix<T>::bSetValue(int x, int y, T t_newValue)
{
	if (x < i_size_x && x >= 0 && y < i_size_y && y >= 0 && t_newValue >= 0) {
		d_matrix[x][y] = t_newValue;
		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<>
double CMatrix<double>::dGetValue(int x, int y)
{
	if (x < i_size_x && x >= 0 && y < i_size_y && y >= 0) {
		return d_matrix[x][y];
	}
}

template<>
int CMatrix<int>::dGetValue(int x, int y)
{
	if (x < i_size_x && x >= 0 && y < i_size_y && y >= 0) {
		return d_matrix[x][y];
	}
}

template<typename T>
T CMatrix<T>::dGetValue(int x, int y)
{
	if (x < i_size_x && x >= 0 && y < i_size_y && y >= 0) {
		return d_matrix[x][y];
	}
}

template<>
bool CMatrix<double>::bCreateNewMatrix(int x, int y, string sNewName)
{
	if (x >= 0 && y >= 0) {
		if (i_size_x > 0) {
			for (int i = 0; i < i_size_x; i++) {
				delete d_matrix[i];
			}
			delete d_matrix;
		}

		s_name = sNewName;

		d_matrix = new double*[x];
		for (int i = 0; i < x; i++) {
			d_matrix[i] = new double[y];
		}

		i_size_x = x;
		i_size_y = y;

		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<>
bool CMatrix<int>::bCreateNewMatrix(int x, int y, string sNewName)
{
	if (x >= 0 && y >= 0) {
		if (i_size_x > 0) {
			for (int i = 0; i < i_size_x; i++) {
				delete d_matrix[i];
			}
			delete d_matrix;
		}

		s_name = sNewName;

		d_matrix = new int*[x];
		for (int i = 0; i < x; i++) {
			d_matrix[i] = new int[y];
		}

		i_size_x = x;
		i_size_y = y;

		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<typename T>
bool CMatrix<T>::bCreateNewMatrix(int x, int y, string sNewName)
{
	if (x >= 0 && y >= 0) {
		if (i_size_x > 0) {
			for (int i = 0; i < i_size_x; i++) {
				delete d_matrix[i];
			}
			delete d_matrix;
		}

		s_name = sNewName;

		d_matrix = new T*[x];
		for (int i = 0; i < x; i++) {
			d_matrix[i] = new T[y];
		}

		i_size_x = x;
		i_size_y = y;

		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<typename T>
bool CMatrix<T>::bLoadFromFile(FILE * file)
{
	char line[LINE_LENGTH];

	if (file == NULL)
		return MYERROR;
	else {
		fgets(line, LINE_LENGTH, file);
		for (int i = 0; i < i_size_x; i++) {
			if (fgets(line, LINE_LENGTH, file) != NULL) {
				char* subtab = strtok(line, " \n");
				for (int j = 0; j < i_size_y; j++) {
					if (subtab != NULL && bSetValue(i, j, atof(subtab))) {
						subtab = strtok(NULL, " \n");
					}
					else {
						return MYERROR;
					}
				}
			}
			else {
				return MYERROR;
			}
		}
		return MYNOERROR;
	}
}

template<typename T>
bool CMatrix<T>::bLoadFromFileForMinMax(FILE * file, CMatrix * maxMatrix)
{
	char line[LINE_LENGTH];

	if (file == NULL)
		return MYERROR;
	else {
		fgets(line, LINE_LENGTH, file);
		for (int i = 0; i < i_size_x; i++) {
			if (fgets(line, LINE_LENGTH, file) != NULL) {
				char* subtab = strtok(line, " \n");
				for (int j = 0; j < i_size_y; j++) {
					if (subtab != NULL && bSetValue(i, j, atof(subtab))) {
						subtab = strtok(NULL, " \n");
					}
					else {
						return MYERROR;
					}

					if (subtab != NULL && maxMatrix->bSetValue(i, j, atof(subtab))) {
						subtab = strtok(NULL, " \n");
					}
					else {
						return MYERROR;
					}
				}
			}
			else {
				return MYERROR;
			}
		}
		return MYNOERROR;
	}
}

template<>
bool CMatrix<double>::bSaveToFile(FILE * file)
{
	if (file == NULL) {
		return MYERROR;
	}
	else {
		if (fprintf(file, s_name.c_str()) == 0)
			return MYERROR;
		if (fprintf(file, "\n") == 0)
			return MYERROR;
		for (int i = 0; i < i_size_x; i++) {
			for (int j = 0; j < i_size_y; j++) {
				if (fprintf(file, "%f ", dGetValue(i, j)) == 0) {
					return MYERROR;
				}
			}
			if (fprintf(file, "\n") == 0)
				return MYERROR;
		}
		return MYNOERROR;
	}
}

template<>
bool CMatrix<int>::bSaveToFile(FILE * file)
{
	if (file == NULL) {
		return MYERROR;
	}
	else {
		if (fprintf(file, s_name.c_str()) == 0)
			return MYERROR;
		if (fprintf(file, "\n") == 0)
			return MYERROR;
		for (int i = 0; i < i_size_x; i++) {
			for (int j = 0; j < i_size_y; j++) {
				if (fprintf(file, "%d ", dGetValue(i, j)) == 0) {
					return MYERROR;
				}
			}
			if (fprintf(file, "\n") == 0)
				return MYERROR;
		}
		return MYNOERROR;
	}
}

template<typename T>
bool CMatrix<T>::bSaveToFile(FILE * file)
{
	if (file == NULL) {
		return MYERROR;
	}
	else {
		if (fprintf(file, s_name.c_str()) == 0)
			return MYERROR;
		if (fprintf(file, "\n") == 0)
			return MYERROR;
		for (int i = 0; i < i_size_x; i++) {
			for (int j = 0; j < i_size_y; j++) {
				if (fprintf(file, "%f ", dGetValue(i, j)) == 0) {
					return MYERROR;
				}
			}
			if (fprintf(file, "\n") == 0)
				return MYERROR;
		}
		return MYNOERROR;
	}
}

template<typename T>
bool CMatrix<T>::bSaveToFileForMinMax(FILE * file, CMatrix * maxMatrix)
{
	if (file == NULL) {
		return MYERROR;
	}
	else {
		if (fprintf(file, s_name.c_str()) == 0)
			return MYERROR;
		if (fprintf(file, "\n") == 0)
			return MYERROR;
		for (int i = 0; i < i_size_x; i++) {
			for (int j = 0; j < i_size_y; j++) {
				if (fprintf(file, "%f ", dGetValue(i, j)) == 0) {
					return MYERROR;
				}

				if (fprintf(file, "%f ", maxMatrix->dGetValue(i, j)) == 0) {
					return MYERROR;
				}
			}
			if (fprintf(file, "\n") == 0)
				return MYERROR;
		}
		return MYNOERROR;
	}
}

template<typename T>
bool CMatrix<T>::bFillWithRandom(T dMin, T dMax, CRandom * randomGenerator)
{
	for (int i = 0; i < i_size_x; i++) {
		for (int j = 0; j < i_size_y; j++) {
			if (bSetValue(i, j, randomGenerator->dGenerateRandomPositiveDouble(dMin, dMax)) == MYERROR) {
				return MYERROR;
			}
		}
	}
	return MYNOERROR;
}

template<>
bool CMatrix<int>::bFillWithRandom(int dMin, int dMax, CRandom * randomGenerator)
{
	for (int i = 0; i < i_size_x; i++) {
		for (int j = 0; j < i_size_y; j++) {
			if (bSetValue(i, j, randomGenerator->iGenerateRandomPositiveInt(dMin, dMax)) == MYERROR) {
				return MYERROR;
			}
		}
	}
	return MYNOERROR;
}

template<typename T>
bool CMatrix<T>::bFillWithRestrictions(CMatrix * minRestrictions, CMatrix * maxRestrictions, CRandom * randomGenerator)
{
	for (int i = 0; i < i_size_x; i++) {
		for (int j = 0; j < i_size_y; j++) {
			if (bSetValue(i, j, randomGenerator->dGenerateRandomPositiveDouble(minRestrictions->dGetValue(i, j), maxRestrictions->dGetValue(i, j))) == MYERROR) {
				return MYERROR;
			}
		}
	}
	return MYNOERROR;
}

template<>
bool CMatrix<int>::bFillWithRestrictions(CMatrix * minRestrictions, CMatrix * maxRestrictions, CRandom * randomGenerator)
{
	for (int i = 0; i < i_size_x; i++) {
		for (int j = 0; j < i_size_y; j++) {
			if (bSetValue(i, j, randomGenerator->iGenerateRandomPositiveInt(minRestrictions->dGetValue(i, j), maxRestrictions->dGetValue(i, j))) == MYERROR) {
				return MYERROR;
			}
		}
	}
	return MYNOERROR;
}

template<typename T>
bool CMatrix<T>::bCopy(CMatrix * other)
{
	for (int i = 0; i < iGetSizeX(); i++) {
		for (int j = 0; j < iGetSizeY(); j++) {
			if (bSetValue(i, j, other->dGetValue(i, j)) == MYERROR)
				return MYERROR;
		}
	}

	return MYNOERROR;
}
