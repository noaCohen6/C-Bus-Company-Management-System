#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "BusCompany.h"
#include "General.h"

int		initCompany(BusCompany* theCompany)
{
	theCompany->name = getStrExactName("Enter the company name:\n");
	if (!theCompany->name)
		return 0;
	theCompany->allBuses = NULL;
	theCompany->allDrivers = NULL;
	theCompany->allLines = NULL;
	theCompany->allStations = NULL;
	theCompany->countBuses = 0;
	theCompany->countDrivers = 0;
	theCompany->countLines = 0;
	theCompany->countStations = 0;
	theCompany->sortType = eNoSort;
	return 1;
}
int		addLine(BusCompany* theCompany)
{
	Bus* pBus;
	Driver* pDriver;
	int ok = 0;
	int num = 0;
	if (theCompany->countStations < 2 || theCompany->countBuses == 0 || theCompany->countDrivers == 0)
	{
		printf("Not enough data to create a line, You need at least 2 station,1 driver and 1 bus\n");
		return 0;
	}
	printAllBuses(theCompany);
	do
	{
		printf("Enter the license number of the bus that you want to add to the line\n");
		scanf("%d", &num);
		pBus = isBusLicenseNumberUniqe(theCompany->allBuses,theCompany->countBuses, num);
		if (pBus != NULL)
		{
			if (isFault(pBus) == 1)
			{
				printf("There is a fault on the bus, it cannot be added to the line\n");
				return 0;
			}else
				ok = 1;
		}
			
	} while (ok == 0);
	printAllDrivers(theCompany);
	do
	{
		printf("Enter the driver number that you want to add to the line\n");
		scanf("%d", &num);
		pDriver = isDriverNumUniqe(theCompany->allDrivers, theCompany->countDrivers, num);
		if (pDriver != NULL)
			ok = 0;
			
	} while (ok == 1);

	Line* pLine = (Line*)calloc(1, sizeof(Line));
	if (!pLine)
		return 0;

	theCompany->allLines = (Line**)realloc(theCompany->allLines, (theCompany->countLines + 1) * sizeof(Line*));
	if (!theCompany->allLines)
	{
		free(pLine);
		return 0;
	}
	
	if (initLine(pLine, theCompany->allLines, theCompany->countLines, pBus, pDriver) == 0)
	{
		free(pLine);
		free(theCompany->allLines);
		return 0;
	}
	pDriver->numOfTrips++;
	salaryCalculation(pDriver);
	theCompany->allLines[theCompany->countLines] = pLine;
	theCompany->countLines++;
	return 1;

}
int		addBus(BusCompany* theCompany)
{
	theCompany->allBuses = (Bus*)realloc(theCompany->allBuses, (theCompany->countBuses + 1) * sizeof(Bus));
	if (!theCompany->allBuses)
	{
		return 0;
	}
	initBus(&theCompany->allBuses[theCompany->countBuses], theCompany->allBuses, theCompany->countBuses);
	theCompany->countBuses++;
	return 1;

}
int		addDriver(BusCompany* theCompany)
{
	Driver* pDriver = (Driver*)calloc(1, sizeof(Driver));
	if (!pDriver)
		return 0;

	theCompany->allDrivers = (Driver**)realloc(theCompany->allDrivers, (theCompany->countDrivers + 1) * sizeof(Driver*));
	if (!theCompany->allDrivers)
	{
		free(pDriver);
		return 0;
	}
	if (initDriver(pDriver, theCompany->allDrivers, theCompany->countDrivers) ==0)
	{
		free(pDriver);
		free(theCompany->allDrivers);
		return 0;
	}
	theCompany->allDrivers[theCompany->countDrivers] = pDriver;
	theCompany->countDrivers++;
	return 1;

}
int		addStation(BusCompany* theCompany)
{
	Station* pStation = (Station*)calloc(1, sizeof(Station));
	if (!pStation)
		return 0;

	theCompany->allStations = (Station**)realloc(theCompany->allStations, (theCompany->countStations + 1) * sizeof(Station*));
	if (!theCompany->allStations)
	{
		free(pStation);
		return 0;
	}
	if (initStation(pStation, theCompany->allStations, theCompany->countStations) == 0)
	{
		free(pStation);
		free(theCompany->allStations);
		return 0;
	}

	theCompany->allStations[theCompany->countStations] = pStation;
	theCompany->countStations++;
	return 1;
}
int		addStationToLine(BusCompany* theCompany)
{
	int okS = 0;
	int ok = 0;
	int num;
	Station* sTemp = NULL;
	NODE* nTemp = NULL;
	Station* sDest = (Station*)malloc(sizeof(Station));
	if (theCompany->countLines < 1) 
	{
		printf("No lines exist");
		return 0;
	}
	printAllLines(theCompany);
	Line* lTemp = (Line*)Find("Enter the line number that you want to add the station\n", theCompany->allLines, theCompany->countLines, isLineNumUniqe);
	printAllStations(theCompany);
	do
	{
		sTemp = (Station*)Find("Enter the station number that you want to add to the line\n", theCompany->allStations, theCompany->countStations, isStationNumUnique);
		if (L_find(lTemp->listAllStations.head.next, &sTemp->stationNumber, isStationExiest) == NULL)
		{
			okS = 1;
		}
	} while (okS == 0);
	copyStation(sDest, sTemp);
	if (lTemp->listAllStations.head.next == NULL)
	{
		num = 1;
	}
	else
	{
		do {
			printf("Where on the line would you like to add the station?\n1. head of line\n2. Otherwise\n");
			scanf("%d", &num);
			if (num == 1 || num == 2)
			{
				ok = 1;
			}
		} while (ok == 0);
	}
	if (num == 1) 
	{
		nTemp = &lTemp->listAllStations.head;
	}
	else
	{
		int numS;
		printf("Enter the station number that you want to add after it another station to the line\n");
		scanf("%d", &numS);
		nTemp = L_find(lTemp->listAllStations.head.next, &numS, isStationExiest);
	}
	L_insert(nTemp, sDest);
	return 1;
}
int		removeStationFromLine(BusCompany* theCompany)
{
	int ok = 0;
	int num;
	NODE* nTemp = NULL;;
	if (theCompany->countLines < 1)
	{
		printf("No lines exist");
		return 0;
	}
	printAllLines(theCompany);
	Line* lTemp = (Line*)Find("Enter the line number that you want to remove the station from\n", theCompany->allLines, theCompany->countLines, isLineNumUniqe);
	if (lTemp->listAllStations.head.next == NULL)
	{
		printf("There are no stations in the line\n");
		return 0;
	}
	if (listLength(lTemp->listAllStations.head.next) < 3 && lTemp->countPassengers > 0) 
	{
		printf("Need at least 2 stations on the line when there are passengers,Stations on a line cannot be deleted\n");
		return 0;
	}
	printLine(&lTemp);
	if (listLength(lTemp->listAllStations.head.next) == 1)
	{
		num = 1;
		printf("There was only one station on the line so it was deleted\n");
	}
	else
	{
		do {
			printf("Where on the line would you like to remove the station?\n1. head of line\n2. Otherwise\n");
			scanf("%d", &num);
			if (num == 1 || num == 2)
			{
				ok = 1;
			}
		} while (ok == 0);
	}
	if (num == 1)
	{
		nTemp = &lTemp->listAllStations.head;
	}
	else
	{
		int numS;
		printf("Enter the station number in front of the station you want to delete\n");
		scanf("%d", &numS);
		nTemp = L_find(lTemp->listAllStations.head.next, &numS, isStationExiest);
	}

	L_delete(nTemp, freeStation);
	return 1;
}
void	addFaultToBus(BusCompany* theCompany) 
{
	int busNum;
	Bus* busTemp;
	printAllBuses(theCompany);
	printf("Enter the license number of the bus that you want to add a fault\n");
	scanf("%d", &busNum);

	busTemp = isBusLicenseNumberUniqe(theCompany->allBuses, theCompany->countBuses, busNum);
	if (busTemp == NULL) 
	{
		printf("The license number of the bus is not exist\n");
		return;
	}
	if(addFault(busTemp) ==1)
		printf("The fault was added\n");
}
void	removeFaultFromBus(BusCompany* theCompany)
{
	int busNum;
	Bus* busTemp;
	printAllBuses(theCompany);
	printf("Enter the license number of the bus that you want to remove a fault\n");
	scanf("%d", &busNum);

	busTemp = isBusLicenseNumberUniqe(theCompany->allBuses, theCompany->countBuses, busNum);
	if (busTemp == NULL)
	{
		printf("The license number of the bus is not exist\n");
		return;
	}
	if(removeFault(busTemp) ==1)
		printf("The fault was removed\n");
}
void addPassengerToLine(BusCompany* theCompany)
{
	int lineNum;
	Line* lineTemp;
	printAllLines(theCompany);
	printf("Enter the line number that you want to add a passenger\n");
	scanf("%d", &lineNum);

	lineTemp = isLineNumUniqe(theCompany->allLines, theCompany->countLines, lineNum);
	if (lineTemp == NULL)
	{
		printf("The line number is not exist\n");
		return;
	}
	if (listLength(&lineTemp->listAllStations.head) < 2)
	{
		printf("You need at least 2 stations on the line to add a passenger\n");
		return;
	}
	if(addPassenger(lineTemp) == 1)
		printf("The passenger was added to the line\n");
}
void getBestDriver(BusCompany* theCompany)
{
	int max = theCompany->allDrivers[0]->numOfTrips;
	int indexDriver = 0;
	if (theCompany->countDrivers < 2)
	{
		printf("You need at least 2 drivers to perform the operation\n");
		return;
	}
	for (int i = 1; i < theCompany->countDrivers; i++)
	{
		if (theCompany->allDrivers[i]->numOfTrips > max)
		{
			max = theCompany->allDrivers[i]->numOfTrips;
			indexDriver = i;
		}
	}
	printf("The driver who made the most trips:\t");
	printDriver(theCompany->allDrivers[indexDriver]);

}
void	companyProfit(BusCompany* theCompany)
{
	float sumLine = 0;
	float sumDriver = 0;
	float sumBus = 0;
	for (int i = 0; i < theCompany->countLines; i++)
	{
		sumLine += profitFromPassengersForLine(theCompany->allLines[i]);
	}
	for (int i = 0; i < theCompany->countDrivers; i++)
	{
		sumDriver += salaryCalculation(theCompany->allDrivers[i]);
	}
	for (int i = 0; i < theCompany->countBuses; i++)
	{

		sumBus += (float)getFaultTypePriceInt(theCompany->allBuses[i].theFault);
	}
	printf("The profit from the line: %f\nDriver salary expenses: %f\nBus fault expenses: %f\nThe Company profit %f\n", sumLine, sumDriver, sumBus, sumLine - sumDriver - sumBus);

}

void	printCompany(const BusCompany* theCompany)
{
	printf("The Company name: %s\n", theCompany->name);
	printf("\n");
	printAllLines(theCompany);
	printf("\n");
	printAllDrivers(theCompany);
	printf("\n");
	printAllBuses(theCompany);
	printf("\n");
	printAllStations(theCompany);

}
void	freeCompany(BusCompany* theCompany)
{
	for (int i = 0; i < theCompany->countLines; i++)
	{
		freeLine(theCompany->allLines[i]);
	}
	free(theCompany->allLines);
	for (int i = 0; i < theCompany->countDrivers; i++)
	{
		freeDriver(theCompany->allDrivers[i]);
	}
	free(theCompany->allDrivers);
	for (int i = 0; i < theCompany->countStations; i++)
	{

		freeStation(theCompany->allStations[i]);
	}
	free(theCompany->allStations);
	free(theCompany->allBuses);

}
void	printAllLines(const BusCompany* theCompany)
{
	printf("The Company lines:\n");
	generalArrayFunction(theCompany->allLines, theCompany->countLines, sizeof(Line*), printLine);
}
void	printAllBuses(const BusCompany* theCompany)
{
	printf("The Company buses:\n");
	generalArrayFunction(theCompany->allBuses, theCompany->countBuses, sizeof(Bus), printBus);
}
void	printAllStations(const BusCompany* theCompany)
{
	printf("The Company stations:\n");
	for (int i = 0; i < theCompany->countStations; i++)
	{
		printStation(theCompany->allStations[i]);
	}
}
void	printAllDrivers(const BusCompany* theCompany)
{
	printf("The Company drivers:\n");
	for (int i = 0; i < theCompany->countDrivers; i++)
	{
		printDriver(theCompany->allDrivers[i]);
	}
}
eSortType getSortType()
{
	int option;
	printf("\n");
	printf("Base on what field do you want to sort?\n");
	do {
		for (int i = 0; i < eNofSortTypes - 1; i++)
			printf("Enter %d for %s\n", i + 1, SortTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofSortTypes);
	getchar();
	return (eSortType)option - 1;
}

void sortLine(BusCompany* theCompany)
{
	theCompany->sortType = getSortType();
	if (theCompany->sortType == eNumber)
		qsort(theCompany->allLines, theCompany->countLines, sizeof(Line*), compareLineByNumber);
	else if (theCompany->sortType == eStation)
		qsort(theCompany->allLines, theCompany->countLines, sizeof(Station*), compareLineByFirstStation);
	else if (theCompany->sortType == eDate)
		qsort(theCompany->allLines, theCompany->countLines, sizeof(Date*), compareLineByDate);
}
void findLine(BusCompany* theCompany)
{
	int num = 0;
	Line* lTemp = (Line*)malloc(sizeof(Line));
	if (!lTemp)
		return;
	Line** lF = NULL;
	if (theCompany->sortType == eNoSort)
	{
		printf("The search cannot be performed, array not sorted\n");
		return;
	}
	else if (theCompany->sortType == eNumber)
	{
		printf("Enter the line number that you want to find:\n");
		scanf("%d", &num);
		lTemp->lineNumber = num;
		lF = bsearch(&lTemp, theCompany->allLines, theCompany->countLines, sizeof(Line*), compareLineByNumber);
	}
	else if (theCompany->sortType == eStation)
	{
		Station* s1 = (Station*)malloc(sizeof(Station));
		if (!s1)
			return;
		s1->name = getStrExactName("Enter the station name that you want to find:\n");
		L_insert(&lTemp->listAllStations.head, s1);
		lF = bsearch(&lTemp, theCompany->allLines, theCompany->countLines, sizeof(Station*), compareLineByFirstStation);
		freeStation(s1);
	}
	else if (theCompany->sortType == eDate)
	{
		getCorrectDate(&lTemp->theDate);
		lF = bsearch(&lTemp, theCompany->allLines, theCompany->countLines, sizeof(Date*), compareLineByDate);
	}

	if (lF == NULL)
		printf("Line was not found\n");
	else
	{
		printf("Line found, \n");
		printLine(&(*lF));
	}
	free(lTemp);
}

int compareLineByNumber(const void* v1, const void* v2)
{
	const Line* l1 = *(const Line**)v1;
	const Line* l2 = *(const Line**)v2;

	return l1->lineNumber - l2->lineNumber;
}
int compareLineByFirstStation(const void* v1, const void* v2)
{
	const Line* l1 = *(const Line**)v1;
	const Line* l2 = *(const Line**)v2;
	Station* s1 = l1->listAllStations.head.next->key;
	Station* s2 = l2->listAllStations.head.next->key;
	return strcmp(s1->name, s2->name);
}
int compareLineByDate(const void* v1, const void* v2)
{
	const Line* l1 = *(const Line**)v1;
	const Line* l2 = *(const Line**)v2;

	if (l1->theDate.year != l2->theDate.year)
		return l1->theDate.year - l2->theDate.year;
	else if (l1->theDate.month != l2->theDate.month)
		return l1->theDate.month - l2->theDate.month;
	else if (l1->theDate.day != l2->theDate.day)
		return l1->theDate.day - l2->theDate.day;
	return 0;
}

