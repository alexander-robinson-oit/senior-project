/////////////////////////////////////////////////
// Deskmate
// Author: Alex Robinson
//
// This is the project for the Deskmate, a device
// to assist deskworkers with their productivity.
// This is the main file to the project holding
// the primary operation loop.
/////////////////////////////////////////////////

// PIC32MX340F512H Configuration Bit Settings

// 'C' source line config statements

// DEVCFG3
// USERID = No Setting

// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (PLL Divide by 2)

// DEVCFG1
#pragma config FNOSC = FRCPLL           // Oscillator Selection Bits (Fast RC Osc with PLL)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _SUPPRESS_PLIB_WARNING

#include <xc.h>
#include <sys/attribs.h>
#include <plib.h>
#include "functions.h"
#include "timer.h"
#include "lcd.h"
#include "tts.h"
#include "interface.h"

/* Possible inputs from physical interface */
#define UP          1
#define DOWN        2
#define CONFIRM     3
#define CANCEL      4
#define TIMER1      5
#define TIMER2      6
#define TIMER3      7
#define TIMER4      8

#define ACTIVE      1
#define INACTIVE    0

/* Menu definitions */
#define MAIN_M      1
#define EDIT_TIMER  2

// timer_active will hold either a 1 or a 0 for each timer indicating
// active status.
unsigned int timer_active[4] = { 1, 0, 1, 0 };  

// timer_period will hold the value in seconds that each timer will
// run to before triggering an alert.
unsigned int timer_period[4] = { 5, 35, 10, 123 };

// timer_value will hold the current value in seconds of each timer.
unsigned int timer_value[4] =  { 0, 0, 0, 0 };

/* button_pressed will serve as a debounce and anti-ghosting flag */
unsigned int button_pressed = 0;

/* current_menu holds the menu currently occupied */
int current_menu = MAIN_M;

/* menu_choice is the current selection in the current menu */
int menu_choice = 0;

/* menu depth variable */
int menu_depth = 0;

int current_timer = 0;
int timer_input = 0;

void loop();
void wait_for_second();
void check_inputs();
void handle_timers();
void active_timer_check(unsigned timer);
void timer_trigger(unsigned timer);
void alert(unsigned timer);
void update_system(int input);
void update_display();
void confirm();
void cancel();
char int_to_char(int num);
void reset_states();

int main()
{
    init();
    
    update_display();
    
    while(1)
    {
        loop();
    }
    
    return 0;
}

void loop()
{
    // Wait for one second while polling inputs every 100ms
    wait_for_second();
    
    // Once one second has elapsed, check if each timer equals its period
    handle_timers();
}

void wait_for_second()
{
    unsigned msec = 0;
    for (msec; msec < 20; ++msec)   // Regularly check inputs for activity
    {
        delay_ms(50);
        check_inputs();     // Direct user input takes highest priority
    }
    
}

void check_inputs()
{
    /* Retrieve the input register and send it to the update function */
    int input = PORTD & 0xFF0;
    input >> 4;
    //int input = 1;
    
    update_system(input);
    //update_display();
}

void handle_timers()
{
    unsigned timer = 0;
    for (timer; timer < 4; ++timer)
    {
        active_timer_check(timer);
    }
}

void active_timer_check(unsigned timer)
{
    if (timer_active[timer] == ACTIVE)
    {
        if (timer_value[timer] >= timer_period[timer]) timer_trigger(timer);
        else ++timer_value[timer];
    }
}

void timer_trigger(unsigned timer)
{
    timer_value[timer] = 0;
    alert(timer);
}

void alert(unsigned timer)
{
    switch (timer)
    {
        case 0: // Food timer
            lcd_write_string("HABIT 1 ALERT");
            tts_say("Habit one alert.");
            delay_s(1);
            break;
        case 1: // Water timer
            lcd_write_string("HABIT 2 ALERT");
            tts_say("Habit two alert.");
            delay_s(1);
            break;
        case 2: // Stretch timer
            lcd_write_string("HABIT 3 ALERT");
            tts_say("Habit three alert.");
            delay_s(1);
            break;
        default:
            lcd_write_string("HABIT 4 ALERT");
            tts_say("Habit four alert.");
            delay_s(1);
            break;
    }
    update_display();
}

void update_system(int input)
{
    /* if there is an input... */
    if (input > 0)
    {
        /* and if there wasn't a button pressed before... */
        if (button_pressed == 0)
        {
            /* This is the core of the input checker; update the system for button press */
            button_pressed = 1;
            /* First, decipher the input pressed */
            int result = determine_input();
            /* System will be updated based on the button pressed */
            switch (result)
            {
                case UP:
                    if (current_menu != MAIN_M)
                        timer_input = (++timer_input % 60);
//                    lcd_write_string("UP");
                    break;
                case DOWN:
                    if (current_menu != MAIN_M)
                    {
                        if (timer_input == 0)
                            timer_input = 59;
                        else
                            timer_input = (--timer_input % 60);
                    }
                    //lcd_write_string("DOWN");
                    break;
                case CONFIRM:
                    //lcd_write_string("CONFIRM");
                    /* This will be a bit more complicated */
                    if (current_menu != MAIN_M)
                    {
                        switch (menu_depth)
                        {
                            case 0:
                                timer_period[current_timer] = timer_input;
                                timer_input = 0;
                                ++menu_depth;
                                break;
                            case 1:
                                timer_period[current_timer] += (timer_input * 60);
                                timer_input = 0;
                                ++menu_depth;
                                break;
                            case 2:
                                timer_period[current_timer] += (timer_input * 360);
                                timer_input = 0;
                                menu_depth = 0;
                                current_menu = MAIN_M;
                                /* If all values were zero then we don't start the timer */
                                if (timer_period[current_timer] != 0)
                                    timer_active[current_timer] = ACTIVE;
                                else
                                    timer_active[current_timer] = INACTIVE;
                                break;
                        }
                    }
                    break;
                case CANCEL:
                    //lcd_write_string("CANCEL");
                    current_menu = MAIN_M;
                    reset_states();
                    break;
                case TIMER1:
                    //lcd_write_string("TIMER1");
                    current_menu = EDIT_TIMER;
                    current_timer = 0;
                    reset_states();
                    break;
                case TIMER2:
                    current_menu = EDIT_TIMER;
                    current_timer = 1;
                    reset_states();
                    break;
                case TIMER3:
                    current_menu = EDIT_TIMER;
                    current_timer = 2;
                    reset_states();
                    break;
                case TIMER4:
                    current_menu = EDIT_TIMER;
                    current_timer = 3;
                    reset_states();
                    break;
            }
            /* Only update display when a button was pressed */
            update_display();
        }
        /* else do nothing */
    }
    /* If no input, set button_pressed to 0 */
    else
        button_pressed = 0;
}

void update_display()
{
    if (current_menu == MAIN_M)
        main_m_display();
    else
    {
        switch (menu_depth)
        {
            case 0:
                lcd_write_string("Seconds?");
                lcd_cursor_position(0, 1);
                lcd_write_char(int_to_char(timer_input / 10));
                lcd_write_char(int_to_char(timer_input % 10));
                break;
            case 1:
                lcd_write_string("Minutes?");
                lcd_cursor_position(0, 1);
                lcd_write_char(int_to_char(timer_input / 10));
                lcd_write_char(int_to_char(timer_input % 10));
                break;
            case 2:
                lcd_write_string("Hours?");
                lcd_cursor_position(0, 1);
                lcd_write_char(int_to_char(timer_input / 10));
                lcd_write_char(int_to_char(timer_input % 10));
                break;
        }
    }
}

void confirm()
{
    /* This function will change context with current menu */
    /* For now, we will just increase the menu_depth */
    if (menu_depth > 5)
        ++menu_depth;
    else
    {
        menu_depth = 0;
        current_menu = MAIN_M;
    }
}

void cancel()
{
    /* This function will also change with current menu */
    /* This will just decrease menu_depth at the moment */
    if (menu_depth > 0)
        --menu_depth;
    else
        current_menu = MAIN_M;
}

char int_to_char(int num)
{
    return '0' + num;
}

void reset_states()
{
    timer_input = 0;
    menu_depth = 0;
}