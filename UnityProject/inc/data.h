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
	SIG_MAKE_COLD,		//制冷
	SIG_MAKE_HotWater,	//制热，
	SIG_FUN_MAX
}SigFunState;

typedef struct{
	uint16_t state;				//状态开或关
	int16_t inTemper;			//吸气温度
	int16_t outTemper;			//排气温度
	int16_t evaporateTemper;	//蒸发温度
	int16_t current;			//电流
	int16_t valveMainStep;		//主电子膨胀发开度
	int16_t valveSubStep;		//辅助电子膨胀阀开度
}Machine_t;

typedef struct{
	int16_t SetWaterTSet;		//设置水温
	int16_t setWaterCycleTemper;	//设置水温回差
	int16_t setDefrostInTemper;	//进入除霜温度
	uint32_t setDefrostRunTimes;		//除霜时间

	uint32_t setDefrostCycleTimes;		//除霜周期
	int16_t setDefrostOutTemper;		//退出除霜温度

	int16_t setDefrostInOffset;			//除霜进入偏差

	int16_t setDefrostMode;			//除霜控制方式	

	int16_t setValveMode;			//电子膨胀阀控制方式
	int16_t setValveManulSteps;		//手动电子膨胀阀步数
	int16_t setSuperHeatLow5;		//环温5℃以下过热度
	int16_t setSuperHeatOver5;		//环温5℃以上过热度
	int16_t setElecHeatOnTemper;	//发热管启动环境设定温度

	int16_t setElecOnState;			//强制启动电加热
	int16_t setCompressorNumbers;	//压缩机数量
	int16_t setCurrentProtectMax;	//电流保护基准
	int16_t setPhaseProtect;		//相位保护

	int16_t setWorkMode;			//制冷还是制热
	int16_t setColdWaterT;			//制冷温度
	//。。。。..
	uint16_t errState;	//err错误状态
	uint16_t cd4051DectState;	//cd4051错误状态

	int16_t setAirout_water;		//排气-水温插值

	int16_t waterIn;
	int16_t waterOut;
	int16_t waterBank;			//水箱温度
	int16_t environT;			//环温
	int16_t innerTemper;		//内部温度
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



