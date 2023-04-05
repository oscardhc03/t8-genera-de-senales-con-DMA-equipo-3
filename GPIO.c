/*
 * GPIO.c
 *
 *  Created on: 16 feb 2022
 *      Author: LUISPIZANO
 */
#include "GPIO.h"

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
		CLOCK_EnableClock(kCLOCK_PortB);
		CLOCK_EnableClock(kCLOCK_PortC);


		PORT_SetPinConfig(PORTC, bit_6, &porta4_pin38_config);
		GPIO_PinInit(GPIOC, bit_6, &sw_config);



		PORT_SetPinInterruptConfig(PORTC, bit_6, kPORT_DMAFallingEdge);
		PORT_SetPinMux(PORTB, bit_22, kPORT_MuxAsGpio);


		   /* Init output LED GPIO. */
		GPIO_PinInit(GPIOB, bit_22, &led_config);
}
