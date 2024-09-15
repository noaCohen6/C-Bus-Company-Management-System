#include <stdio.h>
#include <stdlib.h>
#include "BusCompany.h"
#include "Line.h"
#include "General.h"
#include "BusCompanyFile.h"


#define FLIE_NAME_TEXT "BusCompany.txt"
#define FLIE_NAME_BIN "BusCompany.bin"

void UploadSystemFromTextOrBinaryFile(BusCompany* company);

int main() {
	BusCompany company;
	//initCompany(&company);

	int option = 0;
	while (option != -1)
	{
		printf("\n\nPlease choose one of the following options\n");
		printf("0 - Upload System From Text Or Binary File\n");
		printf("1 - Print Bus Company\n");
		printf("2 - Add Station\n");
		printf("3 - Add Bus\n");
		printf("4 - Add Driver\n");
		printf("5 - Add Line\n");
		printf("6 - Add Passenger To Line\n");
		printf("7 - Add Fault To Bus\n");
		printf("8 - Remove Fault From Bus\n");
		printf("9 - Add Station To Line\n");
		printf("10 - Remove Station From Line\n");
		printf("11 - Sort Lines\n");
		printf("12 - Search Lines\n");
		printf("13 - Company Profit\n");
		printf("14 - The Driver With The Most Trips\n");
		printf("-1 - Exit And Free\n");

		scanf("%d", &option);
		switch (option)
		{
		case 0:
			UploadSystemFromTextOrBinaryFile(&company);
			break;
		case 1:
			printCompany(&company);
			break;
		case 2:
			addStation(&company);
			break;
		case 3:
			addBus(&company);
			break;
		case 4:
			addDriver(&company);
			break;
		case 5:
			addLine(&company);
			break;
		case 6:
			addPassengerToLine(&company);
			break;
		case 7:
			addFaultToBus(&company);
			break;
		case 8:
			removeFaultFromBus(&company);
			break;
		case 9:
			addStationToLine(&company);
			break;
		case 10:
			removeStationFromLine(&company);
			break;
		case 11:
			sortLine(&company);
			break;
		case 12:
			findLine(&company);
			break;
		case 13:
			companyProfit(&company);
			break;
		case 14:
			getBestDriver(&company);
			break;
		case -1:
			printf("Bey Bey");
			saveCompanyToTextFile(&company, FLIE_NAME_TEXT);
			saveCompanyToBinaryFile(&company, FLIE_NAME_BIN);
			freeCompany(&company);
			break;
		default:
			printf("Wrong option");
			break;
		}
	}

}
void UploadSystemFromTextOrBinaryFile(BusCompany* company)
{
	int option = 0;
	while (option != -1)
	{
		printf("\n\nPlease choose one of the following options\n");
		printf("1 - Upload System From Text File\n");
		printf("2 - Upload System From Binary File\n");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			readCompanyTextFile(company, FLIE_NAME_TEXT);
			option = -1;
			break;
		case 2:
			readCompanyFromBinaryFile(company, FLIE_NAME_BIN);
			option = -1;
			break;
		default:
			printf("Wrong option");
			break;
		}
	}
}