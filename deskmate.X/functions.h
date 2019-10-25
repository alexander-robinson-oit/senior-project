////////////////////////////////////////////////////////////////////////////////
// functions.h
// Author: Alex Robinson
// Date: 3/5/2019
//
// This file will hold a variety of essential functions for the operation of
// the Deskmate project. Implementations can be found in functions.c.
////////////////////////////////////////////////////////////////////////////////

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#define SYSCLK_FREQ 40000000
#define PBCLK_FREQ  5000000
#define MILLISECOND 5000
#define MICROSECOND 5

#ifdef	__cplusplus
extern "C" {
#endif

    void init();
    static void init_port_d_digital_output();
    static void init_port_e_digital_output();
    //static void init_interrupts();
    static void init_timers();
    static void init_spi();
    static void init_uart();
    void uart_enable();
    void uart_disable();
    void uart_send_char(char send);
    void uart_send_string(char string[]);
    int uart_rbuf_full();
    int uart_tbuf_full();
    char uart_read_rbuf();
    
    /*
    static void spi_send_char(char send);
    static void spi_send_string(char string[]);
    static void spi_wait_for_tbe();
     */

#ifdef	__cplusplus
}
#endif

#endif	/* FUNCTIONS_H */

