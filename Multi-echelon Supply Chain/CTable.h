#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "utils.h"
#include <string>
#include <iostream>
#include "CRandom.h"
using namespace std;

template <typename T> class CTable
{
public:
	CTable();
	CTable(string sNewName);
	CTable(int size, string sNewName);
	~CTable();

	T dGetValue(int x);
	bool bSetValue(int x, T newValue);
	bool bCreateNewTable(int size, string newName);

	T* pdGetTable() { return t_tab; }

	int iGetSize() { return i_size; }
	string sGetName() { return s_name; }

	bool bLoadFromFile(FILE * file);
	bool bSaveToFile(FILE * file);

	bool bFillWithRandom(T dMin, T dMax, CRandom * randomGenerator);

	bool bCopy(CTable * other);
private:
	string s_name;
	T* t_tab;
	int i_size;
};

template <typename T>
CTable<T>::CTable()
{
	i_size = 0;
}

template <typename T>
CTable<T>::CTable(string sNewName)
{
	s_name = sNewName;
	i_size = 0;
}

template <typename T>
CTable<T>::CTable(int size, string sNewName)
{
	bCreateNewTable(size, sNewName);
}

template <typename T>
CTable<T>::~CTable()
{
	delete t_tab;
}

template<>
double CTable<double>::dGetValue(int x)
{
	if (x >= 0 && x < i_size) {
		return t_tab[x];
	}
}

template<>
int CTable<int>::dGetValue(int x)
{
	if (x >= 0 && x < i_size) {
		return t_tab[x];
	}
}

template<typename T>
T CTable<T>::dGetValue(int x)
{
	if (x >= 0 && x < i_size) {
		return t_tab[x];
	}
}

template<>
bool CTable<double>::bSetValue(int x, double newValue)
{
	if (x >= 0 && x < i_size && newValue >= 0) {
		t_tab[x] = newValue;
		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<>
bool CTable<int>::bSetValue(int x, int newValue)
{
	if (x >= 0 && x < i_size && newValue >= 0) {
		t_tab[x] = newValue;
		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<typename T>
bool CTable<T>::bSetValue(int x, T newValue)
{
	if (x >= 0 && x < i_size && newValue >= 0) {
		t_tab[x] = newValue;
		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<>
bool CTable<double>::bCreateNewTable(int size, string newName)
{
	if (size > 0) {
		if (i_size > 0) {
			delete t_tab;
		}
		s_name = newName;

		i_size = size;
		t_tab = new double[i_size];
		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<>
bool CTable<int>::bCreateNewTable(int size, string newName)
{
	if (size > 0) {
		if (i_size > 0) {
			delete t_tab;
		}
		s_name = newName;

		i_size = size;
		t_tab = new int[i_size];
		return MYNOERROR;
	}
	else {
		return MYERROR;
	}
}

template<typename T>
bool CTable<T>::bLoadFromFile(FILE * file)
{
	char line[LINE_LENGTH];

	if (file == NULL) {
		return MYERROR;
	}
	else {
		fgets(line, LINE_LENGTH, file);
		if (fgets(line, LINE_LENGTH, file) != NULL) {
			char* subtab = strtok(line, " \n");
			for (int i = 0; i < i_size; i++) {
				if (subtab != NULL && bSetValue(i, atof(subtab))) {
					subtab = strtok(NULL, " \n");
				}
				else {
					return MYERROR;
				}
			}
			return MYNOERROR;
		}
		else {
			return MYERROR;
		}
	}
}

template<>
bool CTable<double>::bSaveToFile(FILE * file)
{
	if (file == NULL) {
		return MYERROR;
	}
	else {
		if (fprintf(file, s_name.c_str()) == 0)
			return MYERROR;
		if (fprintf(file, "\n") == 0)
			return MYERROR;
		for (int i = 0; i < i_size; i++) {
			if (fprintf(file, "%f ", dGetValue(i)) == 0)
				return MYERROR;
		}
		if (fprintf(file, "\n") == 0)
			return MYERROR;
		return MYNOERROR;
	}
}

template<>
bool CTable<int>::bSaveToFile(FILE * file)
{
	if (file == NULL) {
		return MYERROR;
	}
	else {
		if (fprintf(file, s_name.c_str()) == 0)
			return MYERROR;
		if (fprintf(file, "\n") == 0)
			return MYERROR;
		for (int i = 0; i < i_size; i++) {
			if (fprintf(file, "%d ", dGetValue(i)) == 0)
				return MYERROR;
		}
		if (fprintf(file, "\n") == 0)
			return MYERROR;
		return MYNOERROR;
	}
}

template<typename T>
bool CTable<T>::bSaveToFile(FILE * file)
{
	if (file == NULL) {
		return MYERROR;
	}
	else {
		if (fprintf(file, s_name.c_str()) == 0)
			return MYERROR;
		if (fprintf(file, "\n") == 0)
			return MYERROR;
		for (int i = 0; i < i_size; i++) {
			if (fprintf(file, "%f ", dGetValue(i)) == 0)
				return MYERROR;
		}
		if (fprintf(file, "\n") == 0)
			return MYERROR;
		return MYNOERROR;
	}
}

template<>
bool CTable<double>::bFillWithRandom(double dMin, double dMax, CRandom * randomGenerator)
{
	for (int i = 0; i < i_size; i++) {
		if (bSetValue(i, randomGenerator->dGenerateRandomPositiveDouble(dMin, dMax)) == MYERROR) {
			return MYERROR;
		}
	}
	return MYNOERROR;
}

template<>
bool CTable<int>::bFillWithRandom(int dMin, int dMax, CRandom * randomGenerator)
{
	for (int i = 0; i < i_size; i++) {
		if (bSetValue(i, randomGenerator->iGenerateRandomPositiveInt(dMin, dMax)) == MYERROR) {
			return MYERROR;
		}
	}
	return MYNOERROR;
}

template<typename T>
bool CTable<T>::bFillWithRandom(T dMin, T dMax, CRandom * randomGenerator)
{
	for (int i = 0; i < i_size; i++) {
		if (bSetValue(i, randomGenerator->iGenerateRandomPositiveInt(dMin, dMax)) == MYERROR) {
			return MYERROR;
		}
	}
	return MYNOERROR;
}

template<typename T>
bool CTable<T>::bCopy(CTable * other)
{
	for (int i = 0; i < iGetSize(); i++) {
		if (bSetValue(i, other->dGetValue(i)) == MYERROR)
			return MYERROR;
	}

	return MYNOERROR;
}
