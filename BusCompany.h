#pragma once
#ifndef __BUSCOMPANY__
#define __BUSCOMPANY__
#include "Passenger.h"
#include "Date.h"
#include "Station.h"
#include "Bus.h"
#include "Driver.h"
#include "Line.h"
#include "macros.h"

typedef enum {
	eNumber, eStation, eDate, eNoSort, eNofSortTypes
} eSortType;

static const char* SortTypeStr[eNofSortTypes]
= { "Number Line", "First Station", "Date","No Sort" };

typedef struct
{
	char* name;
	Line** allLines;
	Bus* allBuses;
	Driver** allDrivers;
	Station** allStations;
	int countLines;
	int countBuses;
	int countDrivers;
	int countStations;
	eSortType	sortType;
}BusCompany;


int		addLine(BusCompany* theCompany);
int		addBus(BusCompany* theCompany);
int		addDriver(BusCompany* theCompany);
int		addStation(BusCompany* theCompany);
int		addStationToLine(BusCompany* theCompany);
int		removeStationFromLine(BusCompany* theCompany);
void	companyProfit(BusCompany* theCompany);
int		initCompany(BusCompany* theCompany);
void	printCompany(const BusCompany* theCompany);
void	freeCompany(BusCompany* theCompany);
void	addFaultToBus(BusCompany* theCompany);
void	removeFaultFromBus(BusCompany* theCompany);
void	addPassengerToLine(BusCompany* theCompany);
void	getBestDriver(BusCompany* theCompany);
void	printAllLines(const BusCompany* theCompany);
void	printAllBuses(const BusCompany* theCompany);
void	printAllStations(const BusCompany* theCompany);
void	printAllDrivers(const BusCompany* theCompany);
eSortType getSortType();
void	sortLine(BusCompany* theCompany);
void	findLine(BusCompany* theCompany);
int		compareLineByNumber(const void* v1, const void* v2);
int		compareLineByFirstStation(const void* v1, const void* v2);
int		compareLineByDate(const void* v1, const void* v2);

#endif