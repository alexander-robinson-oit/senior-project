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

void lcd_cmd(char cmdout)
{
    lcdport = cmdout;
    RS = 0;
    RW = 0;
    EN = 1;
    timer_1_wait_ms(10);
    EN = 0;
}

void lcd_data(char dataout)
{
    lcdport = dataout;
    RS = 1;
    RW = 0;
    EN = 1;
    timer_1_wait_ms(10);
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
    lcd_cmd(0x38);  // Config LCD in 8-bit, 2 line, and 5x8 font
    lcd_cmd(0x0C);  // Display on and cursor off
    lcd_cmd(0x01);  // Clear display screen
    lcd_cmd(0x06);  // Increment cursor
    lcd_cmd(0x80);  // Set cursor position to 1st line 1st column
}

void lcd_write_char(char a)
{
    RS = 1; // Set register to data register
    lcd_data(a); // Give the port the data
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
    lcdport = 0;
    TRISDSET = 0x80; // Make RD7 an input temporarily
    RS = 0;
    RW = 1;
    while (TRISDbits.TRISD7 == 1);
    RW = 0;
    TRISDCLR = 0x80;
    lcdport = 0;
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