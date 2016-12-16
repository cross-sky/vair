#include "Stm32_ub_adc_spy.h"

void vADCDmaChannel1_ISR(void)
{
	vADCsetSingleInputFlag(STATE_DATA_DONE);
}

void vUartDmaTxHandler_ISR(void)
{
	vUart_setTxStateOn();
}
void DMA_ClearITPendingBit(uint32_t DMAy_IT)
{

}

void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState)
{

}