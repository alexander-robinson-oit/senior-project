//////////////////////////////
// functions.c
// Author: Alex Robinson
// Date: 1/31/19
//
// This file contains the implementation of
// the functions defined in lcd.h.
// Processor used is the PIC32MX340F512H.
//////////////////////////////

#include "functions.h"
#include <xc.h>

// Timer information can be found in section 14.3.1 of Family Reference Manual

// Initialization reference for 16 bit timers in section 14.3.4.2
void timer_1_init()
{
    T1CON = 0x0;    // Stops the timer, clears control register,
                    // sets prescaler at 1:1 with internal clock source
    TMR1 = 0x0;     // Clear the timer register
}

void timer_1_wait_ms(unsigned int ms)
{
    PR1 = 0x9C4;       // Load timer with value for 1ms
    
    int loop;
    for (loop = 0; loop < ms; ++loop)   // Loop the count for ms
    {
        T1CONSET = _T1CON_ON_MASK;  // Start timer
        while (IFS0bits.T1IF != 1); // Wait until interrupt flag is triggered
        T1CONCLR = _T1CON_ON_MASK;  // Stop timer
        TMR1 = 0x0;         // Empty timer value
    }
}