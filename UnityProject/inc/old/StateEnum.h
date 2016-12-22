#ifndef __STATE_H
#define __STATE_H
#include <stdint.h>

typedef enum StateEnum{
	STATE_OFF=0x00,
	STATE_ON,
	STATE_INIT,
	STATE_ERR,
	STATE_DATA_DONE,
	STATE_DATA_UNDONE
}StateEnum;


/************************************************************************/
/* ��ʱִ���¶ȶ�ȡ���ߵ�ѹ���(������5ms���ִ�д���)���̵����������Ҫ��ѯ״̬ 
*/
/************************************************************************/
typedef struct StateStruct{
	uint16_t state;			//״̬
	uint16_t runCount;		//ÿ������ִ�еĴ���-����
	uint16_t needRunCount;	//ÿ��������Ҫ����ִ�д�����5ms/�μ��
	uint16_t cycleTime;		//�������
	uint16_t dataProcessFlag;	//�����Ѵ���
}StateStruct,*ptrState;

//typedef enum {FALSE = 0, TRUE = 1} bool;

bool State_checkStateIsOn(ptrState s);
void State_ChangeState(ptrState s,StateEnum state,uint16_t runCount, uint16_t needRunCount, uint16_t cycleTime);
StateEnum State_getState(ptrState s);
uint16_t State_getRunCount(ptrState s);
void State_setDataProcessedFlag(ptrState s, uint16_t flag);
uint16_t State_getDataProcessedFlag(ptrState s);
void State_addRunCount(ptrState s);

uint8_t State_isStateUndone(StateEnum state);
uint8_t State_isStateDone(StateEnum state);
#endif

