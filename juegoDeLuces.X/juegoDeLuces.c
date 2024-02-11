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
    ADCON1bits.PCFG = 0x0F; // coloca todos los pines como digitales
    TRISDbits.RD0 = 1;
    TRISDbits.RD1 = 1;
    TRISDbits.RD2 = 1;
    TRISDbits.RD3 = 1;
    TRISDbits.RD4 = 1;
    TRISB = 0x00;
    LATB = 0x00;
    
    while (1) {
        if (PORTDbits.RD0 == 1) {
            for (int i = 0; i < 4; i++) {
                LATB = 0b00000001;
                __delay_ms(100);
                LATB = 0b00000010;
                __delay_ms(100);
                LATB = 0b00000100;
                __delay_ms(100);
                LATB = 0b00001000;
                __delay_ms(100);
                LATB = 0b00010000;
                __delay_ms(100);
                LATB = 0b00100000;
                __delay_ms(100);
                LATB = 0b01000000;
                __delay_ms(100);
                LATB = 0b10000000;
                __delay_ms(100);
            }
        }
        else if (PORTDbits.RD1 == 1) {
            for (int i = 0; i < 4; i++) {
                LATB = 0b10000000;
                __delay_ms(100);
                LATB = 0b01000000;
                __delay_ms(100);
                LATB = 0b00100000;
                __delay_ms(100);
                LATB = 0b00010000;
                __delay_ms(100);
                LATB = 0b00001000;
                __delay_ms(100);
                LATB = 0b00000100;
                __delay_ms(100);
                LATB = 0b00000010;
                __delay_ms(100);
                LATB = 0b00000001;
                __delay_ms(100);
            }
        }
        else if (PORTDbits.RD2 == 1) {
            for (int i = 0; i < 4; i++) {
                LATB = 0b10000001;
                __delay_ms(100);
                LATB = 0b01000010;
                __delay_ms(100);
                LATB = 0b00100100;
                __delay_ms(100);
                LATB = 0b00011000;
                __delay_ms(100);
                LATB = 0b00100100;
                __delay_ms(100);
                 LATB = 0b01000010;
                __delay_ms(100);
                LATB = 0b10000001;
                __delay_ms(100);
            }
        }
        else if (PORTDbits.RD3 == 1) {
            for (int i = 0; i < 4; i++) {
                LATB = 0b00001111;
                __delay_ms(400);
                LATB = 0b11110000;
                __delay_ms(400);
            }
        }
        else if (PORTDbits.RD4 == 1) {
            for (int i = 0; i < 4; i++) {
                LATB = 0b00000001;
                __delay_ms(100);
                LATB = 0b00000011;
                __delay_ms(100);
                LATB = 0b00000111;
                __delay_ms(100);
                LATB = 0b00001111;
                __delay_ms(100);
                 LATB = 0b00010000;
                __delay_ms(100);
                LATB = 0b00110000;
                __delay_ms(100);
                LATB = 0b01110000;
                __delay_ms(100);
                LATB = 0b11110000;
                __delay_ms(100);
            }
        }
        else {
            LATB = 0b00000000;
        }
    }
}
