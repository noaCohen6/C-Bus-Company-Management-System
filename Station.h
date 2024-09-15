#pragma once
#ifndef __STATION__
#define __STATION__

typedef unsigned char BYTE;

typedef struct
{
	char* name;
	int stationNumber;
}Station;

int		isSameStation(Station** stationArr, int count, int num);
int		isStationExiest(const void* v1, const void* v2);
int		initStation(Station* theStation, Station** stationArr, int stationCount);
void	printStation(const Station* theStation);
void	freeStation(Station* theStation);
int		saveStationToTextFile(Station* theStation, FILE* f);
int		readStationFromTextFile(Station* theStation, FILE* f);
int		saveStationToBinaryFileCompressed(const Station* theStasion, FILE* f);
int		readStationFromBinaryFileCompressed(Station* theStasion, FILE* f);
void*	isStationNumUnique(void** stationArr, int stationCount, int num);
void	copyStation(Station* destination, const Station* source);


#endif