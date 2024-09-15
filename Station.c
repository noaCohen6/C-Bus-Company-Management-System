#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Station.h"
#include "General.h"

int		isSameStation(Station** stationArr, int count, int num)
{
	for (int i = 0; i < count; i++)
	{
		if (stationArr[i]->stationNumber == num)
			return 0;
	}
	return 1;
}
int isStationExiest(const void* v1, const void* v2)
{
	const Station* s1 = (const Station*)v1;
	int s2 = *((int*)v2);

	if (s1->stationNumber == s2)
		return 1;
	return 0;
}
int initStation(Station* theStation, Station** stationArr, int stationCount)
{
	theStation->name = getStrExactName("Please enter station name:\n");
	if (!theStation->name)
		return 0;
	theStation->stationNumber = getIntNum("Please enter station number:\n", stationArr, stationCount, isSameStation);
		
	return 1;
}
void	printStation(const Station* theStation)
{
	printf("Station Name: %-10s Station Number: %d\n", theStation->name, theStation->stationNumber);
}
void freeStation(Station* theStation)
{
	free(theStation->name);
}
int		saveStationToTextFile(Station* theStation, FILE* f)
{
	int len = (int)strlen(theStation->name) + 1;
	fprintf(f,"%d\n%s\n%d\n", len,theStation->name, theStation->stationNumber);
	return 1;
}
int		readStationFromTextFile(Station* theStation, FILE* f)
{
	char temp[MAX_STR_LEN] = { 0 };
	int len = 0;

	if (fscanf(f, "%d",&len) != 1)
		return 0;
	theStation->name = (char*)malloc(len * sizeof(char));
	if (!theStation->name)
		return 0;
	if (myGets(temp, MAX_STR_LEN, f) == NULL)
		return 0;
	temp[strcspn(temp, "\n")] = '\0';
	theStation->name = _strdup(temp);
	if (!theStation->name)
		return 0;
	if(fscanf(f, "%d", &theStation->stationNumber) !=1)
	{
		free(theStation->name);
		return 0;
	}
	return 1;
}
int		saveStationToBinaryFileCompressed(const Station* theStasion, FILE* f)
{
	BYTE data[2] = { 0 };

	int len = (int)strlen(theStasion->name);
	data[0] = len ;
	data[1] = (len & 0x01) << 7 | (theStasion->stationNumber & 0x7F);

	if (fwrite(&data, sizeof(BYTE), 2, f) != 2)
		return 0;

	if (fwrite(theStasion->name, sizeof(char), len, f) != len)
		return 0;

	return 1;
}
int		readStationFromBinaryFileCompressed(Station* theStasion, FILE* f)
{
	BYTE data[2];
	if (fread(&data, sizeof(BYTE), 2, f) != 2)
		return 0;

	int len = data[0] | ((data[1] >> 7) & 0x1);
	theStasion->stationNumber = data[1] & 0x7F;

	theStasion->name = (char*)calloc(len + 1, sizeof(char));
	if (!theStasion->name)
		return 0;

	if (fread(theStasion->name, sizeof(char), len, f) != len)
	{
		free(theStasion->name);
		return 0;
	}
	return 1;
}

void* isStationNumUnique(void** stationArr, int stationCount, int num)
{
	int stationNum = stationCount;
	Station** arr =   (Station**)stationArr;
	for (int i = 0; i < stationNum; i++)
	{
		if (arr[i]->stationNumber == num)
			return arr[i];
	}
	return NULL;
}
void copyStation(Station* destination, const Station* source)
{
	destination->name = _strdup(source->name);
	destination->stationNumber = source->stationNumber;
}