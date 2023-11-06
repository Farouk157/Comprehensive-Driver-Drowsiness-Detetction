/*
 *  SWC     : BPM_program.c
 *  Author  : Amr Sayed
 *  Date    : 20/10/2023
 *  version : 1.00
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../MCAL/ADC/ADC_int.h"
#include "../../MCAL/SYSTICK/STK_int.h"





/*
*@breif:Initialize the BPM through make configuration for BPM pin (must Compatible with ADC channel)
*@param_: nothing (void)
*@ret:    nothing (void)
*/
void BPM_vInit(void)
{
	MGPIO_Config_t BPM = {
			.port = GPIO_PORTA,
			.pin  = GPIO_PIN1,
			.mode = GPIO_MODE_ANALOG,
			.input_pull = GPIO_NO_PULL_UP_OR_DOWN,
			.speed = GPIO_OUTSPEED_LOW
	};
	MGPIO_vInit(&BPM) ;
}


/*
*@breif:Get the values from ADC then convert them to the number of heart beats per minute
*@param_1:to select ADC channel (must Compatible with BPM pin) :[from: ADC_CHANNAL_0 - to: ADC_CHANNAL_9]
*@ret: number of heart beats per minute (u8)
*/
u8 BPM_u8getreading (u8 ADC_u8channel )
{
	u16 reading =0  	;
	u16 time	=0	 	;
	u8  bpm		=0 		;
//	u8 returned	=0 		;


	//calculate the time of 2 pulses

	//1st pulse
	//1-Wait at the first bottom
	while (reading>2600)
	{
		reading = MADC_u16AnalogRead(ADC_u8channel);
	}
	//2-reach to peak
	while (reading<3100)
	{
		MSTK_vSetBusyWait(20000);
		time +=	20	;
		reading = MADC_u16AnalogRead(ADC_u8channel);
	}
	//3-reach to bottom
	while (reading>2600)
	{
		MSTK_vSetBusyWait(20000);
		time +=	20	;
		reading = MADC_u16AnalogRead(ADC_u8channel);
	}

	//2nd pulse
	//1-reach to peak
	while (reading<3100)
	{
		MSTK_vSetBusyWait(20000);
		time +=	20	;
		reading = MADC_u16AnalogRead(ADC_u8channel);
	}
	//3-reach to bottom
	while (reading>2600)
	{
		MSTK_vSetBusyWait(20000);
		time +=	20	;
		reading = MADC_u16AnalogRead(ADC_u8channel);
	}
	//number of heart beats per minute = 60 000  / time of one pulse
	//number of heart beats per minute = 120 000  / time of 2 pulse

	bpm = 120000 / time		;
//	returned = bpm	;

//	time	=	0	;
//	bpm		=	0	;
//	reading =   0	;

	return bpm	;
}



