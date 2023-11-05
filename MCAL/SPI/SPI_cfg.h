/*
 *  SWC     : SPI_cfg.h
 *  Author  : Amr Sayed
 *  Date    : 9/10/2023
 *  version : 1.00
 */

#ifndef MCAL_SPI_SPI_CFG_H_
#define MCAL_SPI_SPI_CFG_H_


/*
 * ENABLE
 * DISABLE
 */
#define SPI1_ENABLE    ENABLE

/*
 * MASTER
 * SLAVE
 */
#define MODE_MASTER_OR_SLAVE_SPI1   MASTER
/*
 * PS_2
 * PS_4
 */
#define PS1_FPCLK   PS_2   //4MHZ

/*
 * LSB_FIRST_TO_SEND_RECEIVE
 * MSB_FIRST_TO_SEND_RECEIVE
 */
#define SPI1_MSB_LSB  MSB_FIRST_TO_SEND_RECEIVE

#endif /* MCAL_SPI_SPI_CFG_H_ */
