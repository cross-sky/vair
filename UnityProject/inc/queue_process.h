#ifndef __QUEUE_PROCESS_H
#define __QUEUE_PROCESS_H

//#include "RTdataStruct.h"

#define QueueBuffLen 32
#define QueueBuffLenMask 0x1f

typedef uint8_t (*ptrfuntion)(void);

typedef struct{
	//	uint8_t code;
	uint8_t sig;
}QueueSig_t;

typedef struct 
{
	uint8_t in;
	uint8_t out;
	QueueSig_t buff[QueueBuffLen];
}QueueProcess_t;





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

typedef struct{
	uint8_t funExcuted;			//状态是否转换完成
	uint8_t funState;			//状态
	ptrfuntion tempfun;
	ptrfuntion functions;
	ptrfuntion prefunction;
	RunState_t runState;
	CoreParams_t coreParems;
}CoreProcess_t;

void vQueSetCoreParams(Command2RequestDataStruct *srcData);

void vInpSetCoreParamADC(ptrInputProcessStruct srcData);

uint8_t xQUESigPush(uint8_t sig);
uint8_t vqueGetMachineState(void);
void vTask3QUEProcess(void);
uint8_t vQueCheck3MinDelay(void);
void vInpSetCoreParamCd4051(uint16_t srcData);

void vInpSetErrState(void);

void vQueSetCoreParamErrstate(uint16_t errType);

void vQUEGetTemperParams(Command3ReturnDataStruct *dstData);

int16_t iQUE_getInTemper(void);
int16_t iQUE_getEvaporateTemper(void);
int16_t iQUE_getSuperheat(void);

int16_t iQUE_getAirOutTemper(void);
int16_t iQUE_getEvirTemper(void);
int16_t iQUE_getWaterBankTemper(void);
int16_t iQUE_getUpperLimit(void);
int16_t iQUE_getWorkerModel(void);
void iQUE_setWorkerModel(int16_t newstate);


CoreProcess_t* xQue_getCoreData(void);

void vTaskQUEProcess(void);
void vQUEInit(void);

void iQUE_ValveChanges(ValveKinds valveKind,uint16_t step);
void vQUE_changeWorkerModel(void);
void checkWorkModelIsChange(void);
/*
void vQUESetADCDectState(uint16_t adcstate);
*/
#endif

