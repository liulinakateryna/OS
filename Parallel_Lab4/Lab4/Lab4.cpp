#include "pch.h"
#include <iostream>
#include <omp.h>
#include <Windows.h>
#include <thread>
#include <cmath>
#include <limits>

#define M_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647

#pragma region task1

void CheckOpenMPSupport()
{
#ifdef _OPENMP
	std::cout << "Open MP is supported." << std::endl;
#else
	std::cout << "Open MP is not supported." << std::endl;
#endif
}

#pragma endregion

#pragma region task2
DWORD GetThreadNumberWindows() 
{
	DWORD maxConcurrencyThread = std::thread::hardware_concurrency();
	return maxConcurrencyThread;
}

DWORD GetThreadNumberOpenMP()
{
	DWORD maxConcurrencyThread = omp_get_max_threads();
	return maxConcurrencyThread;
}
#pragma endregion

#pragma region task3

//ряд тейлора 
//arctg(x) = 1 ==> x = п/4
//arctg(x) = sum( (-1)^(n+1) / (2n - 1)), где n [1, infinity)
double GetPITeilor(int accuracy, __out DWORD * time) 
{
	FILETIME previous, current;
	GetSystemTimeAsFileTime(&previous);

	double PI = 0.;
	double pow = 1;
	for (int i = 1; i < accuracy; i++) 
	{
		PI += pow / (2 * i - 1);
		pow *= -1;
	}

	PI *= 4;
	std::cout << "PI using Teilor series: " << PI << std::endl;
	GetSystemTimeAsFileTime(&current);

	*time = current.dwLowDateTime - previous.dwLowDateTime;
	return PI;
}

#define RAND() (((rand () % 4096))/4096.)

double GetPIMonteCarloMethod(int accuracy, __out DWORD * time) 
{
	FILETIME previous, current;
	GetSystemTimeAsFileTime(&previous);

	double x, y, PI;
	int numberOfPointsInCircle = 0;
	for (int i = 0; i < accuracy; i++) 
	{
		x = RAND();
		y = RAND();
		numberOfPointsInCircle += (x*x + y * y <= 1);
	}

	PI = 4. * numberOfPointsInCircle / accuracy;
	std::cout << "PI using Monte-Carlo method: " << PI << std::endl;
	GetSystemTimeAsFileTime(&current);

	*time = current.dwLowDateTime - previous.dwLowDateTime;
	return PI;
}

double GetPIRectangleMethod(int accuracy, __out DWORD * time) 
{
	FILETIME previous, current;
	GetSystemTimeAsFileTime(&previous);

	double deltaX = 1. / accuracy;
	double square;
	double PI = 0;
	for (int y = 0; y < accuracy; y++) 
	{
		square = deltaX * y;
		PI += 1. / (1 + square * square);
	}
	PI *= 4 * deltaX;
	std::cout << "PI using rectangle method: " << PI << std::endl;
	GetSystemTimeAsFileTime(&current);
	*time = current.dwLowDateTime - previous.dwLowDateTime;
	return PI;
}

void GetPiCalculationEfficiency(int numberOfLoops) 
{
	DWORD executionTime = 0;
	std::cout << "Number of loops: " << numberOfLoops << std::endl << std::endl;
	GetPITeilor(numberOfLoops, &executionTime);
	std::cout << "Time (100 nanoseconds): " << executionTime << std::endl;
	GetPIMonteCarloMethod(numberOfLoops, &executionTime);
	std::cout << "Time (100 nanoseconds): " << executionTime << std::endl;
	GetPIRectangleMethod(numberOfLoops, &executionTime);
	std::cout << "Time (100 nanoseconds): " << executionTime << std::endl;
}

#pragma endregion

#pragma region task5

int GetIterationNumberTeilor(__out DWORD * time)
{
	FILETIME previous, current;
	GetSystemTimeAsFileTime(&previous);

	DWORD numberOfIterations = 1;
	double PI = 0.;
	double pow = 1;
	auto minValue = 0.000000001;
	//auto minValue = std::numeric_limits<double>::denorm_min();

	while (fabs((PI * 4 - (double)M_PI)) > minValue)
	{
		PI += pow / (2 * numberOfIterations - 1);
		pow *= -1;
		numberOfIterations++;
	}

	std::cout << "PI: " << 4 * PI << std::endl;
	GetSystemTimeAsFileTime(&current);

	*time = current.dwLowDateTime - previous.dwLowDateTime;
	std::cout << "Time (100 nanoseconds): " << *time << std::endl;

	return numberOfIterations;
}

int GetIterationNumberMonteCarloMethod(__out DWORD * time)
{
	FILETIME previous, current;
	GetSystemTimeAsFileTime(&previous);

	DWORD numberOfIterations = 1;
	double x, y, PI = 1;

	int numberOfPointsInCircle = 0;
	auto minValue = 0.000000001;

	while (fabs(PI - (double)M_PI) >= minValue)
	{
		x = RAND();
		y = RAND();
		numberOfPointsInCircle += (x*x + y * y <= 1);
		PI = 4. * numberOfPointsInCircle / numberOfIterations;
		numberOfIterations++;
	}

	std::cout << "PI: " << PI << std::endl;
	GetSystemTimeAsFileTime(&current);

	*time = current.dwLowDateTime - previous.dwLowDateTime;
	std::cout << "Time (100 nanoseconds): " << *time << std::endl;
	return numberOfIterations;
}

int GetIterationNumberRectangleMethod(__out DWORD * time)
{
	FILETIME previous, current;
	GetSystemTimeAsFileTime(&previous);

	int accuracy = 1000000000, y = 0;
	double deltaX = 1. / accuracy;
	double square;
	double PI = 0;
	auto minValue = 0.000000001;

	while (fabs(4 * deltaX * PI - (double)M_PI) >= minValue)
	{
		square = deltaX * y;
		PI += 1. / (1 + square * square);
		y++;
	}

	PI *= 4 * deltaX;
	std::cout << "PI: " << PI << std::endl;
	GetSystemTimeAsFileTime(&current);

	*time = current.dwLowDateTime - previous.dwLowDateTime;
	std::cout << "Time (100 nanoseconds): " << *time << std::endl;
	return y;
}

void GetPiCalculationEfficiency()
{
	DWORD executionTime = 0;

	std::cout << "Teilor series" << std::endl;
	int iterations = GetIterationNumberTeilor(&executionTime);
	std::cout << "Number of loops: " << iterations << std::endl << std::endl;
	std::cout << "Monte-Carlo method" << std::endl;
	iterations = GetIterationNumberMonteCarloMethod(&executionTime);
	std::cout << "Number of loops: " << iterations << std::endl << std::endl;
	std::cout << "Rectangle method" << std::endl;
	iterations = GetIterationNumberRectangleMethod(&executionTime);
	std::cout << "Number of loops: " << iterations << std::endl;
}
#pragma endregion

#pragma region task6

typedef struct
{
	int iterationsNumber;
	int pointsInCircle;
	int numberOfPoints;
}ThreadData, *PThreadData;

DWORD WINAPI ThreadFunctionMonteCarlo(PVOID data) 
{
	PThreadData threadData = (PThreadData)data;
	int iterations = threadData->iterationsNumber;
	int pointsInCircle = threadData->pointsInCircle;
	int points = threadData->numberOfPoints;

	double x, y;

	for (points = 0; points < iterations; points++) 
	{
		x = RAND();
		y = RAND();
		pointsInCircle += (x*x + y * y <= 1);
	}

	threadData->numberOfPoints = points;
	threadData->pointsInCircle = pointsInCircle;

	return 0;
}

double GetPIMonteCarloWindowsThread(int iterations, __out DWORD * time) 
{
	FILETIME previous, current;
	GetSystemTimeAsFileTime(&previous);

	int maxThreadNumber = GetThreadNumberWindows();
	HANDLE * pThreads = new HANDLE[maxThreadNumber - 1]; //one thread is current thread
	PThreadData data = new ThreadData[maxThreadNumber];

	int iterationsInThread = iterations / maxThreadNumber;

	for (int i = 0; i < maxThreadNumber; i++)
	{
		data[i] = *(new ThreadData());
		data[i].iterationsNumber = iterationsInThread;
	}

	for (int i = 0; i < maxThreadNumber - 1; i++) 
	{
		pThreads[i] = CreateThread(0, 0, ThreadFunctionMonteCarlo, &data[i], 0, 0);
	}

	ThreadFunctionMonteCarlo(&data[maxThreadNumber - 1]);
	WaitForMultipleObjects(maxThreadNumber - 1, pThreads, TRUE, INFINITE);

	int generalPointsNumber = 0;
	int generalPointsNumberInCircle = 0;
	for (int i = 0; i < maxThreadNumber; i++) 
	{
		generalPointsNumber += data[i].numberOfPoints;
		generalPointsNumberInCircle += data[i].pointsInCircle;
	}

	GetSystemTimeAsFileTime(&current);
	*time = current.dwLowDateTime - previous.dwLowDateTime;

	for (int i = 0; i < maxThreadNumber - 1; i++)
	{
		CloseHandle(pThreads[i]);
	}

	return 4. * generalPointsNumberInCircle / generalPointsNumber;
}

double GetPIMonteCarloMethodOpenMP(int iterations, __out DWORD * time) 
{
	FILETIME previous, current;
	GetSystemTimeAsFileTime(&previous);

	int numberOfPointsInCircle = 0;

#pragma omp parallel for reduction(+:numberOfPointsInCircle)
	for (int i = 0; i < iterations; i++) 
	{
		double x = RAND();
		double y = RAND();
		numberOfPointsInCircle += (x*x + y * y <= 1);
	}

	GetSystemTimeAsFileTime(&current);
	*time = current.dwLowDateTime - previous.dwLowDateTime;
	return 4. * numberOfPointsInCircle / iterations;
}

void GetPiParallelCalculationEfficiency(int iterations)
{
	DWORD time = 0;
	double PI = GetPIMonteCarloWindowsThread(iterations, &time);
	std::cout << "Number of loops: " << iterations << std::endl << std::endl;
	std::cout << "PI (Threads): " << PI << std::endl;
	std::cout << "Time (100 nanoseconds): " << time << std::endl;
	PI = GetPIMonteCarloMethodOpenMP(iterations, &time);
	std::cout << "PI (Open MP): " << PI << std::endl;
	std::cout << "Time (100 nanoseconds): " << time << std::endl;
}

#pragma endregion



int main()
{
#pragma region task1
	std::cout << "\t Task 1" << std::endl << std::endl;
	CheckOpenMPSupport();
#pragma endregion

#pragma region task2
	std::cout << std::endl << "\t Task 2" << std::endl << std::endl;
	std::cout << "Max concurrent thread number (Windows): " << GetThreadNumberWindows() << std::endl;
	std::cout << "Max concurrent thread number (Open MP): " << GetThreadNumberOpenMP() << std::endl;
#pragma endregion

#pragma region task3
	std::cout << std::endl << "\t Task 3" << std::endl << std::endl;
	GetPiCalculationEfficiency(100000);
#pragma endregion

#pragma region task5
	std::cout << std::endl << "\t Task 5" << std::endl << std::endl;
	GetPiCalculationEfficiency();
#pragma endregion

#pragma region task6
	std::cout << std::endl << "\t Task 6" << std::endl << std::endl;
	GetPiParallelCalculationEfficiency(100000);

#pragma endregion

	return 0;
}
