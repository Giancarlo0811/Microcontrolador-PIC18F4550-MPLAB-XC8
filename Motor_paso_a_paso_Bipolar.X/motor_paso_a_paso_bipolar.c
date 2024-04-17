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

#define velocidad 6000 // velocidad de giro del motor

unsigned char pasos[4] = {0b1100, 0b0110, 0b0011, 0b1001}; // paso doble

void pasos_izquierda(void);
void pasos_derecha(void);

void main(void) {
    ADCON1bits.PCFG = 0x0F;
    TRISBbits.RB0 = 1; // pulsador para giro izquierda
    TRISBbits.RB1 = 1; // pulsador para giro derecha
    TRISDbits.RD0 = 0; // fase 1
    TRISDbits.RD1 = 0; // fase 2
    TRISDbits.RD2 = 0; // fase 3
    TRISDbits.RD3 = 0; // fase 4
    LATD = 0x00; // inicializa apagado el motor
    
    while (1) {
        if (PORTBbits.RB0 == 1) { // si se presiona pulsador 1, gira a la izquierda
            pasos_izquierda();
        }
        else if (PORTBbits.RB1 == 1) { // si se presiona pulsador 2, gira a la derecha
            pasos_derecha();
        }
        else {
            LATD = 0x00; // apaga motor
        }
    }
}

void pasos_izquierda(void) { // funcion para el giro a la izquierda
    for (signed char i = 0; i < 4; i++) {
        LATD = pasos[i];
        __delay_us(velocidad);
    }
}

void pasos_derecha(void) { // funcion para el giro a la derecha
    for (signed char i = 3; i >= 0; i--) {
        LATD = pasos[i];
        __delay_us(velocidad);
    }
}
