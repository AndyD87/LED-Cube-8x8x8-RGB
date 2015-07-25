#ifndef _cube_control_
	#define _cube_control_

#include "../CONFIG.h"

#define Clock     PORTBbits.RB4
#define Switch    PORTBbits.RB5
#define CLK       PORTBbits.RB6
#define Leveldat  PORTBbits.RB7

extern unsigned char led[3][64];
extern unsigned char delay_ms;

extern void set_stage(unsigned char );
extern void cube_setDelay(unsigned char delay);
extern void cube_reset();

#endif