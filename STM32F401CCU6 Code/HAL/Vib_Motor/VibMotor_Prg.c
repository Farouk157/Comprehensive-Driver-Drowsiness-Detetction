/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   Vibration Motor                   */
/*      Date    :   25/10/2023                        */
/*      version :       1.00                          */
/******************************************************/

#ifndef HAL_VIB_MOTOR_VIBMOTOR_PROG_C_
#define HAL_VIB_MOTOR_VIBMOTOR_PROG_C_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/GPIO/GPIO_int.h"
#include "VibMotor_Int.h"

extern GPIO_cfg_t Vibration_Disk;

/*
 * @brief: this function used to initialize the Vibration Motor
 * @ret  : Nothing 
 * @param: Nothing
*/
void VibMotor_voidInit(void)
{
	MGPIO_vInit(&Vibration_Disk);
}

/*
 * @brief: this function used to turn on the Vibration Motor
 * @ret  : Nothing 
 * @param: Nothing
*/
void VibMotor_voidTurnOn(void)
{
	MGPIO_vSetPinValue(Vibration_Disk.port, Vibration_Disk.pin, GPIO_HIGH);
}

/*
 * @brief: this function used to turn off the Vibration Motor
 * @ret  : Nothing 
 * @param: Nothing
*/
void VibMotor_voidTurnOff(void)
{
	MGPIO_vSetPinValue(Vibration_Disk.port, Vibration_Disk.pin, GPIO_LOW);
}

#endif /* HAL_VIB_MOTOR_VIBMOTOR_PROG_C_ */
