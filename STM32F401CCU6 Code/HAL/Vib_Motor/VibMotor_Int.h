/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   Vibration Motor                   */
/*      Date    :   25/10/2023                        */
/*      version :       1.00                          */
/******************************************************/

#ifndef HAL_VIB_MOTOR_VIBMOTOR_INT_H_
#define HAL_VIB_MOTOR_VIBMOTOR_INT_H_

/*
 * @brief: this function used to initialize the Vibration Motor
 * @ret  : Nothing 
 * @param: Nothing
*/
void VibMotor_voidInit(void);


/*
 * @brief: this function used to turn on the Vibration Motor
 * @ret  : Nothing 
 * @param: Nothing
*/
void VibMotor_voidTurnOn(void);

/*
 * @brief: this function used to turn off the Vibration Motor
 * @ret  : Nothing 
 * @param: Nothing
*/
void VibMotor_voidTurnOff(void);

#endif /* HAL_VIB_MOTOR_VIBMOTOR_INT_H_ */
