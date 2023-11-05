/*
 *  SWC     : SPI_int.h
 *  Author  : Amr Sayed
 *  Date    : 9/10/2023
 *  version : 1.00
 */

#ifndef MCAL_SPI_SPI_INT_H_
#define MCAL_SPI_SPI_INT_H_

typedef enum {
	SPI_1=1,
	SPI_2
}SPI_id_t;



/*
*@breif:Initialize the SPI
*@param_: nothing (void)
*@ret:    nothing (void)
*/
void MSPI_vInit(void);




/*
*@breif:Send and receive through SPI
*@param_1: sent data  (u16)
*@param_2: to select SPI_ID (SPI_1,SPI_2)
*@ret:    received data (u16)
*/

u16 MSPI_u16Transceive(u16 A_u16Data,SPI_id_t SPI_ID);


#endif /* MCAL_SPI_SPI_INT_H_ */
