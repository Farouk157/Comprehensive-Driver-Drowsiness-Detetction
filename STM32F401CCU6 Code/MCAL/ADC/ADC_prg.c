/*
 *  SWC     : ADC_prg.c
 *  Author  : Amr Sayed
 *  Date    : 6/10/2023
 *  version : 1.00
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_int.h"
#include "ADC_int.h"
#include "ADC_cfg.h"
#include "ADC_prv.h"

#define  delay    5000000      //1sec
void (*ADC_Callback) (void);
//2 channels  ???????????
//0: Right alignment
//Interrupt disable

//ENABLE ADC
//Prescaler    PCLK2 divided by 2  			//2
//12 bit res						//3



/*
*@breif:Initialize the ADC through
*@param_: nothing (void)
*@ret:	  nothing (void)
*/
void MADC_vInit(void)
{
	/*2-Set ADC resolution */
	ADC1->CR1 &= ~((u32)(0b11)<<ADC_CR1_RES_BIT0) ;
	ADC1->CR1 |= ((u32)(ADC_RESOLUTION)<<ADC_CR1_RES_BIT0) ;
	// page 230  Bits 15:13
	/* Set the number of channels to be converted in discontinuous mode */
	//		ADC1->CR1 &= ~(8 << ADC_CR1_DISCNUM_BIT0) ;
	/////////////////////////////////////
#if NUMBER_OF_CHANNEL_TO_BE_CONVERTED >0 && NUMBER_OF_CHANNEL_TO_BE_CONVERTED<9
	ADC1->CR1 &= ~((u32)(CLEAR_3_BIT)<<ADC_CR1_DISCNUM_BIT0) ;
	ADC1->CR1 |= ((u32)(NUMBER_OF_CHANNEL_TO_BE_CONVERTED-1)<<ADC_CR1_DISCNUM_BIT0) ;
#else
#error "invalid choice of NUMBER_OF_CHANNEL_TO_BE_CONVERTED"
#endif
	///////////////////////////////	/////
	/*3-Select Prescaler Bits*/
#if ADC_PRESCALLER >=0 && ADC_PRESCALLER<=3
	ADC1->CCR &= ~((0b11) << ADC_CCR_ADCPRE_BIT0 ) ;
	ADC1->CCR |=  (ADC_PRESCALLER << ADC_CCR_ADCPRE_BIT0 ) ;
#else
	ADC1->CCR &= ~((0b11) << ADC_CCR_ADCPRE_BIT0 ) ;
	ADC1->CCR |=  (ADC_PS_2 << ADC_CCR_ADCPRE_BIT0 ) ;
#endif

	/*4-Data alignment (right) */
	CLR_BIT (ADC1->CR2 , ADC_CR2_ALIGN_BIT) ;
	//External Trigger detection disabled
	CLR_BIT(ADC1->CR2,ADC_CR2_EXTEN_BIT0);
	CLR_BIT(ADC1->CR2,ADC_CR2_EXTEN_BIT1);
	///////////////////////////////////
	/*5-Interrupt Enable /disable*/
#if  ADC_INTERRUPT_ENABLE== ENABLE
	SET_BIT(ADC1->CR1,ADC_CR1_EOCIE_BIT);
#else
	CLR_BIT(ADC1->CR1,ADC_CR1_EOCIE_BIT);
#endif
	////////////////////////////////////////
	/* choice the number of Discontinuous mode channel count */
#if  (NUMBER_OF_CHANNEL_TO_BE_CONVERTED > 0 ) && (NUMBER_OF_CHANNEL_TO_BE_CONVERTED < 9)
	ADC1->CR1 &= ~((0x7U) << ADC_CR1_DISCNUM_BIT0);
	ADC1->CR1 |= ((u32)(NUMBER_OF_CHANNEL_TO_BE_CONVERTED-1) << ADC_CR1_DISCNUM_BIT0);
#endif

	////////////////////////////////////
#if DISCONTINUOUS_MODE_ENABLE == ENABLE
	SET_BIT(ADC1->CR1,ADC_CR1_DISCEN_BIT);

#else
	CLR_BIT(ADC1->CR1, ADC_CR1_DISCEN_BIT);
#endif
	/////////////////////////////////////
#if ADC_CONTINUOUS_CONVERSION_MODE==ADC_CONTINUOUS_CONVERSION
	SET_BIT(ADC1->CR2,ADC_CR2_CONT_BIT);
#else
	CLR_BIT(ADC1->CR2,ADC_CR2_CONT_BIT);
#endif
	/* Enable the ADC peripheral */
	SET_BIT(ADC1->CR2 , ADC_CR2_ADON_BIT) ; // A/D Converter ON
}



void MADC_vConfigChannel (CHANNEL_No A_xChannelNum , ADC_SAMPLE A_xSampleTime)
{
	if(A_xChannelNum <9 && A_xSampleTime<8 )
	{
		if(A_xChannelNum < 8)
		{
			MGPIO_vSetPinAnalog(GPIO_PORTA,A_xChannelNum);
		}
		else
		{
			MGPIO_vSetPinAnalog(GPIO_PORTB,A_xChannelNum);
		}
		/* Clear the old sample time */
		ADC1 ->SMPR2 &= ~(0x7U << (A_xChannelNum * 3U)) ;//0b111
		ADC1 ->SMPR2 &= ~(A_xSampleTime << (A_xChannelNum * 3U)) ;

		//	Bits 23:20 L[3:0]: Regular channel sequence length
		//	These bits are written by software to define the total number of conversions in the regular
		//	channel conversion sequence.
		//	0000: 1 conversion
		//	0001: 2 conversions
		//	...
		//	1111: 16 conversions
//		ADC1->SQR1 &= ~(REGULAR_CHANNEL_SEQUENCE_LENGTH << ADC_SQR1_L_BIT0);

		/*1- Select Channel*/
		/* set regular sequence for selected channel */
		ADC1 ->SQR3 = A_xChannelNum ;
	}
}


/*
*@breif:Get the Reading from ADC *pooling*
*@param_1:to select ADC channel :[from: ADC_CHANNAL_0 - to: ADC_CHANNAL_9]
*@ret: digital value (u16) [from 0 to 4096]
*/
/*without interrupt _ using polling or discontinuous */
u16 MADC_u16AnalogRead(CHANNEL_No A_xChannelNum)
{
	/*1-Start conversion & select channel*/
	MADC_vStartConversion(A_xChannelNum);
	/*2-Poll on Flag */
	while(GET_BIT(ADC1->SR,ADC_SR_EOC_BIT)==0 );
	/*3-Clear Flag */
	CLR_BIT(ADC1->SR,ADC_SR_EOC_BIT);  // not need if read DR The flag will clear
	/*4- return ADC Data*/
	return ADC1->DR ;//now  EOC bit is cleared
}









/*interrupt*/
//we need [init(interrupt) + StartConversion + ReadData (in APP func) ]



/*
*@breif:to Start the Conversion *interrupt*
*@param_1:to select ADC channel :[from: ADC_CHANNAL_0 - to: ADC_CHANNAL_9]
*@ret: digital value (u16) [from 0 to 4096]
*/
void MADC_vStartConversion(CHANNEL_No A_xChannelNum)
{
	/*1- Select Channel*/
	ADC1 ->SQR3 = A_xChannelNum ;
//	/* delay for ADC stabilization time  */
//	ARM_DELAY(48);
	/*2-Start conversion for regular group*/
	SET_BIT(ADC1->CR2,ADC_CR2_SWSTART_BIT);

}



/*
*@breif:Get the Reading from ADC *interrupt* (we will use this func in the func that will be executed when firing interrupt  )
*@param_1:nothing (void)
*@ret: digital value (u16) [from 0 to 4096]
*/
u16 MADC_u16ReadData(void)
{
	/*return ADC Data*/
	return ADC1->DR ;
}


void MADC_vSetCallback(void (*A_fptr) (void))
{
	ADC_Callback = A_fptr ;
}

/* IRQHandler for ADC */
void ADC_IRQHandler(void)
{
	if(ADC_Callback != NULL)
	{
		ADC_Callback();
		/* Clear Regular channel start flag */
		CLR_BIT(ADC1->SR ,ADC_SR_STRT_BIT) ;

		/* Clear Regular channel end of conversion */
		CLR_BIT(ADC1->SR , ADC_SR_EOC_BIT) ;
	}
}

//#if ADC_RESOLUTION == ADC_RES_10_BIT  //01
//	SET_BIT (ADC1->CR1 , ADC_CR1_RES_BIT0) ;
//	CLR_BIT (ADC1->CR1 , ADC_CR1_RES_BIT1) ;
//#elif ADC_RESOLUTION == ADC_RES_9_BIT   //10
//	CLR_BIT (ADC1->CR1 , ADC_CR1_RES_BIT0) ;
//	SET_BIT (ADC1->CR1 , ADC_CR1_RES_BIT1) ;
//#elif ADC_RESOLUTION == ADC_RES_6_BIT   //11
//	SET_BIT (ADC1->CR1 , ADC_CR1_RES_BIT0) ;
//	SET_BIT (ADC1->CR1 , ADC_CR1_RES_BIT1) ;
//#else  // default
//	CLR_BIT (ADC1->CR1 , ADC_CR1_RES_BIT0) ;//24
//	CLR_BIT (ADC1->CR1 , ADC_CR1_RES_BIT1) ;//25
//#endif

//#if   ADC0_CHANNAL==ENABLE
//MGPIO_vSetPinAnalog(GPIO_PORTA,GPIO_PIN0);
//#endif
//#if   ADC1_CHANNAL==ENABLE
//MGPIO_vSetPinAnalog(GPIO_PORTA,GPIO_PIN1);
//#endif
//#if   ADC2_CHANNAL==ENABLE
//MGPIO_vSetPinAnalog(GPIO_PORTA,GPIO_PIN2);
//#endif
//#if   ADC3_CHANNAL==ENABLE
//MGPIO_vSetPinAnalog(GPIO_PORTA,GPIO_PIN3);
//#endif
//#if   ADC4_CHANNAL==ENABLE
//MGPIO_vSetPinAnalog(GPIO_PORTA,GPIO_PIN4);
//#endif
//#if   ADC5_CHANNAL==ENABLE
//MGPIO_vSetPinAnalog(GPIO_PORTA,GPIO_PIN5);
//#endif
//#if   ADC6_CHANNAL==ENABLE
//MGPIO_vSetPinAnalog(GPIO_PORTA,GPIO_PIN6);
//#endif
//#if   ADC7_CHANNAL==ENABLE
//MGPIO_vSetPinAnalog(GPIO_PORTA,GPIO_PIN7);
//#endif
//#if   ADC8_CHANNAL==ENABLE
//MGPIO_vSetPinAnalog(GPIO_PORTB,GPIO_PIN0);
//#endif
//#if   ADC9_CHANNAL==ENABLE
//MGPIO_vSetPinAnalog(GPIO_PORTB,GPIO_PIN1);
//#endif
