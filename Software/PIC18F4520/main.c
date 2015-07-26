/**
 * @mainpage LED-Cube Project
 * @file    main.c
 * @author  Andreas Dirmeier
 * @version 0.01
 *  
 * @brief   main file, starting cube and handle interrupts
 */
#include "cube/cube_main.h"

unsigned char level_counter=0; /**< Counter for Writinge out the LED-Level*/
unsigned char timer_counter=0; /**< Counts timer-interupts of 1ms until delay reached */

extern unsigned char delay_ms; /**< delay in ms until event gets called */

/**
 * @brief Main interrupt-routine
 */ 
void isr_3(void){
	//Timer 1ms
	if(PIR2 & 0x02){
		TMR3H = 0xcf;
		if(timer_counter >= delay_ms){
			timer_counter = 0;
			if(!cube_timer_interrupt()) 
        T3CONbits.TMR3ON = 0;
		}
		else {
			timer_counter ++;
		}
		PIR2 &= 0xfd;
	}
	if(PIR1 & 0x01){
		INTCONbits.GIE=0;
		TMR1H=0xf0;
		PIR1 &= 0xfe;
		Cube_WriteLevel(level_counter);
    //setup next level
		if(level_counter>14){
			level_counter = 0;
			Leveldat=0;
		}
		else {
			level_counter++;;
			Leveldat=1;
		}
		INTCONbits.GIE=1;
	}
	if(PIR1 & 0x20){
		PIE1 &= 0xdf;
		PIR1 &= 0xdf;
		TXREG = Cube_ParseCmd(RCREG);
		PIE1 |= 0x20;
	}
}

/**
 * @brief high priority interrupt, calles the main interrupt routine
 */ 
void interrupt high_priority isr1( void )
{  isr_3();}

/**
 * @brief low priority interrupt, calles the main interrupt routine
 */ 
void interrupt low_priority isr2( void )
{  isr_3();}

/**
 *
 */
void main ()
{
  LoadConfig();
	init_cube();
  //do nothing, cube is interrupt controled
	while(1);
}