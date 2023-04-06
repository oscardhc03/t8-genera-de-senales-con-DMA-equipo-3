/*
 * PIT.c
 *
 *  Created on: 5 abr 2023
 *      Author: 2399d
 */

#include "PIT.h"

void PIT0_IRQHandler(void){
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	DMA_StartTransfer();
}
void PIT_init(uint32_t period){

	pit_config_t pitConfig;

	PIT_GetDefaultConfig(&pitConfig);

	PIT_Init(PIT, &pitConfig);

	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(period, CLOCK_GetFreq(kCLOCK_BusClk)));

	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

	NVIC_SetPriority(PIT0_IRQn, 5);

	EnableIRQ(PIT0_IRQn);

	PIT_StartTimer(PIT, kPIT_Chnl_0);


}
