//////////////////////////////
// lcd.c
// Author: Alex Robinson
// Date: 1/23/19
//
// This file contains the implementation of
// the functions defined in lcd.h.
// Processor used is the PIC32MX340F512H.
//////////////////////////////

#include "lcd.h"
#include "functions.h"

void lcd_port(char a)
{
    D0 = (a & 1 ? 1 : 0);
    D1 = (a & 2 ? 1 : 0);
    D2 = (a & 4 ? 1 : 0);
    D3 = (a & 8 ? 1 : 0);
    D4 = (a & 16 ? 1 : 0);
    D5 = (a & 32 ? 1 : 0);
    D6 = (a & 64 ? 1 : 0);
    D7 = (a & 128 ? 1 : 0);
}

void lcd_cmd(char a)
{
    RS = 0;
    lcd_port(a);
    EN = 1;
    timer_1_wait_ms(5);
    EN = 0;
}

void lcd_clear()
{
    lcd_cmd(1);
    lcd_wait_for_busy();
}

void lcd_set_cursor(char a, char b)
{
    if (a == 1)
        lcd_cmd(0x80 + b);
    else if (a == 2)
        lcd_cmd(0xC0 + b);
    lcd_wait_for_busy();
}

void lcd_init()
{
    
}

void lcd_write_char(char a)
{
    RS = 1; // Set register to data register
    lcd_port(a); // Give the port the data
    EN = 1;     // Data Pulse start
    timer_1_wait_ms(4);
    EN = 0;     // Data Pulse end
    lcd_wait_for_busy();
}

void lcd_write_string(char *a)
{
    int i;
    for (i = 0; a[i] != '\0'; ++i)
        lcd_write_char(a[i]);
}

void lcd_shift_right()
{
    lcd_cmd(0x1C);
    lcd_wait_for_busy();
}

void lcd_shift_left()
{
    lcd_cmd(0x18);
    lcd_wait_for_busy();
}

void lcd_wait_for_busy()
{
    lcd_port(0x0);
    TRISDSET = 0x80; // Make RD7 an input temporarily
    RS = 0;
    RW = 1;
    while (D7 == 1);
    RW = 0;
    TRISDCLR = 0x80;
    lcd_port(0x0);
}



// KEPT FOR REFERENCE
//void lcd_init()
//{
//    lcd_port(0x00); // clear whatever is in the port
//    RS = 0; // Select the command register   
//    timer_1_wait_ms(25);    // Wait the required time
//    // Reset process from LCD datasheet
//    lcd_cmd(0x30);
//    timer_1_wait_ms(5);
//    lcd_cmd(0x30);
//    timer_1_wait_ms(15);
//    lcd_cmd(0x30);  
//    // End of reset process
//    lcd_cmd(0x38);  // Set function with DL = 8-bit, N = 2 lines, font = 5x8
//    lcd_cmd(0x08);  // Display off
//    lcd_cmd(0x01);  // Clear the display
//    lcd_cmd(0x06);  // Entry mode set increment
//    // initialization ends
//    lcd_wait_for_busy();
//    lcd_cmd(0x0C);  // Turn display on, cursor off, blink off
//}