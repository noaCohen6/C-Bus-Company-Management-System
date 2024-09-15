#pragma once
#ifndef __BUS__
#define __BUS__
#include "FaultInBus.h"

#define MIN_SEATS 5
#define MAX_SEATS 50
#define LICENSE_NUMBER_LEN 8


typedef struct
{
	int licenseNumber;
	int numOfSeats;
	eFaultType theFault;
}Bus;

int		isSameBus(Bus* b1, Bus* b2);
int		initBus(Bus* theBus, Bus* busArr, int countBuses);
int		getCorrectLicenseNumber(Bus* busArr, int countBuses);
int		getBusNumOfSeats(Bus* theBus);
int		addFault(Bus* theBus);
int		removeFault(Bus* theBus);
int		isFault(Bus* theBus);
void	printBus(const void* v);
int		savetBusToBinaryFile(Bus* pBus, FILE* f);
int		readBusFromBinaryFile(Bus* pBus, FILE* f);
int		savetBusToTextFile(Bus* pBus, FILE* f);
int		readBusFromTextFile(Bus* pBus, FILE* f);
int		convertToFaultTypeEnum(char* str);
Bus*	isBusLicenseNumberUniqe(Bus* busArr, int busCount, int num);

#endif