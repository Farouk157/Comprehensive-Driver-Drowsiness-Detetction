/*
 * GPIO_int.h
 *
 *  Created on: Aug 22, 2022
 *      Author: DELL
 */

#ifndef MCAL_GPIO_GPIO_INT_H_
#define MCAL_GPIO_GPIO_INT_H_
typedef struct{
u8 port ;
u8 pin;
u8 mode ;
u8 speed;
u8 out_type;
u8 input_pull ;
u8 alt_func;
u8 first_pin ;
u8 last_pin ;
}MGPIO_Config_t;
typedef enum{
GPIO_PIN0,
GPIO_PIN1,
GPIO_PIN2,
GPIO_PIN3,
GPIO_PIN4,
GPIO_PIN5,
GPIO_PIN6,
GPIO_PIN7,
GPIO_PIN8,
GPIO_PIN9,
GPIO_PIN10,
GPIO_PIN11,
GPIO_PIN12,
GPIO_PIN13,
GPIO_PIN14,
GPIO_PIN15,
}PinNo;

#define 	GPIO_PORTA    'A'
#define 	GPIO_PORTB    'B'
#define 	GPIO_PORTC    'C'

//00: Input (reset state)
//01: General purpose output mode
//10: Alternate function mode
//11: Analog mode
typedef enum{
	GPIO_MODE_INPUT,
	GPIO_MODE_OUTPUT,
	GPIO_MODE_ALTFUNC,
	GPIO_MODE_ANALOG
}GPIO_MODE;
//#define GPIO_MODE_INPUT         0b00
//#define GPIO_MODE_OUTPUT        0b01
//#define GPIO_MODE_ALTFUNC       0b10
//#define GPIO_MODE_ANALOG        0b11

#define GPIO_PUSH_PULL        0
#define GPIO_OPEN_DRAIN       1

#define GPIO_OUTSPEED_LOW        0b00
#define GPIO_OUTSPEED_MEDIUM     0b01
#define GPIO_OUTSPEED_HIGH       0b10
#define GPIO_OUTSPEED_VERYHIGH   0b11

#define GPIO_HIGH     1
#define GPIO_LOW      0

#define  GPIO_NO_PULL_UP_OR_DOWN  0b00
#define  GPIO_PULL_UP  0b01
#define  GPIO_PULL_DOWN  0b10

/**
 * @brief   this function is used to selection of mode of pin.
 * @param   port_Id ,A_PinNo,A_u8OutMode
 * @retval  none
 */
void MGPIO_vSetPinMode(u8 A_u8PortId ,PinNo A_PinNo,GPIO_MODE A_u8Mode);
/**
 * @brief   this function is used to selection of output type of pin.
 * @param   port_Id ,A_PinNo,A_u8OutType
 * @retval  none
 */
void MGPIO_vSetPinOutputType (u8 A_u8PortId ,
		                       PinNo A_PinNo,
							   u8 A_u8OutType);

/**
 * @brief   this function is used to selection speed  of pin.
 * @param   port_Id ,A_PinNo,A_u8OutSpeed
 * @retval  none
 */

void MGPIO_vSetPinOutputSpeed(u8 A_u8PortId ,
                              PinNo A_PinNo,
		                      u8 A_u8OutSpeed);
/*my func*/
/*set pin speed and pull_up or pull down with mean output*/
/**
 * @brief   this pin to identifity state of pin is output.
 * @param   port_Id , pinNumber,A_u8OutType
 * @retval  none
 */
void MGPIO_vSetPinOutput(u8 A_u8PortId ,PinNo A_PinNo,u8 A_u8OutSpeed ,u8 A_u8OutType);
/*set pin speed and pull_up or pull down with mean output*/

/**
 * @brief   this pin to identifity state of pin is input.
 * @param   port_Id , pinNumber,A_u8PupDr
 * @retval  none
 */
void MGPIO_vSetPinInput(u8 A_u8PortId ,PinNo A_PinNo,u8 A_u8PupDr);
/**
 * @brief   this used to select the pin mode  is working by mode different GPIO like Uart  SPI else.
 * @param   port_Id , pinNumber,A_u8AltFunc
 * @retval  none
 */

void MGPIO_vSetPinAltFuncLow(u8 A_u8PortId ,PinNo A_PinNo,u8 A_u8AltFunc);

/**
 * @brief   this used to select analog pin .
 * @param   port_Id , pinNumber,
 * @retval  none
 */
void MGPIO_vSetPinAnalog(u8 A_u8PortId ,PinNo A_PinNo);
/**
 * @brief   this used to set pin value by atomic(fast) way one clock cycle.
 * @param   port_Id , pinNumber,A_u8Val
 * @retval  none
 */
void MGPIO_vSetPinVal_Fast(u8 A_u8PortId ,PinNo A_PinNo,u8 A_u8Val);
/**
 * @brief   this used to set pin value by normal way .
 * @param   port_Id , pinNumber,A_u8Val
 * @retval  none
 */

void MGPIO_vSetPinVal(u8 A_u8PortId ,PinNo A_PinNo,u8 A_u8Val);
/**
 * @brief   this used to set port value by normal way .
 * @param   port_Id,A_u8Val
 * @retval  none
 */
void MGPIO_vSetPortVal(u8 A_u8PortId ,u16 A_u16Val);
/**
 * @brief   this used to get value of pin   .
 * @param   port_Id,pinNumber
 * @retval  none
 */
u8 MGPIO_u8GetPinVal(u8 A_u8PortId ,PinNo A_PinNo);
/**
 * @brief   this used to get value of port   .
 * @param   port_Id
 * @retval  none
 */

u16 MGPIO_u16GetPortVal(u8 A_u8PortId);
/*extra func */
/**
 * @brief   this used to set the modes of number of pins you  select and tell about speed   .
 * @param   port_Id,first pin , last pin , output speed , outputype
 * @retval  none
 */
void MGPIO_vSetPinOutPart(u8 A_u8PortId ,PinNo A_FirstPinNo,PinNo A_LastPinNo,u8 A_u8OutSpeed ,u8 A_u8OutType);
/**
 * @brief   this used to set the values of number of pins   .
 * @param   PortId , A_xFirstPinNo , A_xLastPinNo ,  A_u16Val
 * @retval  none
 */
void MGPIO_vSetOnSomePinVal (u8 A_u8PortId , PinNo A_xFirstPinNo ,PinNo A_xLastPinNo , u16 A_u16Val);

/*init func*/
/**
 * @brief   intinaliztion of pin   .
 * @param   MGPIO_Config_t
 * @retval  none
 */

void MGPIO_vInit(MGPIO_Config_t* A_xconfig);

/**
 * @brief   toggel of pin   .
 * @param   PortId ,PinNo A_PinNo
 * @retval  none
 */


void MGPIO_vTogglePin(u8 A_u8PortId ,PinNo A_PinNo);
/**
 * @brief   intinaliztion of ALtrneat _pin   .
 * @param   MGPIO_Config_t , altrnative_portcol_select
 * @retval  none
 */
void void MGPIO_vInit_Alt_func(MGPIO_Config_t* A_xGpioConfig, u8 altrnative_portcol_select);

#endif /* MCAL_GPIO_GPIO_INT_H_ */
