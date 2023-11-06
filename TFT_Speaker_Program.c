/*********************************************************/
/*      Author  :   Esraa Mohammed Aly                   */
/*      SWC     :   TFT_Speaker Main Program             */
/*      Date    :   30/10/2023                           */
/*      version :   1.00                                 */
/*********************************************************/


/*
* Include Libraries
*/
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/GPIO/GPIO_int.h"
#include "MCAL/RCC/RCC_int.h"
#include "MCAL/SYSTICK/STK_int.h"

#include "HAL/TFT/TFT_int.h"

/*
* Include Header Files Of Audio and Picture
* Output of TFT and Speaker
*/
#include "Warning_Pic.h"
#include "Warning_Voice.h"



/*
*   Config PORTB For DAC
*/
MGPIO_Config_t Dac_pin[8]={
		{.port=GPIO_PORTB,.pin=GPIO_PIN0,.mode=GPIO_MODE_OUTPUT,.out_type=GPIO_OUTSPEED_LOW},
		{.port=GPIO_PORTB,.pin=GPIO_PIN1,.mode=GPIO_MODE_OUTPUT,.out_type=GPIO_OUTSPEED_LOW},
		{.port=GPIO_PORTB,.pin=GPIO_PIN2,.mode=GPIO_MODE_OUTPUT,.out_type=GPIO_OUTSPEED_LOW},
		{.port=GPIO_PORTB,.pin=GPIO_PIN3,.mode=GPIO_MODE_OUTPUT,.out_type=GPIO_OUTSPEED_LOW},
		{.port=GPIO_PORTB,.pin=GPIO_PIN4,.mode=GPIO_MODE_OUTPUT,.out_type=GPIO_OUTSPEED_LOW},
		{.port=GPIO_PORTB,.pin=GPIO_PIN5,.mode=GPIO_MODE_OUTPUT,.out_type=GPIO_OUTSPEED_LOW},
		{.port=GPIO_PORTB,.pin=GPIO_PIN6,.mode=GPIO_MODE_OUTPUT,.out_type=GPIO_OUTSPEED_LOW},
		{.port=GPIO_PORTB,.pin=GPIO_PIN7,.mode=GPIO_MODE_OUTPUT,.out_type=GPIO_OUTSPEED_LOW}
};


/*
*	@breif: 	The main role of this function is to Iterate on Audio Header File
                to Set Pins Value of PORTB TO Output the voice
*	@ret: 		This function return nothing
*	@param_1:
*	@patam_2:
*/

void audio(void)
{
	static u32 count=0;
	for(u8 i=0;i<8;i++) // 0b 0101 1011
	{
		MGPIO_vSetPinVal(Dac_pin[i].port,Dac_pin[i].pin,GET_BIT(warnning_raw[count],i));
	}
	count++;
	if(count == (sizeof(warnning_raw)/sizeof(warnning_raw[0]))) count=0;
}
void main(void)
{
/*
* Initlize Ports and Clocks
*/
	MRCC_vInit();
	MSTK_vInit();


	MRCC_vEnableClock(RCC_AHB1,RCC_EN_GPIOA);

	MRCC_vEnableClock(RCC_AHB1,RCC_EN_GPIOB);

	MRCC_vEnableClock(RCC_APB2,RCC_EN_SPI1);

	HTFT_vInit();
	while(1)
	{
		HTFT_vDisplayPicture(Warning_Pic);
		MSTK_vSetBusyWait(50000);

		for(u8 i=0;i<8;i++) MGPIO_vInit(&Dac_pin[i]);
		MSTK_vSetInterval_Periodic(250,audio);
    }

}
