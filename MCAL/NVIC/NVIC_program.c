/*******************************************************/
/*      Author  :   Mohamed Ashraf Mohamed             */
/*      SWC     :   NVIC_program.c                     */
/*      Date    :   7/10/2023                          */
/*      version :       1.00                           */
/*******************************************************/

#include "../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"


static u32 NVIC_Glosu32GroupConf = 0 ;

/**
 * @brief   If a pending interrupt is enabled, the NVIC activates the interrupt based on its priority.
 * @param   NUM OF interrupt
 * @retval  none
 */

void NVIC_voidEnablePeripheral	(u8 Copy_u8IntID)
{
	NVIC ->ISER[Copy_u8IntID / 32] = 1 << (Copy_u8IntID %32);
}

/**
 * @brief   If a pending interrupt is Disable , the NVIC activates the interrupt based on its priority.
 * @param   NUM OF interrupt
 * @retval  none
 */
void NVIC_voidDisablePeripheral	(u8 Copy_u8IntID)
{
	NVIC ->ICER[Copy_u8IntID / 32] = 1 << (Copy_u8IntID %32);

}

/**
 * @brief   set a flag means interrupt that is pending has no effect.
 * @param   NUM OF flag
 * @retval  none
 */

void NVIC_voidSetPendingFlag	(u8 Copy_u8IntID)
{
	NVIC ->ISPR[Copy_u8IntID / 32] = 1 << (Copy_u8IntID %32);

}

/**
 * @brief   Removes the pending state of an interrupt
 * @param   NUM OF flag
 * @retval  none
 */
void NVIC_voidClearPendingFlag	(u8 Copy_u8IntID)
{
	NVIC ->ICPR[Copy_u8IntID / 32] = 1 << (Copy_u8IntID %32);

}

/**
 * @brief   Removes the pending state of an interrupt
 * @param   NUM OF flag
 * @retval  return active flag (interrupt)
 */
u8 NVIC_u8GetActive	(u8 Copy_u8IntID)
{
	return GET_BIT((NVIC->IAPR[Copy_u8IntID/32]),(Copy_u8IntID % 32));
}

void NVIC_voidSetPriorityConfig	(u8 Copy_u8PriorityOption)
{
	NVIC_Glosu32GroupConf = VECT_KEY | ( Copy_u8PriorityOption << 8);	// 0x0f5A xxxx
	SCB->AIRCR = NVIC_Glosu32GroupConf ;
}

void NVIC_voidSetPriority	(s8 Copy_s8IntId , u8 Copy_u8GroupPriority , u8 Copy_u8SubPriority)
{
	u8 Local_u8Priority = Copy_u8SubPriority | (Copy_u8GroupPriority << ((NVIC_Glosu32GroupConf - 0x05FA0300)/256));
	
	if(Copy_s8IntId < 0)
	{
		if(Copy_s8IntId == MEMORY_MANAGE || Copy_s8IntId == BUS_FAULT || Copy_s8IntId == USAGE_FAULT)
		{
			Copy_s8IntId += 3 ;
			SCB->SHPR1 = (Local_u8Priority)<< ((8* Copy_s8IntId) +4);
		}
		else if(Copy_s8IntId == SV_CALL)
		{
			Copy_s8IntId +=7 ;
			SCB->SHPR2 = (Local_u8Priority) << ((8 * Copy_s8IntId) + 4 );
		}
		else if ( Copy_u8GroupPriority == PEND_SV)
			//		else if ( Copy_u8GroupPriority == PEND_SV)

		{
			Copy_s8IntId += 8 ;
			SCB->SHPR3 = (Local_u8Priority) << ((8*Copy_s8IntId) + 4 );
		}
	}
	else if ( Copy_s8IntId >= 0)
	{
		NVIC->IPR[Copy_s8IntId] = Local_u8Priority << 4 ;
	}
}

