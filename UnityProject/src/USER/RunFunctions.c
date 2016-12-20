#include "cominc.h"

xRunFunctions _funTables[SIG_FUN_MAX];

StateEnum RunFun_funOff_run(void)
{
	printf("off run\r\n");
	return FUN_STATE_NULL;
}

StateEnum RunFun_funOff_init(void)
{
	printf("off init\r\n");
	//��ɺ�ת�뵱ǰ״̬��run״̬
	return FUN_STATE_RUN;
}

StateEnum RunFun_funOff_exit(void)
{
	printf("off exit\r\n");
	//��ɺ�ת����״̬��init״̬
	return FUN_STATE_INIT;
}
StateEnum RunFun_funOn_run(void)
{
	printf("on run\r\n");
	return FUN_STATE_NULL;
}

StateEnum RunFun_funOn_init(void)
{
	printf("on init\r\n");
	//��ɺ�ת�뵱ǰ״̬��run״̬
	return FUN_STATE_RUN;
}

StateEnum RunFun_funOn_exit(void)
{
	printf("on exit\r\n");
	//��ɺ�ת����״̬��init״̬
	return FUN_STATE_INIT;
}

pRunFunctions RunFun_getRunFun(SigFunState sigFun)
{
	return _funTables[sigFun];
}

void RunFunction_init(void)
{
	_funTables[SIG_FUN_OFF].exit = RunFun_funOff_exit;
	_funTables[SIG_FUN_OFF].init = RunFun_funOff_init;
	_funTables[SIG_FUN_OFF].run  = RunFun_funOff_run;
	_funTables[SIG_FUN_ON].exit =  RunFun_funOn_exit;
	_funTables[SIG_FUN_ON].init =  RunFun_funOn_init;
	_funTables[SIG_FUN_ON].run  =  RunFun_funOn_run;
}

