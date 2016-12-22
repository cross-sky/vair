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
	SIG_FUN_MAX
}SigFunState;


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

#endif



