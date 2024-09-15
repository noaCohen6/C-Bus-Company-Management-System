#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "General.h"



char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s", msg);
	myGets(temp, MAX_STR_LEN, NULL);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}

char* myGets(char* buffer, int size, FILE* f)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do { //skip only '\n' strings
			if (f == NULL)
				ok = fgets(buffer, size, stdin);
			else
				ok = fgets(buffer, size, f);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

int listLength(NODE* head)
{
	int length = 0;
	NODE* current = head;
	while (current != NULL) {
		length++;
		current = current->next;
	}
	return length;
}

void generalArrayFunction(void* arr, int count, int sizeElement, void (*f)(void* element))
{
	for (int i = 0; i < count; i++)
	{
		f((char*)(arr)+i * sizeElement);
	}
}
int getIntNum(const char* msg, void* arr, int count, int (*func)(void*, int, int)) {
	int num;
	int unique = 0;
	do {
		printf("%s",msg);
		scanf("%d", &num);
		unique = func(arr, count, num);
	} while (!unique);
	return num;

}
float	getFloatNum(const char* msg)
{
	float num;
	
	printf("%s", msg);
	scanf("%f", &num);
		
	return num;
}
void* Find(const char* msg, void** arr, int count, void* (*func)(void*, int, int))
{
	int find;
	void* temp = NULL;
	do {
		printf("%s", msg);
		scanf("%d", &find);
		temp = func(arr, count, find);
	} while (temp == NULL);
	return temp;
}

int countDigits(int num) 
{
	int count = 0;

	while (num != 0) {
		num /= 10;
		count++;
	}
	return count;
}