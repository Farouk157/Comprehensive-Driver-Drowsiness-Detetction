/*
 *  SWC     : ADC_prv.h
 *  Author  : Amr Sayed
 *  Date    : 6/10/2023
 *  version : 1.00
 */





#ifndef MCAL_ADC_ADC_PRV_H_
#define MCAL_ADC_ADC_PRV_H_
/*define base address of ADC1*/
#define ADC1_BASE_ADDRESS  0x40012000

/*define MADC1_MemMap_t*/
typedef struct
{
	volatile u32 SR              ;
	volatile u32 CR1             ;
	volatile u32 CR2             ;
	volatile u32 SMPR1           ;
	volatile u32 SMPR2           ;
	volatile u32 JOFR1           ;
	volatile u32 JOFR2           ;
	volatile u32 JOFR3           ;
	volatile u32 JOFR4           ;
	volatile u32 HTR             ;
	volatile u32 LTR             ;
	volatile u32 SQR1            ;
	volatile u32 SQR2            ;
	volatile u32 SQR3            ;
	volatile u32 JSQR            ;
	volatile u32 JDR1            ;
	volatile u32 JDR2            ;
	volatile u32 JDR3            ;
	volatile u32 JDR4            ;
	volatile u32 DR              ; //4c+4 = 50
	volatile u32 RESERVED [55]    ;/*due to offset address of CCR is relative to ADC1 base address + 0x300*/
	volatile u32 CCR             ;// 04 + 300 = 304
}MADC1_MemMap_t;

/*define ADC1*/
#define ADC1 ((volatile MADC1_MemMap_t *)(ADC1_BASE_ADDRESS))


/*********************************************************/
/* 				SR BITS Mapping 			             */
/*********************************************************/
/* Analog watchdog flag                                  */
#define ADC_SR_AWD_BIT      0
/* Regular channel end of conversion                     */
#define ADC_SR_EOC_BIT      1
/* Injected channel end of conversion                    */
#define ADC_SR_JEOC_BIT     2
/* Injected channel start flag                           */
#define ADC_SR_JSTRT_BIT    3
/* Regular channel start flag                            */
#define ADC_SR_STRT_BIT     4
/* Overrun                                               */
#define ADC_SR_OVR_BIT      5

/*********************************************************/
/* 				CR1 BITS Mapping 			             */
/*********************************************************/
/* Analog watchdog channel select bits                   */
#define ADC_CR1_AWDCH_BIT0      0
#define ADC_CR1_AWDCH_BIT1      1
#define ADC_CR1_AWDCH_BIT2      2
#define ADC_CR1_AWDCH_BIT3      3
#define ADC_CR1_AWDCH_BIT4      4
/* Interrupt enable for EOC                              */
#define ADC_CR1_EOCIE_BIT       5
/* Analog watchdog interrupt enable                      */
#define ADC_CR1_AWDIE_BIT       6
/* Interrupt enable for injected channels                */
#define ADC_CR1_JEOCIE_BIT      7
/* Scan mode                                             */
#define ADC_CR1_SCAN_BIT        8
/* Enable the watchdog on a single channel in scan mode  */
#define ADC_CR1_AWDSGL_BIT      9
/* Automatic injected group conversion                   */
#define ADC_CR1_JAUTO_BIT       10
/* Discontinuous mode on regular channels                */
#define ADC_CR1_DISCEN_BIT      11
/* Discontinuous mode on injected channels               */
#define ADC_CR1_JDISCEN_BIT     12
/* Discontinuous mode channel count                      */
#define ADC_CR1_DISCNUM_BIT0    13
#define ADC_CR1_DISCNUM_BIT1    14
#define ADC_CR1_DISCNUM_BIT2    15
/* Analog watchdog enable on injected channels           */
#define ADC_CR1_JAWDEN_BIT      22
/* Analog watchdog enable on regular channels            */
#define ADC_CR1_AWDEN_BIT       23
/* Resolution                                            */
#define ADC_CR1_RES_BIT0        24
#define ADC_CR1_RES_BIT1        25
/* Overrun interrupt enable                              */
#define ADC_CR1_OVRIE_BIT       26

/*********************************************************/
/* 				CR2 BITS Mapping 			             */
/*********************************************************/
/* A/D Converter ON / OFF                                */
#define ADC_CR2_ADON_BIT      0
/* Continuous conversion                                 */
#define ADC_CR2_CONT_BIT      1
/* Direct memory access mode                             */
#define ADC_CR2_DMA_BIT       8
/* DMA disable selection                                 */
#define ADC_CR2_DDS_BIT       9
/* End of conversion selection                           */
#define ADC_CR2_EOCS_BIT      10
/* Data alignment                                        */
#define ADC_CR2_ALIGN_BIT     11
/* External event select for injected group              */
#define ADC_CR2_JEXTSEL_BIT0  16
#define ADC_CR2_JEXTSEL_BIT1  17
#define ADC_CR2_JEXTSEL_BIT2  18
#define ADC_CR2_JEXTSEL_BIT3  19
/* External trigger enable for injected channels         */
#define ADC_CR2_JEXTEN_BIT0   20
#define ADC_CR2_JEXTEN_BIT1   21
/* Start conversion of injected channels                 */
#define ADC_CR2_JSWSTART_BIT  22
/* External event select for regular group               */
#define ADC_CR2_EXTSEL_BIT0   24
#define ADC_CR2_EXTSEL_BIT1   25
#define ADC_CR2_EXTSEL_BIT2   26
#define ADC_CR2_EXTSEL_BIT3   27
/* External trigger enable for regular channels          */
#define ADC_CR2_EXTEN_BIT0    28
#define ADC_CR2_EXTEN_BIT1    29
/* Start conversion of regular channels                  */
#define ADC_CR2_SWSTART_BIT   30

/*********************************************************/
/* 				CCR BITS Mapping 			             */
/*********************************************************/
/* ADC prescaler                                         */
#define ADC_CCR_ADCPRE_BIT0   16
#define ADC_CCR_ADCPRE_BIT1   17
/* VBAT enable                                           */
#define ADC_CCR_VBATE_BIT     22
/* Temperature sensor and VREFINT enable                 */
#define ADC_CCR_TSVREFE_BIT   23





/***********************************************
 * Define ADC_RESOLUTION
 ***********************************************/

#define ADC_RES_12_BIT   0b00
#define ADC_RES_10_BIT   0b01
#define ADC_RES_8_BIT    0b10
#define ADC_RES_6_BIT    0b11

/***********************************************
 * Define ADC_PRESCALER
 ***********************************************/
#define ADC_PS_2         0b00
#define ADC_PS_4         0b01
#define ADC_PS_6         0b10
#define ADC_PS_8         0b11

#define  CLEAR_3_BIT     0b111

#define ENABLE 1
#define DISABLE 0

#define ADC_SINGLE_CONVERSION       1
#define ADC_CONTINUOUS_CONVERSION   2

#define ARM_DELAY(d)  do{unsigned long int i=d; \
		while(i--){asm("nop");}}while(0)

#endif /* MCAL_ADC_ADC_PRV_H_ */
