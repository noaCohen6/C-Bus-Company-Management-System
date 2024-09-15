#pragma once
#ifndef __DRIVER__
#define __DRIVER__

#define PRICE_FOR_DRIVE 100
#define PRICE_FOR_SENIORITY 15

typedef struct
{
	char* name;
	int driverNumber;
	float salary;
	float seniority;
	int numOfTrips;
}Driver;

float	salaryCalculation(Driver* theDriver);
int		isSameDriver(Driver** driverArr, int count, int num);
int		initDriver(Driver* theDriver, Driver** driverArr, int driverCount);
void	printDriver(const Driver* theDriver);
void	freeDriver(Driver* theDriver);
int		saveDriverToTextFile(Driver* theDriver, FILE* f);
int		readDriverFromTextFile(Driver* theDriver, FILE* f);
int		saveDriverToBinaryFile(Driver* theDriver, FILE* f);
int		readDriverFromBinaryFile(Driver* theDriver, FILE* f);
Driver*	isDriverNumUniqe(Driver** driverArr, int driverCount, int num);
void	copyDriver(Driver* destination, const Driver* source);

#endif