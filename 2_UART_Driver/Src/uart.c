/*
 * uart.c
 *
 *  Created on: Jul 19, 2023
 *      Author: luong
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

void clock_init(void);
void uart0_tx_init(void);
void uart0_write(int ch);


void clock_init(void)
{
    // Set the clocking to run directly from the external crystal/oscillator.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
}

void uart0_tx_init(void)
{
    /****** Configure UART GPIO Pin ******/

    /* Enable UART0:
    Use UART0 because the ICDI chip connects to PA0 (U0RX) and PA1 (U0TX) pin
    When plugged in to a PC, the device enumerates as a debugger and a virtual COM port
    */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    /* Enable GPIOA:
    Because GPIOA contains the UART0 TX and RX pin
    */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    /* Configure the GPIO pin muxing for the UART function.*/
    GPIOPinConfigure(GPIO_PA1_U0TX);
    //GPIOPinConfigure(GPIO_PA0_U0RX);

    /* Set PA1 alternate function type to U0Tx
    Since GPIO A0 and A1 are used for the UART function, they must be
    configured for use as a peripheral function (instead of GPIO).
    */
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_1);
    //GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);


    /* Configure UART
    Configure the UART for 115,200, 8-N-1 operation.
    This function uses SysCtlClockGet() to get the system clock
    frequency.  This could be also be a variable or hard coded value
    instead of a function call.
    */
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));

}

void uart0_write(int ch)
{
    UARTCharPut(UART0_BASE, ch);
}





