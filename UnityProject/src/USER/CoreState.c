#include "cominc.h"

//初始状态设置转换完成
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
		//获取前一个状态函数的exit
		setTempFun(RunFun_getRunFun(Data_getPreFunState()).exit);
		break;
	case FUN_STATE_INIT:
		//获取当前状态函数的init
		setTempFun(RunFun_getRunFun(Data_getCurrentFunState()).init);
		break;
	case FUN_STATE_RUN:
		//设置状态转换完成，设置函数转换完成
		//设置新状态的run
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
	//1.1设置状态转换undone
	//1.2设置函数转换undone
	//1.3设置函数转换标志exit
	CoreState_setStateChangeFlag(FUN_STATE_UNDONE);
	CoreState_setFunChangeFlag(FUN_STATE_UNDONE);
	CoreState_setFunSwitchState(FUN_STATE_EXIT);

	//1.3.1设置新状态，保存旧状态

	Data_setPreFunState(Data_getCurrentFunState());
	Data_setCurrentFunState(CoreState_getNewState());

	//1.4清除本次新状态-----后续估计要删掉
	CoreState_setNewStateFlag(0);
}

void CoreState_coreFun(void)
{
	if (isStateDone(CoreState_getStateChangeFlag()))
	{
		//1.是否存在新状态待转换
		if (CoreState_haveNewStateFlag())
		{
			setFlagAndState();
		}
	}
	if (isStateUndone(CoreState_getFunChangeFlag()))
	{
		//根据funChangeFlag获取要执行的函数指针
		setRunfun(CoreState_getFunSwitchState());
	}
	CoreState_setFunSwitchState(runTempFun());
	//runTempFun();
}

void CoreState_init(void)
{
	_tempFun = RunFun_getRunFun(SIG_FUN_OFF).run;
}

