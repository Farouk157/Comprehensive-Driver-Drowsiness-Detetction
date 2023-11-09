/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   SYSTICK                           */
/*      Date    :   9/9/2023                          */
/*      version :       1.00                          */
/******************************************************/

#ifndef MCAL_SYSTICK_STK_INTERFACE_H_
#define MCAL_SYSTICK_STK_INTERFACE_H_

/*
 * @breif: This function is used to initialize the SYSTICK timer
 * @ret:   Nothing 
 * @param: No Parameters 
 */
void STK_voidInit(void);

/*
 * @breif: This function is used to Stop the SYSTICK timer
 * @ret:   Nothing 
 * @param: No Parameters 
 */
void STK_voidStopTimer(void);

/*
 * @breif: This function is used to make delay and stop the system for specific period
 * @ret:   Nothing 
 * @param1: Copy_u32Ticks -> holds the desired value of time in ticks  
 */
void STK_voidSetBusyWait(u32 Copy_u32Ticks);

/*
 * @breif: This function is used to make delay but with event trigger only once 
 * @ret:   Nothing 
 * @param1: Copy_u32Ticks -> holds the desired value of time in ticks
 * @param2: this is the address of the ISR function that you want to be executed in the Interrupt   
 */
void STK_voidSetInterval_Single(u32 Copy_u32Ticks, void (* CallBackFunction)(void));

/*
 * @breif: This function is used to make delay but with event trigger periodicly 
 * @ret:   Nothing 
 * @param1: Copy_u32Ticks -> holds the desired value of time in ticks
 * @param2: this is the address of the ISR function that you want to be executed in the Interrupt   
 */
void STK_voidSetInterval_Periodic(u32 Copy_u32Ticks, void (* CallBackFunction)(void));

/*
 * @breif: This function is used to get the finished time
 * @ret:   Return the value of the finished time already  
 * @param: No Parameters 
 */
u32 STK_u32GetElapsedTime(void);

/*
 * @breif: This function is used to get the remaining time
 * @ret:   Return the value of the remaining time   
 * @param: No Parameters 
 */
u32 STK_u32GetRemainingTime(void);

#endif /* MCAL_SYSTICK_STK_INTERFACE_H_ */
