/**
 * @file    cube_cmd.c
 * @author  Andreas Dirmeier
 * @version 0.01
 *  
 * @brief   Cube command handling
 */
#include "cube_cmd.h"
#include "cube_functions.h"

unsigned char args=0;
unsigned char argp=0;
unsigned char argv[5]={0};
unsigned char gl_order=0;
unsigned char order_active=0;

unsigned char Cube_GetAxis(unsigned char prev){
	return (prev>>4)+(prev&0x07)<<3;
}

unsigned char Cube_ParseCmd(unsigned char recv){
	if(order_active){
		if(argp < args){
			argv[argp] = recv;
			argp++;
		}
		if(argp==args){
			if(cube_activ_order(recv)) {
				order_active=0;
				argp=0;
				return 0;
			}
		}
		return 1;
	}
	else{
		gl_order = recv;
		if(args = cube_check_order()){
			order_active=1;
			return 1;
		}
		else{
			cube_activ_order(0);
			return 0;
		}
	}
}

unsigned char cube_check_order(){
	switch(gl_order){
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

unsigned char cube_activ_order(unsigned char recv){
	switch(gl_order){
		case 0x01:
			switch(argv[0] & 0x30){
				case 0x00: cube_set_x_line(((argv[0]&0x07)*8)+argv[2],0,recv); break;
				case 0x10: cube_set_y_line(((argv[0]&0x07)*8)+argv[2],0,recv); break;
				case 0x20: cube_set_z_line(((argv[0]&0x07)*8)+argv[2],0,recv); break;
			}
			if(argv[2] == 7){
				argv[2]=argv[1]=argv[0]=0;
				return 1;
			}
			argv[2]++;
			return 0;
		case 0x02:
			switch(argv[0] & 0x30){
				case 0x00: cube_set_x_line(((argv[0]&0x07)*8)+argv[2],1,recv); break;
				case 0x10: cube_set_y_line(((argv[0]&0x07)*8)+argv[2],1,recv); break;
				case 0x20: cube_set_z_line(((argv[0]&0x07)*8)+argv[2],1,recv); break;
			}
			if(argv[2] == 7){
				argv[2]=argv[1]=argv[0]=0;
				return 1;
			}
			argv[2]++;
			return 0;
		case 0x03:
			switch(argv[0] & 0x30){
				case 0x00: cube_set_x_line(((argv[0]&0x07)*8)+argv[2],2,recv); break;
				case 0x10: cube_set_y_line(((argv[0]&0x07)*8)+argv[2],2,recv); break;
				case 0x20: cube_set_z_line(((argv[0]&0x07)*8)+argv[2],2,recv); break;
			}
			if(argv[2] == 7){
				argv[2]=argv[1]=argv[0]=0;
				return 1;
			}
			argv[2]++;
			return 0;
		case 0x04:
			switch(argv[0] & 0x30){
				case 0x00: cube_set_x_line(Cube_GetAxis(argv[1]),0,recv); break;
				case 0x10: cube_set_y_line(Cube_GetAxis(argv[1]),0,recv); break;
				case 0x20: cube_set_z_line(Cube_GetAxis(argv[1]),0,recv); break;
			}
			return 1;
		case 0x05:
			switch(argv[0] & 0x30){
				case 0x00: cube_set_x_line(Cube_GetAxis(argv[1]),1,recv); break;
				case 0x10: cube_set_y_line(Cube_GetAxis(argv[1]),1,recv); break;
				case 0x20: cube_set_z_line(Cube_GetAxis(argv[1]),1,recv); break;
			}
			return 1;
		case 0x06:
			switch(argv[0] & 0x30){
				case 0x00: cube_set_x_line(Cube_GetAxis(argv[1]),2,recv); break;
				case 0x10: cube_set_y_line(Cube_GetAxis(argv[1]),2,recv); break;
				case 0x20: cube_set_z_line(Cube_GetAxis(argv[1]),2,recv); break;
			}
			return 1;
		case 0x07:
			cube_set_led(argv[0], argv[1]);
			return 1;
		case 0x08:
			cube_set_color(argv[0]);
			return 1;
		case 0x10:
			switch(argv[0] & 0x03){
				case 0x00: cube_mv_x_level(argv[1] >> 4, argv[1] & 0x0f); break;
				case 0x01: cube_mv_y_level(argv[1] >> 4, argv[1] & 0x0f); break;
				case 0x02: cube_mv_z_level(argv[1] >> 4, argv[1] & 0x0f); break;
			}
			return 1;
		case 0x11:
			switch(argv[0] & 0x03){
				case 0x00: cube_cp_x_level(argv[1] >> 4, argv[1] & 0x0f); break;
				case 0x01: cube_cp_y_level(argv[1] >> 4, argv[1] & 0x0f); break;
				case 0x02: cube_cp_z_level(argv[1] >> 4, argv[1] & 0x0f); break;
			}
			return 1;
		case 0x20:
			switch(argv[0] & 0x03){
				case 0x00: cube_mv_x_line(Cube_GetAxis(argv[1]), Cube_GetAxis(argv[2])); break;
				case 0x01: cube_mv_y_line(Cube_GetAxis(argv[1]), Cube_GetAxis(argv[2])); break;
				case 0x02: cube_mv_z_line(Cube_GetAxis(argv[1]), Cube_GetAxis(argv[2])); break;
			}
			return 1;
		case 0x21:
			switch(argv[0] & 0x03){
				case 0x00: cube_cp_x_line(Cube_GetAxis(argv[1]), Cube_GetAxis(argv[2])); break;
				case 0x01: cube_cp_y_line(Cube_GetAxis(argv[1]), Cube_GetAxis(argv[2])); break;
				case 0x02: cube_cp_z_line(Cube_GetAxis(argv[1]), Cube_GetAxis(argv[2])); break;
			}
			return 1;
		default: return 1;
	}
}