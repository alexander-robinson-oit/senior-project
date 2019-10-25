///////////////////////////////////////////////////
// timer.h
// Author: Alex Robinson
// 
// This file holds the definitions of timer related
// functions

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    void timer_1_init();
    void timer_2_init();
    void delay_s(unsigned s);
    void delay_ms(unsigned ms);
    void delay_us(unsigned us);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

