/*********************************************************/
/*      Author  :   Esraa Mohammed Aly                   */
/*      SWC     :   Speaker                              */
/*      Date    :   30/10/2023                           */
/*      version :   1.00                                 */
/*********************************************************/

/*
 * Includes Libraies
 */

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_int.h"



/*
 *GPIO CONFIG OF DataSerial PIN
 */

MGPIO_Config_t DataSerial ={
		.mode = GPIO_MODE_OUTPUT,
		.port = GPIO_PORTB,
		.pin  = GPIO_PIN0,
		.speed = GPIO_OUTSPEED_LOW,
		.out_type = GPIO_PUSH_PULL,

};



/*
 *GPIO CONFIG OF Shift PIN
 */
MGPIO_Config_t Shift ={
		.mode = GPIO_MODE_OUTPUT,
		.port = GPIO_PORTB,
		.pin  = GPIO_PIN1,
		.speed = GPIO_OUTSPEED_LOW,
		.out_type = GPIO_PUSH_PULL,

};


/*
 *GPIO CONFIG OF Latch PIN
 */
MGPIO_Config_t Latch ={
		.mode = GPIO_MODE_OUTPUT,
		.port = GPIO_PORTB,
		.pin  = GPIO_PIN2,
		.speed = GPIO_OUTSPEED_LOW,
		.out_type = GPIO_PUSH_PULL,

};
