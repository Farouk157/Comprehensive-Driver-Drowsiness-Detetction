/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   Push Button                       */
/*      Date    :   25/10/2023                        */
/*      version :       1.00                          */
/******************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/GPIO/GPIO_int.h"
#include "PushButton_Int.h"

extern GPIO_cfg_t Button;

/*
 * @brief: this function used to initialize the Push Button
 * @ret  : Nothing 
 * @param: Nothing
*/
void PushButton_voidInit(void)
{
	MGPIO_vInit(&Button);
	MGPIO_vSetPinValue(Button.port, Button.pin, GPIO_HIGH);
}


