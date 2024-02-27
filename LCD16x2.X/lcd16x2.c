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

int v = 1023;
float t = 24.32; 
char buffer[20];

const char figura_1[8] = {0x0A, 0x0A, 0x0A, 0x00, 0x11, 0x11, 0x0E, 0x00};
const char figura_2[8] = {0x04, 0x11, 0x0E, 0x04, 0x04, 0x0A, 0x11, 0x00};

void main(void) {
    ADCON1bits.PCFG = 0x0F; // colocar pines como digitales
    Lcd_Init(); // inicializar pantalla LCD
    
    Lcd_CGRAM_Init(); // acceder a la CGRAM
    Lcd_CGRAM_CreateChar(0, figura_1); // almacenar caracter 1 en la posicion 0 de la CGRAM
    Lcd_CGRAM_CreateChar(1, figura_2); // almacenar caracter 2 en la posicion 1 de la CGRAM
    Lcd_CGRAM_Close(); // salir de la CGRAM
    Lcd_Clear(); // limpiar pantalla 
    
    while (1) {
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Test LCD 16x2");
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_String("PIC18F4550");
        Lcd_Set_Cursor(2, 12);
        Lcd_Blink();
        __delay_ms(2000);
        Lcd_NoBlink();
        Lcd_Clear();
        __delay_ms(500);
        
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("CGRAM Caracteres");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_Char(0);
        Lcd_Write_Char(1);
        __delay_ms(1500);
        Lcd_Clear();
        __delay_ms(500);
        
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Hola");
        __delay_ms(500);
        for (char i = 0; i < 15; i++) {
            Lcd_Shift_Right();
            __delay_ms(400);
        }
        __delay_ms(400);
        for (char i = 0; i < 15; i++) {
            Lcd_Shift_Left();
            __delay_ms(400);
        }
        Lcd_Clear();
        __delay_ms(500);
        
        Lcd_Set_Cursor(1,1);
        sprintf(buffer, "Int: %u", v); // convertir tipo int a string
        Lcd_Write_String(buffer);
        Lcd_Set_Cursor(2,1);
        sprintf(buffer, "Float: %0.2f", t); // convertir tipo float a string
        Lcd_Write_String(buffer);
        __delay_ms(1500);
        Lcd_Clear();
        __delay_ms(200);
    }
}
