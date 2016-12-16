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
	DirectForward,	//���з��� 1������(����)
	DirectBack,		//������(����)
	DirectHold		//������
}VALVE_ENUM;

typedef enum ValveKinds{
	ValveMainA = 0x00,
	ValveSubB,
	ValveKindsMax
}ValveKinds;

typedef struct{
	int16_t code;// ���в���
	uint16_t sig;// ��ʼ/��˪/����״̬
	uint16_t kindValue; //���������ͷ����Ǹ��������ͷ�
}ValveSig_t;

typedef struct 
{
	uint8_t in;	//�������ӳ��ȣ���������
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
