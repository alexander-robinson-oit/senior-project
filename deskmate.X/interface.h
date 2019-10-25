/* 
 * File:   interface.h
 * Author: Alex Robinson
 *
 * This file holds the declarations of functions related to the user
 * interface of the DeskMate.
 */

#ifndef INTERFACE_H
#define	INTERFACE_H

#ifdef	__cplusplus
extern "C" {
#endif


    /* Determines input given a register of inputs*/
    int determine_input();
    /* Gather input from user to set timer value */
    int edit_timer_period();
    
    /* Display functions */
    void main_m_display();


#ifdef	__cplusplus
}
#endif

#endif	/* INTERFACE_H */

