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

#include "data.h"
#include "queue.h"
#include "RunFunctions.h"
//#include "ModeState.h"
#include "CoreState.h"
//#include "ControllerState.h"

#endif

