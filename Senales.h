/*
 * Senales.h
 *
 *  Created on: 4 abr 2023
 *      Author: 2399d
 */

#ifndef SENALES_H_
#define SENALES_H_
#include "stdint.h"
#include "bits.h"

#define BUFFER_SIZE 256
#define DEFAULT_FREQ 500000
#define MAX_FREQ 1500000
#define FREQ_STEP 500000

#define PI 3.14159265

typedef enum{
	SIGNAL_SINE,
	SIGNAL_TRIANGLE,
	SIGNAL_SAWTOOTH,
	SIGNAL_COUNT
}signal_type_t;

typedef float myfloat;

void Signal_init(void);
void Signal_NexType(void);
void Signal_NexFreq(void);

uint16_t *Signals_GetActiveSignalBuffer(void);


#endif /* SENALES_H_ */
