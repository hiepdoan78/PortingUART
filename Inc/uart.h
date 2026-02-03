/*
 * uart.h
 *
 *  Created on: Feb 2, 2026
 *      Author: Hiepm
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

typedef enum {
	UART_OK,
	UART_BUSY,
	UART_ERROR
} uart_status_t;

void uart_init(void);
void uart_send_byte(uint8_t data);
void uart_send_string(const char *str);
uint8_t uart_receive_byte(void);

#endif /* UART_H_ */
