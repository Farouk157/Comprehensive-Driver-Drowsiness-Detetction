/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   USART                             */
/*      Date    :   6/10/2023                         */
/*      version :       1.00                          */
/******************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "UART_prv.h"
#include "UART_int.h"
#include "UART_cfg.h"

/*
 * @brief: this is the pointer to function that holds the address of the USART1 Interrupt Handler 
 */
void (*MUSART1_CallBack)(void);

/*
 * @brief: this is the pointer to function that holds the address of the USART2 Interrupt Handler 
 */
void (*MUSART2_CallBack)(void);

/*
 * @brief: this is the pointer to function that holds the address of the USART6 Interrupt Handler 
 */
void (*MUSART6_CallBack)(void);

/*
 * @brief: This function is used to initialize the USART 
 * @ret:   Nothing 
 * @param1: pointer to struct that contains the data about USART 
 * @param2: pointer to struct that contains the registers of the USART
 */
void MUSART_vInit(USART_InitType *A_InitStruct,USART_MemMap_t *USARTx)
{
	USARTx->CR1 = 0;
	switch(A_InitStruct->Oversampling)
	{
	case USART_OVER_SAMPLING_16: USARTx->BRR = UART_BRR_SAMPLING16(__PCLK__,A_InitStruct->BaudRate); break;
	case USART_OVER_SAMPLING_8:  USARTx->BRR = UART_BRR_SAMPLING8(__PCLK__,A_InitStruct->BaudRate); break;
	}
	USARTx->CR1 = (A_InitStruct->Oversampling<<MUSART_CR1_OVER8_BIT) |
			      (A_InitStruct->DataWidth<<MUSART_CR1_M_BIT)        |
				  (A_InitStruct->Parity_Enable<<MUSART_CR1_PCE_BIT)  |
				  (A_InitStruct->Parity_Selection<<MUSART_CR1_PS_BIT);
	switch(A_InitStruct->TransferDirection)
	{
	case USART_TX_ONLY: SET_BIT(USARTx->CR1,MUSART_CR1_TE_BIT);  break;
	case USART_RX_ONLY: SET_BIT(USARTx->CR1,MUSART_CR1_RE_BIT);  break;
	case USART_TX_RX: SET_BIT(USARTx->CR1,MUSART_CR1_TE_BIT);
	                  SET_BIT(USARTx->CR1,MUSART_CR1_RE_BIT); break;
	}
USARTx->SR = 0;

}
/*
 * @brief: This function is used to Enable the USART 
 * @ret:   Nothing 
 * @param1: pointer to struct that contains the registers of the USART 
 */
void MUSART_vEnable(USART_MemMap_t *USARTx)
{
	SET_BIT(USARTx->CR1,MUSART_CR1_UE_BIT);
}

/*
 * @brief: This function is used to Disable the USART 
 * @ret:   Nothing 
 * @param1: pointer to struct that contains the registers of the USART 
 */
void MUSART_vDisable(USART_MemMap_t *USARTx)
{
	CLR_BIT(USARTx->CR1,MUSART_CR1_UE_BIT);
}

/*
 * @brief: This function is used to send byte of data with blocking mode 
 * @ret:   Nothing 
 * @param1: pointer to struct that contains the registers of the USART 
 * @param2: byte of data you want to send 
 */
void MUSART_vTransmitByteSynch(USART_MemMap_t *USARTx ,u8 A_u8Byte)
{
	while(GET_BIT(USARTx->SR,MUSART_SR_TXE_BIT)==0) ;
	USARTx->DR = A_u8Byte ;
	while(GET_BIT(USARTx->SR,MUSART_SR_TC_BIT)==0)  ;
	//clear flag
	CLR_BIT(USARTx->SR,MUSART_SR_TC_BIT) ;
}

/*
 * @brief: This function is used to send byte of data Asynchronous mode 
 * @ret:   return the state 
			- if (0) means sent successfully
			- if (1) means something wrong 
 * @param1: pointer to struct that contains the registers of the USART 
 * @param2: byte of data you want to send 
 */
u8 MUSART_vTransmitByteAsynch(USART_MemMap_t *USARTx ,u8 A_u8Byte)
{
	if(GET_BIT(USARTx->SR,MUSART_SR_TXE_BIT)==1)
	{
		USARTx->DR = A_u8Byte ;
		return 0 ;
	}
	else
	{
		return 1;
	}
}

/*
 * @brief: This function is used to send string of data blocking mode 
 * @ret:   Nothing 
 * @param1: pointer to struct that contains the registers of the USART 
 * @param2: pointer to the string you want to send 
 */
void MUSART_vTransmitString(USART_MemMap_t *USARTx,u8 *A_ptru8String)
{
	u8 L_u8Itrator=0;
	while(A_ptru8String[L_u8Itrator] != '\0')
	{
		MUSART_vTransmitByteSynch(USARTx,A_ptru8String[L_u8Itrator]);
		L_u8Itrator++;
	}

}

/*
 * @brief: This function is used to receive byte of data Non-blocking mode 
 * @ret:   data received
 * @param1: pointer to struct that contains the registers of the USART  
 */
u8 MUSART_u8ReceiveByteSynchNonBlocking(USART_MemMap_t *USARTx )
{
	u8 L_u8Data = 0 ;
	u32 L_u32TimeOut=0 ;
	while(GET_BIT(USARTx->SR,MUSART_SR_RXNE_BIT)==0 && L_u32TimeOut< THRESHOLD_VALUE )
	{
		L_u32TimeOut++;
	}
	if(L_u32TimeOut== THRESHOLD_VALUE)  L_u8Data= 255;
	else                                L_u8Data = USARTx->DR ;
	return L_u8Data ;
}

/*
 * @brief: This function is used to receive byte of data Asynchronous mode 
 * @ret:   status of receiving 
			- if(0) means something wrong 
			- if(1) means received successfully
 * @param1: pointer to struct that contains the registers of the USART
 * @param2: pointer to variable that you want to receive the data inside   
 */
u8 MUSART_u8ReceiveByteAsynch_(USART_MemMap_t *USARTx , u8* ptr )
{
	u8 Status=1 ;
	if(GET_BIT(USARTx->SR,MUSART_SR_RXNE_BIT)==1)
	{
		*ptr= USARTx->DR ;
	}
	else
	{
		Status = 0;
	}
	return Status ;
}

/*
 * @brief: This function is used to receive byte of data blocking mode 
 * @ret:   data received
 * @param1: pointer to struct that contains the registers of the USART  
 */
u8 MUSART_u8ReceiveByteSynchBlocking(USART_MemMap_t *USARTx )
{
	u8 L_u8Data = 0 ;
	while(GET_BIT(USARTx->SR,MUSART_SR_RXNE_BIT)==0 );
	L_u8Data = USARTx->DR ;
	return L_u8Data ;
}

void MUSART_ptrReceiveStringSynchNonBlocking(USART_MemMap_t *USARTx ,char A_u8str[] ,u32 A_u32Size )
{
	u32 L_u8Itrator = 0;
 while(L_u8Itrator <A_u32Size )
 {
	 A_u8str[L_u8Itrator] = MUSART_u8ReceiveByteSynchNonBlocking(USARTx);
	 if(A_u8str[L_u8Itrator]== '\n' || A_u8str[L_u8Itrator]== '\r')
	 {
		 A_u8str[L_u8Itrator] = '\0';
		 break;
	 }
 }
 A_u8str[A_u32Size-1] = '\0';
}


/*enable the interrupt*/

/*
 * @brief: This function is used to Enable the Interrupt of specific USART
 * @ret:   Nothing
 * @param1: pointer to struct that contains the registers of the USART  
 * @param2: the state of the Interrupt
			-Options
			    1- Enable 
				2- Disable
 */
void MUSART_RxIntSetStatus(USART_MemMap_t *USARTx, u8 A_u8Status)
{
	switch(A_u8Status)
	{
	case ENABLE :  SET_BIT(USARTx->CR1,MUSART_CR1_RXNEIE_BIT);break ;
	case DISABLE : CLR_BIT(USARTx->CR1,MUSART_CR1_RXNEIE_BIT);break ;
	}
}
/*
 * @brief: this function is used to clear the flag of the USART
 * @ret: Nothing 
 * @param1: pointer to struct that contains the registers of the USART  
*/
void MUSART_voidClearFlags(USART_MemMap_t *USARTx)
{
	USARTx->SR = 0;
}

/*
 * @brief: This function is used to read the stored data in the register of the USART 
 * @ret:   stored received
 * @param1: pointer to struct that contains the registers of the USART  
 */
u8 MUSART_u8ReadDataRegisterAsynch(USART_MemMap_t *USARTx)
{
  return USARTx->DR;
}

void MUSART_u8ReceivesGsm_string(USART_MemMap_t *USARTx ,u8*Copy_u8RecievedData,u32 i)
{
	u8 k=40;
	u8 n=0;
	i=0;
	while(k--){
		i=0;
		while(GET_BIT(USARTx->SR,MUSART_SR_RXNE_BIT)==0 && i<1000000 ){

			i++;
		}

		if(i>=500000){
			break;
						}

			if(Copy_u8RecievedData != NULL)
						{
							Copy_u8RecievedData[n] = USARTx->DR  ;
							n++;
						}

		}

}

/*
 * @brief: this function is used to get the address of the API you want to execute when the flag of USART1 Interrupt being set
 * @ret  : Nothing 
 * @param1: pointer to function (The API you want to execute when the interrupt being fired) 
*/
void MUSART1_vSetCallBack(void (*ptr) (void) )
{
	MUSART1_CallBack = ptr ;
}

/*
 * @brief: this function is used to get the address of the API you want to execute when the flag of USART2 Interrupt being set
 * @ret  : Nothing 
 * @param1: pointer to function (The API you want to execute when the interrupt being fired) 
*/
void MUSART2_vSetCallBack(void (*ptr) (void) )
{
	MUSART2_CallBack = ptr ;
}

/*
 * @brief: this function is used to get the address of the API you want to execute when the flag of USART6 Interrupt being set
 * @ret  : Nothing 
 * @param1: pointer to function (The API you want to execute when the interrupt being fired) 
*/
void MUSART6_vSetCallBack(void (*ptr) (void) )
{
	MUSART6_CallBack = ptr ;
}

/*
 * @brief: this is the USART1 Interrupt Handler 
 * @ret  : Nothing 
 * @param: Nothing
*/
void USART1_IRQHandler(void)
{
	/* Reset the flag`s register */
	USART1 -> SR = 0 ;
	if(MUSART1_CallBack != NULL)
	{
		MUSART1_CallBack();
	}
}

/*
 * @brief: this is the USART2 Interrupt Handler 
 * @ret  : Nothing 
 * @param: Nothing
*/
void USART2_IRQHandler(void)
{
	USART2 -> SR = 0 ;
	if(MUSART2_CallBack != NULL)
	{
		MUSART2_CallBack();
	}
}

/*
 * @brief: this is the USART6 Interrupt Handler 
 * @ret  : Nothing 
 * @param: Nothing
*/
void USART6_IRQHandler(void)
{
	USART6 -> SR = 0 ;
	if(MUSART6_CallBack != NULL)
	{
		MUSART6_CallBack();
	}
}


