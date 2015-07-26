/**
 * @file    SDCard.h
 * @author  Andreas Dirmeier
 * @version 0.01
 *  
 * @brief   Read and Write functions on SD-Card over SPI
 *          Actual it works just with MMC and SD 
 */
#ifndef _SDCARD_H_
	#define _SDCARD_H_

//SPI
#include "SPI.h"

#define SD_SS     PORTCbits.RC2

//SDCard Commands
#define SD_GO_IDLE_STATE             0x40
#define SD_SEND_OP_COND              0x41
#define SD_APP_SEND_OP_COND          0xe9
#define SD_SEND_IF_COND              0x48
#define SD_SEND_CSD                  0x49
#define SD_SEND_CID                  0x4a
#define SD_STOP_TRANSMISSION         0x4c
#define SD_SET_BLOCKLEN              0x50
#define SD_READ_SINGLE_BLOCK         0x51
#define SD_READ_MULTIPLE_BLOCK       0x52
#define SD_SET_BLOCK_COUNT           0x57
#define SD_SET_WR_BLOCK_ERASE_COUNT  0xd7
#define SD_WRITE_BLOCK               0x58
#define SD_WRITE_MULTIPLE_BLOCK      0x59
#define SD_APP_CMD                   0x77
#define SD_READ_OCR                  0x7a

#define CMD0 		0x40
#define CMD1 		0x41
#define ACMD41      0xe9
#define CMD8		0x48
#define CMD9        0x49
#define CMD10       0x4a
#define CMD12       0x4c
#define CMD16       0x50
#define CMD17       0x51
#define CMD18     	0x52
#define CMD23       0x57
#define ACMD23  	0xd7
#define CMD24       0x58
#define CMD25     	0x59
#define CMD55       0x77
#define CMD58       0x7a

extern void init_SD();
extern unsigned char SD_sendSingleCommand(unsigned char);
extern unsigned char SD_sendCommand(unsigned char, unsigned char*);
extern unsigned char SD_getByte();
extern unsigned char SD_sendByte(unsigned char);
extern void SD_setNextBlock();
extern void SD_goToStart();
extern void SD_setAddress(unsigned char*);
extern void SD_setPointer(unsigned char*);
extern void SD_endBlock();
extern void SD_setBlock(unsigned char*);
extern void SD_writeBlock(unsigned char*);
extern unsigned char SD_writeByte(unsigned char);
extern unsigned char SD_getInfo();
extern void SD_getAddress(unsigned char* adr);

#endif
