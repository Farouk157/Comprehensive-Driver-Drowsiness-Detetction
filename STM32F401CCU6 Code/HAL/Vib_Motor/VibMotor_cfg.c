/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   Vibration Motor                   */
/*      Date    :   25/10/2023                        */
/*      version :       1.00                          */
/******************************************************/


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/GPIO/GPIO_int.h"

/*
	this is the structure that contains the pin data of the Vibration Motor
*/
GPIO_cfg_t Vibration_Disk= {
		.port = GPIO_PORTA,
		.pin =  GPIO_PIN8,
		.mode = GPIO_MODE_OUTPUT,
		.out_type = GPIO_OUTPUTTYPE_PUSHPULL,
		.speed = GPIO_OUTSPEED_LOW,
};
