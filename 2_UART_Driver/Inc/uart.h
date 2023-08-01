/*
 * uart.h
 *
 *  Created on: Jul 19, 2023
 *      Author: luong
 */

#ifndef INC_UART_H_
#define INC_UART_H_

void clock_init(void);
void uart0_tx_init(void);
void uart0_write(int ch);

#endif /* INC_UART_H_ */
