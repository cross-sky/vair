#ifndef STM32_UB_ADC_SPY_H
#define STM32_UB_ADC_SPY_H
#include "cominc.h"
//#include "stm32_ub_adc.h"
//#include "stm32_ub_dma_usart1.h"

void vADCDmaChannel1_ISR(void);
void vUartDmaTxHandler_ISR(void);
void DMA_ClearITPendingBit(uint32_t DMAy_IT);
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);
#endif

