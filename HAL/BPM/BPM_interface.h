/*
 *  SWC     : BPM_int.h
 *  Author  : Amr Sayed
 *  Date    : 20/10/2023
 *  version : 1.00
 */


#ifndef HAL_BPM_BPM_INTERFACE_H_
#define HAL_BPM_BPM_INTERFACE_H_

/*
*@breif:Initialize the BPM through make configuration for BPM pin (must Compatible with ADC channel)
*@param_: nothing (void)
*@ret:    nothing (void)
*/
void BPM_vInit(void);

/*
*@breif:Get the values from ADC then convert them to the number of heart beats per minute
*@param_1:to select ADC channel (must Compatible with BPM pin) :[from: ADC_CHANNAL_0 - to: ADC_CHANNAL_9]
*@ret: number of heart beats per minute (u8)
*/
u8 BPM_u8getreading (u8 ADC_u8channel )



#endif /* HAL_BPM_BPM_INTERFACE_H_ */
