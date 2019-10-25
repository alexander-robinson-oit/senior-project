////////////////////////////////////////////////////////////////////////////////
// tts.c
// Author: Alex Robinson
// Date: 4/6/2019
//
// This file contains the implementations for the text-to-speech module of the
// DeskMate. Communications are performed through SPI, so implementations will
// use that communication format. Definitions can be found in tts.h
////////////////////////////////////////////////////////////////////////////////

#include "tts.h"
#include "functions.h"
#include <xc.h>

void tts_say(char string[])
{             
    tts_stop();
    uart_send_char('S');        // 'S' char initiates speaking string
    uart_send_string(string);   // Send the actual string contents
    uart_send_char(13);         // '.' char ends the speaking string
    tts_wait_for_idle();
}

void tts_stop()
{
    //tts_wait_for_idle();
    uart_send_char('X');         // 'X' char stops playback during message
    uart_send_char(13);
    tts_wait_for_idle();
}

void tts_select_voice(int voice)
{
    //tts_wait_for_idle();
    if (voice >= 0 && voice <= 8)           // If voice invalid, do nothing
    {
        uart_send_char('N');                 // 'N' char signals voice change
        uart_send_char((char)(voice + 30));  // Convert selection to ASCII char
        uart_send_char(13);
    }
    tts_wait_for_idle();
}

void tts_volume(int volume)
{
    //tts_wait_for_idle();
    if (volume >= -48 && volume <= 18)      // Boundaries for volume
    {
        uart_send_char('V');
        uart_send_char((char)(volume + 30));
        uart_send_char(13);
    }
    tts_wait_for_idle();
}

void tts_speed(int speed)
{
    //tts_wait_for_idle();
    if (speed >= 75 && speed <= 600)
    {
        uart_send_char('W');
        uart_send_char((char)(speed + 30));
        uart_send_char(13);
    }
    tts_wait_for_idle();
}

void tts_default()
{
    //tts_wait_for_idle();
    uart_send_char('R'); // 'R' char resets to defaults
    uart_send_char(13);
    tts_wait_for_idle();
}

void tts_demo()
{
    //tts_wait_for_idle();
    uart_send_string("D0");
    uart_send_char(13);
    tts_wait_for_idle();
}

void tts_wait_for_idle()
{
    while (idle() != 1);
}

void tts_max_volume()
{
    uart_send_string("V18");
    uart_send_char(13);
    tts_wait_for_idle();
}

static int idle()
{
    while (!(uart_rbuf_full() == 1));
    char rbuf = uart_read_rbuf();
    if (rbuf == ':')
    {
        return 1;
    }
    return 0;
}