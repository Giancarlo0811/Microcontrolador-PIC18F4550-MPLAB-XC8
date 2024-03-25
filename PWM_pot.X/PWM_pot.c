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
#include "map_function.h"

void main(void) {
    ADCON1 = 0x0E; // Configura el pin RA0 como analogico
    ADCON0 = 0x00; // Selecciona el canal 0 del ADC
    ADCON2 = 0x8F; // Configura el tiempo de adquisicion
    ADCON0bits.ADON = 1; // Habilita el conversor
    
    PR2 = 0X3E; // Valor del periodo para freq = 12Khz
    CCPR1L = 0; // Inicia el CCP1 en 0
    TRISCbits.TRISC2 = 0; // Pin C2 como salida
    T2CON = 0x03; // Configuracion Timer 2
    CCP1CON = 0x0C; // Configuracion del CCP1 en modo PWM
    TMR2 = 0; // Timer 2 en 0
    T2CONbits.TMR2ON = 1; // Timer 2 ON
    
    while (1) {
        ADCON0bits.GO_DONE = 1;
        while (ADCON0bits.GO_DONE == 1);
        int valor_adc = ADRES;
        unsigned char valor_pwm = map(valor_adc, 0, 1023, 0, 250); // 0-250
        // Funcion map (valor, valor min, valor max, valor min salida, valor max salida)
        CCPR1L = (valor_pwm >> 2);
    }
}

