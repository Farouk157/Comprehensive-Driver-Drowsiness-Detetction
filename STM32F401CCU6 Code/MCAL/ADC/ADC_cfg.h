/*
 *  SWC     : ADC_cfg.h
 *  Author  : Amr Sayed
 *  Date    : 6/10/2023
 *  version : 1.00
 */




#ifndef MCAL_ADC_ADC_CFG_H_
#define MCAL_ADC_ADC_CFG_H_

/*
 * 00: 12-bit (15 ADCCLK cycles)
   01: 10-bit (13 ADCCLK cycles)
   10: 8-bit  (11 ADCCLK cycles)
   11: 6-bit  (9 ADCCLK cycles)
 * Set Resolution Bit
 * Options        default --> ADC_RES_12_BIT
 * 0 -> ADC_RES_12_BIT
 * 1 -> ADC_RES_10_BIT
 * 2 -> ADC_RES_8_BIT
 * 3 -> ADC_RES_6_BIT
 */
#define ADC_RESOLUTION   ADC_RES_12_BIT

/**set Number of channels to be converted
   **Options
      1->>>>> 1UL
      2->>>>> 2UL
      3->>>>> 3UL
      4->>>>> 4UL
      5->>>>> 5UL
      6->>>>> 6UL
      7->>>>> 7UL
      8->>>>> 8UL
*/
#define NUMBER_OF_CHANNEL_TO_BE_CONVERTED 2UL

/*
 * ENABLE
 * DISABLE
 */
#define  DISCONTINUOUS_MODE_ENABLE   ENABLE
#define  ADC_INTERRUPT_ENABLE        DISABLE
/*
 * Select ADC_CONTINUOUS_CONVERSION_MODE =
 * 1->>>>>>> ADC_SINGLE_CONVERSION
 * 2->>>>>>> ADC_CONTINUOUS_CONVERSION
 */
#define  ADC_CONTINUOUS_CONVERSION_MODE    ADC_SINGLE_CONVERSION
/*
   Options:
   ADC_PRESCALER = ADC_PS_X
   Where X :
               2
               4
               6
               8
 */
#define   ADC_PRESCALLER    ADC_PS_2

#endif /* MCAL_ADC_ADC_CFG_H_ */
//#define  ADC0_CHANNAL     ENABLE
//#define  ADC1_CHANNAL     DISABLE
//#define  ADC2_CHANNAL     DISABLE
//#define  ADC3_CHANNAL     DISABLE
//#define  ADC4_CHANNAL     DISABLE
//#define  ADC5_CHANNAL     DISABLE
//#define  ADC6_CHANNAL     DISABLE
//#define  ADC7_CHANNAL     DISABLE
//


// ADC_SAMPLE_3_CYCLES     0
// ADC_SAMPLE_15_CYCLES    1
// ADC_SAMPLE_28_CYCLES    2
// ADC_SAMPLE_56_CYCLES    3
// ADC_SAMPLE_84_CYCLES    4
// ADC_SAMPLE_112_CYCLES   5
// ADC_SAMPLE_144_CYCLES   6
// ADC_SAMPLE_480_CYCLES   7

//#define A_u8SampleTime ADC_SAMPLE_3_CYCLES
