/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   EXTI                              */
/*      Date    :   9/10/2023                         */
/*      version :       1.00                          */
/******************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

/*
 * @brief: this is the pointer to function that holds the address of the External Interrupt Handler 
 */
void (*EXTI0_CallBack)(void);


/*
 * @brief: This function is used to initialize the External Interrupt
 * @ret:   Nothing 
 * @param: No Parameters 
 */

void EXTI_voidInit		(void)
{
	EXTI->IMR = 0 ;
	EXTI->IMR |= (EXTI_LINE_0_EN <<0) |
				(EXTI_LINE_1_EN	 <<1	)|
				(EXTI_LINE_2_EN << 2 ) |
				(EXTI_LINE_3_EN << 3) ;
				
				
				;

	/*Clear All Flags*/
	EXTI->PR = 0xffffffff ;

}


/*
 * @brief: This function is used to Enable EXTI for specific line and choosing triggering methodology 
 * @ret:   Nothing 
 * @param1: this is the number of line you want to activate and use
 * @param2: this is the Triggering Edge 
			Options:
			        - Falling Edge
					- Raising Edge
 */
void EXTI_voidEnableLine	(u8 Copy_u8Line , u8 Copy_u8TriggerEdge	)
{
	if(Copy_u8Line < 16 )
	{
		SET_BIT(EXTI->IMR , Copy_u8Line);
		switch(Copy_u8TriggerEdge)
		{
		case EXTI_RISING:
			SET_BIT(EXTI->RTSR , Copy_u8Line);
			CLR_BIT(EXTI->FTSR , Copy_u8Line);
			break;
		case EXTI_FALLING:
			CLR_BIT(EXTI->RTSR , Copy_u8Line);
			SET_BIT(EXTI->FTSR , Copy_u8Line);
			break ;
		case EXTI_ON_CHANGE:
			SET_BIT(EXTI->RTSR , Copy_u8Line);
			SET_BIT(EXTI->FTSR , Copy_u8Line);
			break;
		default :
			break;
		}
	}
}

/*
 * @brief:  This function is used to Disable EXTI for specific line
 * @ret  :  Nothing 
 * @param1: this is the number of line you want to activate and use
 */
void EXTI_voidDisableLine	(u8 Copy_u8Line)
{
	if(Copy_u8Line <16)
	{
		CLR_BIT(EXTI->IMR , Copy_u8Line);
	}
}

/*
 * @brief: this used to configure which port and line you want to enable the EXTI on 
 * @ret  : Nothing 
 * @param1:this is the number of line that you want
 * @param2:this is the number of port that you want  
*/

void SYSCFG_voidEXTIPort	(	u8 Copy_u8Line	, u8 Copy_u8PortNo	)
{
	if ( Copy_u8Line < 16)
	{
		SYSCFG->EXTICR[Copy_u8Line/4] &= ~((0b1111) << (4 * (Copy_u8Line % 4 )));
		SYSCFG->EXTICR[Copy_u8Line/4] |= (Copy_u8PortNo << (4 * (Copy_u8Line % 4 )));
	}
}

/*
 * @brief: this function is used to get the address of the API to be excuted when Interrupt being fired
 * @ret  : Nothing 
 * @Param: takes the pointer to function you want to execute when the interrupt being fired
*/
void EXTI_vSetCallBack( void( *ptr )(void) )
{
	EXTI0_CallBack = ptr;
}

/*
 * @brief: this is the Handler function of the interrupt 
 * @ret  : Nothing 
 * @param: Nothing 
*/
void EXTI0_IRQHandler(void)
{
	if(EXTI0_CallBack != NULL)
	{
		EXTI0_CallBack();
		SET_BIT(EXTI->PR, 0);
	}
}
