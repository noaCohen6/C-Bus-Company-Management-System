#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Passenger.h"
#include "General.h"

int	initPassenger(Passenger* thePassenger,Passenger** passengerArr, int countPassenger)
{
	thePassenger->name = getStrExactName("Enter the passengers name\n");
	if (!thePassenger->name)
		return 0;
	getPassengerID(thePassenger->id);
	for (int i = 0; i < countPassenger; i++)
	{
		if (isSamePassenger(thePassenger, passengerArr[i]) == 0)
		{
			free(thePassenger->name);
			return 0;
		}
	}
	thePassenger->ticketType = getTicketType();
	return 1;
}
void getPassengerID(char* id)
{
	char temp[MAX_STR_LEN];
	int isValidID = 0;
	while (isValidID == 0)
	{
		isValidID = 1;
		printf("please enter the passengers ID number: need to be %d digits\n", LENGTH_ID);
		myGets(temp, MAX_STR_LEN, NULL);
		if (strlen(temp) != LENGTH_ID)
		{
			printf("ID should be %d digits\n", LENGTH_ID);
			isValidID = 0;
		}
		else
		{
			for (int i = 0; i < LENGTH_ID; i++)
			{
				if (isdigit(temp[i]) == 0)
				{
					printf("Need to be only digits\n");
					isValidID = 0;
					break;
				}
			}
		}

	}
	strcpy(id, temp);

}
int isSamePassenger(Passenger* p1, Passenger* p2)
{
	if (strcmp(p1->id,p2->id)==0)
		return 0;
	return 1;
}
eTicketType getTicketType()
{
	int option=0;
	printf("\n");
	do
	{
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofTicketType; i++)
			printf("%d for %s\n", i, TicketTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofTicketType);
	return (eTicketType)option;
}

char* getTicketTypeStr(int type)
{
	if (type < 0 || type >= eNofTicketType)
		return NULL;
	return TicketTypeStr[type];

}
void printPassenger(const void* v)
{
	const Passenger** thePassenger = (const Passenger**)v;
	printf("\t");
	printf("Passenger: name:%-10s\t", (*thePassenger)->name);
	printf("ID:%-10s\t", (*thePassenger)->id);
	printf("Ticket type:%s\n", TicketTypeStr[(*thePassenger)->ticketType]);
}
void freePassenger(Passenger* thePassenger)
{
	free(thePassenger->name);
}
int	savetPassengerToBinaryFile(Passenger* pPassenger, FILE* f)
{
	int len = (int)strlen(pPassenger->name) + 1;
	if (fwrite(&len, sizeof(int), 1, f) != 1)
		return 0;
	if (fwrite(pPassenger->name, sizeof(char), len, f) != len)
		return 0;
	if (fwrite(pPassenger->id, sizeof(char), LENGTH_ID, f) != LENGTH_ID)
		return 0;
	if (fwrite(&pPassenger->ticketType, sizeof(int), 1, f) != 1)
		return 0;
	return 1;
}
int	readPassengerFromBinaryFile(Passenger* pPassenger, FILE* f)
{
	int len;
	if (fread(&len, sizeof(int), 1, f) != 1)
		return 0;
	pPassenger->name = (char*)malloc(len * sizeof(char));
	if (!pPassenger->name)
		return 0;
	if (fread(pPassenger->name, sizeof(char), len, f) != len)
	{
		free(pPassenger->name);
		return 0;
	}
	if (fread(pPassenger->id, sizeof(char), LENGTH_ID, f) != LENGTH_ID)
	{
		free(pPassenger->name);
		return 0;
	}

	if (fread(&pPassenger->ticketType, sizeof(int), 1, f) != 1)
	{
		free(pPassenger->name);
		return 0;
	}
	return 1;
}

int	savetPassengerToTextFile(Passenger* pPassenger, FILE* f)
{
	int len = (int)strlen(pPassenger->name) + 1;
	fprintf(f, "%d\n%s\n%s\n%s\n", len,pPassenger->name, pPassenger->id, TicketTypeStr[pPassenger->ticketType]);
	return 1;
}
int	readPassengerFromTextFile(Passenger* pPassenger, FILE* f)
{
	char temp[MAX_STR_LEN] = { 0 };
	int len = 0;

	if (fscanf(f, "%d", &len) != 1)
		return 0;
	pPassenger->name = (char*)malloc(len * sizeof(char));
	if (!pPassenger->name)
		return 0;
	if (myGets(temp, MAX_STR_LEN, f) == NULL)
		return 0;
	temp[strcspn(temp, "\n")] = '\0';
	pPassenger->name = _strdup(temp);
	if (!pPassenger->name)
	{
		free(pPassenger->name);
		return 0;
	}
	if (myGets(temp, MAX_STR_LEN, f) == NULL)
	{
		free(pPassenger->name);
		return 0;
	}
	temp[strcspn(temp, "\n")] = '\0';
	strcpy(pPassenger->id, temp);
	if (!pPassenger->id)
	{
		free(pPassenger->name);
		free(pPassenger->id);
		return 0;
	}
	if (myGets(temp, MAX_STR_LEN, f) == NULL)
	{
		free(pPassenger->name);
		free(pPassenger->id);
		return 0;
	}
	temp[strcspn(temp, "\n")] = '\0';
	pPassenger->ticketType = convertToTicketTypeEnum(temp);
	if (pPassenger->ticketType == -1)
	{
		free(pPassenger->name);
		free(pPassenger->id);
		return 0;
	}
	return 1;
}

int convertToTicketTypeEnum(char* str) {
	if (strcmp(str, "Ordinary") == 0) {
		return 0;
	}
	else if (strcmp(str, "Soldier") == 0) {
		return 1;
	}
	else if (strcmp(str, "Student") == 0) {
		return 2;
	}
	else if (strcmp(str, "Child") == 0) {
		return 3;
	}
	else if (strcmp(str, "Pensioner") == 0) {
		return 4;
	}
	return -1;
}