#pragma once
#ifndef __BUSLINE__
#define __BUSLINE__

#include "Passenger.h"
#include "Date.h"
#include "Station.h"
#include "Bus.h"
#include "Driver.h"
#include "list.h"
#include "macros.h"


#define PRICE_FOR_KM 20

typedef struct
{
	int lineNumber;
	float numOfKM;
	Date theDate;
	Bus theBus;
	Driver theDriver;
	Passenger** allPassengers;
	int countPassengers;
	LIST listAllStations;
}Line;

int		isSameLine(Line** lineArr,int count,int num);
int		addPassenger(Line* theLine);
int		checkIfBusFull(Line* theLine);
float	priceForPassenger(Line* theLine, Passenger* thePassenger);
float	profitFromPassengersForLine(Line* theLine);
int		initLine(Line* theLine, Line** lineArr, int lineCount, Bus* pBus, Driver* pDriver);
void	printLine(const void* v);
void	freeLine(Line* theLine);
int		saveLineToTextFile(Line* theLine, FILE* f);
int		readLineFromTextFile(Line* theLine, FILE* f);
int		saveLineToBinaryFile(Line* theLine, FILE* f);
int		readLineFromBinaryFile(Line* theLine, FILE* f);
void*	isLineNumUniqe(void** lineArr, int lineCount, int num);


#endif