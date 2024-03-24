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
    ADCON1bits.PCFG = 0x0F; // colocar todos los pines como digitales
    TRISBbits.RB1 = 1; // Pin RB1 como entrada
    TRISBbits.RB2 = 1; // Pin RB2 como entrada
    
    INTCON3bits.INT1E = 1; // Habilitar interrupcion externa en RB1
    INTCON3bits.INT1IP = 1; // Alta prioridad para RB1
    INTCON3bits.INT1IF = 0; // Flag 0
    INTCON2bits.INTEDG1 = 1; // Flanco de subida
    
    INTCON3bits.INT2IE = 1; // Habilitar interrupcion externa en RB2
    INTCON3bits.INT2IP = 0; // baja prioridad para RB2
    INTCON3bits.INT2IF = 0; // Flag 0
    INTCON2bits.INTEDG2 = 1; // Flanco de subida
    
    RCONbits.IPEN = 1; // Habilitar niveles de interrupcion
    INTCONbits.GIEH = 1; // Habilitar la prioridad alta en interrupciones
    INTCONbits.GIEL = 1; // Habilita la prioridad baja en interrupciones
    
    TRISA = 0x00; // Puerto A como salida
    TRISD = 0x00l; // Puerto D como salida
    LATA = 0x00; // Limpia el puerto A
    LATD = 0x00; // Limpia el puerto D
    
    while (1) {
        LATA = 0x01;
        __delay_ms(500);
        LATA = 0x02;
        __delay_ms(500);
        LATA = 0x04;
        __delay_ms(500);
        LATA = 0x08;
        __delay_ms(500);
    }
}

void __interrupt(high_priority) INT_EXT_RB1() { // interrupcion externa RB1
    if (INTCON3bits.INT1IF == 1) { // verificar si ha ocurrido el evento
        for (char i = 0; i < 8; i++) {
            LATDbits.LD0 = 1;
            LATDbits.LD1 = 1;
            LATDbits.LD2 = 0;
            LATDbits.LD3 = 0;
            __delay_ms(10);
            LATDbits.LD0 = 0;
            LATDbits.LD1 = 0;
            LATDbits.LD2 = 1;
            LATDbits.LD3 = 1;
            __delay_ms(10);
        }
        LATDbits.LD0 = 0;
        LATDbits.LD1 = 0;
        LATDbits.LD2 = 0;
        LATDbits.LD3 = 0;
        
        INTCON3bits.INT1IF = 0; // limpiar el flag
    }
}

void __interrupt(low_priority) INT_EXT_RB2() { // interrupcion externa RB2
    if (INTCON3bits.INT2IF == 1) { // Verifica si ha ocurrido el evento
        for (char i = 0; i < 3; i++) {
            for (char j = 0; j < 3; j++) {
                LATDbits.LD4 = 1;
                LATDbits.LD5 = 1;
                __delay_ms(10);
                LATDbits.LD4 = 0;
                LATDbits.LD5 = 0;
                __delay_ms(10);
            }
            for (char j = 0; j < 3; j++) {
                LATDbits.LD6 = 1;
                LATDbits.LD7 = 1;
                __delay_ms(10);
                LATDbits.LD6 = 0;
                LATDbits.LD7 = 0;
                __delay_ms(10);
            }
        }
        INTCON3bits.INT2IF = 0; // Limpia la Flag
    }
}

