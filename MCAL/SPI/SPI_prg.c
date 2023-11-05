/*
 *  SWC     : SPI_prg.c
 *  Author  : Amr Sayed
 *  Date    : 9/10/2023
 *  version : 1.00
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "SPI_cfg.h"
#include "SPI_int.h"
#include "SPI_prv.h"

#include "../../MCAL/GPIO/GPIO_int.h"
/*
 * SP1 ,SPI2,SPI4   AF5
 * SPI3             AF6
 */
#define  CPHA  0
#define  CPOL  1
#define  MSTR  2
#define  BR0   3
#define  SPE   6
#define  LSBFIRST  7
#define  DFF  11
#define  BSY  7






/*
*@breif:Initialize the SPI
*@param_: nothing (void)
*@ret:    nothing (void)
*/


void MSPI_vInit(void)
{

	u16 CR1_RegData = 0 ;
#if SPI1_ENABLE==ENABLE

	/*Read at Raising edge , write at failing edge*/
	SET_BIT(CR1_RegData,CPHA);
	SET_BIT(CR1_RegData,CPOL);
	/*Master or slave*/
#if MODE_MASTER_OR_SLAVE_SPI1==MASTER
	SET_BIT(CR1_RegData,MSTR);
#elif  MODE_MASTER_OR_SLAVE_SPI1==SLAVE
	CLR_BIT(CR1_RegData,MSTR);
#endif
/*BOUD Rate control*/
#if PS1_FPCLK>=0  && PS1_FPCLK<=7
	CR1_RegData &= ~((0b111)<<BR0);
	CR1_RegData |= (PS1_FPCLK<<BR0);
#endif
	/*Lest or Most*/
#if   SPI1_MSB_LSB== MSB_FIRST_TO_SEND_RECEIVE
	CLR_BIT(CR1_RegData,LSBFIRST);
#elif SPI1_MSB_LSB== LSB_FIRST_TO_SEND_RECEIVE
 SET_BIT(CR1_RegData,LSBFIRST);
#endif
/*Data frame 8bit*/
 CLR_BIT(CR1_RegData,DFF);
/*SSM = 1  SSI=1*/
 SET_BIT(CR1_RegData,8);
 SET_BIT(CR1_RegData,9);
 /*Enable*/
 SET_BIT(CR1_RegData,SPE);
 SPI1->CR1 = CR1_RegData ;


	MGPIO_Config_t MOSI1 ={
			.port = GPIO_PORTA,
			.pin  = GPIO_PIN7,
			.mode = GPIO_MODE_ALTFUNC,
			.alt_func = 5
	};
	MGPIO_Config_t MISO1 ={
			.port = GPIO_PORTA,
			.pin  = GPIO_PIN6,
			.mode = GPIO_MODE_ALTFUNC,
			.alt_func = 5
	};
	MGPIO_Config_t SCK1 ={
			.port = GPIO_PORTA,
			.pin  = GPIO_PIN5,
			.mode = GPIO_MODE_ALTFUNC,
			.alt_func = 5
		};
MGPIO_vInit(&MOSI1);
MGPIO_vInit(&MISO1);
MGPIO_vInit(&SCK1);
#endif
//SPI1->CR1 = 0x0347 ;

}


/*
*@breif:Send and receive through SPI
*@param_1: sent data  (u16)
*@param_2: to select SPI_ID (SPI_1,SPI_2)
*@ret:    received data (u16)
*/


u16 MSPI_u16Transceive(u16 A_u16Data,SPI_id_t SPI_ID)
{
	u16 Return_data=0;
	switch(SPI_ID)
	{
	case SPI_1 :
//		SPI1->DR = A_u16Data ;
//		while(GET_BIT(SPI1->SR,BSY)==1);
//			Return_data =SPI1->DR ;
		while(GET_BIT(SPI1->SR,1)==0);
		SPI1->DR = A_u16Data ;
		while(GET_BIT(SPI1->SR,0)==0);
		Return_data =SPI1->DR ;
		break;
	case SPI_2:
		break;
	default :
		break;
	}
return Return_data ;
}

