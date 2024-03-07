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
    ADCON1 = 0x0E; // Vref = VSS y GND, Configuracion de entradas analogicas
    ADCON0 = 0x00; // Seleccion del canal, Habilitacion del convertidor
    ADCON2 = 0x8F; // Tiempo de adquisicion, Justificacion hacia la derecha
    ADCON0bits.ADON = 1; // Enciende el conversor
    
    TRISD = 0x00;
    TRISE = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    
    while (1) {
        ADCON0bits.GO_DONE = 1; // inicia la conversion
        while (ADCON0bits.GO_DONE == 1); // espera a que termine la conversion
        LATD = ADRESL; // muestra el dato de la parte baja en el puerto D
        LATE = ADRESH; // muestra el dato de la parte alta en el puerto E
        __delay_ms(10);
        
    }
}
