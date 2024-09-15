#pragma once
#ifndef __FAULTINBUS__
#define __FAULTINBUS__


typedef enum {
	eFlatTire, eEngineProblem, eHeadlightProblem, eAirConditionerProblem, eElectricalProblem,eNoFault ,eNofFaultType
}eFaultType;

static char* FaultTypeStr[eNofFaultType] = { "Flat Tire", "Engine Problem", "Headlight Problem", "AirConditioner Problem", "Electrical Problem", "No Fault"};

static int FaultTypePriceInt[eNofFaultType] = { 10,40,10,30,50,0 };

typedef struct
{
	eFaultType theFault;
}FaultInBus;


int		initFault(FaultInBus* pFault);
eFaultType getFaultType();
char*	getFaultTypeStr(int type);
int		getFaultTypePriceInt(int type);
void	printFault(const FaultInBus* pFault);

#endif