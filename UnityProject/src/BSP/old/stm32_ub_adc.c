#include "cominc.h"

/*
 *	ADC状态
 */
StateStruct stateADC={
	STATE_ON,0,ADC_NeedRunCount,100,STATE_DATA_DONE
};

ptrState BspAdc_getPtrStateAdc(void)
{
	return &stateADC;
}

static uint16_t adcSingleInputCompleteFlag=STATE_DATA_DONE;


 
//************************************
// Method:    checkSigleInputFlag
// FullName:  checkSigleInputFlag
// Access:    public 
// Returns:   uint8_t
// Qualifier:检查硬件外设完成标志
// Parameter: void
//************************************
uint16_t checkSigleInputFlag(void)
{
	return adcSingleInputCompleteFlag;
}

void vADCsetSingleInputFlag(uint16_t flag)
{
	adcSingleInputCompleteFlag = flag;
}

void vADCDmaChannel1_ISR(void)
{
	//vADCsetSingleInputFlag(STATE_DATA_DONE);
}
void adcStartSimpling(void)
{
	vADCsetSingleInputFlag(STATE_DATA_UNDONE);
}

void vADCSimpling(void)
{
	StateStruct *s=&stateADC;

	if (State_getDataProcessedFlag(s) == STATE_DATA_UNDONE)
	{
		return;
	}

	if (checkSigleInputFlag() == STATE_DATA_UNDONE)
	{
		return ;
	}

	if (State_checkStateIsOn(s) ==  FALSE)
	{
		return;
	}

	//开始单次转换
	adcStartSimpling();
	State_addRunCount(s);
}
