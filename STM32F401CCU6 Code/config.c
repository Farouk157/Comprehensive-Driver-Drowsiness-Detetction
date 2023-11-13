/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   Configurations                    */
/*      Date    :   4/11/2023                         */
/*      version :       1.00                          */
/******************************************************/

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/GPIO/GPIO_int.h"


GPIO_cfg_t Tx_UART_1 = {
		.port = GPIO_PORTB,
		.pin =  GPIO_PIN6,
		.mode = GPIO_MODE_ALTFUN,
		.out_type = GPIO_OUTPUTTYPE_PUSHPULL,
		.speed = GPIO_OUTSPEED_LOW,
		.A_u8Altfun = 7
};
GPIO_cfg_t Rx_UART_1 = {
		.port = GPIO_PORTB,
		.pin =  GPIO_PIN7,
		.mode = GPIO_MODE_ALTFUN,
		.out_type = GPIO_OUTPUTTYPE_PUSHPULL,
		.speed = GPIO_OUTSPEED_LOW,
		.A_u8Altfun = 7
};

GPIO_cfg_t Tx_UART_2 = {
		.port = GPIO_PORTA,
		.pin =  GPIO_PIN2,
		.mode = GPIO_MODE_ALTFUN,
		.out_type = GPIO_OUTPUTTYPE_PUSHPULL,
		.speed = GPIO_OUTSPEED_LOW,
		.A_u8Altfun = 7
};

GPIO_cfg_t Rx_UART_2 = {
		.port = GPIO_PORTA,
		.pin =  GPIO_PIN3,
		.mode = GPIO_MODE_ALTFUN,
		.out_type = GPIO_OUTPUTTYPE_PUSHPULL,
		.speed = GPIO_OUTSPEED_LOW,
		.A_u8Altfun = 7
};

GPIO_cfg_t led_test = {
		.port = GPIO_PORTA,
		.pin =  GPIO_PIN12,
		.mode = GPIO_MODE_OUTPUT,
		.out_type = GPIO_OUTPUTTYPE_PUSHPULL,
		.speed = GPIO_OUTSPEED_LOW,
};


