#ifndef __DATA_HP_H
#define __DATA_HP_H

#include <stdint.h>
#include "stm32f10x.h"

#define TRUE 1
#define FALSE 0

typedef enum{
	STATE_OFF = 0x00,
	STATE_ON,
	STATE_UNDONE,
	STATE_DONE,
	FUN_STATE_EXIT,
	FUN_STATE_INIT,
	FUN_STATE_RUN,
	FUN_STATE_EXCUTED,
	FUN_STATE_NULL,
}StateEnum;

typedef StateEnum (*pFunction)(void);


typedef struct dataTemStruct{
	uint16_t targetBoxT;
	uint16_t targetWarmT;
	uint16_t realBoxT;
	uint16_t realWarmT;
}dataTemStruct;

typedef struct dataRelayStruct{
	uint16_t relay;
}dataRelayStruct;

typedef enum{
	Relay01Box=0x00,
	Relay02Warm,
	Relay03,
	Relay04,
	RelayMax
}RelayBits;

typedef enum{
	SIG_FUN_OFF,
	SIG_FUN_ON,			
	SIG_MAKE_COLD,		//����
	SIG_MAKE_HotWater,	//���ȣ�
	SIG_FUN_MAX
}SigFunState;

typedef struct{
	uint16_t state;				//״̬�����
	int16_t inTemper;			//�����¶�
	int16_t outTemper;			//�����¶�
	int16_t evaporateTemper;	//�����¶�
	int16_t current;			//����
	int16_t valveMainStep;		//���������ͷ�����
	int16_t valveSubStep;		//�����������ͷ�����
}Machine_t;

typedef struct{
	int16_t SetWaterTSet;		//����ˮ��
	int16_t setWaterCycleTemper;	//����ˮ�»ز�
	int16_t setDefrostInTemper;	//�����˪�¶�
	uint32_t setDefrostRunTimes;		//��˪ʱ��

	uint32_t setDefrostCycleTimes;		//��˪����
	int16_t setDefrostOutTemper;		//�˳���˪�¶�

	int16_t setDefrostInOffset;			//��˪����ƫ��

	int16_t setDefrostMode;			//��˪���Ʒ�ʽ	

	int16_t setValveMode;			//�������ͷ����Ʒ�ʽ
	int16_t setValveManulSteps;		//�ֶ��������ͷ�����
	int16_t setSuperHeatLow5;		//����5�����¹��ȶ�
	int16_t setSuperHeatOver5;		//����5�����Ϲ��ȶ�
	int16_t setElecHeatOnTemper;	//���ȹ����������趨�¶�

	int16_t setElecOnState;			//ǿ�����������
	int16_t setCompressorNumbers;	//ѹ��������
	int16_t setCurrentProtectMax;	//����������׼
	int16_t setPhaseProtect;		//��λ����

	int16_t setWorkMode;			//���仹������
	int16_t setColdWaterT;			//�����¶�
	//��������..
	uint16_t errState;	//err����״̬
	uint16_t cd4051DectState;	//cd4051����״̬

	int16_t setAirout_water;		//����-ˮ�²�ֵ

	int16_t waterIn;
	int16_t waterOut;
	int16_t waterBank;			//ˮ���¶�
	int16_t environT;			//����
	int16_t innerTemper;		//�ڲ��¶�
	uint16_t valvesteps;
	Machine_t machineA;
}CoreParams_t;

typedef struct {
	pFunction init;
	pFunction exit;
	pFunction run;
}xRunFunctions,pRunFunctions;

typedef struct funStruct{
	SigFunState CurrentFunState;
	SigFunState preFunState;
}funStruct;

typedef struct  IOControl
{
	uint8_t 		name;
	uint16_t		pin;
	GPIO_TypeDef*	port;
	uint32_t		clk;
}IOControl;

typedef struct dataAllStruct{
	dataTemStruct dataTemp;
	dataRelayStruct dataRelay;
	funStruct	funcRun;
	CoreParams_t coreParems;
}dataAllStruct;



void Data_setTargetBoxT(uint16_t dataBoxT);
uint16_t Data_getTargetBoxT(void);
void Data_setTargetWarmT(uint16_t targetWarmT);
uint16_t Data_getTargetWarmT(void);
void Data_setRealWarmT(uint16_t realWarmT);
uint16_t Data_getRealWarmT(void);
void Data_setRealBoxT(uint16_t realBoxT);
uint16_t Data_getRealBoxT(void);
void Data_setRelayState(RelayBits relayBit, StateEnum state);
uint16_t Data_getRelayState(uint16_t relayBit);
void Data_setCurrentFunState(SigFunState newFunc);
SigFunState Data_getCurrentFunState(void);
void Data_setPreFunState(SigFunState newFunc);
SigFunState Data_getPreFunState(void);


int16_t iQUE_getUpperLimit(void);
int16_t iQUE_getWorkerModel(void);
int16_t iQUE_getAirOutTemper(void);
int16_t iQUE_getInTemper(void);
int16_t iQUE_getEvaporateTemper(void);
int16_t iQUE_getSuperheat(void);
dataAllStruct* xQue_getCoreData(void);
void iQUE_setWorkerModel(int16_t newstate);
int16_t iQUE_getWaterBankTemper(void);
int16_t iQUE_getEvirTemper(void);
#endif



