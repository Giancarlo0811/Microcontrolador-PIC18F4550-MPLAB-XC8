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
    ADCON1bits.PCFG = 0x0F; // Coloca todos los pines como digitales
    TRISBbits.RB0 = 0;
    LATBbits.LB0 = 1;
    
    T1CON = 0xF8; // Configuracion Timer 1
    T1CONbits.TMR1ON = 1; // Habilita Timer 1
    PIE1bits.TMR1IE = 1; // Habilita la interrupcion del Timer 1
    PIR1bits.TMR1IF = 0; // Flag 0
    INTCONbits.PEIE = 1; // Habilita las interrupciones de perifericos
    INTCONbits.GIE = 1; // Habilita las interrupciones globales
    TMR1 = 35536; // Carga el valor del Timer 1
    
    while (1) {

    }
}

void __interrupt() INT_TMR1() { // Interrupcion Timer 1
    if (PIR1bits.TMR1IF == 1) {
        LATBbits.LB0 = !LATBbits.LB0;
        TMR1 = 35536;
        PIR1bits.TMR1IF = 0; 
    }
}