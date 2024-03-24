// CONFIGURACION DEL PIC
#pragma config PLLDIV = 2, CPUDIV = OSC1_PLL2, USBDIV = 2  
#pragma config FOSC = HSPLL_HS, FCMEN = OFF, IESO = OFF      
#pragma config PWRT = OFF, BOR = OFF, BORV = 3, VREGEN = OFF    
#pragma config WDT = OFF
#pragma config WDTPS = 32768    
#pragma config CCP2MX = ON, PBADEN = OFF, LPT1OSC = OFF, MCLRE = ON       
#pragma config STVREN = ON, LVP = OFF, ICPRT = OFF, XINST = OFF      
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF   
#pragma config CPB = OFF, CPD = OFF       
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF     
#pragma config WRTC = OFF, WRTB = OFF, WRTD = OFF      
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF     
#pragma config EBTRB = OFF  

#define _XTAL_FREQ 48000000
#include <xc.h>

void main(void) {
    ADCON1bits.PCFG = 0x0F; // Colocar todos los pines como digitales
    TRISBbits.RB0 = 0;
    LATBbits.LB0 = 1;
    
    T2CON = 0x7B; // Configuracion Timer 2
    T2CONbits.TMR2ON = 1; // Habilitar Timer 2
    PIE1bits.TMR2IE = 1; // Habilita interrupcion del timer 2
    PIR1bits.TMR2IF = 0; // Flag 0
    INTCONbits.PEIE = 1; // Habilita las interrupciones perifericas
    INTCONbits.GIE = 1; // Habilita las interrupciones globales
    TMR2 = 0; // Timer 2 en 0
    PR2 = 22; // Valor del PR2
    
    while (1) {

    }
}

void __interrupt() INT_TMR2() { // interrupcion timer 2
    if (PIR1bits.TMR2IF == 1) {
        LATBbits.LB0 = !LATBbits.LB0;
        PIR1bits.TMR2IF = 0;
    }
}