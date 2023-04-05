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
typedef void (*gpio_call_back_t)(void);

void GPIO_config(void);
void GPIO_callbck(gpio_call_back_t callback );
void IRQHandler_portC(void);


#endif /* GPIO_H_ */
