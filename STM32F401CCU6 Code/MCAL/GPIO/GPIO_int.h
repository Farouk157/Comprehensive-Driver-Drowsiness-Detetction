/****************************************************************************************
 /*   Author: Abdalah Beshary
 /*   SWC   : GPIO_int.h
 /*	  Date  : 6/10/2023
 /*  Version: 1
 **************************************************************************************/

#ifndef MCAL_GPIO_GPIO_INT_H_
#define MCAL_GPIO_GPIO_INT_H_

typedef struct{
	u8 mode;
	u8 out_type;
	u8 input_type;
	u8 speed;
	u8 A_u8Altfun ;
	u8 port ;
	u8 pin ;
}GPIO_cfg_t;

//////////////////////////////////
#define GPIO_PIN0    0
#define GPIO_PIN1    1
#define GPIO_PIN2    2 // etc
#define GPIO_PIN3    3
#define GPIO_PIN4    4
#define GPIO_PIN5    5
#define GPIO_PIN6    6
#define GPIO_PIN7    7
#define GPIO_PIN8    8
#define GPIO_PIN9    9
#define GPIO_PIN10   10
#define GPIO_PIN11   11
#define GPIO_PIN12   12
#define GPIO_PIN13   13
#define GPIO_PIN14   14
#define GPIO_PIN15   15

/*PORT NAME*/
#define GPIO_PORTA   1
#define GPIO_PORTB   2
#define GPIO_PORTC   3
/*MODES*/
#define GPIO_MODE_INPUT    0b00
#define GPIO_MODE_OUTPUT   0b01
#define GPIO_MODE_ALTFUN   0b10
#define GPIO_MODE_ANALOG   0b11

/*OUT type*/
#define GPIO_PUSH_PULL				0
#define GPIO_OUTTYPE_OPENDRAIN      1
#define GPIO_OUTPUTTYPE_PUSHPULL    2

/*OUT SPEED*/
#define GPIO_OUTSPEED_LOW    0b00
#define GPIO_OUTSPEED_MEDIUM 0b01
#define GPIO_OUTSPEED_HIGH   0b10

/*INPUT TYPE*/
#define GPIO_INPUTTYPE_NPU   0b00
#define GPIO_INPUTTYPE_PU    0b01
#define GPIO_INPUTTYPE_PD    0b10

#define GPIO_HIGH    1
#define GPIO_LOW     0

#define GPIO_AF0    0
#define GPIO_AF1    1
///////////////////////////////////////
/*Mode*/

/**
 * @brief   intinaliztion of pin   .
 * @param   GPIO_cfg_t
 * @retval  none
 */
void MGPIO_vInit(GPIO_cfg_t *A_ptr);

/**
 * @brief   this function is used to selection of mode of pin.
 * @param   A_u8PortId ,A_u8PinNo,A_u8Mode
 * @retval  none
 */

void MGPIO_vSetPinMode(u8 A_u8PortId,
		u8 A_u8PinNo,
		u8 A_u8Mode );

/**
 * @brief   this function is used to selection of output type of pin.
 * @param   A_u8PortId ,A_u8PinNo,A_u8OutType
 * @retval  none
 */
void MGPIO_vSetPinOutputType(u8 A_u8PortId,
		u8 A_u8PinNo,
		u8 A_u8OutType );

/**
 * @brief   this function is used to selection speed  of pin.
 * @param   A_u8PortId ,A_u8PinNo,A_u8OutSpeed
 * @retval  none
 */

void MGPIO_vSetPinOutputSpeed(u8 A_u8PortId,
		u8 A_u8PinNo,
		u8 A_u8OutSpeed );

/**
 * @brief   this function is used to choicr pulltype.
 * @param   A_u8PortId ,A_u8PinNo,A_u8PullType
 * @retval  none
 */

void MGPIO_vSetPinInputPull(u8 A_u8PortId,
        u8 A_u8PinNo,
        u8 A_u8PullType );


/**
 * @brief   this used to get value of pin   .
 * @param   A_u8PortId,A_u8PinNo
 * @retval  Value of pin
 */

u8 MGPIO_u8GetPinValue(u8 A_u8PortId,
        u8 A_u8PinNo);

/**
 * @brief   this used to set pin value by normal way .
 * @param   A_u8PortId , A_u8PinNo,A_u8PinVal
 * @retval  none
 */
void MGPIO_vSetPinValue(u8 A_u8PortId,
        u8 A_u8PinNo,
        u8 A_u8PinVal );

/**
 * @brief   this used to set pin value by atomic(fast) way one clock cycle.
 * @param   A_u8PortId , A_u8PinNo,A_u8PinVal
 * @retval  none
 */
void MGPIO_vSetPinValFast(u8 A_u8PortId,
        u8 A_u8PinNo,
        u8 A_u8PinVal );

/**
 * @brief   this used to select the pin mode  is working by mode different GPIO like Uart  SPI else.
 * @param   A_u8PortId , A_u8PinNo,A_u8Altfun
 * @retval  none
 */
void MGPIO_vSetAlternativeFunction(u8 A_u8PortId,
        u8 A_u8PinNo,
        u8 A_u8Altfun );




#endif /* MCAL_GPIO_GPIO_INT_H_ */
