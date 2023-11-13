/*
 *  SWC     : ADC_int.h
 *  Author  : Amr Sayed
 *  Date    : 6/10/2023
 *  version : 1.00
 */





#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_

typedef enum {
	ADC_CHANNAL_0,
	ADC_CHANNAL_1,
	ADC_CHANNAL_2,
	ADC_CHANNAL_3,
	ADC_CHANNAL_4,
	ADC_CHANNAL_5,
	ADC_CHANNAL_6,
	ADC_CHANNAL_7,
	ADC_CHANNAL_8,
	ADC_CHANNAL_9
}CHANNEL_No;
typedef enum{
	ADC_SAMPLE_3_CYCLES,
	ADC_SAMPLE_15_CYCLES,
	ADC_SAMPLE_28_CYCLES,
	ADC_SAMPLE_56_CYCLES,
	ADC_SAMPLE_84_CYCLES,
	ADC_SAMPLE_112_CYCLES,
	ADC_SAMPLE_144_CYCLES,
	ADC_SAMPLE_480_CYCLES,
}ADC_SAMPLE;

/*
*@breif:Initialize the ADC through
*@param_: nothing (void)
*@ret:    nothing (void)
*/
void MADC_vInit(void);


/*
*@breif:Get the Reading from ADC *pooling*
*@param_1:to select ADC channel :[from: ADC_CHANNAL_0 - to: ADC_CHANNAL_9]
*@ret: digital value (u16) [from 0 to 4096]
*/
u16 MADC_u16AnalogRead(CHANNEL_No A_xChannelNum);





/*interrupt*/
void MADC_vStartConversion(CHANNEL_No A_xChannelNo);
u16  MADC_u16ReadData(void);
void MADC_vSetCallback(void (*A_fptr) (void));
void MADC_vConfigChannel (CHANNEL_No A_u8ChannelNum , ADC_SAMPLE A_xSampleTime);


#endif /* MCAL_ADC_ADC_INT_H_ */
