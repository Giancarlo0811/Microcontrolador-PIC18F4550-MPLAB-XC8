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
#include <stdio.h>

#include "lcd.h"

unsigned int valor_pasos;
unsigned int frecuencia;
float periodo;
char buffer[20];

void main(void) {
    ADCON1bits.PCFG = 0x0F; // Coloca todos los pines como digitales
    INTCONbits.GIE = 1; // Habilita las interrupciones globales
    INTCONbits.PEIE = 1; // Habilita las interrupciones de perifericos
    PIE1bits.CCP1IE = 1; // Habilita la interrupcion del CCP1
    PIR1bits.CCP1IF = 0; // Flag 0
    T1CON = 0xF8; // Configura el Timer 1
    TMR1L = 0x00;
    TMR1H = 0x00;
    CCP1CON = 0x05; // Configura el CCP1 en Modo Captura
    T1CONbits.TMR1ON = 1; // Habilita el Timer 1
    Lcd_Init(); // Inicializa la pantalla LCD
    
    while (1) {
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        sprintf(buffer, "T: %f", periodo);
        Lcd_Write_String(buffer);
        Lcd_Set_Cursor(2,1);
        sprintf(buffer, "F: %u", frecuencia);
        Lcd_Write_String(buffer);
        __delay_ms(100);
    }
}

void __interrupt() INT_CCP1() { // Interrupcion CCP1
    if (PIR1bits.CCP1IF == 1) {
        valor_pasos = (CCPR1H << 8) + CCPR1L;
        TMR1H = 0x00;
        TMR1L = 0x00;
        periodo = valor_pasos * 0.000000666; // t_avance = (4/Fosc) * Preescaler
        frecuencia = 1 / periodo; // f = 1 / T
        PIR1bits.CCP1IF = 0;
    }
}
