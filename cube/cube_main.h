#ifndef _cube_main_
	#define _cube_main_

#include "pic18f4420.h"
#include "cube_orders.h"
#include "cube_control.h"
#include "cube_com.h"

unsigned char led[3][64];
unsigned char delay_ms=10;

void init_cube(){
	cube_reset();
	init_SD();
}

#endif