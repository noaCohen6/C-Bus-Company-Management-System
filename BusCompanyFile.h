#pragma once
#ifndef __BUSCOMPANYFILE__
#define __BUSCOMPANYFILE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "General.h"
#include "BusCompany.h"


int		saveCompanyToTextFile(BusCompany* theCompany, const char* fileName);
int		readCompanyTextFile(BusCompany* theCompany, const char* fileName);
int		saveCompanyToBinaryFile(BusCompany* theCompany, const char* fileName);
int		readCompanyFromBinaryFile(BusCompany* theCompany, const char* fileName);

#endif