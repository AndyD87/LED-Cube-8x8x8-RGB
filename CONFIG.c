#include "CONFIG.h"

void CcLoadConfig()
{
    //Interrupts
    INTCON = 0x00;
    PIE1   = 0x00;
    PIR1   = 0x00;

    //PortA
    PORTA  = 0x00;
    TRISA  = 0xff;
    //PortB
    PORTB  = 0x00;
    TRISB  = 0xdf;

    //Timer
    TMR1ON = 0;
    PR2    = 0xff;
    T2CON  = 0x3f;
    
    //Disable CCP
    CCP1CON = 0x00;
    
    //UART
    SPBRG = 0x01;
    TXSTA = 0xB4;
    RCSTA = 0x80;
}
