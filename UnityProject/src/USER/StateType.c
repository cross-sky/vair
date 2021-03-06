#include "cominc.h"

uint8_t State_isStateUndone(StateEnum state)
{
	return state == STATE_UNDONE;
}

uint8_t State_isStateDone(StateEnum state)
{
	return state == STATE_DONE;
}


StateEnum State_getState(ptrState s)
{
	return s->state;
}

uint16_t State_getRunCount(ptrState s)
{
	return s->runCount;
}

uint16_t isNextSimpleCycle(ptrState s)
{
	return (++(s->runCount)) >= s->cycleTime;
}

StateEnum State_checkState(ptrState s)
{
	if (s->state == STATE_UNDONE)
	{
		//下一个检测时间到
		if (++(s->runCount) >= s->cycleTime)
		{
			//设置状态为开始
			s->state = STATE_DONE;
			s->runCount = 0;
		}
	}
	return s->state;
}

void State_ChangeState(ptrState dst, ptrState src)
{
	dst->state = src->state;
	dst->runCount = src->runCount;
	dst->needRunCount = src->needRunCount;
	dst->cycleTime = src->cycleTime;
}

StateEnum State_getDataProcessedFlag(ptrState s)
{
	return s->dataProcessFlag;
}

void State_setDataProcessedFlag(ptrState s, StateEnum flag)
{
	s->dataProcessFlag = flag;
}

void State_addRunCount(ptrState s)
{
	s->runCount++;
	if (s->runCount >= s->needRunCount)
	{
		s->state = STATE_UNDONE;
		s->dataProcessFlag = STATE_UNDONE;
	}
}

