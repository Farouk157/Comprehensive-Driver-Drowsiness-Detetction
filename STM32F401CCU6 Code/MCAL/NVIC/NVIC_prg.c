/*******************************************************/
/*      Author  :   Mohamed Ashraf Mohamed             */
/*      SWC     :   NVIC_program.c                     */
/*      Date    :   6/10/2023                          */
/*      version :       1.00                           */
/*******************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "NVIC_prv.h"
#include "NVIC_int.h"
static u8 A_u8GroupPriorty ;

/**
 * @brief   If a pending interrupt is enabled, the NVIC activates the interrupt based on its priority.
 * @param   NUM OF interrupt
 * @retval  none
 */
void MNVIC_vEnableInteruptPeripheral(u8 A_u8IntId)
{
NVIC->ISER[A_u8IntId/32] = 1 << (A_u8IntId % 32);
}

/**
 * @brief   If a pending interrupt is Disable , the NVIC activates the interrupt based on its priority.
 * @param   NUM OF interrupt
 * @retval  none
 */
void MNVIC_vDisableInteruptPeripheral(u8 A_u8IntId)
{
	NVIC->ICER[A_u8IntId/32] = 1 << (A_u8IntId % 32);
}

/*Test SW int*/
/**
 * @brief   set a flag to make software testing
 * @param   NUM OF Interrupt 
 * @retval  none
 */
void MNVIC_vSetPending(u8 A_u8IntId)
{
	NVIC->ISPR[A_u8IntId/32] = 1 << (A_u8IntId % 32);
}

void MNVIC_vClearPending(u8 A_u8IntId)
{
	NVIC->ICPR[A_u8IntId/32] = 1 << (A_u8IntId % 32);
}

//to check
/**
 * @brief   Removes the pending state of an interrupt
 * @param   NUM OF flag
 * @retval  return active flag (interrupt)
 */
u8 MNVIC_u8GetActive(u8 A_u8IntId)
{

	return GET_BIT(NVIC->IABR[A_u8IntId/32],(A_u8IntId % 32));
}
//////////////////////////////////////////////////////////////////////////////////


void MNVIC_vSetPriorityCfg(u8 A_u8Group)
{
	A_u8GroupPriorty = 0x05FA0000 | (A_u8Group<<8);
	SCB->AIRCR = A_u8GroupPriorty  ;
}

void MNVIC_vSetPriority(s8 A_s8IntId , u8 A_u8GroupPriority,u8 A_u8SubPriority)
{
	u32 L_u32Periority = (SCB->AIRCR & (0x00000700)>>8);
	/*configure software periority of Group Priority and Sub Priority*/
	L_u32Periority = A_u8SubPriority | (A_u8GroupPriority<<(L_u32Periority - 3)) ;
	/*interrupts of core peripheral*/
	if (A_s8IntId < 0)
	{
		if (A_s8IntId     == NVIC_MEMORY_MANAGE     ||A_s8IntId == NVIC_BUS_FAULT     || A_s8IntId == NVIC_USAGE_FAULT)
		{
			A_s8IntId += 3;
			SCB->SHPR1 &= ~((0b1111)        << ((8 * A_s8IntId) + 4));
			SCB->SHPR1 |=  ((L_u32Periority) << ((8 * A_s8IntId) + 4));
		}
		else if(A_s8IntId == NVIC_SV_CALL)
		{
			A_s8IntId += 7;
			SCB->SHPR2 &= ~((0b1111)        << ((8 * A_s8IntId) + 4));
			SCB->SHPR2 |=  ((L_u32Periority) << ((8 * A_s8IntId) + 4));
		}
		else if (A_s8IntId == NVIC_PEND_SV || A_s8IntId == NVIC_SYSTICK)
		{
			A_s8IntId += 8;
			SCB->SHPR3 &= ~((0b1111)        << ((8 * A_s8IntId) + 4));
			SCB->SHPR3 |=  ((L_u32Periority) << ((8 * A_s8IntId) + 4));
		}
	}
	/*interrupts of vendor peripheral*/
	else if (A_s8IntId >= 0)
	{
		NVIC -> IPR [A_s8IntId] = L_u32Periority << 4 ;
	}
}

