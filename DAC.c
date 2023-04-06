/*
 * DAC.c
 *
 *  Created on: 4 abr 2023
 *      Author: 2399d
 */

#include "DAC.h"
static DAC_Type *const s_dacBase[]= DAC_BASE_PTRS;

void DAC_init(void){
	DAC_Type *base = s_dacBase[0];


	dac_config_t dac_Configstr;
	DAC_GetDefaultConfig(&dac_Configstr);

	DAC_Init(base, &dac_Configstr);
	DAC_Enable(base, true);

	DAC_SetBufferReadPointer(base, 0U);
	DAC_EnableBuffer(base, false);

}

void DAC_Set(uint32_t val){
	DAC_Type *base = s_dacBase[0];
	DAC_SetBufferValue(base, 0U, val);
}

void DAC_Set_signal(signal_type_t signal_type, uint32_t frequency){
	uint16_t *signal_buffer = Signals_GetActiveSignalBuffer();
	uint32_t signal_length = BUFFER_SIZE;
}

