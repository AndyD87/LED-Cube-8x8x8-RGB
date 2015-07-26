/**
 * @file    SPI.h
 * @author  Andreas Dirmeier
 * @version 0.01
 *  
 * @brief   SPI Functions
 */
#ifndef _SPI_
  #define _SPI_

/**
 * @brief init IOs, Ports and Modes 
 */ 
extern void init_SPI();

/** 
 * @brief write/read Byte to SPI
 * 
 * @param ucByte: Byte to write
 * @return Byte read from bus
 */  
extern unsigned char SPI_send(unsigned char ucByte );

#endif