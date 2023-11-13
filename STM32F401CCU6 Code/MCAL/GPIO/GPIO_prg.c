/****************************************************************************************
 /*   Author: Abdalah Beshary
 /*   SWC   : GPIO_prg.c
 /*	  Date  : 6/10/2023
 /*  Version: 1.0
 **************************************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "GPIO_prv.h"
#include "GPIO_int.h"
///////////////////////////////////////////
void MGPIO_vInit(GPIO_cfg_t *A_ptr)
{
	MGPIO_vSetPinMode(A_ptr->port,A_ptr->pin,A_ptr->mode);
	MGPIO_vSetPinOutputType(A_ptr->port,A_ptr->pin,A_ptr->out_type);
	MGPIO_vSetPinOutputSpeed(A_ptr->port,A_ptr->pin,A_ptr->speed);
	MGPIO_vSetPinInputPull(A_ptr->port,A_ptr->pin,A_ptr->input_type);
	MGPIO_vSetAlternativeFunction(A_ptr->port,A_ptr->pin,A_ptr->A_u8Altfun);
}
///////////////////////////////////////////
void MGPIO_vSetPinMode(u8 A_u8PortId,
		u8 A_u8PinNo,
		u8 A_u8Mode )
{
	if(A_u8PinNo <16 && A_u8Mode<4)
	{
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			GPIOA->MODER &= ~((0b11)<<(A_u8PinNo*2));
			GPIOA->MODER |= (A_u8Mode<<(A_u8PinNo*2));
			break;
		case GPIO_PORTB:
			GPIOB->MODER &= ~((0b11)<<(A_u8PinNo*2));
			GPIOB->MODER |= (A_u8Mode<<(A_u8PinNo*2));
			break;
		case GPIO_PORTC:
			GPIOC->MODER &= ~((0b11)<<(A_u8PinNo*2));
			GPIOC->MODER |= (A_u8Mode<<(A_u8PinNo*2));
			break;
		}
	}

}
void MGPIO_vSetPinOutputType(u8 A_u8PortId,
		u8 A_u8PinNo,
		u8 A_u8OutType )
{
	if(A_u8OutType== GPIO_OUTPUTTYPE_PUSHPULL )
	{
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			CLR_BIT(GPIOA->OTYPER,A_u8PinNo);
			break;
		case GPIO_PORTB:
			CLR_BIT(GPIOB->OTYPER,A_u8PinNo);
			break;
		case GPIO_PORTC:
			CLR_BIT(GPIOC->OTYPER,A_u8PinNo);
			break;
		}
	}
	else if (A_u8OutType == GPIO_OUTTYPE_OPENDRAIN)
	{
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			SET_BIT(GPIOA->OTYPER,A_u8PinNo);
			break;
		case GPIO_PORTB:
			SET_BIT(GPIOB->OTYPER,A_u8PinNo);
			break;
		case GPIO_PORTC:
			SET_BIT(GPIOC->OTYPER,A_u8PinNo);
			break;
		}
	}
	else {/*Error*/}

}

void MGPIO_vSetPinOutputSpeed(u8 A_u8PortId,
		u8 A_u8PinNo,
		u8 A_u8OutSpeed )
{
	if(A_u8PinNo <16 && A_u8OutSpeed<4)
	{
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			GPIOA->OSPEEDR &= ~((0b11)<<(A_u8PinNo*2));
			GPIOA->OSPEEDR |= (A_u8OutSpeed<<(A_u8PinNo*2));
			break;
		case GPIO_PORTB:
			GPIOB->OSPEEDR &= ~((0b11)<<(A_u8PinNo*2));
			GPIOB->OSPEEDR |= (A_u8OutSpeed<<(A_u8PinNo*2));
			break;
		case GPIO_PORTC:
			GPIOC->OSPEEDR &= ~((0b11)<<(A_u8PinNo*2));
			GPIOC->OSPEEDR |= (A_u8OutSpeed<<(A_u8PinNo*2));
			break;
		}
	}
}

void MGPIO_vSetPinInputPull(u8 A_u8PortId,
		u8 A_u8PinNo,
		u8 A_u8PullType )
{
	switch(A_u8PortId)
	{
	case GPIO_PORTA :
		GPIOA->PUPDR &= ~((0b11)<<(A_u8PinNo*2));
		GPIOA->PUPDR |= (A_u8PullType<<(A_u8PinNo*2));
		break;
	case GPIO_PORTB:
		GPIOB->PUPDR &= ~((0b11)<<(A_u8PinNo*2));
		GPIOB->PUPDR |= (A_u8PullType<<(A_u8PinNo*2));
		break;
	case GPIO_PORTC:
		GPIOC->PUPDR &= ~((0b11)<<(A_u8PinNo*2));
		GPIOC->PUPDR |= (A_u8PullType<<(A_u8PinNo*2));
		break;
	}
}


u8 MGPIO_u8GetPinValue(u8 A_u8PortId,
		u8 A_u8PinNo)
{
	u8 L_u8Return = 2 ;
	switch(A_u8PortId)
	{
	case GPIO_PORTA :
		L_u8Return = GET_BIT(GPIOA->IDR,A_u8PinNo);
		break;
	case GPIO_PORTB:
		L_u8Return = GET_BIT(GPIOA->IDR,A_u8PinNo);
		break;
	case GPIO_PORTC:
		L_u8Return = GET_BIT(GPIOA->IDR,A_u8PinNo);
		break;
	}
	return L_u8Return ;
}

void MGPIO_vSetPinValue(u8 A_u8PortId,
		u8 A_u8PinNo,
		u8 A_u8PinVal )
{
	//	switch(A_u8PortId)
	//	{
	//	case GPIO_PORTA :
	//		GPIOA->ODR &= ~((1)<<(A_u8PinNo));
	//		GPIOA->ODR |= (A_u8PinVal<<(A_u8PinNo));
	//		break;
	//	case GPIO_PORTB:
	//		GPIOB->ODR &= ~((1)<<(A_u8PinNo));
	//		GPIOB->ODR |= (A_u8PinVal<<(A_u8PinNo));
	//		break;
	//	case GPIO_PORTC:
	//		GPIOC->ODR &= ~((1)<<(A_u8PinNo));
	//		GPIOC->ODR |= (A_u8PinVal<<(A_u8PinNo));
	//		break;
	//	}
	if(A_u8PinVal==GPIO_HIGH)
	{
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			SET_BIT(GPIOA->ODR,A_u8PinNo);
			break;
		case GPIO_PORTB:
			SET_BIT(GPIOB->ODR,A_u8PinNo);
			break;
		case GPIO_PORTC:
			SET_BIT(GPIOC->ODR,A_u8PinNo);
			break;
		}
	}
	else if (A_u8PinVal==GPIO_LOW)
	{
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			CLR_BIT(GPIOA->ODR,A_u8PinNo);
			break;
		case GPIO_PORTB:
			CLR_BIT(GPIOB->ODR,A_u8PinNo);
			break;
		case GPIO_PORTC:
			CLR_BIT(GPIOC->ODR,A_u8PinNo);
			break;
		}
	}
}


void MGPIO_vSetPinValFast(u8 A_u8PortId,
		u8 A_u8PinNo,
		u8 A_u8PinVal )
{
	switch(A_u8PinVal)
	{
	case GPIO_HIGH :
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			GPIOA->BSRR = (1<<A_u8PinNo);
			break;
		case GPIO_PORTB :
			GPIOB->BSRR = (1<<A_u8PinNo);
			break;
		}
		break;
		case GPIO_LOW :
			switch(A_u8PortId)
			{
			case GPIO_PORTA :
				GPIOA->BSRR = (1<<(A_u8PinNo+16));
				break;
			case GPIO_PORTB :
				GPIOB->BSRR = (1<<(A_u8PinNo+16));
				break;
			}
			break;
	}
}

void MGPIO_vSetAlternativeFunction(u8 A_u8PortId,
		u8 A_u8PinNo,
		u8 A_u8Altfun )
{
	if(A_u8PinNo <8)
	{
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			GPIOA->AFRL  &= ~((0b1111)<<(A_u8PinNo*4));
			GPIOA->AFRL  |= ((A_u8Altfun)<<(A_u8PinNo*4));
			break;
		case GPIO_PORTB :
			GPIOB->AFRL  &= ~((0b1111)<<(A_u8PinNo*4));
			GPIOB->AFRL  |= ((A_u8Altfun)<<(A_u8PinNo*4));
			break;
		}
	}
	else if (A_u8PinNo < 16)
	{
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			GPIOA->AFRH  &= ~((0b1111)<<((A_u8PinNo-8)*4));
			GPIOA->AFRH  |= ((A_u8Altfun)<<((A_u8PinNo-8)*4));
			break;
		case GPIO_PORTB :
			GPIOA->AFRH  &= ~((0b1111)<<((A_u8PinNo-8)*4));
			GPIOA->AFRH  |= ((A_u8Altfun)<<((A_u8PinNo-8)*4));
			break;
		}
	}
}






