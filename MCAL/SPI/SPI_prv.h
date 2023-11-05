/*
 *  SWC     : SPI_prv.h
 *  Author  : Amr Sayed
 *  Date    : 9/10/2023
 *  version : 1.00
 */


#ifndef MCAL_SPI_SPI_PRV_H_
#define MCAL_SPI_SPI_PRV_H_


/*APB2 */
#define SPI1_BASSADDRESS   0x40013000
typedef struct {
	u32 CR1 ;
	u32 CR2;
	u32 SR ;
	u32 DR ;
	u32 CRCPR ;
	u32 RXCRCR ;
	u32 TXCRCR ;
	u32 I2SCFGR ;
	u32 I2SPR ;
}SPI_MemMap_t;

#define SPI1     ((volatile SPI_MemMap_t*)(SPI1_BASSADDRESS))
#define MASTER   1
#define SLAVE    2

#define PS_2   0b000

#define LSB_FIRST_TO_SEND_RECEIVE   5
#define MSB_FIRST_TO_SEND_RECEIVE   6

#define ENABLE  1

#define DISABLE 0
#endif /* MCAL_SPI_SPI_PRV_H_ */
