/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   USART                             */
/*      Date    :   6/10/2023                         */
/*      version :       1.00                          */
/******************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "UART_cfg.h"
#include "UART_int.h"

/* structure contains data of the USART1 */
USART_InitType uart1_cfg =
{
		.BaudRate           = 115200,
		.DataWidth          = USART_MODE_8BIT,
		.StopBits           = USART_STOP_BIT_1,
		.Parity_Enable      = DISABLE,
		.Parity_Selection   = USART_EVEN_PARITY,
		.TransferDirection  = USART_TX_RX,
		.Oversampling       = USART_OVER_SAMPLING_8

};

/* structure contains data of the USART2 */
USART_InitType uart2_cfg =
{
		.BaudRate           = 115200,
		.DataWidth          = USART_MODE_8BIT,
		.StopBits           = USART_STOP_BIT_1,
		.Parity_Enable      = DISABLE,
		.Parity_Selection   = USART_EVEN_PARITY,
		.TransferDirection  = USART_TX_RX,
		.Oversampling       = USART_OVER_SAMPLING_8

};

/* structure contains data of the USART6 */
USART_InitType uart6_cfg =
{
		.BaudRate           = 115200,
		.DataWidth          = USART_MODE_8BIT,
		.StopBits           = USART_STOP_BIT_1,
		.Parity_Enable      = DISABLE,
		.Parity_Selection   = USART_EVEN_PARITY,
		.TransferDirection  = USART_TX_RX,
		.Oversampling       = USART_OVER_SAMPLING_8

};


