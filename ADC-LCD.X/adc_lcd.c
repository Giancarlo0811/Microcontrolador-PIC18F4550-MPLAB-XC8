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

#include "adc.h" // librearia para manejo de ADC
#include "lcd.h" // libreria para control de la pantalla lcd

char buffer[20];
int valor_adc;
float voltaje;

void main(void) {
    ADC_Init(AN0_ANALOG); // inicializar ADC
    Lcd_Init(); // inicializar LCD
    TRISBbits.RB0 = 0;
    LATBbits.LB0 = 0;
    
    while (1) {
        valor_adc = ADC_Read(0);
        voltaje = (float) (valor_adc * 5.0) / 1023.0;
        
        Lcd_Set_Cursor(1,1);
        sprintf(buffer, "ADC: %u", valor_adc);
        Lcd_Write_String(buffer);
        Lcd_Set_Cursor(2,1);
        sprintf(buffer, "Voltaje: %0.2f", voltaje);
        Lcd_Write_String(buffer);
        
        if (voltaje > 4.2) {
            LATBbits.LB0 = 1;
        } else {
            LATBbits.LB0 = 0;
        }
    }    __delay_ms(150);
}
