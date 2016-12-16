#ifndef __VALVE_CALC_H
#define __VALVE_CALC_H

#define ValveBuffLen 16
#define ValveBuffLenMask 0x0f

typedef enum{
	adds=2,
	decr,
	statusRun,
	statusDone,
	valveInit,
	valveClose,
	valveRun,
	DirectForward,	//运行方向 1正方向(增加)
	DirectBack,		//反方向(减少)
	DirectHold		//不运行
}VALVE_ENUM;

typedef enum ValveKinds{
	ValveMainA = 0x00,
	ValveSubB,
	ValveKindsMax
}ValveKinds;

typedef struct{
	int16_t code;// 运行步数
	uint16_t sig;// 开始/结霜/运行状态
	uint16_t kindValue; //主电子膨胀阀还是辅电子膨胀阀
}ValveSig_t;

typedef struct 
{
	uint8_t in;	//可以增加长度，长度掩码
	uint8_t out;
	ValveSig_t buff[ValveBuffLen];
}ValveProcess_t;

typedef struct{
	uint16_t valveStatus;
	uint16_t valveMode;	
	int16_t totalSteps;
	int16_t runStep;
}ValveStatus_t;

void ValveCalv_changeValveData(ValveStatus_t* src);
uint8_t ValveCalc_popSig(ValveSig_t *sig);
uint8_t ValveCalc_pushSig(ValveSig_t *srcSig);
ValveProcess_t* ValveCalc_getSigNodes(void);

#endif
