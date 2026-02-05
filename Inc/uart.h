/*
 * uart.h
 *
 *  Created on: Feb 2, 2026
 *      Author: Hiepm
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stdbool.h>

#define RX_BUF_SIZE 64

typedef enum {
	UART_OK,
	UART_BUSY
} uart_status_t;

typedef struct {
	uint8_t buf[RX_BUF_SIZE];
	volatile uint16_t head;
	volatile uint16_t tail;
}ring_buffer_t;

void uart_init(void);
void uart_send_byte(uint8_t data);
void uart_send_string(const char *str);
uart_status_t uart_read(uint8_t *data);

#endif /* UART_H_ */
