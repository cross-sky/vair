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

#define VALVE_STEPS_ONECE	16	//Ĭ��ÿ�����������
int16_t LastStep=VALVE_STEPS_ONECE;	//���һ�β���
int16_t ValveDirection=0;	//���з���direct**
int16_t ValveCounts=0;		//�������ӻ���ٴ���

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
	//�ж��ǳ�ʼ�����ʱ�����ȷ�Χ�Ӵ�
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
	//���������� ȷ��totalstep��runstep�ڷ�Χ��
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
		//����������
		setValveState(statusDone);
		return;
	}
	if (runStep<0)
	{
		//�����ߣ��ܲ�������
		//���в������ӵ�0
		stepChange(adds);
		Valve_runBack();
	}
	else{
		//��ǰ�ߣ��ܲ�������
		//���в������ٵ�0
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
	//1.��ѯvalve״̬�Ƿ����
	if (getValveState() == statusDone)
	{
		//2.��鲽��
		if (popSig(sig) == TRUE)
		{
			//2.5 ��鲽���ڷ�Χ��
			checkTotalSteps(sig);
			//3.����״̬run
			setValveState(statusRun);
		}

	}

	//4.���ݲ�������
	valveRun();
}

void valveDirectHold(int16_t subT, int16_t superHeat)
{
	//Ŀ����ȶȷ�ΧT+0.5 
	if (subT > superHeat+5)
	{
		//1.���������ϴΣ����ȼӴ󣬴���+1
		ValveDirection = DirectForward;
		ValveCounts +=1;
	}
	else if (subT < superHeat - 5)
	{
		//2.���������ϴΣ����ȼ��٣�����+1
		ValveDirection = DirectBack;
		ValveCounts +=1;
	}
	else{
		//���������ȱ��֣�������0
		ValveDirection = DirectHold;
		ValveCounts = 0;
	}
}

void valveDirectForward(int16_t subT, int16_t superHeat)
{
	//Ŀ����ȶȷ�ΧT+0.5 
	if (subT > superHeat+5)
	{
		//1.���������ϴΣ����ȼӴ󣬴���+1
		ValveDirection = DirectForward;
		ValveCounts +=1;
	}
	else if (subT < superHeat - 5)
	{
		//2.�������룬���ȼ��٣���������
		LastStep >>=1;
		ValveDirection = DirectBack;
	}
	else{
		//���������ȱ��֣�������0
		ValveDirection = DirectHold;
		ValveCounts = 0;
	}
}

void valveDirectBack(int16_t subT, int16_t superHeat)
{
	//Ŀ����ȶȷ�ΧT+0.5 
	if (subT > superHeat+5)
	{
		//1.�������룬���ȼӴ󣬴�������
		LastStep >>=1;
		ValveDirection = DirectForward;
	}
	else if (subT < superHeat - 5)
	{
		//2.���������ϴΣ����ȼ��٣�����+1
		ValveDirection = DirectBack;
		ValveCounts +=1;
	}
	else{
		//���������ȱ����ϴΣ�������0
		ValveDirection = DirectHold;
		ValveCounts = 0;
	}
}

void vTask_valveCalc(void)
{
	int16_t superHeat,subT;
	//1. ��������-����
	subT = iQUE_getInTemper() - iQUE_getEvaporateTemper();
	//2.��ȡĿ����ȶ�
	superHeat = iQUE_getSuperheat();

	//3.1�ϴε������ͷ�ά�ֿ���
	if (ValveDirection == DirectHold)
	{
		valveDirectHold(subT,superHeat);
	}
	//3.2�ϴε������ͷ���������
	else if (ValveDirection == DirectForward)
	{
		valveDirectForward(subT,superHeat);
	}
	//3.3�ϴε������ͷ����ȼ���
	else
	{
		valveDirectHold(subT,superHeat);
	}

	//4.�������ӻ���ٴ���>=4�����ò����ʹ���
	if (ValveCounts >=4)
	{
		if (ValveDirection == DirectForward || ValveDirection == DirectBack)
		{
			LastStep = VALVE_STEPS_ONECE;
			ValveCounts = 0;
		}
	}

	//����<1,������1
	if (LastStep < 1 )
	{
		LastStep = 1;
	}
	//5.���Ͳ���
	ValveCalc_pushSig(LastStep*ValveDirection, valveRun);
}
*/
