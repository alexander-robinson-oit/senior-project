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

// DEVCFG3
// USERID = No Setting

// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_16         // PLL Multiplier (16x Multiplier)
#pragma config FPLLODIV = DIV_32        // System PLL Output Clock Divider (PLL Divide by 32)

// DEVCFG1
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = HS             // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = ON            // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = ON              // Watchdog Timer Enable (WDT Enabled)

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

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