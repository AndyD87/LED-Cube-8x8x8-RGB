/**
 * @file    cube_control.c
 * @author  Andreas Dirmeier
 * @version 0.01
 *  
 * @brief   Cube output functions to LEDs
 */
#include "cube_control.h"
#include "xc.h"

#define Clock     PORTBbits.RB4
#define Switch    PORTBbits.RB5
#define CLK       PORTBbits.RB6
#define Leveldat  PORTBbits.RB7

extern unsigned char led[3][64];
extern unsigned char delay_ms;

void Cube_WriteLevel (unsigned char stage){
	unsigned char counter = 0;
	unsigned char stage_temp, blueL, blueH, tmp_blue;
	stage_temp = (stage)*4;
	if(stage & 0x01)
		stage_temp -= 4;
	else 	stage_temp++;
	while(counter<8)
	{
		tmp_blue = led[2][stage_temp + counter];
		blueL =  tmp_blue & 0x01       | (tmp_blue >> 1) & 0x02 |
			(tmp_blue >> 2) & 0x04 | (tmp_blue >> 3) & 0x08;
		blueH = (tmp_blue >> 1) & 0x01 | (tmp_blue >> 2) & 0x02 |
			(tmp_blue >> 3) & 0x04 | (tmp_blue >> 4) & 0x08;
		PORTD = led[1][stage_temp + counter];
		PORTB = (PORTB & 0xf0) | blueH;
		Clock = 1;
		Clock = 0;
		PORTD = led[0][stage_temp + counter];
		PORTB = (PORTB & 0xf0) | blueL ;
		Clock = 1;
		Clock = 0;
		counter+=2;
	}
	PORTB = (PORTB & 0x9f) | 0x60;
	PORTB &= 0x9f;
}
void cube_reset(){
	unsigned char counter;
	PORTD = 0;
	PORTB = 0;
	Leveldat=1;
	for(counter=0;counter<64;counter++)
	{
		led[0][counter] = 0;
		led[1][counter] = 0;
		led[2][counter] = 0;
		Clock = 1;
		Clock = 0;
		CLK = 1;
		CLK = 0;
	}
}

void cube_setDelay(unsigned char delay){
	delay_ms = delay;
}