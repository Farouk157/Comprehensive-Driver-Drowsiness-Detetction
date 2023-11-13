
/*******************************************************/
/*      Author  :   Mohamed Ashraf Mohamed             */
/*      SWC     :   FSR_interface.h                    */
/*      Date    :   12/10/2023                          */
/*      version :       1.00                           */
/*******************************************************/
#ifndef HAL_FSR_FSR_INTERFACE_H_
#define HAL_FSR_FSR_INTERFACE_H_

#define THRESHOLD_VALUE 		1000

/** FSR mean Force Sensitive Resistor
 * @brief   It's function to Initialize number of pins for FSR sensor in arm-kit in analog mode using GPIO.
 * @param   PORTA ( PIN0, PIN1 )
 * @retval  none
 */

void FSR_Init(void);

/**
 * @brief  this function read analog value from FSR sensor using ADC channel
 * @param   Reading_FSR : THIS parameter contain reading analog value from FSR sensor number 1
 * @retval  Channel of ADC
 */

u16 FSR_Read_1(u8 ADC_u8Channel);

/**
 * @brief  this function read analog value from FSR sensor using ADC channel
 * @param   Reading_FSR : THIS parameter contain reading analog value from FSR sensor number 1
 * @retval  Channel of ADC
 */

u16 FSR_Read_2( u8 ADC_u8Channel);


#endif /* HAL_FSR_FSR_INTERFACE_H_ */
