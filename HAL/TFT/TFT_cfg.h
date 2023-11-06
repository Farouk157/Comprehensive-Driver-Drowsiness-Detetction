/*********************************************************/
/*      Author  :   Esraa Mohammed Aly                   */
/*      SWC     :   TFT                                  */
/*      Date    :   30/10/2023                           */
/*      version :   1.00                                 */
/*********************************************************/


/*
 * Includes Libraies
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_int.h"


/*
 *GPIO CONFIG OF RESET PIN
 */

MGPIO_Config_t   RESET_PIN  ={
		.mode = GPIO_MODE_OUTPUT,
		.port = GPIO_PORTA,
		.pin=GPIO_PIN0,
		.speed = GPIO_OUTSPEED_HIGH,
		.out_type = GPIO_PUSH_PULL
};

/*
 *GPIO CONFIG OF A0 PIN
 */

MGPIO_Config_t   A0_PIN  ={
		.mode = GPIO_MODE_OUTPUT,
		.port = GPIO_PORTA,
		.pin=GPIO_PIN1,
		.speed = GPIO_OUTSPEED_HIGH,
		.out_type = GPIO_PUSH_PULL
};


