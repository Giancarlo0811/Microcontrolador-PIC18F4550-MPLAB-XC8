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
    ADCON1bits.PCFG = 0x0F; // coloca todo los pines como digitales
    TRISBbits.RB0 = 1; // Pin RB0 como entrada
    INTCONbits.INT0IE = 1; // Habilita la interrupcion externa en RB0
    INTCONbits.INT0IF = 0; // Flag 0
    INTCON2bits.INTEDG0 = 1; // Flanco de subida
    INTCONbits.GIE = 1; // habilita las interrupciones globales
    
    TRISD = 0x00; // Puerto D como salida
    LATD = 0x00; // Limpiar puerto D
    TRISCbits.RC7 = 0; // Pin RC7 como salida
    LATCbits.LC7 = 0; // Inicializa en 0 el pin RC7
    
    while (1) {
        LATD = 0x01;
        __delay_ms(1000);
        LATD = 0x02;
        __delay_ms(1000);
        LATD = 0x04;
        __delay_ms(1000);
        LATD = 0x08;
        __delay_ms(1000);
    }
}

void __interrupt() INT_EXT_RB0() { // interrupcion externa en RB0
    if (INTCONbits.INT0IF == 1) { // Verificar si ha ocurrido evento
        for (char i = 0; i < 10; i++) {
            LATCbits.LC7 = 1;
            __delay_ms(400);
            LATCbits.LC7 = 0;
            __delay_ms(400);
        }
        INTCONbits.INT0IF = 0; // Limpiar la flag
    }
}
