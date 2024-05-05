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

#include "uart.h" // Libreria para el modulo USART

char dato_rx;

void main(void) {
    ADCON1bits.PCFG = 0x0F; // coloca todos los pines como digitales
    TRISBbits.RB0 = 0;
    TRISBbits.RB1 = 0;
    LATBbits.LB0 = 0;
    LATBbits.LB1 = 0;
    
    Uart_Init(9600); // Inicializa la comunicacion serial a 9600 baudios
    
    while (1) {
        if (Uart_Available() > 0) { // Verifica si se ha recibido datos por bluetooth
            dato_rx = Uart_Read(); // Lee el dato recibido y lo almacena
            
            switch(dato_rx) {
                case 'a':
                    LATBbits.LB0 = 1; // enciende led 1
                    break;
                case 'b':
                    LATBbits.LB0 = 0; // apaga led 1
                    break;
                case 'c':
                    LATBbits.LB1 = 1; // enciende led 2
                    break;
                case 'd':
                    LATBbits.LB1 = 0; // apaga led 2
                    break;
            }
        }
    }
}
