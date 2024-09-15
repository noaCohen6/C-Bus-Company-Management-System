#pragma once
#ifndef __PASSENGER__
#define __PASSENGER__

#define LENGTH_ID 9
#define DISCOUNT_STUDENT 0.15 
#define DISCOUNT_SOLDIER 0.9
#define DISCOUNT_CHILD 0.15
#define DISCOUNT_PENSIONER 0.3

typedef enum {
	eOrdinary, eSoldier, eStudent, eChild, ePensioner, eNofTicketType
}eTicketType;

static char* TicketTypeStr[eNofTicketType] = { "Ordinary", "Soldier", "Student", "Child", "Pensioner" };

typedef struct
{
	char* name;
	char id[LENGTH_ID + 1];
	eTicketType ticketType;
}Passenger;

int		initPassenger(Passenger* thePassenger, Passenger** passengerArr, int countPassenger);
void	getPassengerID(char* id);
int		isSamePassenger(Passenger* p1, Passenger* p2);
eTicketType getTicketType();
char*	getTicketTypeStr(int type);
void	printPassenger(const void* v);
void	freePassenger(Passenger* thePassenger);
int		savetPassengerToBinaryFile(Passenger* pPassenger, FILE* f);
int		readPassengerFromBinaryFile(Passenger* pPassenger, FILE* f);
int		savetPassengerToTextFile(Passenger* pPassenger, FILE* f);
int		readPassengerFromTextFile(Passenger* pPassenger, FILE* f);
int		convertToTicketTypeEnum(char* str);



#endif