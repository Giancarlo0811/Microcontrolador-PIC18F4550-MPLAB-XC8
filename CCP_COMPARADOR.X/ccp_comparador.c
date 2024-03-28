// CONFIGURACION DEL PIC
#pragma config PLLDIV = 1, CPUDIV = OSC1_PLL2, USBDIV = 2  
#pragma config FOSC = INTOSCIO_EC, FCMEN = OFF, IESO = OFF      
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

#define _XTAL_FREQ 8000000
#include <xc.h>

void main(void) {
    OSCCON = 0x72; // Reloj Interno a 8 MHz
    ADCON1bits.PCFG = 0x0F; // Coloca todos los pines como digitales
    
    TRISCbits.RC2 = 0; // Pin RC2 como salida
    CCP1CON = 0x02; // Configura el CCP1 en modo comparador
    PIR1bits.CCP1IF = 0; // Flag 0
    TMR3 = 0; // Timer 3 en 0
    T3CON = 0xC0; // Configura el Timer 3
    CCPR1 = 1000; // Carga el valor al CCP1
    T3CONbits.TMR3ON = 1; // Habilita el Timer 3
    
    while (1) {
        if (PIR1bits.CCP1IF == 1) {
            TMR3 = 0;
            PIR1bits.CCP1IF = 0;
        }
    }
}
