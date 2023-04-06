/*
 * PIT.h
 *
 *  Created on: 5 abr 2023
 *      Author: 2399d
 */

#ifndef PIT_H_
#define PIT_H_

#include "fsl_pit.h"
#include "NVIC.h"

static void PIT0_IRQHandler(void);

void PIT_init(uint32_t period);
#endif /* PIT_H_ */
