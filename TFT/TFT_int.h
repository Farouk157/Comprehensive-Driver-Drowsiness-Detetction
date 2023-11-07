/*********************************************************/
/*      Author  :   Esraa Mohammed Aly                   */
/*      SWC     :   TFT                                  */
/*      Date    :   30/10/2023                           */
/*      version :   1.00                                 */
/*********************************************************/

#ifndef HAL_TFT_TFT_INT_H_
#define HAL_TFT_TFT_INT_H_

/**
 *	@breif: 	The main role of this function is to initialize the TFT
 *	@ret: 		This function return nothing 
 *	@param_1: 
 *	@patam_2: 
*/
void HTFT_vInit(void);



/**
 *	@breif: 	The main role of this function is to Display Pic on TFT
 *	@ret: 		This function return nothing 
 *	@param_1: 	*ptr-> this varibable is used to pass Pic_array
 *	@patam_2: 
*/
void HTFT_vDisplayPicture(u16 *ptr);


#endif /* HAL_TFT_TFT_INT_H_ */
