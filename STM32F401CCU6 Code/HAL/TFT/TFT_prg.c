/*********************************************************/
/*      Author  :   Esraa Mohammed Elghorab              */
/*      SWC     :   TFT                                  */
/*      Date    :   30/10/2023                           */
/*      version :   1.00                                 */
/*********************************************************/

/**
 *Includes Libriaries
*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../MCAL/SPI/SPI_int.h"
#include "../../MCAL/SYSTICK/STK_interface.h"

#include "TFT_cfg.h"
#include "TFT_int.h"
#include "TFT_prv.h"


/**
 *Include GPIOs Congif of HW Pin
*/
extern GPIO_cfg_t   RESET_PIN  ;
extern GPIO_cfg_t   A0_PIN  ;

/**
 *	@breif: 	The main role of this Config Reset Process to Initi the TFT
 *	@ret: 		This function return nothing
 *	@param_1: 	"Void" for Ability to change in Preiod Cycle by User in config
 *	@patam_2:
*/
static void TFT_svReset(void)
{
	MGPIO_vSetPinValFast(RESET_PIN.port,RESET_PIN.pin,GPIO_HIGH);
	STK_voidSetBusyWait(100);
	MGPIO_vSetPinValFast(RESET_PIN.port,RESET_PIN.pin,GPIO_LOW);
	STK_voidSetBusyWait(20);
	MGPIO_vSetPinValFast(RESET_PIN.port,RESET_PIN.pin,GPIO_HIGH);
	STK_voidSetBusyWait(100);
	MGPIO_vSetPinValFast(RESET_PIN.port,RESET_PIN.pin,GPIO_LOW);
	STK_voidSetBusyWait(100);
	MGPIO_vSetPinValFast(RESET_PIN.port,RESET_PIN.pin,GPIO_HIGH);
	STK_voidSetBusyWait(120000);
}

/**
 *	@breif: 	The main role of this function is to Config A0 to Send Commands
 *	@ret: 		This function return nothing
 *	@param_1: 	A_u8Command -> The Command That We Need To send
 *	@patam_2:
*/
static void TFT_svWriteCommand(u8 A_u8Command)
{
	MGPIO_vSetPinValFast(A0_PIN.port,A0_PIN.pin,GPIO_LOW);
	(void)MSPI_u16Transceive(A_u8Command,SPI_1);
}

/**
 *	@breif: 	The main role of this function is to Config A0 to Send Data
 *	@ret: 		This function return nothing
 *	@param_1: 	A_u8Data -> The Data That We Need To send
 *	@patam_2:
*/
static void TFT_svWriteData(u8 A_u8Data)
{
	MGPIO_vSetPinValFast(A0_PIN.port,A0_PIN.pin,GPIO_HIGH);
	(void)MSPI_u16Transceive(A_u8Data,SPI_1);
}

/**
 *	@breif: 	The main role of this function is to initialize the TFT
 *	@ret: 		This function return nothing
 *	@param_1:
 *	@patam_2:
*/
void HTFT_vInit(void)
{
/**
 * Initialize Pins and Drivers
*/
	MGPIO_vInit(&RESET_PIN);
	MGPIO_vInit(&A0_PIN);
	MSPI_vInit();
	STK_voidInit();

/**
 * Reset sequence
*/
TFT_svReset();

/**
 * Sleep out
*/
TFT_svWriteCommand(COMMAND_SLEAPOUT);

/**
 * Delay(10ms)
*/
STK_voidSetBusyWait(10000);

/**
 * Color Mode
*/
TFT_svWriteCommand(COMMAND_COLOR_MODE);
TFT_svWriteData(DATA_COLOR); 			// RGB565

}

/**
 *	@breif: 	The main role of this function is to Display Pic on TFT
 *	@ret: 		This function return nothing
 *	@param_1: 	*ptr-> this varibable is used to pass Pic_array
 *	@patam_2:
*/
void HTFT_vDisplayPicture(u16 *ptr)
{
	TFT_svWriteCommand(COMMAND_DISPLAY_ON);

/**
 * X
*/
	TFT_svWriteCommand(COMMAND_X);

/**
 * Start x
*/
	TFT_svWriteData(0); 		//High
	TFT_svWriteData(0); 		//Low

/**
 * End x
*/
	TFT_svWriteData(0); 		//High
	TFT_svWriteData(127); 		//Low

/**
* Y
*/
	TFT_svWriteCommand(COMMAND_Y);

/**
 * Start x
*/
	TFT_svWriteData(0); 		//High
	TFT_svWriteData(0); 		//Low

/**
 * End x
*/
	TFT_svWriteData(0); 		//High
	TFT_svWriteData(159); 		//Low

/**
 * Command write Data
*/
	TFT_svWriteCommand(COMMAND_MEM_WRITE);

	for(u32 i=0;i<20480;i++)
	{
		TFT_svWriteData((u8)(ptr[i]>>8)); 	//High
		TFT_svWriteData((u8)ptr[i]); 		//Low
	}
}
