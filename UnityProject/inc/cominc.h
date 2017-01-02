#ifndef __COMMINCV2_H
#define __COMMINCV2_H
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

//stm32����������,�Լ�������Ӧ��ͷ�ļ�
//Ϊ����vs�б��롢���ٴ���ָ���궨�壬���¶���
//....�Ѿ�������Ԥ��������
//#define __INLINE    __inline
//#define STM32F10X_MD 
//#define USE_STDPERIPH_DRIVER 
#ifdef __dsb_vs
void __dsb(uint8_t);
#endif // __dsb_vs

#include "stm32f10x_conf.h"
#include "stm32f10x.h"
#include "stm32f10x_it.h"

#include "data.h"
#include "StateType.h"
#include "ErrType.h"
#include "IoDetectErr.h"
#include "adc_filter.h"
#include "RTdataStruct.h"
#include "valve_calc.h"

#include "stm32_ub_adc.h"
#include "stm32_ub_cd4051.h"
#include "input_process.h"

#include "queue.h"


#include "RunFunctions.h"
//#include "ModeState.h"
#include "CoreState.h"
//#include "ControllerState.h"

#endif

