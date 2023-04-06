/*
 * DAC.h
 *
 *  Created on: 4 abr 2023
 *      Author: 2399d
 */

#ifndef DAC_H_
#define DAC_H_

#include "fsl_dac.h"
#include "Senales.h"
#include "GPIO.h"

void DAC_init(void);
void DAC_Set(uint32_t val);


#endif /* DAC_H_ */
