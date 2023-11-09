/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   SYSTICK                           */
/*      Date    :   9/9/2023                          */
/*      version :       1.00                          */
/******************************************************/


#ifndef MCAL_SYSTICK_STK_CONFIG_H_
#define MCAL_SYSTICK_STK_CONFIG_H_

/* clock source options */
#define AHB_CLOCK					1
#define AHB_CLOCK_FACT_8			2

/*	Choose clock source
 *		1- AHB / 8
 *		2- AHB
 */
#define AHB_CLOCK_STATUS 			AHB_CLOCK_FACT_8

#define ENABLE						1
#define DISABLE						0

/*	choose interrupt option
 * 		1- INTERRUPT_ENABLE
 * 		2- INTERRUPT DISABLE
 */

#define STK_INTERRUPT_STATE			ENABLE

#endif /* MCAL_SYSTICK_STK_CONFIG_H_ */
