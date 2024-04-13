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

#include "lcd.h"                                // Libreria de la pantalla lcd
#include "kbd4x4.h"                             // Libreria del teclado matricial 4x4

char tecla;                                     // Almacena el valor de la tecla presionada

void main()
{
    ADCON1bits.PCFG = 0x0F;                     // Coloca todos los pines como digitales
    Keypad_Init();                              // Inicializa el teclado matricial 4x4
    Lcd_Init();                                 // Inicializa la pantalla lcd
    
    Lcd_Set_Cursor(1,1);                        // Muestra mensaje inicial en la lcd
    Lcd_Write_String("Tecla: ");
    
    while(1)
    {
        tecla = Keypad_Get_Char();              // Lee el dato de la tecla presionada
        if(tecla != 0)                          // Verifica si se ha presionado alguna tecla
        {
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Tecla: ");
            Lcd_Write_Char(tecla);              // Muestra el valor de la tecla presionada
        }
    }
}