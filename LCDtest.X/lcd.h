//////////////////////////////////
// lcd.h
// Author: Alex Robinson
// Date: 1/23/19
//
// This file has the define macros for each of
// the corresponding characters and commands
// on the Adafruit LCD. This will also contain
// operational information for the LCD.
// Processor used is the PIC32MX340F512H.
//////////////////////////////////

// LCD DDRAM address diagram based on physical display (in hex)
// /-----------------------\
// |00|01|02|03|04|05|06|07|
// |--+--+--+--+--+--+--+--|
// |40|41|42|43|44|45|46|47|
// \-----------------------/

// KEY INFORMATION
// LCD has two 8-bit registers, instruction register (IR)
// and data register (DR). IR stores instruction codes,
// such as display clear and cursor shift, and address
// information for display data RAM (DDRAM) and 
// character generator RAM (CGRAM).
//
// The LCD has a busy flag (BF) that indicates internal
// operation mode. When BF = 1, next instruction will not
// be accepted. When RS = 0 and R/W = 1, BS is output to
// DB7. When reading BS, make sure DB7 is set to input.
// 
// DDRAM is 80 (0x67) characters in length. This means
// that different display modes can use shift left and
// shift right to "tab" between different info displays.
// Check Page 11 of HD44780U Datasheet for details.
//
// Example of operation with instruction writing is on
// Page 43 of the HD44780U Datasheet.


#ifndef LCD_H
#define	LCD_H
#include <xc.h>

// CHANGE THE IR COMMANDS TO THE PORT BEING USED BY THE MCU
#define IR LATD
#define IRSET LATDSET
#define IRCLR LATDCLR

#define RS PORTDbits.RD10
#define RW PORTDbits.RD9
#define EN PORTDbits.RD8
#define D0 PORTDbits.RD7
#define D1 PORTDbits.RD6
#define D2 PORTDbits.RD5
#define D3 PORTDbits.RD4
#define D4 PORTDbits.RD3
#define D5 PORTDbits.RD2
#define D6 PORTDbits.RD1
#define D7 PORTDbits.RD0

#define INCREMENT_POSITION 1
#define DECREMENT_POSITION 0
#define SHIFT 1
#define NO_SHIFT 0
#define DISPLAY_ON 1
#define DISPLAY_OFF 0
#define CURSOR_ON 1
#define CURSOR_OFF 0
#define BLINK_ON 1
#define BLINK_OFF 0
#define DISPLAY_SHIFT 1
#define CURSOR_SHIFT 0
#define SHIFT_RIGHT 1
#define SHIFT_LEFT 0
#define EIGHT_BIT 1
#define FOUR_BIT 0
#define TWO_LINES 1
#define ONE_LINE 0
#define FIVE_BY_TEN 1
#define FIVE_BY_EIGHT 0

// LETTER CHARACTERS ///
#define CHAR_A 0b01000001
#define CHAR_B 0b01000010
#define CHAR_C 0b01000011
#define CHAR_D 0b01000100
#define CHAR_E 0b01000101
#define CHAR_F 0b01000110
#define CHAR_G 0b01000111
#define CHAR_H 0b01001000
#define CHAR_I 0b01001001
#define CHAR_J 0b01001010
#define CHAR_K 0b01001011
#define CHAR_L 0b01001100
#define CHAR_M 0b01001101
#define CHAR_N 0b01001110
#define CHAR_O 0b01001111
#define CHAR_P 0b01010000
#define CHAR_Q 0b01010001
#define CHAR_R 0b01010010
#define CHAR_S 0b01010011
#define CHAR_T 0b01010100
#define CHAR_U 0b01010101
#define CHAR_V 0b01010110
#define CHAR_W 0b01010111
#define CHAR_X 0b01011000
#define CHAR_Y 0b01011001
#define CHAR_Z 0b01011010
////////////////////////

// NUMBER CHARACTERS ///
#define CHAR_0 0b00110000
#define CHAR_1 0b00110001
#define CHAR_2 0b00110010
#define CHAR_3 0b00110011
#define CHAR_4 0b00110100
#define CHAR_5 0b00110101
#define CHAR_6 0b00110110
#define CHAR_7 0b00110111
#define CHAR_8 0b00111000
#define CHAR_9 0b00111001
////////////////////////

// SPECIAL CHARACTERS ////////////////
#define CHAR_COLON           0b00111010
#define CHAR_QUESTIONMARK    0b00111111
#define CHAR_SPACE           0b00100000
#define CHAR_PERIOD          0b00101110
//////////////////////////////////////

// LCD FUNCTION DEFINITIONS //
void lcd_port(char a);
void lcd_cmd(char a);
void lcd_clear();
void lcd_set_cursor(char a, char b);
void lcd_init();
void lcd_write_char(char a);
void lcd_write_string(char *a);
void lcd_shift_right();
void lcd_shift_left();
void lcd_wait_for_busy();

#endif	/* LCD_CHARACTERS_H */

