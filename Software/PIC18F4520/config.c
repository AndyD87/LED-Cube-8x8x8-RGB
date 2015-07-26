/**
 * @file    config.c
 * @author  Andreas Dirmeier
 * @version 0.01
 *  
 * @brief   Configuration Functions for uController
 */
#include "CONFIG.h"

void LoadConfig()
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
}
