// Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <tchar.h>
#include <map>
#include <list>
#include <cmath>
#include <Time.h>

//task 1
#pragma region task1

DWORD GetNumberOfPositiveValues(int * values, int size)
{
	FILETIME prevoius, current;
	DWORD countPositive = 0;
	GetSystemTimePreciseAsFileTime(&prevoius);
	for (int i = 0; i < size; i++)
	{
		if (values[i] >= 0)
		{
			countPositive++;
		}
	}
	GetSystemTimePreciseAsFileTime(&current);
	std::cout << "Time: " << current.dwLowDateTime - prevoius.dwLowDateTime << " in 100 nanoseconds" << std::endl;

	return countPositive;
}

DWORD GetNumberOfPositiveValuesOptimized(int * values, int size)
{
	FILETIME prevoius, current;
	DWORD countPositive = 0;
	GetSystemTimePreciseAsFileTime(&prevoius);
	int i = 0;
	while(i < size)
	{
		countPositive += !(values[i] >> 31);
		i++;
	}
	GetSystemTimePreciseAsFileTime(&current);
	std::cout << "Time (optimized): " << current.dwLowDateTime - prevoius.dwLowDateTime << " in 100 nanoseconds" << std::endl;
	return countPositive;
}
#pragma endregion

//task 2
#pragma region task2

void BubbleSort(int *array, int size) {
	FILETIME prevoius, current;
	GetSystemTimePreciseAsFileTime(&prevoius);

	for (int i = size - 1; i >= 1; i--) 
	{
		for (int j = 0; j < i; j++) 
		{
			if (array[j] > array[j + 1]) 
			{
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}

	GetSystemTimePreciseAsFileTime(&current);
	std::cout << "Time: " << current.dwLowDateTime - prevoius.dwLowDateTime << " in 100 nanoseconds" << std::endl;
}

void BubbleSortOptimized(int * array, int size)
{
	FILETIME prevoius, current;
	GetSystemTimePreciseAsFileTime(&prevoius);

	int i = 0, j, temp;
	while (i < size) 
	{
		j = i - 1;
		while (j >= 0) {
			if (array[j] > array[j + 1]) 
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j--;
		}
		i++;
	}

	GetSystemTimePreciseAsFileTime(&current);
	std::cout << "Time (optimized): " << current.dwLowDateTime - prevoius.dwLowDateTime << " in 100 nanoseconds" << std::endl;
}
#pragma endregion

//task 3
#pragma region task3

int * MultiplyPolinomial(int * first, int * second, int size)
{
	//x^2 * x^2 == x^4 -- порядок увеличивается вдвое
	int * result = new int[size * 2];
	//init result array
	for (int i = 0; i < size * 2; i++) 
	{
		result[i] = 0;
	}

	FILETIME prevoius, current;
	GetSystemTimePreciseAsFileTime(&prevoius);

	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++) 
		{
			result[i + j] += first[i] * second[j];
		}
	}

	GetSystemTimePreciseAsFileTime(&current);
	std::cout << "Time: " << current.dwLowDateTime - prevoius.dwLowDateTime << " in 100 nanoseconds" << std::endl;
	return result;
}

int * MultiplyPolinomialOptimized(int * first, int * second, int size)
{
	int resultArraySize = size * 2;
	int * result = new int[resultArraySize];

	for (int i = 0; i < size * 2; i++) 
	{
		result[i] = 0;
	}

	FILETIME prevoius, current;
	GetSystemTimePreciseAsFileTime(&prevoius);


	for (int j = 0; j < size; j++) 
	{
		if (first[j] != 0) 
		{
			int * resultCoefficientPointer = result + j;

			if (second[j] == 1) 
			{
				for (int i = 0; i < size; i++) 
				{
					resultCoefficientPointer[i] += first[i];
				}
			}
			else 
			{
				for (int i = 0; i < size; i++) 
				{
					resultCoefficientPointer[i] -= first[i];
				}
			}
		}
	}

	GetSystemTimePreciseAsFileTime(&current);
	std::cout << "Time (optimized): " << current.dwLowDateTime - prevoius.dwLowDateTime << " in 100 nanoseconds" << std::endl;
	return result;
}

#pragma endregion

//task 4
#pragma region task4
int * Round(double * array, int size)
{
	FILETIME prevoius, current;
	GetSystemTimePreciseAsFileTime(&prevoius);
	int * result = new int[size];
	for (int i = 0; i < size; i++)
	{
		result[i] = round(array[i]);
	}
	GetSystemTimePreciseAsFileTime(&current);
	std::cout << "Time: " << current.dwLowDateTime - prevoius.dwLowDateTime << " in 100 nanoseconds" << std::endl;
	return result;
}

int * RoundOptimized(double * array, int size)
{
	FILETIME prevoius, current;
	GetSystemTimePreciseAsFileTime(&prevoius);
	int * result = new int[size];
	for (int i = 0; i < size; i++)
	{
		result[i] = (int)array[i];
		result[i] += (array[i] - result[i]) > 0.5;
	}
	GetSystemTimePreciseAsFileTime(&current);
	std::cout << "Time (optimized): " << current.dwLowDateTime - prevoius.dwLowDateTime << " in 100 nanoseconds" << std::endl;
	return result;
}
#pragma endregion

//task 5
#pragma region task5
std::map<int, bool> * InitPredictionMap(int bitNumber)
{
	std::map<int, bool> * predictions = new std::map<int, bool>();
	int mapSize = (int)pow(2, bitNumber);
	for (int i = 0; i < mapSize; i++)
	{
		predictions->insert({ i, false });
	}
	return predictions;
}

int ConvertToDecimal(std::list<int> * jumpsCombination)
{
	int number = 0;
	int combinationSize = jumpsCombination->size();
	int i = 0;
	for (auto element = jumpsCombination->begin(); element != jumpsCombination->end() && i < combinationSize; element++, i++)
	{
		number += (int)pow(2, i) * (*element);
	}
	return number;
}

int GetPredictionsFailure(std::list<int> * jumpsList)
{
	int bitNumber = 4;
	std::map<int, bool> * predictions = InitPredictionMap(bitNumber);
	std::list<int> * lastJumpsCombination = new std::list<int>();

	//init first 4 bits
	for (int i = 0; i < 4; i++)
	{
		jumpsList->push_front(0);
		lastJumpsCombination->push_back(0);
	}

	int failures = 0;
	int combinationNumber;
	for (auto element = std::next(jumpsList->begin(), 4); element != jumpsList->end(); element++)
	{
		combinationNumber = ConvertToDecimal(lastJumpsCombination);
		failures += !(predictions->at(combinationNumber) ^ (*element));
		predictions->at(combinationNumber) = (*element);
		lastJumpsCombination->pop_front();
		lastJumpsCombination->push_back(*element);
	}

	//delete first 4 inited bits
	for (int i = 0; i < 4; i++)
	{
		jumpsList->pop_front();
		lastJumpsCombination->pop_front();
	}
	return failures;
}
#pragma endregion

//additional methods
#pragma region additionalMethods
void PrintPolinomial(int * coef, int size)
{

	for (int i = 0; i < size; i++)
	{
		std::cout << coef[i] << "x^" << size - i - 1;
		if (i < size - 1) {
			std::cout << " + ";
		}
	}
}

int * GetArray(int size)
{
	int * array = new int[size];
	for (int i = 0; i < size; i++)
	{
		array[i] = rand() % 1 - 1;
	}
	return array;
}

double * GetArrayDouble(int size)
{
	double * array = new double[size];
	for (int i = 0; i < size; i++)
	{
		array[i] = rand() % 20 - 20;
		array[i] += (double)(rand() % 1 + 100) / (pow(10, rand() % 1 - 3));
	}
	return array;
}

int * Copy(int * array, int size)
{
	int * copiedArray = new int[size];
	for (int i = 0; i < size; i++)
	{
		copiedArray[i] = array[i];
	}
	return copiedArray;
}
#pragma endregion

int main()
{

	//task 1
	std::cout << "\t Task 1" << std::endl;
	int arraySize = 100000;
	int * array = GetArray(arraySize);
	DWORD positiveNumbersCount = GetNumberOfPositiveValues(array, arraySize);
	DWORD positiveNumbersCountOptimized = GetNumberOfPositiveValuesOptimized(array, arraySize);
	std::cout << "Number of positive values: " << positiveNumbersCount << std::endl << std::endl;

	//task 2
	std::cout << "\t Task 2" << std::endl;
	int arraySize10000 = 10000;
	int * unsortedArray = GetArray(arraySize10000);
	int * unsortedArrayCopy = Copy(unsortedArray, arraySize10000);
	BubbleSort(unsortedArray, arraySize10000);
	BubbleSortOptimized(unsortedArrayCopy, arraySize10000);
	std::cout << "a[0]: " << unsortedArray[0] << std::endl;
	std::cout << "a[0] optimized: " << unsortedArrayCopy[0] << std::endl << std::endl;

	//task 3
	std::cout << "\t Task 3" << std::endl;
	int polinomOrder = 3;

	int * x = GetArray(polinomOrder);
	int * y = GetArray(polinomOrder);
	
	int * values = MultiplyPolinomial(x, y, polinomOrder);
	int * valuesOpt = MultiplyPolinomialOptimized(x, y, polinomOrder);

	std::cout << "(";
	PrintPolinomial(x, polinomOrder);
	std::cout << ") * (";
	PrintPolinomial(y, polinomOrder);
	std::cout << ") = ";
	PrintPolinomial(values, polinomOrder * 2);
	std::cout << std::endl;
	std::cout << "First optimized coefficient: " << valuesOpt[0] << std::endl << std::endl;
	

	//task 4
	std::cout << "\t Task 4" << std::endl;
	int sizeRound = 10000;
	double * doubleArray = GetArrayDouble(sizeRound);
	int * roundArr = Round(doubleArray, sizeRound);
	int * roundArrOpt = RoundOptimized(doubleArray, sizeRound);
	std::cout << "value: " << roundArr[0] << std::endl;
	std::cout << "value optimized: " << roundArrOpt[0] << std::endl << std::endl;

	//predictions
	std::cout << "\t Task 5" << std::endl;
	auto list = new std::list<int>(); 
	list->push_back(1);
	list->push_back(1);
	list->push_back(1);
	list->push_back(0);
	list->push_back(1);
	list->push_back(1);
	list->push_back(1);
	list->push_back(0);
	list->push_back(1);
	list->push_back(1);
	list->push_back(1);
	list->push_back(1);
	int fails = GetPredictionsFailure(list);
	std::cout << "Number of fails: " << fails;

	return 0;
}