/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   SYSTICK                           */
/*      Date    :   8/10/2023                         */
/*      version :       1.00                          */
/******************************************************/

#ifndef MCAL_SYSTICK_STK_PRIVATE_H_
#define MCAL_SYSTICK_STK_PRIVATE_H_



/* Base Address for SYSTICK Registers */

#define STK_BASE_ADDRESS		0xE000E010

/* structure containing the SYSTICK registers */
typedef struct{
	volatile u32 STK_CTRL;
	volatile u32 STK_LOAD;
	volatile u32 STK_VAL;
	volatile u32 STK_CALIB;

}STK_MemMap_t;

/* this is a macro pointer to the base address*/
#define 	STK 	((volatile STK_MemMap_t *) STK_BASE_ADDRESS)

/* macros for SYSTICK CTRL_Register Bits  */

#define COUNTER_ENABLE_BIT				0
#define CLKSOURCE_BIT					2
#define TICKINT_BIT						1
#define COUNTFLAG_BIT					16

#endif /* MCAL_SYSTICK_STK_PRIVATE_H_ */

