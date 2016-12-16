#include "cominc.h"

StateStruct stateCd4051={
	STATE_ON,0,CDinMax*ADC_NeedRunCount,100,STATE_DATA_DONE
};

ptrState BspAdc_getPtrStateCd4051(void)
{
	return &stateCd4051;
}

uint16_t CD4051_IOread(void)
{
	return 0;
}

void CD4051_startSimple(ptrState s)
{
	uint16_t data;
	uint8_t runTimes,cdInX;
	runTimes = State_getRunCount(s)>>3;//���̣���Ҫ��ȡ5����ͬcdin���ݣ�
	cdInX = State_getRunCount(s)&0x07;//���࣬Ŀǰ��ȡ��cdinX������
	data |= CD4051_IOread()<<cdInX;
	Inp_setDataCd4051(data, cdInX);
}

void vCd4051Simpling(void)
{
	StateStruct *s=&stateCd4051;
	if (State_getDataProcessedFlag(s) == STATE_DATA_UNDONE)
	{
		return;
	}

	if (State_checkStateIsOn(s) ==  FALSE)
	{
		return;
	}

	CD4051_startSimple(s);
	State_addRunCount(s);
}

/*

void vCd4051Detect(void)
{
uint8_t t,i;
uint16_t tdata;
static uint16_t data;
Event_t *e=&eventCd4051;


//�����ݶ˿�, 2���������ͬһ��port
//tdata=GPIO_ReadInputData(comminCd4051[0].port);
//1.send read 2 times;
tdata=(uint16_t)comminCd4051[0].port->IDR;
for(i=0;i<CD4051_BANKS;i++)
{
if (rwCdabc[i][e->code].nhard != CDunused)
{
t=(tdata>>comminCd4051[i].nsoft)&0x01;//Ӳ��λ������
data |= t<<rwCdabc[i][e->code].name;//���λ������
}
}

e->code++;
if (e->code >= e->COUNT)
{
//1.send data;2.clear data;3.set state_off
//e->code=0--���ô�����������0
//@@@@@@@
vINPSendCd405xData(data);
data=0;
e->state=STATE_OFF;
//e->code=0;
}

//1.���һ������cdabc=0���´�ֱ�Ӷ�ȡ
t=(e->code)&CD4051_MASK_INPUTS;
for(i=0; i<CD4051_NUMBER_CONTROL; i++)
{
if (t&0x01)
{
IOH(&controlCd4051[i]);
}
else
IOL(&controlCd4051[i]);

t>>=1;
}

}
*/



/*
const IOControl controlCd4051[]={
	{CDa, 0, GPIO_Pin_2, GPIOE,RCC_APB2Periph_GPIOE},
	{CDb, 1, GPIO_Pin_3, GPIOE,RCC_APB2Periph_GPIOE},
	{CDc, 2, GPIO_Pin_4, GPIOE,RCC_APB2Periph_GPIOE}
};
const IOControl comminCd4051[]={
	{CDcom1, 5, GPIO_Pin_5, GPIOE,RCC_APB2Periph_GPIOE},
	{CDcom2, 6, GPIO_Pin_6, GPIOE,RCC_APB2Periph_GPIOE}
};

const CDabcRW rwCdabc[CD4051_BANKS][8]={
	{{CDin02, 0},{CDin03, 1},{CDin04, 2},{CDin01, 3},
	 {CDin05, 4},{0,CDunused},{CDin06, 6},{CDin07, 7}}, 
	{{CDin16, 0},{0,CDunused},{0,CDunused},{0,CDunused},
	 {CDin08, 4},{CDin14, 5},{CDin12, 6},{CDin15, 7} }
};

//@@@@@@@@1. need init
Event_t eventCd4051={
	STATE_ON,0,8,100
};

void vCd4051Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	uint8_t name;

	//�ֶ���CLK�ɣ�Ҳ�ͼ���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	for (name=0; name<CDcomMax; name++)
	{
		//�����ֶ����ˣ���1��
		//RCC_APB2PeriphClockCmd(controlCd4051[name].clk, ENABLE);
		GPIO_InitStructure.GPIO_Pin = comminCd4051[name].pin;
		//��������Ϊ����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
		GPIO_Init(comminCd4051[name].port, &GPIO_InitStructure);
	}

	for (name=0; name<CDControlMAX; name++)
	{
		//�����ֶ����ˣ���1��
		//RCC_APB2PeriphClockCmd(controlCd4051[name].clk, ENABLE);
		GPIO_InitStructure.GPIO_Pin = controlCd4051[name].pin;
		//��������Ϊ��©������ѽ���������
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(controlCd4051[name].port, &GPIO_InitStructure);
		//��ʼʱҪ������cd4051��cdin01��Ӧ��in��
		//CDabc set 0
		IOL(&controlCd4051[name]);
	}
}



*/
