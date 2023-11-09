/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   SYSTICK                           */
/*      Date    :   9/9/2023                          */
/*      version :       1.00                          */
/******************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

/*
 * @breif: this is the pointer to function that holds the address of the Timer Interrupt Handler 
 */

static void (* GS_STK_Callback)(void);

/* this is a flag to indecate interval single or periodic */
static u8 Global_Falg;


/*
 * @breif: This function is used to initialize the SYSTICK timer
 * @ret:   Nothing 
 * @param: No Parameters 
 */
void STK_voidInit(void)
{
	/*for selecting the AHB clock option*/
	#if	AHB_CLOCK_STATUS == AHB_CLOCK_FACT_8
	CLR_BIT(STK->STK_CTRL, CLKSOURCE_BIT);
	#elif AHB_CLOCK_STATUS == AHB_CLOCK
	SET_BIT(STK->STK_CTRL, CLKSOURCE_BIT);
	#endif


	/*for selecting interrupt option */
	#if STK_INTERRUPT_STATE == ENABLE
	SET_BIT(STK->STK_CTRL, TICKINT_BIT);
	#endif

}


/*
 * @breif: This function is used to Stop the SYSTICK timer
 * @ret:   Nothing 
 * @param: No Parameters 
 */

void STK_voidStopTimer(void)
{
	/* Clear the flag bit*/
	CLR_BIT(STK->STK_CTRL, 16);
	/* Clear the control bit */    
	CLR_BIT(STK->STK_CTRL, COUNTER_ENABLE_BIT);
}


/*
 * @breif: This function is used to make delay and stop the system for specific period
 * @ret:   Nothing 
 * @param1: Copy_u32Ticks -> holds the desired value of time in ticks  
 */

void STK_voidSetBusyWait(u32 Copy_u32Ticks)
{
	/* 1- Clear the VAL register */
	STK->STK_VAL = 0;
	/* 2- Set The New Value note We are working on tick = 1us */
	STK->STK_LOAD = Copy_u32Ticks;
	/* 3- Enable the counter */
	SET_BIT(STK->STK_CTRL, COUNTER_ENABLE_BIT);
	/* 4- wait for timer flag */
	while(GET_BIT(STK->STK_CTRL, COUNTFLAG_BIT) != 1)
	{

	}
	/* 5- Stop the timer */
	CLR_BIT(STK->STK_CTRL, COUNTER_ENABLE_BIT);
}


/*
 * @breif: This function is used to make delay but with event trigger only once 
 * @ret:   Nothing 
 * @param1: Copy_u32Ticks -> holds the desired value of time in ticks
 * @param2: this is the address of the ISR function that you want to be executed in the Interrupt   
 */

void STK_voidSetInterval_Single(u32 Copy_u32Ticks, void (* CallBackFunction)(void))
{
	/* 1- Set the call back function */
	GS_STK_Callback = CallBackFunction;
	/* 2- Enable the Interrupt */
	SET_BIT(STK->STK_CTRL, TICKINT_BIT);
	/* 3- set the flag by 1 for using the ISR only once */
	Global_Falg = 1;
	/* 4- Clear value of VAL Register */
	STK->STK_VAL = 0;
	/* 5- Set the Ticks you want in the LOAD Register */
	STK->STK_LOAD = Copy_u32Ticks;
	/* 6- Enable the timer */
	SET_BIT(STK->STK_CTRL, COUNTER_ENABLE_BIT);
}


/*
 * @breif: This function is used to make delay but with event trigger periodicly 
 * @ret:   Nothing 
 * @param1: Copy_u32Ticks -> holds the desired value of time in ticks
 * @param2: this is the address of the ISR function that you want to be executed in the Interrupt   
 */
void STK_voidSetInterval_Periodic(u32 Copy_u32Ticks, void (* CallBackFunction)(void))
{
	/* 1- Set the call back function */
	GS_STK_Callback = CallBackFunction;
	/* 2- Enable the Interrupt */
	SET_BIT(STK->STK_CTRL, TICKINT_BIT);
	/* 3- set the flag by 1 for using the ISR only once */
	Global_Falg = 0;
	/* 4- Clear value of VAL Register */
	STK->STK_VAL = 0;
	/* 5- Set the Ticks you want in the LOAD Register */
	STK->STK_LOAD = Copy_u32Ticks;
	/* 6- Enable the timer */
	SET_BIT(STK->STK_CTRL, COUNTER_ENABLE_BIT);
}


/*
 * @breif: This function is used to get the finished time
 * @ret:   Return the value of the finished time already  
 * @param: No Parameters 
 */
u32 STK_u32GetElapsedTime(void)
{
	return((STK->STK_LOAD) - (STK->STK_VAL));
}


/*
 * @breif: This function is used to get the remaining time
 * @ret:   Return the value of the remaining time   
 * @param: No Parameters 
 */
u32 STK_u32GetRemainingTime(void)
{
	return((STK->STK_VAL));
}


/*
 * @breif: this is function used for the calling the ISR 
 * @ret:   Nothing   
 * @param: No Parameters 
 */
void SysTick_Handler(void)
{
	if(GS_STK_Callback != NULL)
	{
		GS_STK_Callback();
	}
	if(Global_Falg)
	{
		Global_Falg = 0;
		CLR_BIT(STK->STK_CTRL, COUNTER_ENABLE_BIT);
	}
}

