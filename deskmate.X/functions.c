////////////////////////////////////////////////////////////////////////////////
// functions.c
// Author: Alex Robinson
// Date: 3/5/2019
//
// This file holds the implementations of the functions defined in functions.h.
// These functions provide the core functionality of the Deskmate project and
// will be used throughout the program.
////////////////////////////////////////////////////////////////////////////////

#define _SUPPRESS_PLIB_WARNING

#include "functions.h"
#include "lcd.h"
#include "timer.h"
#include <xc.h>
#include <plib.h>

void init()
{
    //SYSTEMConfigPerformance(SYSCLK_FREQ);
    init_uart();
    init_port_d_digital_output();
    init_port_e_digital_output();
    //init_spi();
    lcd_init();
    //delay_s(3);
    lcd_write_string("Initialization  complete");
}

static void init_port_d_digital_output()
{
    PORTSetPinsDigitalOut(IOPORT_D, BIT_0 | BIT_1 | BIT_2 | BIT_3 );
    PORTDCLR = 0xFF0;
    TRISD &= 0xFF0;
}

static void init_port_e_digital_output()
{
    PORTSetPinsDigitalOut(IOPORT_E, BIT_2 | BIT_3 | BIT_4);
}

// init_interrupt()
// This function will initialize interrupt functionality in single-
// vector mode. This is done with an interrupt handling function
// in mind that will also be implemented.
//static void init_interrupts()
//{
//    INTEnableSystemSingleVectoredInt();  // Enables system multi-vector interrupts
//    INTEnableInterrupts();
//}

static void init_timers()
{
    timer_1_init();
    timer_2_init();
}

// init_spi()
// This function initializes SPI functionality intended for the
// Emic 2 text-to-speech module. Steps for initialization are
// from the family reference manual. Transmitting data from the
// SPI is done by writing the SPIxBUF.
static void init_spi()
{
    int tempData;
    
    // Disable interrupts
    IEC0CLR = _IEC0_SPI1RXIE_MASK | _IEC0_SPI1TXIE_MASK | _IEC0_SPI1EIE_MASK;
    
    // Stop and reset the SPI module by clearing the ON bit
    SPI1CONCLR = _SPI1CON_ON_MASK;
    
    // Clear the recieve buffer
    tempData = SPI1BUF;
    
    // Write the Baud Rate register
    SPI1BRG = 0x103;
    
    // Clear the SPIROV bit
    SPI1STATCLR = _SPI1STAT_SPIROV_MASK;
    
    // Write the deisred settings to the SPIxCON register with MSTEN = 1
    SPI1CONSET = _SPI1CON_MSTEN_MASK;
    
    // Enable SPI operation by setting the ON bit
    SPI1CONSET = _SPI1CON_ON_MASK;
}

// The following SPI-related functions are kept for legacy purposes

/*

static void spi_send_string(char string[])
{
    char send = string[0];  // First get the first char
    
    while (send != '\0')
        spi_send_char(send);    // Loop through the entire string
}

static void spi_send_char(char send)
{
    SPI1BUF = send;                         // Load transmit data
    SPI1STATCLR = _SPI1STAT_SPITBE_MASK;    // Clear the TBE indicator
    spi_wait_for_tbe();                     // Wait for TBE to be set
}

static void spi_wait_for_tbe()
{
    while (!(SPI1STAT & _SPI1STAT_SPITBE_MASK)); // Wait for TBE == 1
}

 */

// init_uart()
// This function initializes UART functionality for the TTS module
static void init_uart()
{
    // Family Reference manual section 21.4 UART CONFIGURATION
    // Section 21.5.3 UART TRANSMITTER SETUP
    // Section 21.6.0.4 Setup for UART Reception
    
    U1MODESET = _U1MODE_BRGH_MASK;    // Set BRGH for more accurate BRG baud rate
    U1BRG = 0x82;   // BRG value to generate ~9600 bps
    U1STA = 0;
    U1MODESET = _U1MODE_ON_MASK;
    U1STASET = 0x1400;
}

void uart_enable()
{
    U1MODESET = _U1MODE_ON_MASK;
}

void uart_disable()
{
    U1MODECLR = _U1MODE_ON_MASK;
}

// uart_send_char()
// Takes in a character as input value and sends that
// character through the UART channel.
void uart_send_char(char send)
{
//    while (uart_tbuf_full() == 1);  // Only transmit when buffer has room
//    // load U1TXREG with character
//    U1TXREG = send;
    WriteUART1(send);
}

// uart_send_string()
// Takes in a character string as input and sends the
// string one character at a time through the UART
// channel.
// NOTE: Input string must be null char terminated.
void uart_send_string(char string[])
{
    // uart_send_char() and wait for TXBF == 0
//    int iter = 0;
//    while (string[iter] != '\0')
//    {
//        uart_send_char(string[iter++]);
//    }
    putsUART1(string);
}

// uart_check_rbuf_full()
// Polls the RXDA bit (UxSTA<0>) and returns value.
int uart_rbuf_full()
{
    return (U1STA & _U1STA_URXDA_MASK);
}

// uart_tbuf_full()
// Polls the TXBF bit (U1STA<9>) and returns value.
int uart_tbuf_full()
{
    return (U1STA & _U1STA_UTXBF_MASK);
}

char uart_read_rbuf()
{
    char temp = U1RXREG;
    return temp;
}