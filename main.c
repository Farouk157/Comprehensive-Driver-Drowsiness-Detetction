

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/RCC/RCC_int.h"
#include "MCAL/GPIO/GPIO_int.h"
#include "MCAL/NVIC/NVIC_int.h"
#include "MCAL/SYSTICK/STK_int.h"
#include "MCAL/UART/UART_int.h"

extern USART_InitType uart1_cfg;

int main(void)
{
	u8 Ret_u8Val = 0;
	MRCC_vInit();
	MRCC_vEnableClock(RCC_AHB1, RCC_EN_GPIOA);
	MRCC_vEnableClock(RCC_APB2, RCC_EN_UART1);

	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN3,GPIO_MODE_OUTPUT);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN3,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN3,GPIO_OUTSPEED_LOW);

	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN9,GPIO_MODE_ALTFUN);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN9,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN9,GPIO_OUTSPEED_LOW);
	MGPIO_vSetAlternativeFunction(GPIO_PORTA,GPIO_PIN9,7);
	///////////////////////////////////////////////////////////////////////
	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN10,GPIO_MODE_ALTFUN);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN10,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN10,GPIO_OUTSPEED_LOW);
	MGPIO_vSetAlternativeFunction(GPIO_PORTA,GPIO_PIN10,7);

	MUSART_vInit(&uart1_cfg, USART1);
	MUSART_vEnable(USART1);
	MSTK_vInit();

	while(1)
	{
		Ret_u8Val = MUSART_u8ReceiveByteSynchBlocking(USART1);

		if(Ret_u8Val == 'D')
		{
			MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN3, GPIO_HIGH);
		}
		else
		{
			MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN3, GPIO_LOW);
		}
	}

	return 0;
}
