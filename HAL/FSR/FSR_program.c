/*******************************************************/
/*      Author  :   Mohamed Ashraf Mohamed             */
/*      SWC     :   FSR_program.c                      */
/*      Date    :   12/10/2023                         */
/*      version :       1.00                           */
/*******************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/ADC/ADC_int.h"
#include "../../MCAL/GPIO/GPIO_int.h"


#include "FSR_interface.h"

/** FSR mean Force Sensitive Resistor
 * @brief   It's function to Initialize number of pins for FSR sensor in arm-kit in analog mode using GPIO.
 * @param   PORTA ( PIN0, PIN1 )
 * @retval  none
 */

void FSR_Init(void)
{

	MGPIO_Config_t FSR = {
				.port = GPIO_PORTA,
				.pin  = GPIO_PIN1,
				.mode = GPIO_MODE_ANALOG,
				.input_pull = GPIO_NO_PULL_UP_OR_DOWN,
				.speed = GPIO_OUTSPEED_LOW
		};

		MGPIO_Config_t FSR2 ={
					.port = GPIO_PORTA,
					.pin  = GPIO_PIN0,
					.mode = GPIO_MODE_ANALOG,
					.input_pull = GPIO_NO_PULL_UP_OR_DOWN,
					.speed = GPIO_OUTSPEED_LOW
			};


		    MGPIO_vInit(&FSR);
			MGPIO_vInit(&FSR2);
}

/**
 * @brief  this function read analog value from FSR sensor using ADC channel
 * @param   Reading_FSR : THIS parameter contain reading analog value from FSR sensor number 1
 * @retval  Channel of ADC
 */

u16 FSR_Read_1(u8 ADC_u8Channel )
{




    u16 reding_FSR_1 = MADC_u16AnalogRead(ADC_u8Channel);

return reding_FSR_1;
}

/**
 * @brief  this function read analog value from FSR sensor using ADC channel
 * @param   Reading_FSR : THIS parameter contain reading analog value from FSR sensor number 2
 * @retval  Channel of ADC
 */

u16 FSR_Read_2(u8 ADC_u8Channel )
{



    u16 reding_FSR_2 = MADC_u16AnalogRead(ADC_u8Channel);

	return reding_FSR_2;
}

