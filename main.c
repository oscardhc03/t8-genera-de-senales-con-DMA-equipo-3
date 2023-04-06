#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
//#include "fsl_debu"

#include "GPIO.h"
#include "DAC.h"
#include "PIT.h"
#include "DMA.h"
#include "Senales.h"

int main(void){

	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();

	//Modulos
	GPIO_config();
	DAC_init();
	DMA_init();

	//Config señal inicial y freq inicial
	Signal_NexType();
	Signal_NexFreq();
	while(1)
	{
		if(!GPIO_PinRead(GPIOA, 4))
		{
			Signal_NexFreq();//Change freq

			//Esperar a que el boton se suelte y agregamos un delay
			while(!GPIO_PinRead(GPIOA, 4))
			{
			SDK_DelayAtLeastUs(1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
			}
		}

		//Verificamos el SW3
		if(!GPIO_PinRead(GPIOC, 6))
		{
			Signal_NexType();

			while(!GPIO_PinRead(GPIOC, 6)){
				SDK_DelayAtLeastUs(1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
			}

		}
	}
	return 0;

}
