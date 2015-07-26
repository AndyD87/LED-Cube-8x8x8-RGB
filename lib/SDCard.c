/**
 * @file    SDCard.c
 * @author  Andreas Dirmeier
 * @version 0.01
 *  
 * @brief   Read and Write functions on SD-Card
 *          Actual it works just with MMC and SD 
 */
#include "SDCard.h"

unsigned char block_p[4]={0,0,0,0};
unsigned char read_active=0;
unsigned char write_active=0;
unsigned char adr_pointer[2] = {0,0};

void init_SD(){
	unsigned char i=0;
	unsigned char result;
	init_SPI();
	SSPCON1  = 0x22;         //Takt drosseln um sicheres initalisieren zu ermoegl.
	SD_SS=1;
	for(i =0; i <15; i++)    //80 Takte senden
		SPI_send(0xff);
	/*SD_sendByte(0x40);       //initialisierung per SPI aktivieren
	SD_sendByte(0x00);
	SD_sendByte(0x00);
	SD_sendByte(0x00);
	SD_sendByte(0x00);*/
  SD_sendSingleCommand(0x40);
	SD_sendByte(0x95);
	while(SD_sendByte(0xff) > 0x01);

	result = SD_sendSingleCommand(ACMD41);
	if(result & 0x04) 
	{
		while(result = SD_sendSingleCommand(CMD1));
	}
	else
	{
		while(result = SD_sendSingleCommand(ACMD41));
	}
	block_p[2] = 0x02;
	SD_sendCommand(SD_SET_BLOCKLEN, block_p); //Blockgroesse auf 512 setzen 
	block_p[2] = 0;
	SSPCON1  = 0x20; 
	return;
}
unsigned char SD_sendCommand(unsigned char cmd, unsigned char *para ){
	unsigned char response = 0xff;
	unsigned char i=0;
	SD_sendByte(0xff);
	if(cmd > 0x7f)
	{
    SD_sendByte( SD_APP_CMD );
    SD_sendByte( 0 );
    SD_sendByte( 0 );
    SD_sendByte( 0 );
    SD_sendByte( 0 );
		cmd &= 0x7f;
	}
	SD_sendByte( cmd);
	for(i=0; i<4; i++)
	{
		SD_sendByte( para[i]);
	}
	SD_sendByte( 0x01);
	while(response > 0x4f) response = SD_sendByte(0xff);
	return response;
}
unsigned char SD_sendByte(unsigned char toSend){
	SD_SS=0;
	toSend = SPI_send(toSend);
	SD_SS=1;
	return toSend;
}

unsigned char SD_sendSingleCommand(unsigned char cmd){
	unsigned char para[4] = {0,0,0,0};
	return SD_sendCommand(cmd, para);
}

unsigned char SD_getByte(){
	if(read_active)
	{
		if(255 == adr_pointer[1])
		{
			adr_pointer[0]++;
			adr_pointer[1] = 0;
			if(adr_pointer[0] == 2)
			{
				adr_pointer[0]=0;
				read_active=0;
			}
		}
		else
		{
			adr_pointer[1]++;
		}
		return SD_sendByte(0xff);
	}
	else
	{
		SD_sendByte(0xff);
		SD_sendByte(0xff);
		SD_setNextBlock();
		return SD_getByte();
	}
}
void SD_setNextBlock(){
	if(block_p[2] == 255)
	{
		block_p[2]=0;
		if(block_p[1]==255)
		{
			block_p[0]++;
			block_p[1]=0;
		}
		else
			block_p[1]++;
	}
	else
		block_p[2] += 2;
	SD_setBlock(block_p);
}
void SD_setBlock(unsigned char* adr){
	unsigned char i;
	for(i=0; i<3; i++)
		block_p[i] = adr[i];
	block_p[2] &= 0xfe;
	if(adr_pointer[0] || adr_pointer[1]) SD_endBlock();
	if(!SD_sendCommand(SD_READ_SINGLE_BLOCK, block_p))
	{
		while(SD_sendByte(0xff)!=0xfe);
		read_active=1;
		return;
	}
}
unsigned char SD_getInfo(){
	return 0;
}
void SD_setPointer(unsigned char* adr){
	unsigned char temp;
	temp = 0x01 & adr[0];
	while(adr_pointer[0] != temp | adr_pointer[1] != adr[1] )
	{
		SD_getByte();
	}
}
void SD_endBlock(){
	unsigned char end[2] = {1 , 255};
	SD_setPointer(end);
	SD_sendByte(0xff);
	SD_sendByte(0xff);
	SD_sendByte(0xff);
	SD_sendByte(0xff);
	SD_sendByte(0xff);
	adr_pointer[0] = adr_pointer[1] = 0;
}
void SD_setAddress(unsigned char* adr){
	SD_setBlock(adr);
	SD_setPointer(&adr[2]);
}
void SD_getAddress(unsigned char* adr){
	adr[0] = block_p[0];
	adr[1] = block_p[1];
	adr[2] = block_p[2] | adr_pointer[0];
	adr[3] = adr_pointer[1];
}
void SD_writeBlock(unsigned char* adr){
	unsigned char i;
	for(i=0; i<3; i++)
		block_p[i] = adr[i];
	block_p[2] &= 0xfe;
	if(adr_pointer[0] || adr_pointer[1]) SD_endBlock();
	if(!SD_sendCommand(SD_WRITE_BLOCK, block_p))
	{
		SD_sendByte(0xfe);
		write_active=1;
		return;
	}
}
unsigned char SD_writeByte(unsigned char value){
	if(write_active)
	{
		if(255 == adr_pointer[1])
		{
			adr_pointer[0]++;
			adr_pointer[1] = 0;
			if(adr_pointer[0] == 2)
			{
				adr_pointer[0]=0;
				write_active=0;
			}
		}
		else
		{
			adr_pointer[1]++;
		}
		value = SD_sendByte(value);
	}
	if(!adr_pointer[0] && !adr_pointer[1])
	{
		while(!SD_sendByte(0xff));
		return 2;
	}
	if(!value)
		return 0;
	else
		return 1;
}
void SD_goToStart(){
	unsigned char goTo[4] = {0x00, 0x00, 0x02, 0x00};
	SD_setBlock(goTo);
}