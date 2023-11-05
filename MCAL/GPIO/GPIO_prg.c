/*
 * GPIO_prg.c
 *
 *  Created on: Aug 22, 2022
 *      Author: DELL
 */

#include "../../LIB/STD_TYPES.h"

#include "../../LIB/BIT_MATH.h"

#include "GPIO_prv.h"
#include "GPIO_int.h"

#include "GPIO_cfg.h"



void MGPIO_vSetPinMode(u8 A_u8PortId ,PinNo A_PinNo,GPIO_MODE GPIO_Mode)
{
	if(GPIO_Mode<=3 && A_PinNo<=15)
	{
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			GPIOA->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOA->MODER |= ((GPIO_Mode)<<(A_PinNo*2));
			break;
		case GPIO_PORTB :
			GPIOB->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOB->MODER |= ((GPIO_Mode)<<(A_PinNo*2));
			break;
		case GPIO_PORTC :
			GPIOC->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOC->MODER |= ((GPIO_Mode)<<(A_PinNo*2));
			break;
		default:
			/* Error: GPIO ID  not be founded */
			break;
		}
	}

}
void MGPIO_vSetPinOutputType (u8 A_u8PortId ,PinNo A_PinNo,u8 A_u8OutType)
{
	if(A_PinNo<=15)
	{
		if(A_u8OutType==GPIO_PUSH_PULL)
		{
			switch(A_u8PortId)
			{
			case GPIO_PORTA :
				CLR_BIT(GPIOA->OTYPER,A_PinNo);
				break;
			case GPIO_PORTB :
				CLR_BIT(GPIOB->OTYPER,A_PinNo);
				break;
			case GPIO_PORTC :
				CLR_BIT(GPIOC->OTYPER,A_PinNo);
				break;
			default:
				/* Error: GPIO ID  not be founded */
				break;
			}
		}
		else if (A_u8OutType==GPIO_OPEN_DRAIN)
		{
			switch(A_u8PortId)
			{
			case GPIO_PORTA :
				SET_BIT(GPIOA->OTYPER,A_PinNo);
				break;
			case GPIO_PORTB :
				SET_BIT(GPIOB->OTYPER,A_PinNo);
				break;
			case GPIO_PORTC :
				SET_BIT(GPIOC->OTYPER,A_PinNo);
				break;
			default:
				/* Error: GPIO ID  not be founded */
				break;
			}
		}
	}
}


void MGPIO_vSetPinOutputSpeed(u8 A_u8PortId ,
		PinNo A_PinNo,
		u8 A_u8OutSpeed)
{
	if(A_u8OutSpeed<=3 && A_PinNo<=15)
	{
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			GPIOA->OSPEEDR &= ~((0b11)<<(A_PinNo*2));
			GPIOA->OSPEEDR |= ((A_u8OutSpeed)<<(A_PinNo*2));
			break;
		case GPIO_PORTB :
			GPIOB->OSPEEDR &= ~((0b11)<<(A_PinNo*2));
			GPIOB->OSPEEDR |= ((A_u8OutSpeed)<<(A_PinNo*2));
			break;
		case GPIO_PORTC :
			GPIOC->OSPEEDR &= ~((0b11)<<(A_PinNo*2));
			GPIOC->OSPEEDR |= ((A_u8OutSpeed)<<(A_PinNo*2));
			break;
		default:
			/* Error: GPIO ID  not be founded */
			break;
		}
	}
}


/*my function*/
void MGPIO_vSetPinOutput(u8 A_u8PortId ,PinNo A_PinNo,u8 A_u8OutSpeed ,u8 A_u8OutType)
{
	if(A_PinNo <=15 &&  A_u8OutSpeed<=3 && A_u8OutType<=1)
	{
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			GPIOA->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOA->OSPEEDR &= ~((0b11)<<(A_PinNo*2));

			GPIOA->MODER |=((GPIO_MODE_OUTPUT)<<(A_PinNo*2));
			GPIOA->OSPEEDR |=((A_u8OutSpeed)<<(A_PinNo*2));

			CLR_BIT(GPIOA->OTYPER,A_PinNo);
			GPIOA->OTYPER |=((A_u8OutType)<<(A_PinNo));
			break;
		case GPIO_PORTB :
			GPIOB->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOB->OSPEEDR &= ~((0b11)<<(A_PinNo*2));

			GPIOB->MODER |=((GPIO_MODE_OUTPUT)<<(A_PinNo*2));
			GPIOB->OSPEEDR |=((A_u8OutSpeed)<<(A_PinNo*2));

			CLR_BIT(GPIOB->OTYPER,A_PinNo);
			GPIOB->OTYPER |=((A_u8OutType)<<(A_PinNo));
			break;
		case GPIO_PORTC :
			GPIOC->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOC->OSPEEDR &= ~((0b11)<<(A_PinNo*2));

			GPIOC->MODER |=((GPIO_MODE_OUTPUT)<<(A_PinNo*2));
			GPIOC->OSPEEDR |=((A_u8OutSpeed)<<(A_PinNo*2));

			CLR_BIT(GPIOC->OTYPER,A_PinNo);
			GPIOC->OTYPER |=((A_u8OutType)<<(A_PinNo));
			break;
		}
	}
}
void MGPIO_vSetPinInput(u8 A_u8PortId ,PinNo A_PinNo,u8 A_u8PupDr)
{
	if(A_PinNo <=15 &&  A_u8PupDr<=3)
	{

		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			GPIOA->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOA->MODER |=((GPIO_MODE_INPUT)<<(A_PinNo*2));

			GPIOA->PUPDR &= ~((0b11)<<(A_PinNo*2));
			GPIOA->PUPDR |=((A_u8PupDr)<<(A_PinNo*2));
			break;
		case GPIO_PORTB :
			GPIOB->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOB->MODER |=((GPIO_MODE_INPUT)<<(A_PinNo*2));

			GPIOA->PUPDR &= ~((0b11)<<(A_PinNo*2));
			GPIOA->PUPDR |=((A_u8PupDr)<<(A_PinNo*2));
			break;
		case GPIO_PORTC :
			GPIOC->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOC->MODER |=((GPIO_MODE_INPUT)<<(A_PinNo*2));

			GPIOA->PUPDR &= ~((0b11)<<(A_PinNo*2));
			GPIOA->PUPDR |=((A_u8PupDr)<<(A_PinNo*2));
			break;
		}
	}
}
void MGPIO_vSetPinAltFuncLow(u8 A_u8PortId ,PinNo A_PinNo,u8 A_u8AltFunc)
{
	if(A_PinNo <=7 &&  A_u8AltFunc<=0b1111)
	{

		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			GPIOA->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOA->MODER |=((GPIO_MODE_ALTFUNC)<<(A_PinNo*2));

			GPIOA->AFRL &= ~((0b1111)<<(A_PinNo*4));
			GPIOA->AFRL |=((A_u8AltFunc)<<(A_PinNo*4));
			break;
		case GPIO_PORTB :
			GPIOB->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOB->MODER |=((GPIO_MODE_ALTFUNC)<<(A_PinNo*2));

			GPIOA->AFRL &= ~((0b1111)<<(A_PinNo*4));
			GPIOA->AFRL |=((A_u8AltFunc)<<(A_PinNo*4));
			break;
		case GPIO_PORTC :
			GPIOC->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOC->MODER |=((GPIO_MODE_ALTFUNC)<<(A_PinNo*2));

			GPIOA->AFRL &= ~((0b1111)<<(A_PinNo*4));
			GPIOA->AFRL |=((A_u8AltFunc)<<(A_PinNo*4));
			break;
		}
	}
	else if(A_PinNo <=15 &&  A_u8AltFunc<=0b1111)
	{

		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			GPIOA->MODER &= ~((0b11)<<((A_PinNo)*2));
			GPIOA->MODER |=((GPIO_MODE_ALTFUNC)<<((A_PinNo)*2));

			GPIOA->AFRH &= ~((0b1111)<<((A_PinNo-8)*4));
			GPIOA->AFRH |=((A_u8AltFunc)<<((A_PinNo-8)*4));
			break;
		case GPIO_PORTB :
			GPIOA->MODER &= ~((0b11)<<((A_PinNo)*2));
			GPIOA->MODER |=((GPIO_MODE_ALTFUNC)<<((A_PinNo)*2));

			GPIOA->AFRH &= ~((0b1111)<<((A_PinNo-8)*4));
			GPIOA->AFRH |=((A_u8AltFunc)<<((A_PinNo-8)*4));
			break;
		case GPIO_PORTC :
			GPIOA->MODER &= ~((0b11)<<((A_PinNo)*2));
			GPIOA->MODER |=((GPIO_MODE_ALTFUNC)<<((A_PinNo)*2));

			GPIOA->AFRH &= ~((0b1111)<<((A_PinNo-8)*4));
			GPIOA->AFRH |=((A_u8AltFunc)<<((A_PinNo-8)*4));
			break;
		}
	}
}
void MGPIO_vSetPinAnalog(u8 A_u8PortId ,PinNo A_PinNo)
{
	if(A_PinNo <=15)
	{
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			GPIOA->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOA->MODER |=((GPIO_MODE_ANALOG)<<(A_PinNo*2));
			break;
		case GPIO_PORTB :
			GPIOB->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOB->MODER |=((GPIO_MODE_ANALOG)<<(A_PinNo*2));
			break;
		case GPIO_PORTC :
			GPIOC->MODER &= ~((0b11)<<(A_PinNo*2));
			GPIOC->MODER |=((GPIO_MODE_ANALOG)<<(A_PinNo*2));
			break;
		}
	}
}

void MGPIO_vSetPinVal_Fast(u8 A_u8PortId ,PinNo A_PinNo,u8 A_u8Val)
{
	// 0 to 15     (1 means set)
	//16 to 32     (1 means clr)
	if(A_u8Val==GPIO_HIGH)
	{
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			GPIOA->BSRR =(1<<(A_PinNo));
			break;
		case GPIO_PORTB :
			GPIOA->BSRR =(1<<(A_PinNo));
			break;
		case GPIO_PORTC :
			GPIOA->BSRR =(1<<(A_PinNo));
			break;
		}
	}
	else if(GPIO_LOW)
	{
		switch(A_u8PortId)
		{
		case GPIO_PORTA :
			GPIOA->BSRR =(1<<(A_PinNo+16));
			break;
		case GPIO_PORTB :
			GPIOA->BSRR =(1<<(A_PinNo+16));
			break;
		case GPIO_PORTC :
			GPIOA->BSRR =(1<<(A_PinNo+16));
			break;
		}
	}
}
void MGPIO_vSetPinVal(u8 A_u8PortId ,PinNo A_PinNo,u8 A_u8Val)
{
	if(A_PinNo<=15)
	{
		if(A_u8Val==GPIO_HIGH)
		{
			switch(A_u8PortId)
			{
			case GPIO_PORTA :
				SET_BIT(GPIOA->ODR,A_PinNo);
				break;
			case GPIO_PORTB :
				SET_BIT(GPIOB->ODR,A_PinNo);
				break;
			case GPIO_PORTC :
				SET_BIT(GPIOC->ODR,A_PinNo);
				break;
			}
		}
		else if(A_u8Val==GPIO_LOW)
		{
			switch(A_u8PortId)
			{
			case GPIO_PORTA :
				CLR_BIT(GPIOA->ODR,A_PinNo);
				break;
			case GPIO_PORTB :
				CLR_BIT(GPIOB->ODR,A_PinNo);
				break;
			case GPIO_PORTC :
				CLR_BIT(GPIOC->ODR,A_PinNo);
				break;
			}
		}
	}

}
void MGPIO_vSetPortVal(u8 A_u8PortId ,u16 A_u16Val)
{
	switch(A_u8PortId)
	{
	case GPIO_PORTA :
		GPIOA->ODR = (A_u16Val) & (0x0000FFFF) ;
		break;
	case GPIO_PORTB :
		GPIOB->ODR = (A_u16Val) & (0x0000FFFF) ;
		break;
	case GPIO_PORTC :
		GPIOB->ODR = (A_u16Val) & (0x0000FFFF) ;
		break;
	}
}

u8 MGPIO_u8GetPinVal(u8 A_u8PortId ,PinNo A_PinNo)
{
	u8 L_u8Val=0;
	switch(A_u8PortId)
	{
	case GPIO_PORTA :
		L_u8Val=GET_BIT(GPIOA->IDR,A_PinNo);
		break;
	case GPIO_PORTB :
		L_u8Val=GET_BIT(GPIOB->IDR,A_PinNo);
		break;
	case GPIO_PORTC :
		L_u8Val=GET_BIT(GPIOC->IDR,A_PinNo);
		break;
	}
	return L_u8Val;
}
u16 MGPIO_u16GetPortVal(u8 A_u8PortId)
{
	u16 L_u8Val=0;
	switch(A_u8PortId)
	{
	case GPIO_PORTA :
		L_u8Val= (GPIOA->IDR) & (0x0000FFFF) ;
		break;
	case GPIO_PORTB :
		L_u8Val= (GPIOB->IDR) & (0x0000FFFF) ;
		break;
	case GPIO_PORTC :
		L_u8Val= (GPIOC->IDR) & (0x0000FFFF) ;
		break;
	}
	return L_u8Val;
}




/*init*/
void MGPIO_vInit(MGPIO_Config_t* A_xGpioConfig)
{
	switch(A_xGpioConfig->mode)
	{
	case GPIO_MODE_OUTPUT :
		MGPIO_vSetPinOutput(A_xGpioConfig->port ,A_xGpioConfig->pin,A_xGpioConfig->speed,A_xGpioConfig->out_type);
		break;
	case GPIO_MODE_INPUT :
		MGPIO_vSetPinInput(A_xGpioConfig->port ,A_xGpioConfig->pin,A_xGpioConfig->input_pull);
		break;
	case GPIO_MODE_ALTFUNC:
		MGPIO_vSetPinAltFuncLow(A_xGpioConfig->port ,A_xGpioConfig->pin,A_xGpioConfig->alt_func);
		break;
	case GPIO_MODE_ANALOG :
		MGPIO_vSetPinAnalog(A_xGpioConfig->port ,A_xGpioConfig->pin);
		break;
	}
}



/*for 7-Seg*/
/*extra func*/
void MGPIO_vSetPinOutPart(u8 A_u8PortId ,PinNo A_FirstPinNo,PinNo A_LastPinNo,u8 A_u8OutSpeed ,u8 A_u8OutType)
{
	u8 L_u8Iter=A_FirstPinNo;
	if(A_LastPinNo >=A_FirstPinNo)
	{
		if(A_FirstPinNo <=15 && A_LastPinNo <=15 && A_u8OutSpeed<=3 && A_u8OutType<=1)
		{
			switch(A_u8PortId)
			{
			case GPIO_PORTA :
				for(L_u8Iter=A_FirstPinNo ;L_u8Iter<=A_LastPinNo;L_u8Iter++)
				{
					GPIOA->MODER &= ~((0b11)<<(L_u8Iter*2));
					GPIOA->MODER |=((GPIO_MODE_OUTPUT)<<(L_u8Iter*2));

					GPIOA->OSPEEDR &= ~((0b11)<<(L_u8Iter*2));
					GPIOA->OSPEEDR |=((A_u8OutSpeed)<<(L_u8Iter*2));

					CLR_BIT(GPIOA->OTYPER,L_u8Iter);
					GPIOA->OTYPER |=((A_u8OutType)<<(L_u8Iter));
				}
				break;
			case GPIO_PORTB :
				for(L_u8Iter=A_FirstPinNo ;L_u8Iter<=A_LastPinNo;L_u8Iter++)
				{
					GPIOB->MODER &= ~((0b11)<<(L_u8Iter*2));
					GPIOB->MODER |=((GPIO_MODE_OUTPUT)<<(L_u8Iter*2));

					GPIOB->OSPEEDR &= ~((0b11)<<(L_u8Iter*2));
					GPIOB->OSPEEDR |=((A_u8OutSpeed)<<(L_u8Iter*2));

					CLR_BIT(GPIOB->OTYPER,L_u8Iter);
					GPIOB->OTYPER |=((A_u8OutType)<<(L_u8Iter));
				}
				break;
			case GPIO_PORTC :
				for(L_u8Iter=A_FirstPinNo ;L_u8Iter<=A_LastPinNo;L_u8Iter++)
				{
					GPIOC->MODER &= ~((0b11)<<(L_u8Iter*2));
					GPIOC->MODER |=((GPIO_MODE_OUTPUT)<<(L_u8Iter*2));

					GPIOC->OSPEEDR &= ~((0b11)<<(L_u8Iter*2));
					GPIOC->OSPEEDR |=((A_u8OutSpeed)<<(L_u8Iter*2));

					CLR_BIT(GPIOC->OTYPER,L_u8Iter);
					GPIOC->OTYPER |=((A_u8OutType)<<(L_u8Iter));
				}

				break;
			}
		}
	}
}
void MGPIO_vTogglePin(u8 A_u8PortId ,PinNo A_PinNo)
{
	if(A_PinNo<=15)
	{

			switch(A_u8PortId)
			{
			case GPIO_PORTA :
				TOG_BIT(GPIOA->ODR,A_PinNo);
				break;
			case GPIO_PORTB :
				TOG_BIT(GPIOB->ODR,A_PinNo);
				break;
			case GPIO_PORTC :
				TOG_BIT(GPIOC->ODR,A_PinNo);
				break;
			}

	}
}


