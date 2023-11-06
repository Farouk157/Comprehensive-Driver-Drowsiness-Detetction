/*********************************************************/
/*      Author  :   Esraa Mohammed Aly                   */
/*      SWC     :   Speaker                              */
/*      Date    :   30/10/2023                           */
/*      version :   1.00                                 */
/*********************************************************/

/*
* Include Libraries
*/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../MCAL/SYSTICK/STK_int.h"


#include "S2P_cfg.h"
#include "S2P_int.h"

/*
 *Include GPIOs Congif of HW Pin  
 */

extern MGPIO_Config_t DataSerial ;
extern MGPIO_Config_t Shift ;
extern MGPIO_Config_t Latch ;


/*
*	@breif: 	The main role of this function is to Initlize Serial To Parallel/Speaker
*	@ret: 		This function return nothing
*	@param_1:
*	@patam_2:
*/

void HS2P_vInit(void)
{
	/*
	* port SD, pin,out
	*/
	MGPIO_vInit(&DataSerial);
	MGPIO_vInit(&Shift);
	MGPIO_vInit(&Latch);
}

/*
 * Setting Shift Pin High and Low
*/
static void S2P_svShift(void)
{
	MGPIO_vSetPinVal(Shift.port,Shift.pin,1);

	MGPIO_vSetPinVal(Shift.port,Shift.pin,0);

}

/*
 * Setting Latch Pin High and Low
*/
static void S2P_svLatch(void)
{
	MGPIO_vSetPinVal(Latch.port,Latch.pin,1);

	MGPIO_vSetPinVal(Latch.port,Latch.pin,0);
}


/*
*	@breif: 	The main role of this function is to Send Data of Header file
*	@ret: 		This function return nothing
*	@param_1:   A_pu8Data -> Array of Data/ Header File of Audio
*	@patam_2:   A_u8Size -> Array Size of Audio.Raw
*/
void HS2P_vSendData(u8 * A_pu8Data, u8 A_u8Size)
{
	for(u8 j=0;j<A_u8Size;j++)
	{
		for(u8 i=0;i<8;i++) 
			{
				/*
				* SD
				*/
				MGPIO_vSetPinVal(DataSerial.port,DataSerial.pin,GET_BIT(A_pu8Data[j],i));
				
				/*
				* Shift
				*/
				S2P_svShift();

			}
	}
		/*
		* latch
		*/
		S2P_svLatch();

}


/*
*	@breif: 	The main role of this function is to Send Data of Header file "Another Method"
*	@ret: 		This function return nothing
*	@param_1:   A_pu8Data -> Array of Data/ Header File of Audio
*	@patam_2:
*/
void HS2P_vSendData_(u32 A_pu8Data)
{
    /*
	* Serial Data Send
	*/
	for(u8 i=0;i<8*NUMBER_OF_REGISTER;i++) 
	{
		/*
		* SD Bit
		*/
		MGPIO_vSetPinVal(DataSerial.port,DataSerial.pin,GET_BIT(A_pu8Data,i));
		/*
		*Shift
		*/
		S2P_svShift();

	}
	/*
	*latch
	*/
	S2P_svLatch();
}










