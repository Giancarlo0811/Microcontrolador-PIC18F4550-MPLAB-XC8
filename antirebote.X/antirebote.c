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

unsigned char contador = 0;

void main(void) {
    ADCON1bits.PCFG = 0x0F; // coloca todos los pines como digitales
    TRISAbits.RA0 = 1;  // pin RA0 como entrada
    TRISD = 0x00; // puerto D como salida
    LATD = 0x00; // limpiar el puerto D
            
    while(1) {
        if (PORTAbits.RA0 == 1) {
            while(PORTAbits.RA0 == 1);
            __delay_ms(20);
                
            if (contador > 14) {
                contador = 0;
                LATD = contador;
            }
            else {
               contador++;
               LATD = contador;
            }
        }
    }
}
