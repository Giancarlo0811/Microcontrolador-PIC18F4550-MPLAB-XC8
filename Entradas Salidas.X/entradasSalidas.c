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
    TRISCbits.RC0 = 1;
    TRISCbits.RC1 = 1;
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;
    LATDbits.LD0 = 0;
    LATDbits.LD1 = 0;
    
    while (1) {
        if (PORTCbits.RC0 == 1) {
            LATDbits.LD0 = 1;
        } else {
             LATDbits.LD0 = 0;
        }
        
        if (PORTCbits.RC1 == 1) {
            LATDbits.LD1 = 1;
        } else {
             LATDbits.LD1 = 0;
        }
    }
}
