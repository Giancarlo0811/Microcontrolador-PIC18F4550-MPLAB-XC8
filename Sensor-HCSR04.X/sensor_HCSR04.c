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

#include "lcd.h" // libreria para el control del LCD
#include "hc_sr04.h" // libreria para sensor ultrasonico
#include "float_str.h" // libreria para convertir float a string

char buffer[20];

void main(void) {
    ADCON1bits.PCFG = 0x0F; // coloca todos los pines como digitales
    TRISBbits.RB0 = 0;
    TRISBbits.RB1 = 0;
    LATBbits.LB0 = 0;
    LATBbits.LB1 = 0;
    HCSR04_Init(); // inicializa el sensor ultrasonico
    Lcd_Init();
    
    while (1) {
        float distancia = HCSR04_Get_Distance(); // obtener la distancia
        Lcd_Clear();
        Lcd_Set_Cursor(1,2);
        Lcd_Write_String("Sensor HC-SR04");
        Lcd_Set_Cursor(2,1);
        floattostr(distancia, buffer, 2); // convierte float a string
        Lcd_Write_String("Dist: ");
        Lcd_Write_String(buffer); // Imprime el valor de la distancia
        Lcd_Write_String(" cm");
        
        if (distancia < 10) {
            LATBbits.LB0 = 0;
            LATBbits.LB1 = 1;
        } else {
            LATBbits.LB0 = 1;
            LATBbits.LB1 = 0;
        }
        __delay_ms(200);
    }
}
