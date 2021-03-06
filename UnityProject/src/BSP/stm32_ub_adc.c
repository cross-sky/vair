#include "cominc.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)
#define ADCx_DMA1_IRQn     DMA1_Channel1_IRQn

/*
 *	ADC状态
 */
StateStruct stateADC={
	STATE_DONE,0,ADC_NeedRunCount,200,STATE_DONE
};

ptrState BspAdc_getPtrStateAdc(void)
{
	return &stateADC;
}


static StateEnum _adcDoneFlag=STATE_DONE;

#define  NTCPINCs GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
#define  NTCPINAs GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5
//1.头文件设置adc 2.adc数组初始化 3.adc规则组设置 4.转换成实际数据
const IOControl adcInput[]={
	{0, NTCPINCs, GPIOC,RCC_APB2Periph_GPIOC},  //pincs
	{1, NTCPINAs, GPIOA,RCC_APB2Periph_GPIOA},	//pinas
};

//channel 序号以adc01-09所使用的引脚为准
uint8_t tabChannel[ADCMAX]={
	ADC_Channel_10,ADC_Channel_11,ADC_Channel_12,ADC_Channel_13,
	ADC_Channel_0, ADC_Channel_1, ADC_Channel_4, ADC_Channel_16,
	ADC_Channel_5
};
 
//************************************
// Method:    checkSigleInputFlag
// FullName:  checkSigleInputFlag
// Access:    public 
// Returns:   uint8_t
// Qualifier:检查硬件外设完成标志
// Parameter: void
//************************************
StateEnum checkInputDoneFlag(void)
{
	return _adcDoneFlag;
}

void vADCsetSingleInputFlag(StateEnum flag)
{
	_adcDoneFlag = flag;
}

void vADCDmaChannel1_ISR(void)
{
	if (DMA_GetITStatus(DMA1_IT_TC1) != RESET)
	{
		DMA_ClearITPendingBit(DMA1_IT_GL1);
		DMA_ClearITPendingBit(DMA1_IT_TC1);//清除全局中断
		ADC_SoftwareStartConvCmd(ADC1, DISABLE);
		vADCsetSingleInputFlag(STATE_DONE);
	}
}
void adcStartSimpling(void)
{
	vADCsetSingleInputFlag(STATE_UNDONE);
	//1.重新设置规则组?；2.清除转换完成；3.dma设置；4.adc软启动
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA1_Channel1->CMAR=(uint32_t)uINPGetADCaddress(&stateADC);
	DMA1_Channel1->CNDTR =ADCMAX;	//这里大意了
	DMA_Cmd(DMA1_Channel1, ENABLE);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void vADCSimpling(void)
{
	StateStruct *s=&stateADC;

	if (State_isStateUndone(State_getDataProcessedFlag(s)))
	{
		return;
	}

	if (State_isStateUndone(checkInputDoneFlag()))
	{
		return ;
	}

	if (State_isStateUndone(State_checkState(s)))
	{
		return;
	}

	//开始单次转换
	adcStartSimpling();
	State_addRunCount(s);
}

void vADCInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	uint8_t name;
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_ClearFlag(DMA1_FLAG_TC1);
	NVIC_InitStructure.NVIC_IRQChannel=ADCx_DMA1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=10;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//手动开CLK吧，也就2个,注意开ADC的时钟树
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1
		, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);//<14MHz
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	//按定义的adcINput定义的数量为准(一般adc使用GPIOA和GPIOC)
	for (name=0; name<2; name++)
	{
		GPIO_InitStructure.GPIO_Pin = adcInput[name].pin;
		//这里设置为ADC输入是
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(adcInput[name].port, &GPIO_InitStructure);
	}

	/* DMA1 channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)uINPGetADCaddress(&stateADC);
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = ADCMAX;	//
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;	//
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);


	//使能DMA传输完成中断
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC,ENABLE);

	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = ADCMAX;
	ADC_Init(ADC1, &ADC_InitStructure);

	//cdmax-1 个外部adc，1个内部adc
	for(name=0;name<ADCMAX; name++)
	{
		//  /* ADC1 regular channel14 configuration */ 
		//ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_55Cycles5);
		//1. rank start at 1
		ADC_RegularChannelConfig(ADC1, tabChannel[name], name+1, ADC_SampleTime_239Cycles5);
	}

	//need to enable
	ADC_TempSensorVrefintCmd(ENABLE);
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Enable ADC1 reset calibration register */   
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));

	/* Start ADC1 calibration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));

	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);

	/* Start ADC1 Software Conversion */ 
	//ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

