////////////////////////////////////////////////////////////////////////////////
// lcd.c
// Author: Alex Robinson
// 
// This file holds the implementations for the Adafruit LCD using the HD44780U
// LCD controller. Definitions for all functions found within this file can be
// located in lcd.h.
////////////////////////////////////////////////////////////////////////////////

#include "lcd.h"
#include "timer.h"
#include <xc.h>


unsigned char lcd_line;

void lcd_init()                         // Initializing by Instruction
{                                       // from HD44780U datasheet p.45
    delay_ms(100);                      // Delay 100ms to wait for power to rise to 4.5V
    EN = 0;
    RS = 0;
    lcd_send_nibble(COMMAND, 0x3);
    delay_ms(10);
    lcd_send_nibble(COMMAND, 0x3);
    delay_us(125);
    lcd_send_nibble(COMMAND, 0x3);
    delay_ms(1);
    lcd_send_nibble(COMMAND, 0x2);
    delay_ms(1);
    lcd_send_byte(COMMAND, 0x28);       // Function set: 8-bit, 2 lines, 5x8 font
    lcd_send_byte(COMMAND, 0x08);       // Display off
    lcd_send_byte(COMMAND, 0x01);       // Display clear
    lcd_send_byte(COMMAND, 0x06);       // Entry Mode set
    
    // INITIALIZATION OVER
    
    lcd_send_byte(COMMAND, 0x28);       // Function set: 8-bit, 2 lines, 5x8 font
    lcd_send_byte(COMMAND, 0x0E);       // Display on, Cursor on, blinking off
    lcd_send_byte(COMMAND, 0x06);       // Entry mode set
}

static void lcd_send_nibble(unsigned char type, char nibble)
{
    RW = 0;
    RS = type;
    DBCLR = 0x0F;
    DBSET = nibble & 0x0F;
    EN = 1;
    delay_us(1);
    EN = 0;
//    delay_ms(1);    // Delay for busy flag
}
static void lcd_send_byte(unsigned char type, char byte)
{
    lcd_send_nibble(type, byte >> 4);
    lcd_send_nibble(type, byte & 0x0F);
    delay_ms(1);  // Delay for busy flag
}

void lcd_write_char(char character)
{
    lcd_send_byte(DATA, character);
}


////////////////////////////////////////////////////////////////////////////////
// lcd_write_string(char s[])
//
// Stipulations: s[] must be no longer than 32 characters, not including
//               a null character.
// Entry state: LCD is empty or contains data to be changed.
// Exit state: LCD now displays the desired string.
////////////////////////////////////////////////////////////////////////////////
void lcd_write_string(char s[])
{      
    lcd_clear_display();
    
    char pos = s[0];
    int i = 0;
    short col = 0;
    
    while (pos != '\0')
    {
        lcd_write_char(pos);
        ++i;
        pos = s[i];
        if (col == 15) lcd_cursor_position(0, 1);
        ++col;
    }
    
    lcd_cursor_position(0, 0);
}

void lcd_cursor_position(unsigned char x, unsigned char y)
{
    unsigned char address;
    
    if (y == 1)
        address = 0xC0;
    else
        address = 0x80;
    
    address += x;
    lcd_send_byte(COMMAND, address);
}

void lcd_clear_display()
{
    lcd_send_byte(COMMAND, 0x01);
    delay_ms(10);
}