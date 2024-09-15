#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Date.h"
#include "General.h"

const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
#define SPECIAL_TAV '/'

void getCorrectDate(Date* pDate)
{
	char date[MAX_STR_LEN];
	int ok = 1;

	do {
		printf("Enter Flight Date dd%c%cmm%c%cyyyy  minimum year %d\t",
			SPECIAL_TAV, SPECIAL_TAV, SPECIAL_TAV, SPECIAL_TAV, MIN_YEAR);
		myGets(date, MAX_STR_LEN, NULL);
		ok = checkDate(date, pDate);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);
}


int	 checkDate(char* date, Date* pDate)
{
	int day, month, year;
	if (strlen(date) != 12)
		return 0;
	if ((date[2] != SPECIAL_TAV) || (date[3] != SPECIAL_TAV)
		|| (date[6] != SPECIAL_TAV) || (date[7] != SPECIAL_TAV))
		return 0;
	sscanf(date, "%d%*c%*c%d%*c%*c%d", &day, &month, &year);
	if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR)
		return 0;

	if (day > DAY_MONTHS[month - 1])
		return 0;

	pDate->day = day;
	pDate->month = month;
	pDate->year = year;

	return 1;
}

void printDate(const Date* pDate)
{
	printf("Date: %d/%d/%d\n\t", pDate->day, pDate->month, pDate->year);
}

int savetDateToTextFile(Date* pDate, FILE* f)
{
	fprintf(f, "%d\n%d\n%d\n", pDate->day, pDate->month, pDate->year);
	return 1;
}
int readDateFromTextFile(Date* pDate, FILE* f)
{
	fscanf(f, "%d", &pDate->day);
	if (!pDate->day)
		return 0;
	fscanf(f, "%d", &pDate->month);
	if (!pDate->month)
		return 0;
	fscanf(f, "%d", &pDate->year);
	if (!pDate->year)
		return 0;
	return 1;
}
int savetDateToBinaryFile(Date* pDate, FILE* f)
{
	if (fwrite(pDate, sizeof(Date), 1, f) != 1)
		return 0;
	return 1;
}

int readDateFromBinaryFile(Date* pDate, FILE* f)
{
	if (fread(pDate, sizeof(Date), 1, f) != 1)
		return 0;
	return 1;
}
