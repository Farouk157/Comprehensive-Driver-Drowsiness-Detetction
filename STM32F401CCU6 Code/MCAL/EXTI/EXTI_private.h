/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   EXTI                              */
/*      Date    :   9/10/2023                         */
/*      version :       1.00                          */
/******************************************************/

#ifndef MCAL_EXTI_EXTI_PRIVATE_H_
#define MCAL_EXTI_EXTI_PRIVATE_H_

/* Base Address for EXTI registers */
#define EXTI_BASE_ADDRESS		0x40013C00

/* structure containing the EXTI Registers */
typedef struct
{
	volatile u32 	IMR		;
	volatile u32 	EMR		;
	volatile u32 	RTSR	;
	volatile u32 	FTSR	;
	volatile u32	SWIER	;
	volatile u32 	PR		;
}EXTI_MemMap_t;

/* this is a macro pointer to the base address*/
#define EXTI		((volatile EXTI_MemMap_t *)EXTI_BASE_ADDRESS)

/*******************************************************************************************************/

/* Base Address for SYSCFG Registers*/
#define SYSCFG_BASE_ADDRESS		0x40013800

/* structure containing the SYSCFG Registers */
typedef struct
{
	volatile u32 MEMRMP		;
	volatile u32 PMC		;
	volatile u32 EXTICR[4]	;
	volatile u32 CMPCR		;
}SYSCFG_MemMap_t;

/* this is a macro pointer to the base address*/
#define SYSCFG		((volatile SYSCFG_MemMap_t *)SYSCFG_BASE_ADDRESS)

#endif /* MCAL_EXTI_EXTI_PRIVATE_H_ */
