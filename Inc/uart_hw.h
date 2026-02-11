/*
 * uart_hw.h
 *
 *  Created on: Feb 2, 2026
 *      Author: Hiepm
 */

#ifndef UART_HW_H_
#define UART_HW_H_

#include <stdint.h>

void uart_hw_init(void);

void uart_hw_enable_tx_irq(void);
void uart_hw_disable_tx_irq(void);

uint8_t uart_hw_tx_ready(void);
uint8_t uart_hw_rx_ready(void);

void uart_hw_send(uint8_t data);
uint8_t uart_hw_read(void);

uint32_t uart_hw_get_error(void);
void uart_hw_clear_error(void);

#endif /* UART_HW_H_ */
