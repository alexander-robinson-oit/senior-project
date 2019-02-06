////////////////////////////////////
// LCDtest - main.c
// Author: Alex Robinson
// Created: 1/10/19
// 
// This file serves as the main for a test of the
// Adafruit standard LCD.
// Processor is PIC32MX340F512H.
////////////////////////////////////

////////////////////////////////////
//
// CONFIGBITS
//

// DEVCFG2
#pragma config FPLLIDIV = DIV_2     // PLL Input Divider: 2x Divider (8 MHz / 2 = 4 MHz)
#pragma config FPLLMUL = MUL_16     // PLL Multiplier: 16x Multiplier (4 MHz * 15 = 64 MHz)
#pragma config FPLLODIV = DIV_32    // System PLL Output Clock Divider: PLL Divide by 32 (2 MHz)

// DEVCFG1
#pragma config FNOSC = PRIPLL       // Oscillator Selection Bits: Primary Osc (XT,HS,EC)
#pragma config FSOSCEN = OFF        // Secondary Oscillator Enable: Off
#pragma config POSCMOD = HS         // Primary Oscillator Configuration: High Speed (HS)
#pragma config FCKSM = CSDCMD       // Clock Switching and Monitor Selection: Clock Switch Disabled, FSCM Disabled
#pragma config FWDTEN = OFF         // Watchdog Timer Enable: WDT Disabled

// DEVCFG0
#pragma config ICESEL = ICS_PGx2    // ICE/ICD Comm Channel Select: ICE EMUC2/EMUD2 pins shared with PGC2/PGD2

//
////////////////////////////////////

////////////////////////////////////
//
// INCLUDES AND DEFINES
//

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "functions.h"

//
////////////////////////////////////

void setup();
void print(char string[]);
void print_char(char character);
void string_copy(char str1[], char str2[]);

int main()
{
    setup();
    
    char * string = "Hello";
    lcd_set_cursor(1, 1);
    lcd_write_string(string);
    while(1);
    
    return 0;
}

void setup()
{
    // Set up port D as non-open drain output
    PORTD = 0x0;
    TRISDCLR = 0xFFF;
    ODCDCLR = 0xFFF;
    PORTE = 0;
    TRISE = 0;
    ODCE = 0;
    
    timer_1_init();
    lcd_init();
}