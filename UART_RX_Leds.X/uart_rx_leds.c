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

#include "uart.h" // liberia modulo USART

char dato_rx; // Almacena el dato recibido

void main(void) {
    ADCON1bits.PCFG = 0x0F;
    TRISBbits.RB2 = 0; // pin RB2 como salida
    TRISBbits.RB3 = 0; // pin RB3 como salida
    LATBbits.LB2 = 0;
    LATBbits.LB3 = 0;
    
    Uart_Init(9600); // inicializa la comunicacion serial a 9600 baudios
    
    Uart_Send_String("Encender LED 1: a\r\n");
    Uart_Send_String("Apagar LED 1: b\r\n");
    Uart_Send_String("Encender LED 2: c\r\n");
    Uart_Send_String("Apagar LED 2: d\r\n");
    Uart_Send_String("\r\n");
    
    while (1) {
        if (Uart_Available() > 0) { // verifica si se ha recbido datos
            dato_rx = Uart_Read();
            
            switch(dato_rx) {
                case 'a':
                    LATBbits.LB2 = 1;
                    Uart_Send_String("LED 1 Encendido\r\n");
                    break;
                case 'b':
                    LATBbits.LB2 = 0;
                    Uart_Send_String("LED 1 Apagado\r\n");
                    break;
                case 'c':
                    LATBbits.LB3 = 1;
                    Uart_Send_String("LED 2 Encendido\r\n");
                    break;
                case 'd':
                    LATBbits.LB3 = 0;
                    Uart_Send_String("LED 2 Apagado\r\n");
                    break;
            }
        }
    }
}
