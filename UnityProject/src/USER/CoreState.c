#include "cominc.h"

//��ʼ״̬����ת�����
static StateEnum _funSwitchState = FUN_STATE_RUN;
static StateEnum _funChangeFlag = FUN_STATE_DONE;
static StateEnum _stateChangeFlag = FUN_STATE_DONE;
static uint8_t _haveNewStateFlag=0;
static SigFunState _newState;

static pFunction _tempFun ;

void CoreState_setFunChangeFlag(StateEnum newState)
{
	_funChangeFlag = newState;
}
StateEnum CoreState_getFunChangeFlag(void)
{
	return _funChangeFlag;
}
void CoreState_setFunSwitchState(StateEnum newState)
{
	_funSwitchState = newState;
}
StateEnum CoreState_getFunSwitchState(void)
{
	return _funSwitchState;
}

void CoreState_setStateChangeFlag(StateEnum newState)
{
	_stateChangeFlag = newState;
}
StateEnum CoreState_getStateChangeFlag(void)
{
	return _stateChangeFlag;
}

uint8_t isStateUndone(StateEnum state)
{
	return state == FUN_STATE_UNDONE;
}

uint8_t isStateDone(StateEnum state)
{
	return state == FUN_STATE_DONE;
}

void setTempFun(pFunction fun)
{
	_tempFun = fun;
}

StateEnum runTempFun(void)
{
	return _tempFun();
}
void setRunfun(StateEnum state)
{
	switch(state)
	{
	case FUN_STATE_EXIT: 
		//��ȡǰһ��״̬������exit
		setTempFun(RunFun_getRunFun(Data_getPreFunState()).exit);
		break;
	case FUN_STATE_INIT:
		//��ȡ��ǰ״̬������init
		setTempFun(RunFun_getRunFun(Data_getCurrentFunState()).init);
		break;
	case FUN_STATE_RUN:
		//����״̬ת����ɣ����ú���ת�����
		//������״̬��run
		setTempFun(RunFun_getRunFun(Data_getCurrentFunState()).run);
		break;
	default:break;
	}
}
uint16_t CoreState_haveNewStateFlag(void)
{
	return _haveNewStateFlag;
}

void CoreState_setNewStateFlag(uint8_t newFlag)
{
	_haveNewStateFlag = newFlag;
}

SigFunState CoreState_getNewState(void)
{
	return _newState;
}
void CoreState_setNewState(SigFunState newState)
{
	_newState = newState;
}


void setFlagAndState()
{
	//1.1����״̬ת��undone
	//1.2���ú���ת��undone
	//1.3���ú���ת����־exit
	CoreState_setStateChangeFlag(FUN_STATE_UNDONE);
	CoreState_setFunChangeFlag(FUN_STATE_UNDONE);
	CoreState_setFunSwitchState(FUN_STATE_EXIT);

	//1.3.1������״̬�������״̬

	Data_setPreFunState(Data_getCurrentFunState());
	Data_setCurrentFunState(CoreState_getNewState());

	//1.4���������״̬-----��������Ҫɾ��
	CoreState_setNewStateFlag(0);
}

void CoreState_coreFun(void)
{
	if (isStateDone(CoreState_getStateChangeFlag()))
	{
		//1.�Ƿ������״̬��ת��
		if (CoreState_haveNewStateFlag())
		{
			setFlagAndState();
		}
	}
	if (isStateUndone(CoreState_getFunChangeFlag()))
	{
		//����funChangeFlag��ȡҪִ�еĺ���ָ��
		setRunfun(CoreState_getFunSwitchState());
	}
	CoreState_setFunSwitchState(runTempFun());
	//runTempFun();
}

void CoreState_init(void)
{
	_tempFun = RunFun_getRunFun(SIG_FUN_OFF).run;
}

