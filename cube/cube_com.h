#ifndef _cube_com_
	#define _cube_com_

#include "../lib/SDCard.h"

extern void cube_enter_stage(unsigned char);
extern void cube_call_from_uart(unsigned char);
extern unsigned char cube_timer_interrupt();

#endif