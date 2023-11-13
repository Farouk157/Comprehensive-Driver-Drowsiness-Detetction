/*******************************************************/
/*      Author  :   Mohamed Ashraf Mohamed             */
/*      SWC     :   NVIC_private.h                     */
/*      Date    :   6/10/2023                          */
/*      version :       1.00                           */
/*******************************************************/

#ifndef MCAL_NVIC_NVIC_PRV_H_
#define MCAL_NVIC_NVIC_PRV_H_

#define NVIC_BASE_ADDRESS    0xE000E100
typedef struct{

	u32 ISER[8] ;
	u32 Reserved[24];
	u32 ICER[32];
	u32 ISPR[32];
	u32 ICPR[32];
	u32 IABR[64];
	u8  IPR[128];

}NVIC_MemMap_t;

#define NVIC   ((volatile NVIC_MemMap_t*)(NVIC_BASE_ADDRESS))


typedef struct
{
volatile u32 CPUID;
volatile u32 ICSR  ;
volatile u32 VTOR  ;
volatile u32 AIRCR  ;
volatile u32 SCR  ;
volatile u32 CCR  ;
volatile u32 SHPR1  ;
volatile u32 SHPR2  ;
volatile u32 SHPR3  ;
volatile u32 SHCSR  ;
volatile u32 CFSR  ;
volatile u32 HFSR  ;
volatile u32 RESERVED  ;
volatile u32 MMAR  ;
volatile u32 BFAR  ;
volatile u32 AFSR  ;
}SCB_MemMap_t;
#define  SCB_BASE_ADDRESS      0xE000ED00
#define  SCB  ((volatile SCB_MemMap_t*)(SCB_BASE_ADDRESS))

#define  PASSWORD_TOWRITE_TO_AIRCR       0x05FA0000



#endif /* MCAL_NVIC_NVIC_PRV_H_ */
