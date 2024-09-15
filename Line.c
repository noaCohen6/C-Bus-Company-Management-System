#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Line.h"
#include "General.h"

int		isSameLine(Line** lineArr, int count, int num)
{
	for (int i = 0; i < count; i++)
	{
		if (lineArr[i]->lineNumber == num)
			return 0;
	}
	return 1;
}

int		addPassenger(Line* theLine)
{
	if (checkIfBusFull(theLine) == 0)
	{
		printf("The bus is full\n");
		return 0;
	}
	Passenger* pPassenger = (Passenger*)calloc(1, sizeof(Passenger));
	if (!pPassenger)
		return 0;
	if (initPassenger(pPassenger, theLine->allPassengers, theLine->countPassengers) == 0)
	{
		printf("Adding Passenger to line is failed\n");
		return 0;
	}

	theLine->allPassengers = (Passenger**)realloc(theLine->allPassengers, (theLine->countPassengers + 1) * sizeof(Passenger*));
	if (!theLine->allPassengers)
	{
		free(pPassenger);
		return 0;
	}
	theLine->allPassengers[theLine->countPassengers] = pPassenger;
	theLine->countPassengers++;
	return 1;
}
int		checkIfBusFull(Line* theLine)
{
	if (theLine->theBus.numOfSeats == theLine->countPassengers)
		return 0;
	return 1;
}
float	priceForPassenger(Line* theLine, Passenger* thePassenger)
{
	float price = theLine->numOfKM * PRICE_FOR_KM;

	if (thePassenger->ticketType == eSoldier) {
		return CALC_PRICE(price, (float)DISCOUNT_SOLDIER);
	}
	else if (thePassenger->ticketType == eStudent) {
		return CALC_PRICE(price, (float)DISCOUNT_STUDENT);
	}
	else if (thePassenger->ticketType == eChild) {
		return CALC_PRICE(price, (float)DISCOUNT_CHILD);
	}
	else if (thePassenger->ticketType == ePensioner) {
		return CALC_PRICE(price, (float)DISCOUNT_PENSIONER);
	}
	return price;
}
float	profitFromPassengersForLine(Line* theLine)
{
	float sum = 0;
	for (int i = 0; i < theLine->countPassengers; i++)
	{
		sum += priceForPassenger(theLine, theLine->allPassengers[i]);
	}
	return sum;
}
int initLine(Line* theLine, Line** lineArr, int lineCount,Bus* pBus,Driver* pDriver)
{
	theLine->lineNumber = getIntNum("Enter line number:\n", lineArr, lineCount, isSameLine);
	theLine->numOfKM = getFloatNum("Enter the line distance in KM:\n");
	theLine->theBus = *pBus;
	copyDriver(&theLine->theDriver, pDriver);
	theLine->theDriver.numOfTrips++;
	salaryCalculation(&theLine->theDriver);
	getCorrectDate(&theLine->theDate);
	theLine->allPassengers = NULL;
	theLine->countPassengers = 0;
	if (L_init(&theLine->listAllStations) == False)
		return 0;
	return 1;
}
void	printLine(const void* v)
{
	const Line** theLine = (const Line**)v;
	printf("Line:\tLine number: %d\tnum of KM: %f\t", (*theLine)->lineNumber, (*theLine)->numOfKM);
	printDate(&(*theLine)->theDate);
	printf("Bus: ");
	printBus(&(*theLine)->theBus);
	printf("\t");
	printDriver(&(*theLine)->theDriver);
	generalArrayFunction((*theLine)->allPassengers, (*theLine)->countPassengers, sizeof(Passenger*), printPassenger);
	L_print(&(*theLine)->listAllStations, printStation);
}
void	freeLine(Line* theLine)
{
	freeDriver(&theLine->theDriver);
	for (int i = 0; i < theLine->countPassengers; i++)
	{
		freePassenger(theLine->allPassengers[i]);
	}
	free(theLine->allPassengers);
	L_free(&theLine->listAllStations, freeStation);

}
int		saveLineToTextFile(Line* theLine, FILE* f)
{
	fprintf(f, "%d\n%f\n", theLine->lineNumber, theLine->numOfKM);
	if (savetDateToTextFile(&theLine->theDate, f) == 0)
		return 0;
	if (savetBusToTextFile(&theLine->theBus, f) == 0)
		return 0;
	if (saveDriverToTextFile(&theLine->theDriver, f) == 0)
		return 0;
	fprintf(f, "%d\n", theLine->countPassengers);
	for (int i = 0; i < theLine->countPassengers; i++)
	{
		if (savetPassengerToTextFile(theLine->allPassengers[i], f) == 0)
			return 0;
	}
	NODE* pStation = theLine->listAllStations.head.next;
	int length = listLength(pStation);
	fprintf(f, "%d\n", length);

	while (pStation != NULL)
	{
		if (saveStationToTextFile(pStation->key, f) == 0)
			return 0;
		pStation = pStation->next;
	}

	return 1;
}
int		readLineFromTextFile(Line* theLine, FILE* f)
{
	theLine->allPassengers = NULL;
	theLine->countPassengers = 0;
	int length = 0;
	Station* pStation;
	L_init(&theLine->listAllStations);
	NODE* pList = &theLine->listAllStations.head;

	if (fscanf(f, "%d", &theLine->lineNumber) != 1)
		return 0;
	if (fscanf(f, "%f", &theLine->numOfKM) != 1)
		return 0;
	if (readDateFromTextFile(&theLine->theDate, f) == 0)
		return 0;
	if (readBusFromTextFile(&theLine->theBus, f) == 0)
		return 0;
	if (readDriverFromTextFile(&theLine->theDriver, f) == 0)
		return 0;
	if (fscanf(f, "%d", &theLine->countPassengers) != 1)
		return 0;
	theLine->allPassengers = (Passenger**)realloc(theLine->allPassengers, theLine->countPassengers * sizeof(Passenger*));
	if (!theLine->allPassengers)
		return 0;
	for (int i = 0; i < theLine->countPassengers; i++)
	{
		theLine->allPassengers[i] = (Passenger*)calloc(1, sizeof(Passenger));
		if (!theLine->allPassengers[i])
			return 0;
		if (readPassengerFromTextFile(theLine->allPassengers[i], f) == 0)
			return 0;
	}
	if (fscanf(f, "%d", &length) != 1)
		return 0;
	int c;
	while ((c = fgetc(f)) != EOF && c != '\n');
	for (int i = 0; i < length; i++)
	{
		pStation = (Station*)malloc(sizeof(Station));
		if (!pStation)
		{
			return 0;
		}
		if (!readStationFromTextFile(pStation, f))
		{
			freeStation(pStation);
			return 0;
		}
		L_insert(pList, pStation);
		pList = pList->next;
	}
	return 1;
}
int		saveLineToBinaryFile(Line* theLine, FILE* f)
{
	NODE* pStation = theLine->listAllStations.head.next;
	int length = listLength(pStation);
	if (fwrite(&theLine->lineNumber, sizeof(int), 1, f) != 1)
		return 0;
	if (fwrite(&theLine->numOfKM, sizeof(float), 1, f) != 1)
		return 0;
	if (savetDateToBinaryFile(&theLine->theDate, f) == 0)
		return 0;
	if (savetBusToBinaryFile(&theLine->theBus, f) == 0)
		return 0;
	if (saveDriverToBinaryFile(&theLine->theDriver, f) == 0)
		return 0;
	if (fwrite(&theLine->countPassengers, sizeof(int), 1, f) != 1)
		return 0;
	for (int i = 0; i < theLine->countPassengers; i++)
	{
		if (savetPassengerToBinaryFile(theLine->allPassengers[i], f) == 0)
			return 0;
	}
	if (fwrite(&length, sizeof(int), 1, f) != 1)
		return 0;
	while (pStation != NULL)
	{
		if (saveStationToBinaryFileCompressed(pStation->key, f) == 0)
			return 0;
		pStation = pStation->next;
	}
	return 1;
}
int		readLineFromBinaryFile(Line* theLine, FILE* f)
{
	theLine->countPassengers = 0;
	theLine->allPassengers = NULL;

	int length = 0;
	Station* pStation;
	L_init(&theLine->listAllStations);
	NODE* pList = &theLine->listAllStations.head;

	if (fread(&theLine->lineNumber, sizeof(int), 1, f) != 1)
		return 0;
	if (fread(&theLine->numOfKM, sizeof(float), 1, f) != 1)
		return 0;
	if (readDateFromBinaryFile(&theLine->theDate, f) == 0)
		return 0;
	if (readBusFromBinaryFile(&theLine->theBus, f) == 0)
		return 0;
	if (readDriverFromBinaryFile(&theLine->theDriver, f) == 0)
		return 0;
	if (fread(&theLine->countPassengers, sizeof(int), 1, f) != 1)
		return 0;
	theLine->allPassengers = (Passenger**)realloc(theLine->allPassengers, theLine->countPassengers * sizeof(Passenger*));
	if (!theLine->allPassengers)
		return 0;
	for (int i = 0; i < theLine->countPassengers; i++)
	{
		theLine->allPassengers[i] = (Passenger*)calloc(1, sizeof(Passenger));
		if (!theLine->allPassengers[i])
			return 0;
		if (readPassengerFromBinaryFile(theLine->allPassengers[i], f) == 0)
			return 0;
	}
	if (fread(&length, sizeof(int), 1, f) != 1)
		return 0;
	for (int i = 0; i < length; i++)
	{
		pStation = (Station*)malloc(sizeof(Station));
		if (!pStation)
		{
			return 0;
		}
		if (!readStationFromBinaryFileCompressed(pStation, f))
		{
			freeStation(pStation);
			return 0;
		}
		L_insert(pList, pStation);
		pList = pList->next;
	}
	return 1;
}
void* isLineNumUniqe(void** lineArr, int lineCount, int num)
{
	int lineNum = lineCount;
	Line** arr = (Line**)lineArr;
	for (int i = 0; i < lineNum; i++)
	{
		if (arr[i]->lineNumber == num)
			return arr[i];
	}
	return NULL;
}
