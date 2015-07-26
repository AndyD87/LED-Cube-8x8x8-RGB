/**
 * @file    cube_cmd.c
 * @author  Andreas Dirmeier
 * @version 0.01
 *  
 * @brief   Cube command handling
 */
#include "cube_cmd.h"
#include "cube_functions.h"

unsigned char g_cmdArgSize=0;
unsigned char g_cmdArgPos=0;
unsigned char g_cmdArgBuf[5]={0};
unsigned char g_cmdActive=0;
unsigned char order_active=0;

unsigned char Cube_GetAxis(unsigned char prev){
	return (prev>>4)+(prev&0x07)<<3;
}

unsigned char Cube_GetCmdArgSize(){
	switch(g_cmdActive){
		case 0x01: return 2;
		case 0x02: return 2;
		case 0x03: return 2;
		case 0x04: return 3;
		case 0x05: return 3;
		case 0x06: return 3;
		case 0x07: return 2;
		case 0x08: return 1;
		case 0x09: return 2;
		case 0x10: return 2;
		case 0x11: return 2;
		case 0x20: return 3;
		case 0x21: return 3;
		case 0x30: return 1;
		case 0x31: return 1;
	}
	return 0;
}

unsigned char Cube_SendCmd(unsigned char recv){
	switch(g_cmdActive){
		case 0x01:
			switch(g_cmdArgBuf[0] & 0x30){
				case 0x00: cube_set_x_line(((g_cmdArgBuf[0]&0x07)*8)+g_cmdArgBuf[2],0,recv); break;
				case 0x10: cube_set_y_line(((g_cmdArgBuf[0]&0x07)*8)+g_cmdArgBuf[2],0,recv); break;
				case 0x20: cube_set_z_line(((g_cmdArgBuf[0]&0x07)*8)+g_cmdArgBuf[2],0,recv); break;
			}
			if(g_cmdArgBuf[2] == 7){
				g_cmdArgBuf[2]=g_cmdArgBuf[1]=g_cmdArgBuf[0]=0;
				return 1;
			}
			g_cmdArgBuf[2]++;
			return 0;
		case 0x02:
			switch(g_cmdArgBuf[0] & 0x30){
				case 0x00: cube_set_x_line(((g_cmdArgBuf[0]&0x07)*8)+g_cmdArgBuf[2],1,recv); break;
				case 0x10: cube_set_y_line(((g_cmdArgBuf[0]&0x07)*8)+g_cmdArgBuf[2],1,recv); break;
				case 0x20: cube_set_z_line(((g_cmdArgBuf[0]&0x07)*8)+g_cmdArgBuf[2],1,recv); break;
			}
			if(g_cmdArgBuf[2] == 7){
				g_cmdArgBuf[2]=g_cmdArgBuf[1]=g_cmdArgBuf[0]=0;
				return 1;
			}
			g_cmdArgBuf[2]++;
			return 0;
		case 0x03:
			switch(g_cmdArgBuf[0] & 0x30){
				case 0x00: cube_set_x_line(((g_cmdArgBuf[0]&0x07)*8)+g_cmdArgBuf[2],2,recv); break;
				case 0x10: cube_set_y_line(((g_cmdArgBuf[0]&0x07)*8)+g_cmdArgBuf[2],2,recv); break;
				case 0x20: cube_set_z_line(((g_cmdArgBuf[0]&0x07)*8)+g_cmdArgBuf[2],2,recv); break;
			}
			if(g_cmdArgBuf[2] == 7){
				g_cmdArgBuf[2]=g_cmdArgBuf[1]=g_cmdArgBuf[0]=0;
				return 1;
			}
			g_cmdArgBuf[2]++;
			return 0;
		case 0x04:
			switch(g_cmdArgBuf[0] & 0x30){
				case 0x00: cube_set_x_line(Cube_GetAxis(g_cmdArgBuf[1]),0,recv); break;
				case 0x10: cube_set_y_line(Cube_GetAxis(g_cmdArgBuf[1]),0,recv); break;
				case 0x20: cube_set_z_line(Cube_GetAxis(g_cmdArgBuf[1]),0,recv); break;
			}
			return 1;
		case 0x05:
			switch(g_cmdArgBuf[0] & 0x30){
				case 0x00: cube_set_x_line(Cube_GetAxis(g_cmdArgBuf[1]),1,recv); break;
				case 0x10: cube_set_y_line(Cube_GetAxis(g_cmdArgBuf[1]),1,recv); break;
				case 0x20: cube_set_z_line(Cube_GetAxis(g_cmdArgBuf[1]),1,recv); break;
			}
			return 1;
		case 0x06:
			switch(g_cmdArgBuf[0] & 0x30){
				case 0x00: cube_set_x_line(Cube_GetAxis(g_cmdArgBuf[1]),2,recv); break;
				case 0x10: cube_set_y_line(Cube_GetAxis(g_cmdArgBuf[1]),2,recv); break;
				case 0x20: cube_set_z_line(Cube_GetAxis(g_cmdArgBuf[1]),2,recv); break;
			}
			return 1;
		case 0x07:
			cube_set_led(g_cmdArgBuf[0], g_cmdArgBuf[1]);
			return 1;
		case 0x08:
			cube_set_color(g_cmdArgBuf[0]);
			return 1;
		case 0x10:
			switch(g_cmdArgBuf[0] & 0x03){
				case 0x00: cube_mv_x_level(g_cmdArgBuf[1] >> 4, g_cmdArgBuf[1] & 0x0f); break;
				case 0x01: cube_mv_y_level(g_cmdArgBuf[1] >> 4, g_cmdArgBuf[1] & 0x0f); break;
				case 0x02: cube_mv_z_level(g_cmdArgBuf[1] >> 4, g_cmdArgBuf[1] & 0x0f); break;
			}
			return 1;
		case 0x11:
			switch(g_cmdArgBuf[0] & 0x03){
				case 0x00: cube_cp_x_level(g_cmdArgBuf[1] >> 4, g_cmdArgBuf[1] & 0x0f); break;
				case 0x01: cube_cp_y_level(g_cmdArgBuf[1] >> 4, g_cmdArgBuf[1] & 0x0f); break;
				case 0x02: cube_cp_z_level(g_cmdArgBuf[1] >> 4, g_cmdArgBuf[1] & 0x0f); break;
			}
			return 1;
		case 0x20:
			switch(g_cmdArgBuf[0] & 0x03){
				case 0x00: cube_mv_x_line(Cube_GetAxis(g_cmdArgBuf[1]), Cube_GetAxis(g_cmdArgBuf[2])); break;
				case 0x01: cube_mv_y_line(Cube_GetAxis(g_cmdArgBuf[1]), Cube_GetAxis(g_cmdArgBuf[2])); break;
				case 0x02: cube_mv_z_line(Cube_GetAxis(g_cmdArgBuf[1]), Cube_GetAxis(g_cmdArgBuf[2])); break;
			}
			return 1;
		case 0x21:
			switch(g_cmdArgBuf[0] & 0x03){
				case 0x00: cube_cp_x_line(Cube_GetAxis(g_cmdArgBuf[1]), Cube_GetAxis(g_cmdArgBuf[2])); break;
				case 0x01: cube_cp_y_line(Cube_GetAxis(g_cmdArgBuf[1]), Cube_GetAxis(g_cmdArgBuf[2])); break;
				case 0x02: cube_cp_z_line(Cube_GetAxis(g_cmdArgBuf[1]), Cube_GetAxis(g_cmdArgBuf[2])); break;
			}
			return 1;
		default: return 1;
	}
}

unsigned char Cube_ParseCmd(unsigned char recv){
	if(order_active){
		if(g_cmdArgPos < g_cmdArgSize){
			g_cmdArgBuf[g_cmdArgPos] = recv;
			g_cmdArgPos++;
		}
		if(g_cmdArgPos==g_cmdArgSize){
			if(Cube_SendCmd(recv)) {
				order_active=0;
				g_cmdArgPos=0;
				return 0;
			}
		}
		return 1;
	}
	else{
		g_cmdActive = recv;
		if(g_cmdArgSize = Cube_GetCmdArgSize()){
			order_active=1;
			return 1;
		}
		else{
			Cube_SendCmd(0);
			return 0;
		}
	}
}

