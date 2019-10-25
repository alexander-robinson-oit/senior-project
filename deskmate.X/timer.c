////////////////////////////////////////////////
// timer.c
// Author: Alex Robinson
//
// This file hold the implementations for timer
// related functions. Definitions can be found
// in timer.h.
////////////////////////////////////////////////

#define _SUPPRESS_PLIB_WARNING

#include "timer.h"
#include "functions.h"
#include <xc.h>
#include <plib.h>

// Legacy prior to plib.h inclusion
void timer_1_init()
{
    T1CON = 0x0;    // Stop timer, clear control register
                    // set prescaler at 1:1, internal PBCLK source
    TMR1 = 0x0;     // Clear out the timer register
}

// Legacy prior to plib.h inclusion
void timer_2_init()
{
    T2CON = 0x0;
    TMR2 = 0x0;
}

void delay_s(unsigned s)
{
    for (s; s > 0; --s)
    {
        delay_ms(1000);
    }
}

void delay_ms(unsigned ms)
{
    // A delay of 1ms given the internal PBCLK at 1MHz is 1000 cycles.
    for (ms; ms > 0; --ms)
    {
        OpenTimer1(T1_ON | T1_PS_1_1, MILLISECOND);     // Turn on timer
        while (ReadTimer1() < ReadPeriod1());           // Wait for T1IF to trigger
        CloseTimer1();                                  // Clear timer register
    }
}

void delay_us(unsigned us)
{
    for (us; us > 0; --us)
    {
        OpenTimer1(T1_ON | T1_PS_1_1, MICROSECOND);
        while (ReadTimer1() < ReadPeriod1());
        CloseTimer1();
    }
}