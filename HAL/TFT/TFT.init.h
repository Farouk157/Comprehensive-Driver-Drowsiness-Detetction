/*********************************************************/
/*      Author  :   Esraa Mohammed Aly                   */
/*      SWC     :   TFT                                  */
/*      Date    :   30/10/2023                           */
/*      version :   1.00                                 */
/*********************************************************/

#ifndef HAL_TFT_TFT_INT_H_
#define HAL_TFT_TFT_INT_H_

/*
*	@breif: 	The main role of this Config Reset Process to Initi the TFT 
*	@ret: 		This function return nothing 
*	@param_1: 	"Void" for Ability to change in Preiod Cycle by User in config
*	@patam_2: 
*/
static void TFT_svReset(void)

/*
*	@breif: 	The main role of this function is to initialize the TFT
*	@ret: 		This function return nothing 
*	@param_1: 
*	@patam_2: 
*/
void HTFT_vInit(void);



/*
*	@breif: 	The main role of this function is to Display Pic on TFT
*	@ret: 		This function return nothing 
*	@param_1: 	*ptr-> this varibable is used to pass Pic_array
*	@patam_2: 
*/

void HTFT_vDisplayPicture(u16 *ptr);


/*
*	@breif: 	The main role of this function is to Config A0 to Send Data
*	@ret: 		This function return nothing 
*	@param_1: 	A_u8Data -> The Data That We Need To send 
*	@patam_2: 
*/
static void TFT_svWriteData(u8 A_u8Data);

/*
*	@breif: 	The main role of this function is to Config A0 to Send Commands
*	@ret: 		This function return nothing 
*	@param_1: 	A_u8Command -> The Command That We Need To send 
*	@patam_2: 
*/

static void TFT_svWriteCommand(u8 A_u8Command);



#endif /* HAL_TFT_TFT_INT_H_ */
