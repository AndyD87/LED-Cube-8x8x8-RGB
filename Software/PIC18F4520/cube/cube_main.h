/**
 * @file    cube_main.h
 * @author  Andreas Dirmeier
 * @version 0.01
 *  
 * @brief   the one include to get all neccessary cube functions
 */
#ifndef _cube_main_
	#define _cube_main_

#include "cube_cmd.h"
#include "cube_control.h"
#include "cube_com.h"

unsigned char led[3][64];
unsigned char delay_ms=10;

void init_cube(){
	cube_reset();
	init_SD();
}

#endif