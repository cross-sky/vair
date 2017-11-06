#include "data.h"

static dataAllStruct dataParam;

dataAllStruct* xQue_getCoreData(void)
{
	return &dataParam;
}

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

void Data_setCurrentFunState(SigFunState newFunc)
{
	dataParam.funcRun.CurrentFunState = newFunc;
}

SigFunState Data_getCurrentFunState(void)
{
	return dataParam.funcRun.CurrentFunState;
}

SigFunState Data_getPreFunState(void)
{
	return dataParam.funcRun.preFunState;
}

void Data_setPreFunState(SigFunState newFunc)
{
	dataParam.funcRun.preFunState = newFunc;
}


int16_t iQUE_getUpperLimit(void)
{
	return dataParam.coreParems.setAirout_water;
}

//��ȡ�����¶�
int16_t iQUE_getAirOutTemper(void)
{
	return dataParam.coreParems.machineA.outTemper;
}

//��ȡ�����¶�
int16_t iQUE_getInTemper(void)
{
	return dataParam.coreParems.machineA.inTemper;
}

//��ȡ�����¶�
int16_t iQUE_getEvaporateTemper(void)
{
	//����ʱ�����¶ȣ�ѡ������̽ͷ
	return dataParam.coreParems.machineA.evaporateTemper;
}

//��ȡ�����¶�
int16_t iQUE_getEvirTemper(void)
{
	return dataParam.coreParems.environT;
}

//��ȡˮ���¶�
int16_t iQUE_getWaterBankTemper(void)
{
	return dataParam.coreParems.waterBank;
}

int16_t iQUE_getColdModelSuperHeat(void)
{
	//����-ˮ�²����ж�
	int16_t data=0;
	int16_t temp = iQUE_getAirOutTemper() - iQUE_getWaterBankTemper();
	if (temp <= 400)
	{
		data = 50;
	}else if(temp >= 700)
	{
		data = 20;
	}else{
		data = (int16_t)(temp*(-0.1)) + 90;
	}
	return data;
}

int16_t iQUE_getHotWaterModelSuperHeat(void)
{
	int16_t data=0;
	int16_t envirT = iQUE_getEvirTemper();
	if (envirT > 300)
	{
		data = 60;
	}
	else if (envirT < -100)
	{
		data = 20;
	}else{
		//-10ʱ���ȶ�2��0��ʱ���ȶ�3
		data = (int16_t)(envirT*0.1) + 30;
	}

	//ˮ��>40�ȣ����ȶ�-1
	if (iQUE_getWaterBankTemper() >= 400)
	{
		data -=10;
	}
	return data;
}

//���ݻ��£�ˮ��ȷ�����ʵĹ��ȶ�
int16_t iQUE_getSuperheat(void)
{
	return iQUE_getHotWaterModelSuperHeat();
}


void Data_init(void)
{
	dataParam.coreParems.setAirout_water = 20 * 10;
}