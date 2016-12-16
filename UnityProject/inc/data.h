#ifndef __DATA_HP_H
#define __DATA_HP_H

#include <stdint.h>

#define TRUE 1
#define FALSE 0

typedef enum{
	STATE_OFF = 0x00,
	STATE_ON,
	FUN_STATE_INIT,
	FUN_STATE_RUN,
	FUN_STATE_EXIT,
	FUN_STATE_EXCUTED,
	FUN_STATE_NULL
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

typedef struct funStruct{
	pFunction CurrentFunction;
	pFunction preFunction;
}funStruct;

typedef struct dataAllStruct{
	dataTemStruct dataTemp;
	dataRelayStruct dataRelay;
	funStruct	funcRun;
}dataAllStruct;

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
	SIG_FUN_NULL,
	FUN_MAX
}FunSigState;

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
void Data_setCurrentFunction(pFunction newFunc);
pFunction Data_getCurrentFunction(void);
void Data_setPreFunction(pFunction newFunc);
pFunction Data_getPreFunction(void);

#endif