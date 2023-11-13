/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   Buzzer                            */
/*      Date    :   25/10/2023                        */
/*      version :       1.00                          */
/******************************************************/


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/GPIO/GPIO_int.h"
#include "Buzzer_Int.h"

extern GPIO_cfg_t buzzer;

/*
 * @brief: this function used to initialize the Buzzer
 * @ret  : Nothing 
 * @param: Nothing
*/
void Buzzer_voidInit(void)
{
	MGPIO_vInit(&buzzer);
}

/*
 * @brief: this function used to turn on the Buzzer
 * @ret  : Nothing 
 * @param: Nothing
*/
void Buzzer_voidTurnOn(void)
{
	MGPIO_vSetPinValue(buzzer.port, buzzer.pin, GPIO_HIGH);
}

/*
 * @brief: this function used to turn off the Buzzer
 * @ret  : Nothing 
 * @param: Nothing
*/
void Buzzer_voidTurnOff(void)
{
	MGPIO_vSetPinValue(buzzer.port, buzzer.pin, GPIO_LOW);
}

