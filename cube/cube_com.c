#include "cube_com.h"

#include "cube_orders.h"
#include "cube_control.h"
#include "cube_functions.h"

extern unsigned char delay_ms;
extern unsigned char led[3][64];

/*
cube_com_stage 
	0 = root
	1 = Play SD
	2 = Read SD
	3 = Read Config
*/
unsigned char cube_com_stage=1;

void cube_enter_stage(unsigned char stage){
	cube_com_stage = stage;
}
void cube_call_from_uart(unsigned char order_uart){
	switch(cube_com_stage){
		case 0: cube_enter_stage(order_uart);
		default: cube_com_stage = 0;
	}
}
unsigned char cube_timer_interrupt(){
	unsigned char temp;
	if(cube_com_stage==1){
		temp = SD_getByte();
		switch(temp){
			case 0x40: delay_ms = SD_getByte(); return 1;
			case 0x41: cube_set_color(0); return 1;
			case 0x80: return 1;
			case 0x81: return 0;
			case 0x82: SD_goToStart(); return 1;
			default:
				if(1==cube_parse_order(temp)){
					while(!(temp = cube_parse_order(SD_getByte())));
					return 0;
				}
				else return 1;
		}
	}
	return 0;
}