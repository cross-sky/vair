#ifndef __STATE_H
#define __STATE_H
#include <stdint.h>

//typedef enum StateEnum{
//	STATE_OFF=0x00,
//	STATE_ON,
//	STATE_INIT,
//	STATE_ERR,
//	STATE_DATA_DONE,
//	STATE_DATA_UNDONE
//}StateEnum;


/************************************************************************/
/* ��ʱִ���¶ȶ�ȡ���ߵ�ѹ���(������5ms���ִ�д���)���̵����������Ҫ��ѯ״̬ 
*/
/************************************************************************/
typedef struct StateStruct{
	StateEnum state;			//״̬ on - off
	uint16_t runCount;		//ÿ������ִ�еĴ���-����
	uint16_t needRunCount;	//ÿ��������Ҫ����ִ�д�����5ms/�μ��
	uint16_t cycleTime;		//�������
	StateEnum dataProcessFlag;	//�����Ѵ��� done -- undone
}StateStruct,*ptrState;

//typedef enum {FALSE = 0, TRUE = 1} bool;

StateEnum State_checkState(ptrState s);
void State_ChangeState(ptrState s,ptrState src);
StateEnum State_getState(ptrState s);
uint16_t State_getRunCount(ptrState s);
void State_setDataProcessedFlag(ptrState s, StateEnum flag);
StateEnum State_getDataProcessedFlag(ptrState s);
void State_addRunCount(ptrState s);

uint8_t State_isStateUndone(StateEnum state);
uint8_t State_isStateDone(StateEnum state);
#endif

