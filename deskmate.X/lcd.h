////////////////////////////////////////////////////////////////////////////////
// lcd.h
// Author: Alex Robinson
// 
// This file holds the definitions of the functions relating to the operation
// of the Adafruit 16x2 LCD powered by the HD44780U LCD controller.
// Implementations of these functions can be found in lcd.c.
////////////////////////////////////////////////////////////////////////////////

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    // Need defines for EN, RS, and PORTD
#define DATA    1
#define COMMAND 0
#define EN      PORTEbits.RE2
#define RS      PORTEbits.RE3
#define RW      PORTEbits.RE4
#define DB      PORTD
#define DBSET   PORTDSET
#define DBCLR   PORTDCLR

    void lcd_init();
    static void lcd_send_nibble(unsigned char type, char nibble);
    static void lcd_send_byte(unsigned char type, char byte);
    void lcd_write_char(char character);
    void lcd_write_string(char s[]);
    void lcd_cursor_position(unsigned char x, unsigned char y);
    void lcd_clear_display();

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

