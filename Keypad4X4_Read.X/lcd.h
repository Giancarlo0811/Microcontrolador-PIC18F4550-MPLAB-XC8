#include <xc.h>
#define _XTAL_FREQ 48000000

//#define USE_CGRAM_LCD

#define RS LATBbits.LB2
#define EN LATBbits.LB3
#define D4 LATBbits.LB4
#define D5 LATBbits.LB5
#define D6 LATBbits.LB6
#define D7 LATBbits.LB7

#define RS_DIR TRISBbits.TRISB2
#define EN_DIR TRISBbits.TRISB3
#define D4_DIR TRISBbits.TRISB4
#define D5_DIR TRISBbits.TRISB5
#define D6_DIR TRISBbits.TRISB6
#define D7_DIR TRISBbits.TRISB7

void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear(void);
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init(void);
void Lcd_Write_Char(char a);
void Lcd_Write_String(const char *a);
void Lcd_Shift_Right(void);
void Lcd_Shift_Left(void);
void Lcd_Blink(void);
void Lcd_NoBlink(void);

#ifdef USE_CGRAM_LCD
void Lcd_CGRAM_CreateChar(char add, const char* chardata);
void Lcd_CGRAM_Init(void);
void Lcd_CGRAM_Close(void);
#endif