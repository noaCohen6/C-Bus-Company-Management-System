#pragma once
#ifndef __MYDATE__
#define __MYDATE__

#define MIN_YEAR 2023

typedef struct
{
	int			day;
	int			month;
	int			year;
}Date;

void	getCorrectDate(Date* pDate);
int		checkDate(char* date, Date* pDate);
void	printDate(const Date* pDate);
int		savetDateToTextFile(Date* pDate, FILE* f);
int		readDateFromTextFile(Date* pDate, FILE* f);
int		savetDateToBinaryFile(Date* pDate, FILE* f);
int		readDateFromBinaryFile(Date* pDate, FILE* f);

#endif