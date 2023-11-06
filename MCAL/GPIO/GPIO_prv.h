/*
 * GPIO_prv.h
 *
 *  Created on: Aug 22, 2022
 *      Author: DELL
 */

#ifndef MCAL_GPIO_GPIO_PRV_H_
#define MCAL_GPIO_GPIO_PRV_H_
//from memory map 2.3  page 38
#define  GPIOA_BASE_ADDRESS    0x40020000
#define  GPIOB_BASE_ADDRESS    0x40020400
#define  GPIOC_BASE_ADDRESS    0x40020800

//page 164
typedef struct{
u32 MODER;
u32 OTYPER;
u32 OSPEEDR;
u32 PUPDR;
u32 IDR;
u32 ODR;
u32 BSRR;
u32 LCKR;
u32 AFRL;
u32 AFRH;
}GPIO_MemMap_table;

#define GPIOA  ((volatile GPIO_MemMap_table*)(GPIOA_BASE_ADDRESS))
#define GPIOB  ((volatile GPIO_MemMap_table*)(GPIOB_BASE_ADDRESS))
#define GPIOC  ((volatile GPIO_MemMap_table*)(GPIOC_BASE_ADDRESS))
////00: Input (reset state)
////01: General purpose output mode
////10: Alternate function mode
////11: Analog mode
//typedef enum{
//	GPIO_MODE_INPUT,
//	GPIO_MODE_OUTPUT,
//	GPIO_MODE_ALTFUNC,
//	GPIO_MODE_ANALOG
//}GPIO_MODE;

#endif /* MCAL_GPIO_GPIO_PRV_H_ */
