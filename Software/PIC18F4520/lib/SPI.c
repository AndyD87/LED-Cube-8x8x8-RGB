/**
 * @file    SPI.c
 * @author  Andreas Dirmeier
 * @version 0.01
 *  
 * @brief   SPI Functions
 */
#include "SPI.h"

#define SPI_TR    SSPBUF
#define SPI_RC    SSPBUF
#define SPI_INT   PIR1bits.SSPIF
#define SPI_TRIS

void init_SPI()
{
  SSPSTAT = 0x00;
  SSPCON1 = 0x20;
}

unsigned char SPI_send(unsigned char input)
{
	SPI_TR = input;
	while(!SSPSTATbits.BF);
	return SSPBUF;
}