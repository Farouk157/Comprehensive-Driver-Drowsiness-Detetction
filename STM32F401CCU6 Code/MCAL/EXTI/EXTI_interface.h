/*
 * EXTI_interface.h
 *
 *  Created on: Aug 30, 2023
 *      Author: First
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

/*
	Options: 
		1- Enable 
		2- Disable 
*/
#define ENABLE		1
#define DISABLE		0

/*
    Triggering Mechanism Options: 
		1- EXTI on Rising Edge
		2- EXTI on Falling Edge
		3- EXTI on change mode (for any change happens)
*/
#define EXTI_RISING		1
#define EXTI_FALLING	2
#define EXTI_ON_CHANGE	3


/*
	Number of Lines Available with EXTI
*/
#define EXTI_LINE_0			0
#define EXTI_LINE_1			1
#define EXTI_LINE_2			2
#define EXTI_LINE_3			3
#define EXTI_LINE_4			4
#define EXTI_LINE_5			5
#define EXTI_LINE_6			6
#define EXTI_LINE_7			7
#define EXTI_LINE_8			8
#define EXTI_LINE_9			9
#define EXTI_LINE_10		10
#define EXTI_LINE_11		11
#define EXTI_LINE_12		12
#define EXTI_LINE_13		13
#define EXTI_LINE_14		14
#define EXTI_LINE_15		15

/*
	Ports that Available with EXTI
*/
#define	EXTI_PORTA			0000
#define	EXTI_PORTB			0001
#define	EXTI_PORTC			0010

/*
 * @brief: This function is used to initialize the External Interrupt
 * @ret:   Nothing 
 * @param: No Parameters 
 */
void EXTI_voidInit		(void);

/*
 * @brief: This function is used to Enable EXTI for specific line and choosing triggering methodology 
 * @ret:   Nothing 
 * @param1: this is the number of line you want to activate and use
 * @param2: this is the Triggering Edge 
			Options:
			        - Falling Edge
					- Raising Edge
 */
void EXTI_voidEnableLine	(u8 Copy_u8Line , u8 Copy_u8TriggerEdge	);

/*
 * @brief:  This function is used to Disable EXTI for specific line
 * @ret  :  Nothing 
 * @param1: this is the number of line you want to activate and use
 */
void EXTI_voidDisableLine	(u8 Copy_u8Line);

void EXTI_voidSetTrigger	(u8 Copy_u8Line , u8 Copy_u8TriggerEdge	) ;

/*
 * @brief: this used to configure which port and line you want to enable the EXTI on 
 * @ret  : Nothing 
 * @param1:this is the number of line that you want
 * @param2:this is the number of port that you want  
*/
void SYSCFG_voidEXTIPort	(	u8 Copy_u8Line	, u8 Copy_u8PortNo	);

/*
 * @brief: this function is used to get the address of the API to be excuted when Interrupt being fired
 * @ret  : Nothing 
 * @Param: takes the pointer to function you want to execute when the interrupt being fired
*/
void EXTI_vSetCallBack( void( *ptr )(void) );

#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
