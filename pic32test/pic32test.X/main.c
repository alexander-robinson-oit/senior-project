////////////////////////////////////
// pic32test - main.c
// Author: Alex Robinson
// 
// This file serves as the main for a test of the
// Chipkit uC32 microcontroller board.
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

#define MODE 1 // Change this to the desired test mode; 0 = output, 1 = input

//
////////////////////////////////////




////////////////////////////////////
//
// FUNCTION DECLARATIONS
//

void testPortB();
void testPortD();
void testPortE();
void testPortF();
void testPortG();

//
////////////////////////////////////

int main()
{ 
    // Comment out unnecessary tests
//    testPortB();
//    testPortD();
//    testPortE();
//    testPortF();
//    testPortG();
    
    return 0;
}


// Function: testPortB
//
// Parameter(s): TEST_MODE mode
// Return Value: None
//
// This function serves two purposes: testing input capability
// and output capability. When 'mode' is OUTPUT, the pins for
// PORTB accessible externally will be configured for output 
// and then set. When 'mode' is INPUT, pins will be configured
// for input and then, when a signal is detected by any pin,
// the user LED on the board will be set. The analog-capable
// pins of PortB will be ignored in this test.

void testPortB()
{
    if (MODE) // If mode is input
    {
        // Config to input
        TRISBSET = 0x3; // 0b0011;
        ODCBCLR = 0x3;
        
        // Config RF0 for User LED
        TRISFCLR = 0x1; // 0b0001
        ODCFCLR = 0x1;
        LATFCLR = 0x1;
        
        while(1) // Loop forever to test with multimeter
        {
            
            if (0 != (PORTB & 0x3))
                LATFSET = 0x1;
            else
                LATFCLR = 0x1;
        }
    }
    
    else      // If mode is output
    {
        // Config as constant output
        TRISBCLR = 0x3; // 0b0011
        ODCBCLR = 0x3;  
        LATBSET = 0x3;
        
        while(1);   // Loop forever to test with multimeter
    }
}

// Function: testPortD
//
// Parameter(s): TEST_MODE mode
// Return Value: None
//
// This function serves two purposes: testing input capability
// and output capability. When 'mode' is OUTPUT, the pins for
// PORTD accessible externally will be configured for output 
// and then set. When 'mode' is INPUT, pins will be configured
// for input and then, when a signal is detected by any pin,
// the user LED on the board will be set. 
//
// NOTE: Ensure that JP4 has been moved to enable RD4.

void testPortD()
{
    if (MODE) // If mode is input
    {
        // Config to input
        TRISDSET = 0xFFF; // 0b1111 1111 1111;
        ODCDCLR = 0xFFF;
        
        // Config RF0 for User LED
        TRISFCLR = 0x1; // 0b0001
        ODCFCLR = 0x1;
        LATFCLR = 0x1;
        
        while(1) // Loop forever to test with multimeter
        {
            if (0 != (PORTD & 0xFFF))
                LATFSET = 0x1;
            else
                LATFCLR = 0x1;
        }
    }
    
    else      // If mode is output
    {
        // Config as constant output
        TRISDCLR = 0xFFF; // 0b1111 1111 1111
        ODCDCLR = 0xFFF;  
        LATDSET = 0xFFF;
        
        while(1);   // Loop forever to test with multimeter
    }
}

// Function: testPortE
//
// Parameter(s): TEST_MODE mode
// Return Value: None
//
// This function serves two purposes: testing input capability
// and output capability. When 'mode' is OUTPUT, the pins for
// PORTE accessible externally will be configured for output 
// and then set. When 'mode' is INPUT, pins will be configured
// for input and then, when a signal is detected by any pin,
// the user LED on the board will be set. 

void testPortE()
{
    if (MODE) // If mode is input
    {
        // Config to input
        TRISESET = 0xFF; // 0b1111 1111;
        ODCECLR = 0xFF;
        
        // Config RF0 for User LED
        TRISFCLR = 0x1; // 0b0001
        ODCFCLR = 0x1;
        LATFCLR = 0x1;
        
        while(1) // Loop forever to test with multimeter
        {
            if (0 != (PORTE & 0xFF))
                LATFSET = 0x1;
            else
                LATFCLR = 0x1;
        }
    }
    
    else      // If mode is output
    {
        // Config as constant output
        TRISECLR = 0xFF; // 0b1111 1111
        ODCECLR = 0xFF;  
        LATESET = 0xFF;
        
        while(1);   // Loop forever to test with multimeter
    }
}

// Function: testPortF
//
// Parameter(s): TEST_MODE mode
// Return Value: None
//
// This function serves two purposes: testing input capability
// and output capability. When 'mode' is OUTPUT, the pins for
// PORTF accessible externally will be configured for output 
// and then set. When 'mode' is INPUT, pins will be configured
// for input and then, when a signal is detected by any pin,
// the user LED on the board will be set. 
//
// NOTE: RF0 is used exclusively for the User LED LD5, and so
//       will not be tested as an input.

void testPortF()
{
    if (MODE) // If mode is input
    {
        // Config to input
        TRISFSET = 0x7E; // 0b0111 1110;
        ODCFCLR = 0x7E;
        
        // Config RF0 for User LED
        TRISFCLR = 0x1; // 0b0001
        ODCFCLR = 0x1;
        LATFCLR = 0x1;
        
        while(1) // Loop forever to test with multimeter
        {
            if (0 != (PORTF & 0x7F))
                LATFSET = 0x1;
            else
                LATFCLR = 0x1;
        }
    }
    
    else      // If mode is output
    {
        // Config as constant output
        TRISFCLR = 0x7F; // 0b0111 1111
        ODCFCLR = 0x7F;  
        LATFSET = 0x7F;
        
        while(1);   // Loop forever to test with multimeter
                    // With this loop, the User LED LD5 will be constant on
    }
}

// Function: testPortG
//
// Parameter(s): TEST_MODE mode
// Return Value: None
//
// This function serves two purposes: testing input capability
// and output capability. When 'mode' is OUTPUT, the pins for
// PORTG accessible externally will be configured for output 
// and then set. When 'mode' is INPUT, pins will be configured
// for input and then, when a signal is detected by any pin,
// the user LED on the board will be set. 
//
// NOTE: Ensure that JP4, JP6, and JP8 have PortG selected.
//       Also confer with JP5 and JP7 for locations of PortG<7> and <8>.

void testPortG()
{
    if (MODE) // If mode is input
    {
        // Config to input
        TRISGSET = 0x3CC; // 0b0011 1100 1100
        ODCGCLR = 0x3CC;
        
        // Config RF0 for User LED
        TRISFCLR = 0x1; // 0b0001
        ODCFCLR = 0x1;
        LATFCLR = 0x1;
        
        while(1) // Loop forever to test with multimeter
        {
            if (0 != (PORTG & 0x3CC))
                LATFSET = 0x1;
            else
                LATFCLR = 0x1;
        }
    }
    
    else      // If mode is output
    {
        // Config as constant output
        TRISGCLR = 0x3CC; // 0b0011 1100 1100
        ODCGCLR = 0x3CC;  
        LATGSET = 0x3CC;
        
        while(1);   // Loop forever to test with multimeter
    }
}