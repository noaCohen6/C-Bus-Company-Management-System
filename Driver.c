#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Driver.h"
#include "General.h"

float salaryCalculation(Driver* theDriver)
{
	if (theDriver->numOfTrips == 0)
		return 0;
	theDriver->salary = theDriver->numOfTrips * PRICE_FOR_DRIVE + theDriver->seniority * PRICE_FOR_SENIORITY;
	return theDriver->salary;
}
int isSameDriver(Driver** driverArr,int count,int num)
{
	for (int i = 0; i < count; i++)
	{
		if (driverArr[i]->driverNumber == num)
			return 0;
	}
	return 1;
}
int initDriver(Driver* theDriver,Driver** driverArr, int driverCount)
{
	theDriver->name = getStrExactName("Please enter driver name:\n");
	if (!theDriver->name)
		return 0;
	theDriver->driverNumber = getIntNum("Please enter driver work number:\n",driverArr,driverCount, isSameDriver);

	theDriver->salary = 0;
	theDriver->numOfTrips = 0;
	theDriver->seniority = getFloatNum("Please enter driver seniority:\n");
	return 1;
}
void printDriver(const Driver* theDriver)
{
	printf("Driver Name:  %-10s Driver Number: %d\tSalary: %f\tSeniority: %f\tNum Of Trips: %d\n", theDriver->name, theDriver->driverNumber, theDriver->salary, theDriver->seniority, theDriver->numOfTrips);
}
void freeDriver(Driver* theDriver)
{
	free(theDriver->name);
}
int	saveDriverToTextFile(Driver* theDriver, FILE* f)
{
	int len = (int)strlen(theDriver->name) + 1;
	fprintf(f, "%d\n%s\n%d\n%f\n%f\n%d\n", len,theDriver->name, theDriver->driverNumber, theDriver->salary, theDriver->seniority, theDriver->numOfTrips);
	return 1;
}
int readDriverFromTextFile(Driver* theDriver, FILE* f)
{
	char temp[MAX_STR_LEN] = { 0 };
	int len = 0;

	if (fscanf(f, "%d", &len) != 1)
		return 0;
	theDriver->name = (char*)malloc(len * sizeof(char));
	if (!theDriver->name)
		return 0;
	if (myGets(temp, MAX_STR_LEN, f) == NULL)
		return 0;
	temp[strcspn(temp, "\n")] = '\0';
	theDriver->name = _strdup(temp);
	if (!theDriver->name)
		return 0;
	if(fscanf(f, "%d", &theDriver->driverNumber) !=1)
	{
		free(theDriver->name);
		return 0;
	}
	if(fscanf(f, "%f", &theDriver->salary) != 1)
	{
		free(theDriver->name);
		return 0;
	}
	if(fscanf(f, "%f", &theDriver->seniority) !=1)
	{
		free(theDriver->name);
		return 0;
	}
	if(fscanf(f, "%d", &theDriver->numOfTrips)!=1)
	{
		free(theDriver->name);
		return 0;
	}
	return 1;
}

int saveDriverToBinaryFile(Driver* theDriver, FILE* f)
{
	int len = (int)strlen(theDriver->name)+1;
	if (fwrite(&len, sizeof(int), 1, f) != 1)
		return 0;
	if (fwrite(theDriver->name, sizeof(char), len, f) != len)
		return 0;
	if (fwrite(&theDriver->driverNumber, sizeof(int), 1, f) != 1)
		return 0;
	if (fwrite(&theDriver->salary, sizeof(float), 1, f) != 1)
		return 0;
	if (fwrite(&theDriver->seniority, sizeof(float), 1, f) != 1)
		return 0;
	if (fwrite(&theDriver->numOfTrips, sizeof(int), 1, f) != 1)
		return 0;
	return 1;
}
int readDriverFromBinaryFile(Driver* theDriver, FILE* f)
{
	int size = 0;
	if (fread(&size, sizeof(int), 1, f) != 1)
		return 0;
	theDriver->name = (char*)malloc(size * sizeof(char));
	if (!theDriver->name)
		return 0;
	if (fread(theDriver->name, sizeof(char), size, f) != size)
	{
		free(theDriver->name);
		return 0;
	}
	if (fread(&theDriver->driverNumber, sizeof(int), 1, f) != 1)
	{
		free(theDriver->name);
		return 0;
	}
	if (fread(&theDriver->salary, sizeof(float), 1, f) != 1)
	{
		free(theDriver->name);
		return 0;
	}
	if (fread(&theDriver->seniority, sizeof(float), 1, f) != 1)
	{
		free(theDriver->name);
		return 0;
	}
	if (fread(&theDriver->numOfTrips, sizeof(int), 1, f) != 1)
	{
		free(theDriver->name);
		return 0;
	}
	return 1;
}
Driver*		isDriverNumUniqe(Driver** driverArr, int driverCount, int num)
{
	for (int i = 0; i < driverCount; i++)
	{
		if (driverArr[i]->driverNumber == num)
			return driverArr[i];
	}
	return NULL;
}
void copyDriver(Driver* destination, const Driver* source)
{
	destination->name = _strdup(source->name);
	destination->driverNumber = source->driverNumber;
	destination->salary = source->salary;
	destination->seniority = source->seniority;
	destination->numOfTrips = source->driverNumber;
}
