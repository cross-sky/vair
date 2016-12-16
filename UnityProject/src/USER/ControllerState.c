#include "cominc.h"

//����״̬����
static pFunction runFuns[FUN_MAX];
//��ʼ״̬����null
static FunSigState sigRunFun = SIG_FUN_NULL;
//��ʼ״̬����ת�����
static StateEnum funState = FUN_STATE_RUN;
static StateEnum funExcuted = FUN_STATE_EXCUTED;

pFunction tempRunFun;

//������״̬
void ControllerState_sendSig(FunSigState newSig)
{
	sigRunFun = newSig;
}

FunSigState ControllerState_getSig(void)
{
	return sigRunFun;
}
//���ú���״̬
void ControllerState_setFunState(StateEnum newFunState)
{
	funState = newFunState;
}

StateEnum ControllerState_getFunState(void)
{
	return funState;
}
//״̬�Ƿ��л����
void ControllerState_setFunExcuted(StateEnum newFunState)
{
	funExcuted = newFunState;
}

StateEnum ControllerState_getFunExcuted(void)
{
	return funExcuted;
}
//�����л�ʱ�������ϴ�ִ�еĺ���
void setNewfunction(FunSigState newFun)
{
	Data_setPreFunction(Data_getCurrentFunction());
	Data_setCurrentFunction(runFuns[newFun]);
}
//������Ҫ���еĺ���
void setRunFun(pFunction runFun)
{
	tempRunFun = runFun;
}

pFunction getRunFun()
{
	return tempRunFun;
}
//�����л���ִ��
void ControllerState_run(void)
{
	//check that it has a new change
	pFunction tfun;
	FunSigState tSig = ControllerState_getSig();
	StateEnum funState;

	if (ControllerState_getFunExcuted() == FUN_STATE_EXCUTED)
	{
		if (tSig != SIG_FUN_NULL)
		{
			ControllerState_setFunExcuted(FUN_STATE_NULL);
			ControllerState_setFunState(FUN_STATE_EXIT);
			setNewfunction(tSig);
		}
	}
	
	tfun = getRunFun();
	funState = tfun();

	//check that state has exchted
	if (ControllerState_getFunExcuted() != FUN_STATE_EXCUTED)
	{
		if (ControllerState_getFunState() == FUN_STATE_RUN)
		{
			ControllerState_setFunExcuted(FUN_STATE_EXCUTED);
		}
	}

	switch(funState)
	{
	case FUN_STATE_INIT:
			ControllerState_setFunState(FUN_STATE_RUN);
			break;
	case FUN_STATE_RUN:
		break;
	case FUN_STATE_EXIT:
			//�˳�֮ǰ������һ�κ���ת��
		setRunFun(Data_getCurrentFunction());
		ControllerState_setFunState(FUN_STATE_INIT);
		break;
	default:
		break;
	}
}

StateEnum fun_on_init(void)
{
	return FUN_STATE_INIT;	//init���
}
StateEnum fun_on_run(void)
{
	return FUN_STATE_RUN;		//run���
}
StateEnum fun_on_exit(void)
{
	return FUN_STATE_EXIT;	//exit���
}

StateEnum fun_on(void)
{
	StateEnum tsig=ControllerState_getFunState();
	switch(tsig)
	{
	case FUN_STATE_INIT:
		return fun_on_init();
	case FUN_STATE_RUN:
		return fun_on_run();
	case FUN_STATE_EXIT:
		return fun_on_exit();
	default:
		break;
	}
	return FUN_STATE_NULL;
}


StateEnum fun_off_init(void)
{
	return FUN_STATE_INIT;	//init���
}
StateEnum fun_off_run(void)
{
	return FUN_STATE_RUN;		//run���
}
StateEnum fun_off_exit(void)
{
	return FUN_STATE_EXIT;	//exit���
}

StateEnum fun_off(void)
{
	StateEnum tsig=ControllerState_getFunState();
	switch(tsig)
	{
	case FUN_STATE_INIT:
		return fun_off_init();
	case FUN_STATE_RUN:
		return fun_off_run();
	case FUN_STATE_EXIT:
		return fun_off_exit();
	default:
		break;
	}
	return FUN_STATE_NULL;
}

void ControllerState_init(void)
{
	runFuns[SIG_FUN_OFF] = fun_off;	//
	runFuns[SIG_FUN_ON] = fun_on;

	setRunFun(runFuns[SIG_FUN_OFF]);
}




