/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   Push Button                       */
/*      Date    :   25/10/2023                        */
/*      version :       1.00                          */
/******************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/GPIO/GPIO_int.h"



/*
	this is the structure that contains the pin data of the push button
*/

GPIO_cfg_t Button= {
		.port = GPIO_PORTA,
		.pin =  GPIO_PIN0,
		.mode = GPIO_MODE_INPUT,
		.input_type = GPIO_INPUTTYPE_PU,
		.speed = GPIO_OUTSPEED_LOW,
};
