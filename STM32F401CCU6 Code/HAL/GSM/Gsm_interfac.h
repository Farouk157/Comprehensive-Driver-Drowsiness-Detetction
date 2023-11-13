/****************************************************************************************
 /*   Author: Abdalah Beshary
 /*   SWC   : Gsm_interface.h
 /*	  Date  : 25/10/2023
 /*  Version: 1
 **************************************************************************************/

#ifndef HAL_GSM_INTERFAC_H_
#define HAL_GSM_INTERFAC_H_

/**
 * @brief   this function is used to initaliztion gsm .
 * @param   no argument
 * @retval  none
 */
void GSM_init(void);
/**
 * @brief   this function is used to initaliztion gps .
 * @param   no argument
 * @retval  none
 */
void GPS_init(void);
/**
 * @brief   this function is used to send message with ask help.
 * @param   no argument
 * @retval  none
 */
void SMS(void);
/**
 * @brief   this function is used to send message with location.
 * @param   no argument
 * @retval  none
 */
void Send_SMS(void);
/**
 * @brief   this function is used to make phone call to specific number.
 * @param   no argument
 * @retval  none
 */
void Make_Call(void);

/**
 * @brief   this function is used to extract longitude and altitude from gps.
 * @param   no argument
 * @retval  none
 */
void get_poistion(u8 * position);

/**
 * @brief   this function is used to change from integer to string.
 * @param   value,  str,  digits
 * @retval  none
 */
void intToString(u8 value, u8* str, u8 digits);
/**
 * @brief   this function is used to change from integer to string.
 * @param   value, str, integerDigits,  fractionalDigits
 * @retval  none
 */
void floatToString(f32 value, u8* str, u8 integerDigits, u8 fractionalDigits);

/**
 * @brief   this function is used to conversion from ddmm.mmmmmm unit to degree.
 * @param 	no argument
 * @retval  none
 */

void ddmmtodegree(void);



#endif /* HAL_GSM_INTERFAC_H_ */
