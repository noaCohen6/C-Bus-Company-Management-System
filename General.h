#pragma once
#ifndef __GENERAL__
#define __GENERAL__
#include "list.h"


#define MAX_STR_LEN 255


char*	getStrExactName(const char* msg);
char*	myGets(char* buffer, int size, FILE* f);
char*	getDynStr(char* str);
int		listLength(NODE* head);
void	generalArrayFunction(void* arr, int count, int sizeElement, void (*f)(void* element));
int		getIntNum(const char* msg, void* arr, int count, int (*func)(void*, int, int));
float	getFloatNum(const char* msg);
void*	Find(const char* msg, void** arr, int count, void* (*func)(void*, int, int));
int		countDigits(int num);




#endif