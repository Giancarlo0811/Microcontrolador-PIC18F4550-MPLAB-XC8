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
#include <string.h>

#include "lcd.h"                                // Libreria de la pantalla lcd
#include "kbd4x4.h"                             // Libreria del teclado matricial 4x4

#define LED_VERDE_DIR TRISBbits.RB0             // Led de acceso correcto
#define LED_ROJO_DIR  TRISBbits.RB1             // Led de acceso incorrecto

#define LED_VERDE_PIN LATBbits.LB0
#define LED_ROJO_PIN  LATBbits.LB1

char tecla;                                     // Almacena el valor de la tecla presionada
char clave[5];                                  // Almacena la clave ingresada por el usuario
char clave_enter[5] = "0811";                   // Clave para acceder

void main()
{
    ADCON1bits.PCFG = 0x0F;                     // Coloca todos los pines como digitales
    LED_VERDE_DIR = 0;                          // Pin RB0 como salida
    LED_ROJO_DIR = 0;                           // Pin RB1 como salida
    LED_VERDE_PIN = 0;                          // Incializan ambos leds apagados
    LED_ROJO_PIN = 0;
    Keypad_Init();                              // Inicializa el teclado matricial 4x4
    Lcd_Init();                                 // Inicializa la pantalla lcd
    
    while(1)
    {
        int i = 0;                              // Contador para las veces que se pulsa alguna tecla
        Lcd_Set_Cursor(1,2);
        Lcd_Write_String("INGRESAR CLAVE");     // Mensjae de solicitud para ingresar clave
        
        while(i < 4)
        {
            tecla = Keypad_Get_Char();          // Lee el dato de la tecla presionada
            if(tecla != 0)                      // Verifica si se ha presionado alguna tecla
            {
                clave[i] = tecla;               // Almacena cada tecla presionada en el arreglo
                Lcd_Set_Cursor(2,2+i);
                Lcd_Write_Char('*');            // Muestra el '*'
                i++;                            // Incrementa el contador
            }
        }
        __delay_ms(200);
        Lcd_Clear();                            // Limpia la pantalla lcd
        
        if(!strcmp(clave, clave_enter))         // Compara si la clave es la correcta
        {
            LED_VERDE_PIN = 1;
            LED_ROJO_PIN = 0;
            Lcd_Set_Cursor(1,2);
            Lcd_Write_String("CLAVE CORRECTA");
            Lcd_Set_Cursor(2,2);
            Lcd_Write_String("BIENVENIDO!");
            __delay_ms(2000);
        }
        else                                    // Sino es la clave correcta, no permite el acceso
        {
            LED_ROJO_PIN = 1;
            LED_VERDE_PIN = 0;
            Lcd_Set_Cursor(1,6);
            Lcd_Write_String("CLAVE");
            Lcd_Set_Cursor(2,4);
            Lcd_Write_String("INCORRECTA");
            __delay_ms(2000);
        }
        i = 0;                                  // Reinicia el contador
        LED_ROJO_PIN = 0;                       // Apaga ambos leds
        LED_VERDE_PIN = 0;
        Lcd_Clear();                            // Limpia la pantalla lcd
    }
}