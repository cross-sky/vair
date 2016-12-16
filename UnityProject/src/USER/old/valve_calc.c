#include "cominc.h"

#define VALVE_INIT_STEP -560
#define VALVE_CLOSE_STEP 500
#define VALVE_MIN_STEP	30
#define VALVE_MAX_STEP	470



ValveStatus_t valveStatus[ValveKindsMax]={0,0,0,0};
ValveStatus_t* prtvalveStatus= valveStatus;

ValveProcess_t valveProcess={
	0,0
};

#define VALVE_STEPS_ONECE	16	//默认每次运行最大步数
int16_t LastStep=VALVE_STEPS_ONECE;	//最后一次步数
int16_t ValveDirection=0;	//运行方向direct**
int16_t ValveCounts=0;		//连续增加或减少次数

void ValveCalv_changeValveData(ValveStatus_t* src)
{
	prtvalveStatus = src;
}

ValveProcess_t* ValveCalc_getSigNodes(void)
{
	return &valveProcess;
}

uint8_t isValueKindUsed(ValveKinds valveKind)
{
	return valveKind < ValveKindsMax ;
}

void setValveState(VALVE_ENUM state, ValveKinds valveKind)
{
	if (isValueKindUsed(valveKind))
	{
		prtvalveStatus[valveKind].valveStatus = state;
	}
}

uint16_t getValveState(ValveKinds valveKind)
{
	if (isValueKindUsed(valveKind))
	{
		return prtvalveStatus[valveKind].valveStatus;
	}
	return STATE_OFF;
}

int16_t getValveStep(ValveKinds valveKind)
{
	if (isValueKindUsed(valveKind))
	{
		return prtvalveStatus[valveKind].runStep;
	}
	return STATE_OFF;
}

uint8_t ValveCalc_popSig(ValveSig_t *sig)
{
	if (valveProcess.out != valveProcess.in)
	{
		if (++valveProcess.out >= ValveBuffLenMask)
		{
			valveProcess.out = 0;
		}
		sig->code = valveProcess.buff[valveProcess.out].code;
		sig->sig = valveProcess.buff[valveProcess.out].sig;
		sig->kindValue = valveProcess.buff[valveProcess.out].kindValue;
		return TRUE;
	}
	return FALSE;
}

uint8_t ValveCalc_getSig(ValveSig_t *sig)
{
	uint8_t i;
	if (valveProcess.out != valveProcess.in)
	{
		i=++valveProcess.out;
		if (i >= ValveBuffLenMask)
		{
			i = 0;
		}
		sig->code = valveProcess.buff[i].code;
		sig->sig = valveProcess.buff[i].sig;
		sig->kindValue = valveProcess.buff[i].kindValue;
		return TRUE;
	}
	return FALSE;
}

void checkTotalSteps(ValveSig_t *sig)
{
	uint16_t tsig=sig->sig;
	int16_t tcode=sig->code;
	uint16_t tvalveKind = sig->kindValue;

	ValveStatus_t *ptrvalveStatus = &prtvalveStatus[tvalveKind];
	//判断是初始或结束时，开度范围加大
	if (tsig == valveInit || tsig == valveClose)
	{
		if (tsig == valveInit)
		{
			ptrvalveStatus->runStep = VALVE_INIT_STEP;
			ptrvalveStatus->totalSteps = 0;
		}
		else
		{
			ptrvalveStatus->runStep = VALVE_CLOSE_STEP - ptrvalveStatus->totalSteps;
			ptrvalveStatus->totalSteps = VALVE_CLOSE_STEP;
		}
	}
	//开度有限制 确保totalstep和runstep在范围内
	else if (tsig == valveRun)
	{
		if ((ptrvalveStatus->totalSteps + ptrvalveStatus->runStep) < VALVE_MIN_STEP )
		{
			ptrvalveStatus->runStep = VALVE_MIN_STEP - ptrvalveStatus->totalSteps;
			ptrvalveStatus->totalSteps = VALVE_MIN_STEP;
		}
		else if ((ptrvalveStatus->totalSteps + ptrvalveStatus->runStep) > VALVE_MAX_STEP)
		{
			ptrvalveStatus->runStep = VALVE_MAX_STEP - ptrvalveStatus->totalSteps;
			ptrvalveStatus->totalSteps = VALVE_MAX_STEP;
		}
		else{
			ptrvalveStatus->runStep = tcode;
			ptrvalveStatus->totalSteps += tcode;
		}
	}
}

uint8_t ValveCalc_pushSig(ValveSig_t *srcSig)
{
	int16_t code = srcSig->code;
	uint16_t sig = srcSig->sig;
	ValveKinds valveKind =(ValveKinds)srcSig->kindValue;
	if (((valveProcess.in+1)&ValveBuffLenMask) == valveProcess.out)
	{
		return FALSE;
	}
	else{
		if (code != 0)
		{
			//valveProcess.in++;
			if (++valveProcess.in >= ValveBuffLen)
			{
				valveProcess.in=0;
			}
			valveProcess.buff[valveProcess.in].code = code;
			valveProcess.buff[valveProcess.in].sig = sig;
			valveProcess.buff[valveProcess.in].kindValue = valveKind;
			return TRUE;
		}
		return FALSE;
	}
}


/*
int16_t stepChange(VALVE_ENUM addsOrDecr)
{
	if (addsOrDecr == adds)
	{
		valveStatus.runStep++;
	}
	else if (addsOrDecr == decr)
	{
		valveStatus.runStep--;
	}
}
void valveRun(void)
{
	int16_t runStep;
	runStep = getValveStep();
	if (runStep == 0)
	{
		//步数已走完
		setValveState(statusDone);
		return;
	}
	if (runStep<0)
	{
		//返回走，总步数减少
		//运行步数增加到0
		stepChange(adds);
		Valve_runBack();
	}
	else{
		//往前走，总步数增加
		//运行步数减少到0
		stepChange(decr);
		Valve_runForward();
	}
}

uint8_t ValveCalc_pushSig(int16_t code, uint16_t sig)
{
	if ((valveProcess.in+1)&ValveBuffLenMask == valveProcess.out)
	{
		return FALSE;
	}
	else{
		if (code != 0)
		{
			//valveProcess.in++;
			if (++valveProcess.in >= ValveBuffLen)
			{
				valveProcess.in=0;
			}
			valveProcess.buff[valveProcess.in].code = code;
			valveProcess.buff[valveProcess.in].sig = sig;
			return TRUE;
		}
		return FALSE;
	}
}



void vTask_valveProcess(void)
{
	ValveSig_t sig;
	//1.查询valve状态是否完成
	if (getValveState() == statusDone)
	{
		//2.检查步数
		if (popSig(sig) == TRUE)
		{
			//2.5 检查步数在范围内
			checkTotalSteps(sig);
			//3.设置状态run
			setValveState(statusRun);
		}

	}

	//4.根据步数运行
	valveRun();
}

void valveDirectHold(int16_t subT, int16_t superHeat)
{
	//目标过热度范围T+0.5 
	if (subT > superHeat+5)
	{
		//1.步数保持上次，开度加大，次数+1
		ValveDirection = DirectForward;
		ValveCounts +=1;
	}
	else if (subT < superHeat - 5)
	{
		//2.步数保持上次，开度减少，次数+1
		ValveDirection = DirectBack;
		ValveCounts +=1;
	}
	else{
		//步数，开度保持，次数清0
		ValveDirection = DirectHold;
		ValveCounts = 0;
	}
}

void valveDirectForward(int16_t subT, int16_t superHeat)
{
	//目标过热度范围T+0.5 
	if (subT > superHeat+5)
	{
		//1.步数保持上次，开度加大，次数+1
		ValveDirection = DirectForward;
		ValveCounts +=1;
	}
	else if (subT < superHeat - 5)
	{
		//2.步数减半，开度减少，次数保持
		LastStep >>=1;
		ValveDirection = DirectBack;
	}
	else{
		//步数，开度保持，次数清0
		ValveDirection = DirectHold;
		ValveCounts = 0;
	}
}

void valveDirectBack(int16_t subT, int16_t superHeat)
{
	//目标过热度范围T+0.5 
	if (subT > superHeat+5)
	{
		//1.步数减半，开度加大，次数保持
		LastStep >>=1;
		ValveDirection = DirectForward;
	}
	else if (subT < superHeat - 5)
	{
		//2.步数保持上次，开度减少，次数+1
		ValveDirection = DirectBack;
		ValveCounts +=1;
	}
	else{
		//步数，开度保持上次，次数清0
		ValveDirection = DirectHold;
		ValveCounts = 0;
	}
}

void vTask_valveCalc(void)
{
	int16_t superHeat,subT;
	//1. 计算吸气-蒸发
	subT = iQUE_getInTemper() - iQUE_getEvaporateTemper();
	//2.获取目标过热度
	superHeat = iQUE_getSuperheat();

	//3.1上次电子膨胀阀维持开度
	if (ValveDirection == DirectHold)
	{
		valveDirectHold(subT,superHeat);
	}
	//3.2上次电子膨胀阀开度增加
	else if (ValveDirection == DirectForward)
	{
		valveDirectForward(subT,superHeat);
	}
	//3.3上次电子膨胀阀开度减少
	else
	{
		valveDirectHold(subT,superHeat);
	}

	//4.连续增加或减少次数>=4，重置步数和次数
	if (ValveCounts >=4)
	{
		if (ValveDirection == DirectForward || ValveDirection == DirectBack)
		{
			LastStep = VALVE_STEPS_ONECE;
			ValveCounts = 0;
		}
	}

	//步数<1,步数置1
	if (LastStep < 1 )
	{
		LastStep = 1;
	}
	//5.发送步数
	ValveCalc_pushSig(LastStep*ValveDirection, valveRun);
}
*/
