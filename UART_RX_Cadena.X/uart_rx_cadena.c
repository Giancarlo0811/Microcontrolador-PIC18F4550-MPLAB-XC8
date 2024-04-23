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
#include <string.h>

#include "uart.h"

char cadena[20]; // almacena la cadena recibida por el puerto serial


void main(void) {
    ADCON1bits.PCFG = 0x0F;
    TRISBbits.RB0 = 0;
    LATBbits.LB0 = 0;
    Uart_Init(9600);
    
    while (1) {
        if (Uart_Available() > 0) { // verifica si se recibio la cadena
            Uart_Read_String(cadena, 20); // lee la cadena recibida y la almacena
            
            Uart_Send_String("Cadena Recibida: ");
            Uart_Send_String(cadena);
            Uart_Send_String("\r\n");
            
            if (!strcmp(cadena, "encender")) { // si la cadena es encender, enciende el led
                LATBbits.LB0 = 1;
                Uart_Send_String("Led Encendido\r\n");
            }
            if (!strcmp(cadena, "apagar")) { // si la cadena es apagar, apaga el led
                LATBbits.LB0 = 0;
                Uart_Send_String("Led Apagado\r\n");
            }
            Uart_Send_String("\r\n");
        }
    }
}
