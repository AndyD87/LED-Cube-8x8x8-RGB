/**
 * @file    cube_control.h
 * @author  Andreas Dirmeier
 * @version 0.01
 *  
 * @brief   Cube output functions to LEDs
 */
#ifndef _cube_control_
	#define _cube_control_

extern void Cube_WriteLevel(unsigned char );
extern void cube_setDelay(unsigned char delay);
extern void cube_reset();

#endif