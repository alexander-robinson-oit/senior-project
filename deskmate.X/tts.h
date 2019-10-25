////////////////////////////////////////////////////////////////////////////////
// tts.h
// Author: Alex Robinson
// Date: 4/6/2019
//
// This file contains the functions for the text-to-speech module of the
// DeskMate. Communications are performed through SPI, so implementations will
// use that communication format. Implementations can be found in tts.c
////////////////////////////////////////////////////////////////////////////////


#ifndef TTS_H
#define	TTS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    void tts_say(char string[]);
    void tts_stop();
    void tts_select_voice(int voice);
    void tts_volume(int volume);
    void tts_speed(int speed);
    void tts_default();
    void tts_demo();
    void tts_wait_for_idle();
    void tts_max_volume();
    static int idle();

#ifdef	__cplusplus
}
#endif

#endif	/* TTS_H */

