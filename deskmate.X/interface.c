/*
 * File: interface.c
 * Author: Alex Robinson
 * 
 * This file contains the definitions of the functions relating to the
 * user interface of the DeskMate
 */

#include <xc.h>
#include "interface.h"
#include "lcd.h"

int determine_input()
{
        if (PORTDbits.RD4 == 1)
            return 1;
        else if (PORTDbits.RD5 == 1)
            return 2;
        else if (PORTDbits.RD6 == 1)
            return 3;
        else if (PORTDbits.RD7 == 1)
            return 4;
        else if (PORTDbits.RD8 == 1)
            return 5;
        else if (PORTDbits.RD9 == 1)
            return 6;
        else if (PORTDbits.RD10 == 1)
            return 7;
        else if (PORTDbits.RD11 == 1)
            return 8;
        else
            lcd_write_string("No button");
}

int edit_timer_period()
{
    return 5;
}

void main_m_display()
{
    lcd_write_string("DeskMate Active Awaiting input");
}