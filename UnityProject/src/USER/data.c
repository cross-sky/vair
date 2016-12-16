#include "data.h"

static dataAllStruct dataParam;
void Data_setTargetBoxT(uint16_t targetBoxT)
{
	dataParam.dataTemp.targetBoxT = targetBoxT;
}

uint16_t Data_getTargetBoxT(void)
{
	return dataParam.dataTemp.targetBoxT;
}

void Data_setTargetWarmT(uint16_t targetWarmT)
{
	dataParam.dataTemp.targetWarmT = targetWarmT;
}

uint16_t Data_getTargetWarmT(void)
{
	return dataParam.dataTemp.targetWarmT;
}

void Data_setRealWarmT(uint16_t realWarmT)
{
	dataParam.dataTemp.realWarmT = realWarmT;
}

uint16_t Data_getRealWarmT(void)
{
	return dataParam.dataTemp.realWarmT;
}

void Data_setRealBoxT(uint16_t realBoxT)
{
	dataParam.dataTemp.realBoxT = realBoxT;
}

uint16_t Data_getRealBoxT(void)
{
	return dataParam.dataTemp.realBoxT;
}

void Data_setRelayState(RelayBits relayBit, StateEnum state)
{
	if (relayBit >= RelayMax)
	{
		return;
	}
	if (state == STATE_ON)
	{
		dataParam.dataRelay.relay |= (1<<relayBit);
	}else{
		dataParam.dataRelay.relay &= (0<<relayBit);
	}
}

uint16_t Data_getRelayState(RelayBits relayBit)
{
	if (relayBit >= RelayMax)
	{
		return 0;
	}
	else
		return dataParam.dataRelay.relay >> relayBit;
}

void Data_setCurrentFunction(pFunction newFunc)
{
	dataParam.funcRun.CurrentFunction = newFunc;
}

pFunction Data_getCurrentFunction(void)
{
	return dataParam.funcRun.CurrentFunction;
}

pFunction Data_getPreFunction(void)
{
	return dataParam.funcRun.preFunction;
}

void Data_setPreFunction(pFunction newFunc)
{
	dataParam.funcRun.preFunction = newFunc;
}

