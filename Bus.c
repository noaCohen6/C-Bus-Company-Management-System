#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Bus.h"
#include "General.h"


int isSameBus(Bus* b1, Bus* b2)
{
	if (b1->licenseNumber == b2->licenseNumber)
		return 0;
	return 1;
}
int initBus(Bus* theBus, Bus* busArr, int countBuses)
{
	theBus->licenseNumber = getCorrectLicenseNumber(busArr, countBuses);
	theBus->numOfSeats = getBusNumOfSeats(theBus);
	theBus->theFault = eNoFault;
	return 1;
}
int getCorrectLicenseNumber(Bus* busArr, int countBuses)
{
	int temp;
	int isValid = 0;
	while (isValid == 0)
	{
		isValid = 1;
		printf("Enter license number: need to be %d digits\n", LICENSE_NUMBER_LEN);
		scanf("%d", &temp);
		if (countDigits(temp) != LICENSE_NUMBER_LEN)
		{
			printf("licenseNumber should be %d digits\n", LICENSE_NUMBER_LEN);
			isValid = 0;
		}
		if (isBusLicenseNumberUniqe(busArr, countBuses, temp) != NULL) 
		{
			isValid = 0;
		}
	}
	return temp;
}


int getBusNumOfSeats(Bus* theBus)
{
	int num;
	int isValid = 0;
	while (isValid == 0)
	{
		printf("Enter bus number of seats: between %d to %d\n", MIN_SEATS, MAX_SEATS);
		scanf("%d", &num);
		if (num >= MIN_SEATS && num <= MAX_SEATS)
			isValid = 1;
		else
			isValid = 0;
	}
	return num;
}
int addFault(Bus* theBus)
{
	if (isFault(theBus) == 1)
	{
		printf("The bus already has a fault\n");
		return 0;
	}
	theBus->theFault = getFaultType();
	return 1;
}
int		removeFault(Bus* theBus) 
{
	if (isFault(theBus) == 0)
	{
		printf("The bus does not have a fault\n");
		return 0;
	}
	theBus->theFault = eNoFault;
	return 1;
}
int isFault(Bus* theBus)
{
	if ((int)theBus->theFault == eNoFault)
		return 0;
	return 1;
}
void printBus(const void* v)
{
	const Bus* theBus = (const Bus*)v;
	printf("License number:%d\tNumber of seats:%d\tfault type: %s\tthe fault price:%d\n",theBus->licenseNumber,theBus->numOfSeats,FaultTypeStr[theBus->theFault],FaultTypePriceInt[theBus->theFault]);
}
int	savetBusToBinaryFile(Bus* pBus, FILE* f)
{
	if (fwrite(pBus, sizeof(Bus), 1, f) != 1)
		return 0;
	return 1;

}
int	readBusFromBinaryFile(Bus* pBus, FILE* f)
{
	if (fread(pBus, sizeof(Bus), 1, f) != 1)
		return 0;
	return 1;
}
int savetBusToTextFile(Bus* pBus, FILE* f)
{
	fprintf(f, "%d\n%d\n%s\n", pBus->licenseNumber, pBus->numOfSeats, FaultTypeStr[pBus->theFault]);
	return 1;
}
int	readBusFromTextFile(Bus* pBus, FILE* f)
{
	char temp[MAX_STR_LEN] = { 0 };
	fscanf(f, "%d", &pBus->licenseNumber);
	if (!pBus->licenseNumber)
		return 0;
	fscanf(f, "%d", &pBus->numOfSeats);
	if (!pBus->numOfSeats)
		return 0;
	if (myGets(temp, MAX_STR_LEN, f) == NULL)
		return 0;
	temp[strcspn(temp, "\n")] = '\0';
	pBus->theFault = convertToFaultTypeEnum(temp);
	if (pBus->theFault == -1)
		return 0;
	return 1;
}
int convertToFaultTypeEnum(char* str)
{
	if (strcmp(str, "Flat Tire") == 0) {
		return 0;
	}
	else if (strcmp(str, "Engine Problem") == 0) {
		return 1;
	}
	else if (strcmp(str, "Headlight Problem") == 0) {
		return 2;
	}
	else if (strcmp(str, "AirConditioner Problem") == 0) {
		return 3;
	}
	else if (strcmp(str, "Electrical Problem") == 0) {
		return 4;
	}
	else if (strcmp(str, "No Fault") == 0) {
		return 5;
	}
	return -1;
}
Bus* isBusLicenseNumberUniqe(Bus* busArr, int busCount, int num)
{
	for (int i = 0; i < busCount; i++)
	{
		if (busArr[i].licenseNumber == num)
			return &busArr[i];
	}
	return NULL;
}
