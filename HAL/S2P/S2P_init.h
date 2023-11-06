/*********************************************************/
/*      Author  :   Esraa Mohammed Aly                   */
/*      SWC     :   Speaker                              */
/*      Date    :   30/10/2023                           */
/*      version :   1.00                                 */
/*********************************************************/

#ifndef HAL_S2P_S2P_INT_H_
#define HAL_S2P_S2P_INT_H_




/*
*	@breif: 	The main role of this function is to Initlize Serial To Parallel/Speaker
*	@ret: 		This function return nothing
*	@param_1:
*	@patam_2:
*/
void HS2P_vInit(void);



/*
*	@breif: 	The main role of this function is to Send Data of Header file
*	@ret: 		This function return nothing
*	@param_1:   A_pu8Data -> Array of Data/ Header File of Audio
*	@patam_2:   A_u8Size -> Array Size of Audio.Raw
*/
void HS2P_vSendData(u8 * A_pu8Data, u8 A_u8Size);



/*
*	@breif: 	The main role of this function is to Send Data of Header file "Another Method"
*	@ret: 		This function return nothing
*	@param_1:   A_pu8Data -> Array of Data/ Header File of Audio
*	@patam_2:
*/
void HS2P_vSendData_(u32 A_pu8Data);


#endif /* HAL_S2P_S2P_INT_H_ */
