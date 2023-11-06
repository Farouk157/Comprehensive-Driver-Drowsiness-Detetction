/*******************************************************/
/*      Author  :   Mohamed Ashraf Mohamed             */
/*      SWC     :   NVIC_interface.h                   */
/*      Date    :   7/10/2023                          */
/*      version :       1.00                           */
/*******************************************************/


#ifndef MCAL_NVIC_NVIC_INTERFACE_H_
#define MCAL_NVIC_NVIC_INTERFACE_H_


#define GROUP_4BITS		0b011
#define GROUP_3BITS		0b100
#define GROUP_2BITS		0b101
#define GRPUP_1BITS		0b110
#define GROUP_0BITS		0b111

/////////////
#define PEND_SV	-6
#define SYSTICK	-5
//////////
#define SV_CALL	-4
//////////////
#define MEMORY_MANAGE	-3
#define BUS_FAULT		-2
#define USAGE_FAULT		-1
////////////////
#define WWDG			0
#define EXTI16			1

/**
 * @brief   If a pending interrupt is enabled, the NVIC activates the interrupt based on its priority.
 * @param   NUM OF interrupt
 * @retval  none
 */

void NVIC_voidEnablePeripheral	(u8 Copy_u8IntID);

/**
 * @brief   If a pending interrupt is Disable , the NVIC activates the interrupt based on its priority.
 * @param   NUM OF interrupt
 * @retval  none
 */

void NVIC_voidDisablePeripheral	(u8 Copy_u8IntID);

/**
 * @brief   set a flag means interrupt that is pending has no effect.
 * @param   NUM OF flag
 * @retval  none
 */

void NVIC_voidSetPendingFlag	(u8 Copy_u8IntID);

/**
 * @brief   Removes the pending state of an interrupt
 * @param   NUM OF flag
 * @retval  none
 */

void NVIC_voidClearPendingFlag	(u8 Copy_u8IntID);

/**
 * @brief   Removes the pending state of an interrupt
 * @param   NUM OF flag
 * @retval  return active flag (interrupt)
 */

u8 NVIC_u8GetActive	(u8 Copy_u8IntID);

void NVIC_voidSetPriorityConfig	(u8 Copy_u8PriorityOption);

void NVIC_voidSetPriority	(s8 Copy_s8IntId , u8 Copy_u8GroupPriority , u8 Copy_u8SubPriority);


#endif /* MCAL_NVIC_NVIC_INTERFACE_H_ */
