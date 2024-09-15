#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "FaultInBus.h"
#include "General.h"


int initFault(FaultInBus* pFault)
{
	pFault->theFault = getFaultType();
	return 1;
}
eFaultType getFaultType()
{
	int option = 0;
	printf("\n");
	do
	{
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofFaultType; i++)
			printf("%d for %s\n", i, FaultTypeStr[i]);
		scanf("%d", &option);

	} while (option < 0 || option >= eNofFaultType);
	return (eFaultType)option;
}

char* getFaultTypeStr(int type)
{
	if (type < 0 || type >= eNofFaultType)
		return NULL;
	return FaultTypeStr[type];

}
int getFaultTypePriceInt(int type) 
{
	if (type < 0 || type >= eNofFaultType)
		return -1;
	return FaultTypePriceInt[type];
}
void printFault(const FaultInBus* pFault)
{
	printf("Fault type:%s\t", FaultTypeStr[pFault->theFault]);
	printf("Fault price:%d\n", FaultTypePriceInt[pFault->theFault]);
}
