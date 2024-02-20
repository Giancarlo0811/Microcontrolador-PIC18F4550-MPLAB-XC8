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

// catodo comun
unsigned char display[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 
                            0x7D, 0x07, 0x7F, 0x6F};
int contador;

void main(void) {
    ADCON1bits.PCFG = 0x0F;
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    TRISD = 0x00;
    LATD = 0x00;
    LATD = display[contador];
    
    while (1) {
        if (PORTBbits.RB0 == 1) { // incrementa contador
            // antirebote
            while(PORTBbits.RB0 == 1);
            __delay_ms(20);
            
            for (contador = 0; contador < 10; contador++) {
                LATD = display[contador];
                __delay_ms(500);
            }
            
        }
        if (PORTBbits.RB1 == 1) { // decrementa contador
            //antirebote
            while(PORTBbits.RB1 == 1);
            __delay_ms(20);
            
            for (contador = 9; contador >= 0; contador--) {
               LATD = display[contador];
               __delay_ms(500);
            }
        }
        
        
        /* CODIGO ALTERNATIVO PARA INCREMENTAR/DECREMENTAR 
           DE UNO EN UNO USANDO PULSADORES
        
        if (PORTBbits.RB0 == 1) { incrementa
            while(PORTBbits.RB0 == 1);
            __delay_ms(20);
            
            contador++;
            LATD = display[contador];
            if (contador > 9) {
                contador = 9;
                LATD = display[contador];
            }
        }
        
        if (PORTBbits.RB1 == 1) { decrementa
            while(PORTBbits.RB1 == 1);
            __delay_ms(20);
            
            contador--;
            LATD = display[contador];
            if (contador == -1) {
                contador = 0;
                LATD = display[contador];
            }
        }
        */
    }
}
