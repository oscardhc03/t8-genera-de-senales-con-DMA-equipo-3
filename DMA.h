/*
 * DMA.h
 *
 *  Created on: 5 abr 2023
 *      Author: 2399d
 */

#ifndef DMA_H_
#define DMA_H_

#include "fsl_edma.h"
#include "fsl_dmamux.h"
#include "DAC.h"
#include "Senales.h"
#include "GPIO.h"

#define DMA_CHANNEL 0
#define DMA_SOURCE 63 //source del eDMA para el PIT

//typedef enum  {false_, true_};


void DMA_init(void);
void DMA_StartTransfer(void);


#endif /* DMA_H_ */
