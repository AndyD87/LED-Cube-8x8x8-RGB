/**
 * @file    cube_cmd.h
 * @author  Andreas Dirmeier
 * @version 0.01
 *  
 * @brief   Cube command handling
 */
#ifndef _cube_orders_
	#define _cube_orders_

extern unsigned char Cube_ParseCmd(unsigned char recv);
extern unsigned char Cube_CheckCmd();
extern unsigned char Cube_ActivCmd(unsigned char recv);

#endif