/*
 * GPIO.c
 *
 *  Created on: 16 feb 2022
 *      Author: LUISPIZANO
 */
#include "GPIO.h"

static gpio_call_back_t s_gpio_callback;

void GPIO_config(void)
{
	 gpio_pin_config_t sw_config = {
		        kGPIO_DigitalInput,
		        0,
		    };

		    /* Define the init structure for the output LED pin */
		    gpio_pin_config_t led_config = {
		        kGPIO_DigitalOutput,
		        0,
		    };

		    const port_pin_config_t porta4_pin38_config = {/* Internal pull-up resistor is enabled */
		                                                      kPORT_PullUp,
		                                                      /* Fast slew rate is configured */
		                                                      kPORT_FastSlewRate,
		                                                      /* Passive filter is disabled */
		                                                      kPORT_PassiveFilterDisable,
		                                                      /* Open drain is disabled */
		                                                      kPORT_OpenDrainDisable,
		                                                      /* High drive strength is configured */
		                                                      kPORT_HighDriveStrength,
		                                                      /* Pin is configured as PTA4 */
		                                                      kPORT_MuxAsGpio,
		                                                      /* Pin Control Register fields [15:0] are not locked */
		                                                      kPORT_UnlockRegister};
		CLOCK_EnableClock(kCLOCK_PortA);
//		CLOCK_EnableClock(kCLOCK_PortB);
		CLOCK_EnableClock(kCLOCK_PortC);


		// Config SW2 PTA4
		PORT_SetPinConfig(PORTA, bit_4, &porta4_pin38_config);
		GPIO_PinInit(GPIOA, bit_4, &sw_config);
		PORT_SetPinInterruptConfig(PORTA, bit_6, kPORT_DMAFallingEdge);
		// Config SW3 PTC 6
		PORT_SetPinConfig(PORTC, bit_6, &porta4_pin38_config);
		GPIO_PinInit(GPIOC, bit_6, &sw_config);
		PORT_SetPinInterruptConfig(PORTC, bit_6, kPORT_DMAFallingEdge);

		// LED
		PORT_SetPinMux(PORTB, bit_22, kPORT_MuxAsGpio);
		   /* Init output LED GPIO. */
		GPIO_PinInit(GPIOB, bit_22, &led_config);

		NVIC_EnableIRQ(PORTA_IRQn);
		NVIC_EnableIRQ(PORTC_IRQn);
}

void GPIO_callbck(gpio_call_back_t callback ){
	s_gpio_callback = callback;

}

void IRQHandler_PORTA(void){
	uint32_t triggered_pin = 0;
	if(PORT_GetPinsInterruptFlags(PORTA) & ( 1U << 4U)){
		PORT_ClearPinsInterruptFlags(PORTA, 1U << 4U);
		triggered_pin = 4;
	}
	if(s_gpio_callback && triggered_pin){
		s_gpio_callback(PORTA, triggered_pin);
	}

}


void IRQHandler_PORTC(void){
	uint32_t triggered_pin = 0;

	if(PORT_GetPinsInterruptFlags(PORTC)& (bit_1<<bit_6)){
		PORT_ClearPinsInterruptFlags(PORTC, bit_1<<bit_6);
		triggered_pin = bit_6;
	}
	if(s_gpio_callback && triggered_pin){
		s_gpio_callback(PORTC, triggered_pin);
	}

}/*
volatile bool sw2_push = true;
volatile bool sw3_push = true;

void switch_callback(PORT_Type *base, uint32_t pin){
	static uint8_t signal_type=0;
	static uint8_t freq_index =0;

	if(base == PORTA && pin == 4){
		//Cambiar la frecuencia
		Signal_NexFreq();
	}
	else if (base == PORTC && pin 6){
		//Cambiar señal
		Signal_NexType();
	}

}*/
