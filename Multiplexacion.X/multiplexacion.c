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

#define DISPLAY_1_DIR TRISBbits.RB0
#define DISPLAY_2_DIR TRISBbits.RB1

#define DISPLAY_1_PIN LATBbits.LB0
#define DISPLAY_2_PIN LATBbits.LB1

unsigned char display[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 
                            0x7D, 0x07, 0x7F, 0x6F}; // catodo comun
unsigned char unidades, decenas;

void main(void) {
    ADCON1bits.PCFG = 0x0F;
    DISPLAY_1_DIR = 0;
    DISPLAY_2_DIR = 0;
    TRISD = 0x00;
    LATD = 0x00;
    DISPLAY_1_PIN = 0;
    DISPLAY_2_PIN = 0;
    
    while (1) {
        for (decenas = 0; decenas < 10; decenas++) {
            for (unidades = 0; unidades < 10; unidades++) {
                for (int i = 0; i < 20; i++) {
                    DISPLAY_1_PIN = 1;
                    DISPLAY_2_PIN = 0;
                    LATD = display[unidades];
                    __delay_ms(4);

                    DISPLAY_2_PIN = 1;
                    DISPLAY_1_PIN = 0;
                    LATD = display[decenas];
                    __delay_ms(4);
                }
            }
        }
    }
}
