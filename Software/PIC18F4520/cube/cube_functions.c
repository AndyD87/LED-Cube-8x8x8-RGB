/**
 * @file    cube_functions.c
 * @author  Andreas Dirmeier
 * @version 0.01
 *  
 * @brief   functions for API to manipulate LED Array
 */
#include "cube_functions.h"

unsigned char c, tmp_led[64];

//BAUSTELLE check if used
void cube_set_led(unsigned char adr1, unsigned char adr2){
	unsigned char and;
	and = 0x01 << (adr1 & 0x07);
	adr2 = ((adr2 & 0x07) * 8) | ((adr2 & 0x70) >> 4);
	if(adr1 & 0x40)
		led[0][adr2] |= and;
	else
		led[0][adr2] &= ~and;
	if(adr1 & 0x20)
		led[1][adr2] |= and;
	else
		led[1][adr2] &= ~and;
	if(adr1 & 0x10)
		led[2][adr2] |= and;
	else
		led[2][adr2] &= ~and;
}
unsigned char mirror_bits(unsigned char bits){
	unsigned char i, tmp=0;
	for(i=0;i<4;i++)
	{
		tmp |= ((bits & (0x01<<i)) << (7-i*2)) | ((bits & (0x80>>i)) >> (7-i*2));
	}
	return tmp;
}

void cube_set_color(unsigned char color){
	unsigned char i;
  unsigned char ledR=0, ledG=0, ledB=0;
	if(color&0x01)
    ledR = 0xff;
	if(color&0x02)
    ledG = 0xff;
	if(color&0x04)
    ledB = 0xff;
  for(i = 0; i < 64; i++)
  {
    led[0][i] = ledR;
    led[1][i] = ledG;
    led[2][i] = ledB;
  }
}
void cube_set_x_line(unsigned char address, unsigned char color, unsigned char value){
	led[color][address]=value;
}
void cube_set_y_line(unsigned char address, unsigned char color, unsigned char value){
	unsigned char i, _z, _and, _invand;
	signed char diff;
	_z = address & 0xf8;
	address = address%8;
	_and = 0x01 << address;
	_invand = ~_and;
	for(i=0; i<8; i++)
	{
		diff = address - i;
		if(diff > 0){
			led[color][_z+i] = led[color][_z+i] & _invand |  _and & (value << diff);
		}
		else{
			diff = 0 - diff;
			led[color][_z+i] = led[color][_z+i] & _invand |  _and & (value >> diff);
    }
	}
}
void cube_set_z_line(unsigned char address, unsigned char color, unsigned char value){
	unsigned char i, _y, _and, _invand;
	signed char diff;
	_y = address>>3;
	address = address%8;
	_and = 0x01 << address;
	_invand = ~ _and;
	for(i=0; i<8; i++)
	{
		diff = address - i;
		if(diff > 0){
			led[color][_y+i*8] = led[color][_y+i*8] & _invand |  _and & (value << diff);
		}
		else{
			diff = 0 - diff;
			led[color][_y+i*8] = led[color][_y+i*8] & _invand |  _and & (value >> diff);
    }
	}
}
void cube_cp_x_level(unsigned char _from, unsigned char _to){
	unsigned char and, invand, i, diff;
	and = 0x01 << _to;
	invand = ~and;
	for(c=0; c<3; c++)
	{
		if(_from > _to)
		{
			diff = _from - _to;
			for(i = 0; i < 64; i++)
				led[c][i] = (led[c][i]>>diff) & and | led[c][i] & invand;
		}
		else
		{
			diff = _to - _from;
			for(i = 0; i < 64; i++)
				led[c][i] = (led[c][i]<<diff) & and | led[c][i] & invand;
		}
	}
}
void cube_mv_x_level(unsigned char _from, unsigned char _to){
	unsigned char i, rm;
	cube_cp_x_level(_from, _to);
	rm = ~(0x01 << _from);
	for(i = 0; i < 64; i++)
	{
		led[0][i]&=rm;
		led[1][i]&=rm;
		led[2][i]&=rm;
	}
}
void cube_cp_y_level(unsigned char _from, unsigned char _to){
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		led[0][_to+8*i]=led[0][_from+8*i];
		led[1][_to+8*i]=led[1][_from+8*i];
		led[2][_to+8*i]=led[2][_from+8*i];
	}
}
void cube_mv_y_level(unsigned char _from, unsigned char _to){
	unsigned char i;
	cube_cp_y_level(_from,_to);
	for(i = 0; i < 8; i++)
	{
		led[0][_from+8*i]=0;
		led[1][_from+8*i]=0;
		led[2][_from+8*i]=0;
	}
}
void cube_cp_z_level(unsigned char _from, unsigned char _to){
	char i;
	_from = _from << 3;
	_to   = _to <<3; 
	for(i = 0; i < 8; i++)
	{
		led[0][_to+i]=led[0][_from+i];
		led[1][_to+i]=led[1][_from+i];
		led[2][_to+i]=led[2][_from+i];
	}
}
void cube_mv_z_level(unsigned char _from, unsigned char _to){
	unsigned char i;
	cube_cp_z_level(_from, _to);
	_from *= 8;
	_to   *= 8; 
	for(i = 0; i < 8; i++)
	{
		led[0][_from+i]=0;
		led[1][_from+i]=0;
		led[2][_from+i]=0;
	}
}
void cube_cp_x_line (unsigned char _from, unsigned char _to){
	led[0][_to] = led[0][_from];
	led[1][_to] = led[1][_from];
	led[2][_to] = led[2][_from];
}
void cube_mv_x_line (unsigned char _from, unsigned char _to){
	cube_cp_x_line(_from, _to);
	led[0][_from] = 0;
	led[1][_from] = 0;
	led[2][_from] = 0;
}
void cube_cp_y_line (unsigned char _from, unsigned char _to){
  //ToDo readd id with bigger ram
	/*unsigned char i,j, pos_from, inv_to, temp;
	signed char diff;
	diff = (_to & 0x07) - (_from & 0x07);
	if(diff > 0){
    j=0;
	}
	else{
		diff = 0 - diff;
		j=1;
  } 
	pos_from = 0x01 << (_from%8);
	inv_to = ~(0x01 << (_to%8));
	_from = _from&0xf8;
	_to = _to&0xf8;
	for(c=0; c<3; c++)
	{
		for(i=0; i<8; i++)
		{
			temp = _to + i;
			if(j)
					led[c][temp] = led[c][temp] & inv_to | 
						(led[c][_from+i] & pos_from) >> diff;
			else
					led[c][temp] = led[c][temp] & inv_to | 
						(led[c][_from+i] & pos_from) << diff;
		}
	}*/
}
void cube_mv_y_line (unsigned char _from, unsigned char _to){
	unsigned char i, inv_from;
	cube_cp_y_line(_from, _to);
	inv_from = ~(0x01 << (_from%8));
	_from = _from & 0xf8;
	_to = _to & 0xf8;
	for(c=0; c<3; c++)
	{
		for(i=0; i<8; i++)
			led[c][_from + i] = led[c][_from + i] & inv_from;
	}
}
void cube_cp_z_line (unsigned char _from, unsigned char _to){
	unsigned char i,j=0, pos_from, inv_to, inv_from, temp;
	signed char diff;
	diff = _to%8 - _from%8;
	if(diff < 0)
	{
		j=1;
		diff = 0-diff;
	} 
	pos_from = 0x01 << (_from%8);
	inv_from = ~pos_from;
	inv_to = ~(0x01 << (_to%8));
	_from = _from/8;
	_to = _to/8;
	for(c=0; c<3; c++)
	{
		for(i=0; i<8; i++)
		{
			temp = _to + i*8;
			if(j)
			{
					led[c][temp] = led[c][temp] & inv_to | 
						(led[c][_from+i*8] & pos_from) >> diff;
			}
			else
					led[c][temp] = led[c][temp] & inv_to | 
						(led[c][_from+i*8] & pos_from) << diff;
		}
	}
}
void cube_mv_z_line (unsigned char _from, unsigned char _to){
	unsigned char i, inv_from;
	cube_cp_z_line(_from,_to);
	inv_from = ~(0x01 << (_from%8));
	_from = _from>>3;
	_to = _to>>3;
	for(c=0; c<3; c++)
	{
		for(i=0; i<8; i++)
			led[c][_from + i*8] = led[c][_from + i*8] & inv_from;
	}
}
void cube_roll_x_up(unsigned char carry){
	unsigned char i;
	for(c=0; c<3; c++)
	{
		for(i = 0; i < 64; i++)
		{
			if(carry)
				tmp_led[0] = (led[c][i] & 0x80) >> 7;
			led[c][i] = led[c][i] << 1;
			if(carry)
				led[c][i] = led[c][i] | tmp_led[0];
		}
	}
}
void cube_roll_x_down(unsigned char carry){
	unsigned char i, tmp_led = 0;
	for(c=0; c<3; c++)
	{
		for(i = 0; i < 64; i++)
		{
			if(carry)
				tmp_led = (led[c][i] & 0x01) << 7;
			led[c][i] = led[c][i] >> 1;
			if(carry)
				led[c][i] = led[c][i] | tmp_led;
		}
	}
}
void cube_roll_y_up(unsigned char carry){
	unsigned char i;
	for(c=0; c<3 && carry; c++)
		for(i=0; i < 8; i++) tmp_led[8*c+i] = led[c][i*8+7];
	for(i=7; i>0; i--)
		cube_mv_y_level(i-1, i);
	for(c=0; c<3 && carry; c++)
		for(i=0; i < 8; i++) led[c][i*8] = tmp_led[8*c+i];
}
void cube_roll_y_down(unsigned char carry){
	unsigned char i;
	for(c=0; c<3 && carry; c++)
		for(i=0; i < 8; i++) 
			tmp_led[8*c+i] = led[c][i*8];
	for(i=0; i<7; i++)
		cube_mv_y_level(i+1, i);
	for(c=0; c<3 && carry; c++)
		for(i=0; i < 8; i++) 
			led[c][i*8+7] = tmp_led[8*c+i];
}
void cube_roll_z_up(unsigned char carry){
	unsigned char i;
	for(c=0; c<3 && carry; c++)
		for(i=0; i < 8; i++)
			tmp_led[8*c+i] = led[c][i+56];
	for(i=7; i>0; i--)
		cube_mv_z_level(i-1, i);
	for(c=0; c<3 && carry; c++)
		for(i=0; i < 8; i++) 
			led[c][i] = tmp_led[8*c+i];
}
void cube_roll_z_down(unsigned char carry){
	unsigned i;
	for(c=0; c<3 && carry; c++)
		for(i=0; i < 8; i++) 
			tmp_led[8*c+i] = led[c][i];
	for(i=0; i<7; i++)
		cube_mv_z_level(i+1, i);
	for(c=0; c<3 && carry; c++)
		for(i=0; i < 8; i++) 
			led[c][i+56] = tmp_led[8*c+i];
}
void cube_rotate_x(unsigned char steps){
	unsigned char i,j,k, tmp_led;
	for(k=0; k<steps; k++)
	{
		for(i=0; i<4; i++)
		{
			for(j=0; j<(7-2*i); j++)
			{
				for(c=0; c<3; c++)
				{
					tmp_led = led[c][i*9+j];
					led[c][   i*9 +j] = led[c][56-i*7-j*8];
					led[c][56-i*7-j*8] = led[c][63-i*9-j];
					led[c][63-i*9-j] = led[c][7+i*7+j*8];
					led[c][7+ i*7+j*8] = tmp_led;
				}
			}
		}
	}
}
void cube_rotate_y(unsigned char steps){
	unsigned char i,k,j;
	for(k=0; k<steps; k++)
	{
		for(c=0; c<3; c++)
		{
			for(i=0; i<8; i++)
				for(j=0; j<8; j++)
					tmp_led[i+8*j] = led[c][i*8+j];
			for(i=0; i<64; i++)
				cube_set_z_line(i, c, mirror_bits(tmp_led[i]));
		}
	}
}
void cube_rotate_z(unsigned char steps){
	unsigned char i,j,k;
	for(k=0; k<steps; k++)
	{
		for(c=0; c<3; c++)
		{
			for(i=0; i<8; i++)
			{
				for(j=0; j<8; j++)
					tmp_led[j] = led[c][i*8+j];
				for(j=0; j<8; j++)
					cube_set_y_line( (i*8+j), c, mirror_bits(tmp_led[j])  );
			}
		}
	}
}