/*
 * GPIO.h
 *
 *  Created on: 16 feb 2022
 *      Author: LUISPIZANO
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "bits.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "NVIC.h"
typedef void (*gpio_call_back_t)(PORT_Type *base, uint32_t pin);

void GPIO_config(void);
void GPIO_callbck(gpio_call_back_t callback );
void IRQHandler_PORTC(void);
void IRQHandler_PORTA(void);
void switch_callback(PORT_Type *base, uint32_t pin);


#endif /* GPIO_H_ */
