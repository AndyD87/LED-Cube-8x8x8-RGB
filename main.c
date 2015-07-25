#include "CONFIG.h"

#include "cube/cube_main.h"

unsigned char stage_counter=0;
unsigned char timer_counter=0;
unsigned char interrupted=0;
extern unsigned char delay_ms; 

void isr_3(void){
	//Timer 1ms
	if(PIR2 & 0x02){
		TMR3H = 0xcf;
		if(timer_counter >= delay_ms){
			timer_counter = 0;
			if(!cube_timer_interrupt()) T3CONbits.TMR3ON = 0;
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
		set_stage(stage_counter);
		if(stage_counter>14){
			stage_counter = 0;
			Leveldat=0;
		}
		else {
			stage_counter++;;
			Leveldat=1;
		}
		INTCONbits.GIE=1;
	}
	if(PIR1 & 0x20){
		PIE1 &= 0xdf;
		PIR1 &= 0xdf;
		TXREG = cube_parse_order(RCREG);
		PIE1 |= 0x20;
	}
}

void interrupt high_priority isr1( void )
{  isr_3();}

void interrupt low_priority isr2( void )
{  isr_3();}

void main ()
{
	PORTA = 0;
	LATA = 0;
	ADCON1 = 0x0f;
	CMCON = 0x07;
	TRISA = 0xff;

	PORTB = 0;
	LATB = 0;
	TRISB = 0;

	PORTC = 0;
	LATC = 0;
	TRISC = 0xd3;

	PORTD = 0;
	LATD = 0;
	TRISD = 0;
	
	PORTE = 0;
	LATE = 0;
	TRISE = 0x00;

	OSCCON = 0x8c;
	RCON = 0x93;
	INTCON = 0xc0;
	INTCON2 = 0x00;
	INTCON3 = 0x00;
	PIE1 = 0x23;
	PIE2 = 0x02;
	IPR1 = 0x21;
	IPR2 = 0x00;
	
	TXSTA = 0x24;
	RCSTA = 0x90;
	BAUDCON = 0x00;
	SPBRG = 64;
	
	T3CON = 0xc1;
	T1CON = 0x01;
	
	init_cube();
  
	while(1)
	{
		
	}
}