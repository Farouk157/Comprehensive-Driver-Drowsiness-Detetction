/*******************************************************/
/*      Author  :   Mohamed Ashraf Mohamed             */
/*      SWC     :   NVIC_Interface.h                   */
/*      Date    :   6/10/2023                          */
/*      version :       1.00                           */
/*******************************************************/

#ifndef MCAL_NVIC_NVIC_INT_H_
#define MCAL_NVIC_NVIC_INT_H_

#define NVIC_16_GROUPS   0b011  // 3
#define NVIC_8_GROUPS    0b100  // 4
                                // 5   6  7


#define  NVIC_SYSTICK       -5
#define  NVIC_PEND_SV       -6

#define  NVIC_SV_CALL       -4

#define NVIC_USAGE_FAULT    -1
#define NVIC_BUS_FAULT      -2
#define NVIC_MEMORY_MANAGE  -3

#define NVIC_EXTI0			 6
#define NVIC_USART2			 38

/**
 * @brief   If a pending interrupt is enabled, the NVIC activates the interrupt based on its priority.
 * @param   NUM OF interrupt
 * @retval  none
 */
void MNVIC_vEnableInteruptPeripheral(u8 A_u8IntId);

/**
 * @brief   If a pending interrupt is Disable , the NVIC activates the interrupt based on its priority.
 * @param   NUM OF interrupt
 * @retval  none
 */
void MNVIC_vDisableInteruptPeripheral(u8 A_u8IntId);

/*Test SW int*/

/**
 * @brief   set a flag to make software testing
 * @param   NUM OF Interrupt 
 * @retval  none
 */
void MNVIC_vSetPending(u8 A_u8IntId);


void MNVIC_vClearPending(u8 A_u8IntId);

//to check
/**
 * @brief   Removes the pending state of an interrupt
 * @param   NUM OF flag
 * @retval  return active flag (interrupt)
 */
u8 MNVIC_u8GetActive(u8 A_u8IntId);


void MNVIC_vSetPriorityCfg(u8 A_u8Group);

void MNVIC_vSetPriority(s8 A_s8IntId , u8 A_u8GroupPriority,u8 A_u8SubPriority);

#endif /* MCAL_NVIC_NVIC_INT_H_ */
