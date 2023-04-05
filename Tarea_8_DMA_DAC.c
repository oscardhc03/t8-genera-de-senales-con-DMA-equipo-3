//
//#include <stdio.h>
//#include "bits.h"
//#include "fsl_port.h"
//#include "fsl_gpio.h"
//#include "fsl_edma.h"
//#include "NVIC.h"
//#include "GPIO.h"
//#include "fsl_dmamux.h"
//
//#define ARR_SIZE (16u)
//#define BUFFER_LENGTH       8
//#define TCD_QUEUE_SIZE      1U
//
//#define DMA_SOURCE_GPIO (51u)
//
//volatile bool g_Transfer_Done = false;
//
//
//uint8_t srcAddr[ARR_SIZE]  = {0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 9, 10, 11, 12, 13, 14, 15, 16};
//uint16_t destAddr[ARR_SIZE] = {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
//AT_QUICKACCESS_SECTION_DATA_ALIGN(edma_tcd_t tcdMemoryPoolPtr[TCD_QUEUE_SIZE + 1], sizeof(edma_tcd_t));
//
//edma_handle_t g_EDMA_Handle;
//uint8_t g_porta = FALSE;
//
//void PORTA_IRQHandler(void)
//{
//	g_porta = TRUE;
//	 GPIO_PortClearInterruptFlags(GPIOA, 1U << bit_4);
//}
//
//void EDMA_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
//{
//    if (transferDone)
//    {
//        g_Transfer_Done = true;
//    }
//}
//
//int main(void) {
//
//	edma_transfer_config_t transferConfig;
//	    edma_config_t userConfig;
//
//	    GPIO_config();
//
//		NVIC_enable_interrupt_and_priotity(DMA_CH0_IRQ, PRIORITY_5);
//		NVIC_global_enable_interrupts;
//
//	    DMAMUX_Init(DMAMUX0);
//
//	    DMAMUX_SetSource(DMAMUX0, 0, DMA_SOURCE_GPIO);
//
//	    DMAMUX_EnableChannel(DMAMUX0, 0);
//
//
//	    EDMA_GetDefaultConfig(&userConfig);
//	    EDMA_Init(DMA0, &userConfig);
//	    EDMA_CreateHandle(&g_EDMA_Handle, DMA0, 0);
//	    EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback, NULL);
//	    EDMA_ResetChannel(g_EDMA_Handle.base, g_EDMA_Handle.channel);
//
//	    EDMA_PrepareTransferConfig(&transferConfig,
//	    		   &srcAddr[0],
//				   2,
//				   2, /* source offset */
//				   &destAddr[0],
//				   2,
//				   4,               /* dest offset */
//				   2,             /* minor loop bytes: 8*/
//				   8); /* major loop counts : 4 */
//	   EDMA_TcdSetMajorOffsetConfig(
//			    		   tcdMemoryPoolPtr, //param tcd A point to the TCD structure.
//			    		   0, //* param sourceOffset source address offset.
//						   0);//destOffset destination address offset.
//
//	   EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig, NULL);
//
//	   EDMA_TcdEnableInterrupts(&tcdMemoryPoolPtr[0], kEDMA_MajorInterruptEnable);
//	   EDMA_TcdEnableAutoStopRequest(&tcdMemoryPoolPtr[0], false);
//	   EDMA_InstallTCD(DMA0, 0, &tcdMemoryPoolPtr[0]);
//	   EDMA_EnableChannelRequest(DMA0, 0);
//
//
//
//
//    while(1) {
//
//
//    }
//    return 0 ;
//}







#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_dac.h"
#include "fsl_pit.h"
#include "fsl_edma.h"
#include <math.h>

#define SAMPLE_RATE 2000000U // Frecuencia de muestreo de la señal generada
#define SIGNAL_BUFFER_SIZE 512 // Tamaño del buffer de la señal generada
#define MAX_FREQ 1500000U // Frecuencia máxima de la señal generada

// Definición de las señales generadas
typedef enum {
  SIGNAL_SINE,
  SIGNAL_TRIANGLE,
  SIGNAL_SAWTOOTH
} signal_t;

// Buffer de la señal generada
uint16_t signalBuffer[SIGNAL_BUFFER_SIZE];

// Variables para la generación de señales
float sinePhase = 0;
float trianglePhase = 0;
float sawtoothPhase = 0;
signal_t currentSignal = SIGNAL_SINE;
uint32_t currentFreq = 500000U;

// Función para calcular el valor de la señal seno en un determinado instante de tiempo
float calculateSine(float phase) {
  return sinf(phase * 2 * M_PI);
}

// Función para calcular el valor de la señal triangular en un determinado instante de tiempo
float calculateTriangle(float phase) {
  float x = fmodf(phase, 1.0);
  if (x < 0.5) {
    return 4 * x - 1;
  } else {
    return 3 - 4 * x;
  }
}

// Función para calcular el valor de la señal diente de sierra en un determinado instante de tiempo
float calculateSawtooth(float phase) {
  return fmodf(phase, 1.0) * 2 - 1;
}

// Función para generar la señal correspondiente y almacenarla en el buffer
void generateSignal(uint16_t *buffer, uint32_t size, signal_t signal, uint32_t freq) {
  float phase = 0;
  float phaseIncrement = (float)freq / SAMPLE_RATE;
  for (int i = 0; i < size; i++) {
	    float value;
	    switch (signal) {
	      case SIGNAL_SINE:
	        value = calculateSine(phase);
	        break;
	      case SIGNAL_TRIANGLE:
	        value = calculateTriangle(phase);
	        break;
	      case SIGNAL_SAWTOOTH:
	        value = calculateSawtooth(phase);
	        break;
	      default:
	        value = 0;
	        break;
	    }
	    buffer[i] = (uint16_t)((value + 1) * 2048); // Convertir el valor a un valor de 12 bits
	    phase += phaseIncrement;
	  }
	}

	int main(void) {
	  // Inicialización de periféricos
	  BOARD_InitBootPins();
	  BOARD_InitBootClocks();
	  BOARD_InitBootPeripherals();
	  BOARD_InitDebugConsole();

	  // Configuración del DAC
	  dac_config_t dacConfig;
	  DAC_GetDefaultConfig(&dacConfig);
	  DAC_Init(DAC0, &dacConfig);
	  DAC_Enable(DAC0, true);

	  // Configuración del PIT
	  pit_config_t pitConfig;
	  PIT_GetDefaultConfig(&pitConfig);
	  PIT_Init(PIT, &pitConfig);
	  PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(2U, CLOCK_GetBusClkFreq())); // Interrupción cada 2 microsegundos
	  PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
	  EnableIRQ(PIT_IRQn);

	  // Configuración del DMA
	  dma_handle_t dmaHandle;
	  DMA_Init(DMA0);
	  DMA_CreateHandle(&dmaHandle, DMA0, 0);
	  DMA_EnableChannel(DMA0, 0);
	  DMA_SetChannelPriority(DMA0, 0, kDMA_ChannelPriority0);
	  DMA_SetChannelDisableIRQOnCompletion(DMA0, 0, true);
	  DMA_SetTransferConfig(DMA0, 0, (void *)&DAC0->DAT[0], kDMA_MemoryToPeripheral);
	  DMA_SetTransferSize(DMA0, 0, SIGNAL_BUFFER_SIZE * sizeof(uint16_t));
	  DMA_EnableCycleSteal(DMA0, 0, true);

	  // Generación de la señal inicial
	  generateSignal(signalBuffer, SIGNAL_BUFFER_SIZE, currentSignal, currentFreq);
	  DMA_SetSourceBuffer(DMA0, 0, signalBuffer, sizeof(uint16_t));
	  DMA_StartTransfer(&dmaHandle);

	  while (1) {
		    // Cambio de la señal generada al presionar SW3
		    if (BOARD_SW_ReadPins() & BOARD_SW3_MASK) {
		      currentSignal++;
		      if (currentSignal > SIGNAL_SAWTOOTH) {
		        currentSignal = SIGNAL_SINE;
		      }
		      generateSignal(signalBuffer, SIGNAL_BUFFER_SIZE, currentSignal, currentFreq);
		      DMA_SetSourceBuffer(DMA0, 0, signalBuffer, sizeof(uint16_t));
		      DMA_StartTransfer(&dmaHandle);
		      while (BOARD_SW_ReadPins() & BOARD_SW3_MASK) {}
		      delay(); // Retardo para evitar rebotes del botón
		    }

		    // Cambio de frecuencia al presionar SW
		    if (BOARD_SW_ReadPins() & BOARD_SW2_MASK) {
		      currentFreq += 500000U;
		      if (currentFreq > MAX_FREQ) {
		        currentFreq = 500000U;
		      }
		      generateSignal(signalBuffer, SIGNAL_BUFFER_SIZE, currentSignal, currentFreq);
		      float phaseIncrement = (float)currentFreq / SAMPLE_RATE;
		      PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(1e6 / currentFreq, CLOCK_GetBusClkFreq())); // Cambiar la frecuencia de la interrupción del PIT
		      DMA_SetTransferSize(DMA0, 0, SIGNAL_BUFFER_SIZE * sizeof(uint16_t));
		      DMA_SetSourceBuffer(DMA0, 0, signalBuffer, sizeof(uint16_t));
		      DMA_StartTransfer(&dmaHandle);
		      while (BOARD_SW_ReadPins() & BOARD_SW2_MASK) {}
		      delay(); // Retardo para evitar rebotes del botón
		    }
		  }
		}



















