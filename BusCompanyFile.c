
#include "BusCompanyFile.h"

int		saveCompanyToTextFile(BusCompany* theCompany, const char* fileName)
{
	FILE* f;
	int lenghtName = (int)strlen(theCompany->name) + 1;
	f = fopen(fileName, "w");
	if (!f)
		return 0;
	fprintf(f, "%d\n%s\n", lenghtName, theCompany->name);
	fprintf(f, "%d\n", theCompany->countLines);
	for (int i = 0; i < theCompany->countLines; i++)
	{
		if (saveLineToTextFile(theCompany->allLines[i], f) == 0)
			return 0;
	}
	fprintf(f, "%d\n", theCompany->countBuses);
	for (int i = 0; i < theCompany->countBuses; i++)
	{
		if (savetBusToTextFile(&theCompany->allBuses[i], f) == 0)
			return 0;
	}
	fprintf(f, "%d\n", theCompany->countDrivers);
	for (int i = 0; i < theCompany->countDrivers; i++)
	{
		if (saveDriverToTextFile(theCompany->allDrivers[i], f) == 0)
			return 0;
	}
	fprintf(f, "%d\n", theCompany->countStations);
	for (int i = 0; i < theCompany->countStations; i++)
	{
		if (saveStationToTextFile(theCompany->allStations[i], f) == 0)
			return 0;
	}
	fclose(f);
	return 1;
}
int		readCompanyTextFile(BusCompany* theCompany, const char* fileName)
{
	theCompany->countLines = 0;
	theCompany->allLines = NULL;
	theCompany->countBuses = 0;
	theCompany->allBuses = NULL;
	theCompany->countDrivers = 0;
	theCompany->allDrivers = NULL;
	theCompany->countStations = 0;
	theCompany->allStations = NULL;
	theCompany->sortType = eNoSort;

	int len = 0;
	FILE* f;
	f = fopen(fileName, "r");
	if (!f)
		return 0;
	char temp[MAX_STR_LEN] = { 0 };
	if (fscanf(f, "%d", &len) != 1)
	{
		fclose(f);
		return 0;
	}
	theCompany->name = (char*)malloc(len * sizeof(char));
	CHECK_COLSE_RETURN(theCompany->name, f);

	if (myGets(temp, MAX_STR_LEN, f) == NULL)
		return 0;
	temp[strcspn(temp, "\n")] = '\0';
	theCompany->name = _strdup(temp);
	CHECK_COLSE_RETURN(theCompany->name, f);
	if (fscanf(f, "%d", &theCompany->countLines) != 1)
	{
		free(theCompany->name);
		fclose(f);
		return 0;
	}
	temp[strcspn(temp, "\n")] = '\0';
	theCompany->allLines = (Line**)realloc(theCompany->allLines, theCompany->countLines * sizeof(Line*));
	CHECK_FREE_COLSE_RETURN(theCompany->allLines, theCompany->name, f);

	for (int i = 0; i < theCompany->countLines; i++)
	{
		theCompany->allLines[i] = (Line*)calloc(1, sizeof(Line));
		CHECK_FREE_COLSE_RETURN(theCompany->allLines[i], theCompany->name, f);

		if (readLineFromTextFile(theCompany->allLines[i], f) == 0)
		{
			free(theCompany->name);
			fclose(f);
			return 0;
		}
	}
	if (fscanf(f, "%d", &theCompany->countBuses) != 1)
	{
		free(theCompany->name);
		fclose(f);
		return 0;
	}
	temp[strcspn(temp, "\n")] = '\0';
	theCompany->allBuses = (Bus*)realloc(theCompany->allBuses, theCompany->countBuses * sizeof(Bus));
	CHECK_FREE_COLSE_RETURN(theCompany->allBuses, theCompany->name, f);

	for (int i = 0; i < theCompany->countBuses; i++)
	{
		Bus* b = (Bus*)calloc(1, sizeof(Bus));
		CHECK_FREE_COLSE_RETURN(b, theCompany->name, f);

		theCompany->allBuses[i] = *b;
		if (readBusFromTextFile(&theCompany->allBuses[i], f) == 0)
		{
			free(theCompany->name);
			fclose(f);
			return 0;
		}
		free(b);
	}
	if (fscanf(f, "%d", &theCompany->countDrivers) != 1)
	{
		free(theCompany->name);
		fclose(f);
		return 0;
	}
	temp[strcspn(temp, "\n")] = '\0';
	theCompany->allDrivers = (Driver**)realloc(theCompany->allDrivers, theCompany->countDrivers * sizeof(Driver*));
	CHECK_FREE_COLSE_RETURN(theCompany->allDrivers, theCompany->name, f);

	for (int i = 0; i < theCompany->countDrivers; i++)
	{
		theCompany->allDrivers[i] = (Driver*)calloc(1, sizeof(Driver));
		CHECK_FREE_COLSE_RETURN(theCompany->allDrivers[i], theCompany->name, f);

		if (readDriverFromTextFile(theCompany->allDrivers[i], f) == 0)
		{
			free(theCompany->name);
			fclose(f);
			return 0;
		}
	}
	if (fscanf(f, "%d", &theCompany->countStations) != 1)
	{
		free(theCompany->name);
		fclose(f);
		return 0;
	}
	temp[strcspn(temp, "\n")] = '\0';
	theCompany->allStations = (Station**)realloc(theCompany->allStations, theCompany->countStations * sizeof(Station*));
	CHECK_FREE_COLSE_RETURN(theCompany->allStations, theCompany->name, f);

	for (int i = 0; i < theCompany->countStations; i++)
	{
		theCompany->allStations[i] = (Station*)calloc(1, sizeof(Station));
		CHECK_FREE_COLSE_RETURN(theCompany->allStations[i], theCompany->name, f);

		if (readStationFromTextFile(theCompany->allStations[i], f) == 0)
		{
			free(theCompany->name);
			fclose(f);
			return 0;
		}
	}
	fclose(f);
	return 1;
}
int		saveCompanyToBinaryFile(BusCompany* theCompany, const char* fileName)
{
	FILE* f;
	int lengthName = (int)strlen(theCompany->name) + 1;
	f = fopen(fileName, "wb");
	if (!f)
		return 0;
	if (fwrite(&lengthName, sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return 0;
	}
	if (fwrite(theCompany->name, sizeof(char), lengthName, f) != lengthName)
	{
		fclose(f);
		return 0;
	}
	if (fwrite(&theCompany->countLines, sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return 0;
	}
	for (int i = 0; i < theCompany->countLines; i++)
	{
		if (saveLineToBinaryFile(theCompany->allLines[i], f) == 0)
		{
			fclose(f);
			return 0;
		}
	}
	if (fwrite(&theCompany->countBuses, sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return 0;
	}
	for (int i = 0; i < theCompany->countBuses; i++)
	{
		if (savetBusToBinaryFile(&theCompany->allBuses[i], f) == 0)
		{
			fclose(f);
			return 0;
		}
	}
	if (fwrite(&theCompany->countDrivers, sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return 0;
	}
	for (int i = 0; i < theCompany->countDrivers; i++)
	{
		if (saveDriverToBinaryFile(theCompany->allDrivers[i], f) == 0)
		{
			fclose(f);
			return 0;
		}
	}
	if (fwrite(&theCompany->countStations, sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return 0;
	}
	for (int i = 0; i < theCompany->countStations; i++)
	{
		if (saveStationToBinaryFileCompressed(theCompany->allStations[i], f) == 0)
		{
			fclose(f);
			return 0;
		}
	}
	fclose(f);
	return 1;
}
int		readCompanyFromBinaryFile(BusCompany* theCompany, const char* fileName)
{
	theCompany->countLines = 0;
	theCompany->allLines = NULL;
	theCompany->countBuses = 0;
	theCompany->allBuses = NULL;
	theCompany->countDrivers = 0;
	theCompany->allDrivers = NULL;
	theCompany->countStations = 0;
	theCompany->allStations = NULL;
	theCompany->sortType = eNoSort;

	FILE* f;
	int lengthName = 0;
	f = fopen(fileName, "rb");
	if (!f)
		return 0;
	if (fread(&lengthName, sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return 0;
	}
	theCompany->name = (char*)malloc(lengthName * sizeof(char));
	CHECK_COLSE_RETURN(theCompany->name, f);

	if (fread(theCompany->name, sizeof(char), lengthName, f) != lengthName)
	{
		free(theCompany->name);
		fclose(f);
		return 0;
	}

	if (fread(&theCompany->countLines, sizeof(int), 1, f) != 1)
	{
		free(theCompany->name);
		fclose(f);
		return 0;
	}
	theCompany->allLines = (Line**)realloc(theCompany->allLines, theCompany->countLines * sizeof(Line*));
	CHECK_FREE_COLSE_RETURN(theCompany->allLines, theCompany->name, f);

	for (int i = 0; i < theCompany->countLines; i++)
	{
		theCompany->allLines[i] = (Line*)calloc(1, sizeof(Line));
		CHECK_FREE_COLSE_RETURN(theCompany->allLines[i], theCompany->name, f);

		if (readLineFromBinaryFile(theCompany->allLines[i], f) == 0)
		{
			free(theCompany->name);
			fclose(f);
			return 0;
		}
	}
	if (fread(&theCompany->countBuses, sizeof(int), 1, f) != 1)
	{
		free(theCompany->name);
		fclose(f);
		return 0;
	}
	theCompany->allBuses = (Bus*)realloc(theCompany->allBuses, theCompany->countBuses * sizeof(Bus));
	CHECK_FREE_COLSE_RETURN(theCompany->allBuses, theCompany->name, f);

	for (int i = 0; i < theCompany->countBuses; i++)
	{
		Bus* b = (Bus*)calloc(1, sizeof(Bus));
		CHECK_FREE_COLSE_RETURN(b, theCompany->name, f);

		theCompany->allBuses[i] = *b;
		if (readBusFromBinaryFile(&theCompany->allBuses[i], f) == 0)
		{
			free(theCompany->name);
			fclose(f);
			return 0;
		}
		free(b);
	}
	if (fread(&theCompany->countDrivers, sizeof(int), 1, f) != 1)
	{
		free(theCompany->name);
		fclose(f);
		return 0;
	}
	theCompany->allDrivers = (Driver**)realloc(theCompany->allDrivers, theCompany->countDrivers * sizeof(Driver*));
	CHECK_FREE_COLSE_RETURN(theCompany->allDrivers, theCompany->name, f);

	for (int i = 0; i < theCompany->countDrivers; i++)
	{
		theCompany->allDrivers[i] = (Driver*)calloc(1, sizeof(Driver));
		CHECK_FREE_COLSE_RETURN(theCompany->allDrivers[i], theCompany->name, f);

		if (readDriverFromBinaryFile(theCompany->allDrivers[i], f) == 0)
		{
			free(theCompany->name);
			fclose(f);
			return 0;
		}
	}
	if (fread(&theCompany->countStations, sizeof(int), 1, f) != 1)
	{
		free(theCompany->name);
		fclose(f);
		return 0;
	}
	theCompany->allStations = (Station**)realloc(theCompany->allStations, theCompany->countStations * sizeof(Station*));
	CHECK_FREE_COLSE_RETURN(theCompany->allStations, theCompany->name, f);

	for (int i = 0; i < theCompany->countStations; i++)
	{
		theCompany->allStations[i] = (Station*)calloc(1, sizeof(Station));
		CHECK_FREE_COLSE_RETURN(theCompany->allStations[i], theCompany->name, f);

		if (readStationFromBinaryFileCompressed(theCompany->allStations[i], f) == 0)
		{
			free(theCompany->name);
			fclose(f);
			return 0;
		}
	}
	fclose(f);
	return 1;
}