/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   USART                             */
/*      Date    :   6/10/2023                         */
/*      version :       1.00                          */
/******************************************************/

#ifndef MCAL_UART_UART_INT_H_
#define MCAL_UART_UART_INT_H_



/**********************************************/
/* 			USART Register Structure 		  */
/**********************************************/
typedef struct
{
	volatile u32 SR ;
	volatile u32 DR ;
	volatile u32 BRR ;
	volatile u32 CR1 ;
	volatile u32 CR2 ;
	volatile u32 CR3 ;
	volatile u32 GTPR ;
}USART_MemMap_t;


/**********************************************/
/* 		The USART Structure Pointer 		  */
/**********************************************/

#define USART1_BASE_ADDRESS    (0x40011000)
#define USART2_BASE_ADDRESS    (0x40004400)
#define USART6_BASE_ADDRESS    (0x40011400)

#define   USART1  (( USART_MemMap_t*)(USART1_BASE_ADDRESS))
#define   USART2  (( USART_MemMap_t*)(USART2_BASE_ADDRESS))
#define   USART6  (( USART_MemMap_t*)(USART6_BASE_ADDRESS))
typedef struct
{
	u32 BaudRate;
	u16 DataWidth;
	u16 StopBits ;
	u16 Parity_Enable;
	u16 Parity_Selection;
	u16 TransferDirection;//TX_ONLY  RX_ONLY  TX_RX
	u16 Oversampling;
}USART_InitType;
//////////////////////////////////////////////////////////////////

/* Sampling Options */
#define USART_OVER_SAMPLING_16    0
#define USART_OVER_SAMPLING_8     1

/*  Modes of USARTs Options */
#define USART_TX_ONLY             0
#define USART_RX_ONLY             1
#define USART_TX_RX               2

/* Parity options */
#define USART_EVEN_PARITY         0
#define USART_ODD_PARITY          1

/* Data bits options */
#define USART_MODE_8BIT		      0
#define USART_MODE_9BIT		      1

/* Stop bits options */
#define USART_STOP_BIT_1	      0
#define USART_STOP_BIT_0_5	      1
#define USART_STOP_BIT_2	      2
#define USART_STOP_BIT_1_5	      3

/* Enable or Disable options */
#define    ENABLE			      1
#define    DISABLE			      0


////////////////////////////////////////////////////////////////////

/*
 * @brief: This function is used to initialize the USART 
 * @ret:   Nothing 
 * @param1: pointer to struct that contains the data about USART 
 * @param2: pointer to struct that contains the registers of the USART
 */
void MUSART_vInit(USART_InitType *A_InitStruct,USART_MemMap_t *USARTx);

/*
 * @brief: This function is used to Enable the USART 
 * @ret:   Nothing 
 * @param1: pointer to struct that contains the registers of the USART 
 */
void MUSART_vEnable(USART_MemMap_t *USARTx);

/*
 * @brief: This function is used to Disable the USART 
 * @ret:   Nothing 
 * @param1: pointer to struct that contains the registers of the USART 
 */
void MUSART_vDisable(USART_MemMap_t *USARTx);

/*
 * @brief: This function is used to send byte of data with blocking mode 
 * @ret:   Nothing 
 * @param1: pointer to struct that contains the registers of the USART 
 * @param2: byte of data you want to send 
 */
void MUSART_vTransmitByteSynch(USART_MemMap_t *USARTx ,u8 A_u8Byte);

/*
 * @brief: This function is used to send byte of data Asynchronous mode 
 * @ret:   return the state 
			- if (0) means sent successfully
			- if (1) means something wrong 
 * @param1: pointer to struct that contains the registers of the USART 
 * @param2: byte of data you want to send 
 */
u8 MUSART_vTransmitByteAsynch(USART_MemMap_t *USARTx ,u8 A_u8Byte);

/*
 * @brief: This function is used to send string of data blocking mode 
 * @ret:   Nothing 
 * @param1: pointer to struct that contains the registers of the USART 
 * @param2: pointer to the string you want to send 
 */
void MUSART_vTransmitString(USART_MemMap_t *USARTx,u8 *A_ptru8String);

/*
 * @brief: This function is used to receive byte of data Non-blocking mode 
 * @ret:   data received
 * @param1: pointer to struct that contains the registers of the USART  
 */
u8 MUSART_u8ReceiveByteSynchNonBlocking(USART_MemMap_t *USARTx );

/*
 * @brief: This function is used to receive byte of data Asynchronous mode 
 * @ret:   status of receiving 
			- if(0) means something wrong 
			- if(1) means received successfully
 * @param1: pointer to struct that contains the registers of the USART
 * @param2: pointer to variable that you want to receive the data inside   
 */
u8 MUSART_u8ReceiveByteAsynch_(USART_MemMap_t *USARTx , u8* ptr );

/*
 * @brief: This function is used to receive byte of data blocking mode 
 * @ret:   data received
 * @param1: pointer to struct that contains the registers of the USART  
 */
u8 MUSART_u8ReceiveByteSynchBlocking(USART_MemMap_t *USARTx );

void MUSART_ptrReceiveStringSynchNonBlocking(USART_MemMap_t *USARTx ,char A_u8str[] ,u32 A_u32Size );

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
void MUSART_RxIntSetStatus(USART_MemMap_t *USARTx, u8 A_u8Status);

/*
 * @brief: this function is used to clear the flag of the USART
 * @ret: Nothing 
 * @param1: pointer to struct that contains the registers of the USART  
*/
void MUSART_voidClearFlags(USART_MemMap_t *USARTx);

/*
 * @brief: This function is used to read the stored data in the register of the USART 
 * @ret:   stored received
 * @param1: pointer to struct that contains the registers of the USART  
 */
u8 MUSART_u8ReadDataRegisterAsynch(USART_MemMap_t *USARTx);

/*
 * @brief: this function is used to get the address of the API you want to execute when the flag of USART1 Interrupt being set
 * @ret  : Nothing 
 * @param1: pointer to function (The API you want to execute when the interrupt being fired) 
*/
void MUSART1_vSetCallBack(void (*ptr) (void) );

/*
 * @brief: this function is used to get the address of the API you want to execute when the flag of USART2 Interrupt being set
 * @ret  : Nothing 
 * @param1: pointer to function (The API you want to execute when the interrupt being fired) 
*/
void MUSART2_vSetCallBack(void (*ptr) (void) );

/*
 * @brief: this function is used to get the address of the API you want to execute when the flag of USART6 Interrupt being set
 * @ret  : Nothing 
 * @param1: pointer to function (The API you want to execute when the interrupt being fired) 
*/
void MUSART6_vSetCallBack(void (*ptr) (void) );

void MUSART_u8ReceivesGsm_string(USART_MemMap_t *USARTx ,u8*Copy_u8RecievedData,u32 i);

#endif /* MCAL_UART_UART_INT_H_ */
