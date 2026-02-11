/*
 * uart.c
 *
 *  Created on: Feb 2, 2026
 *      Author: Hiepm
 */

#include "uart.h"
#include "uart_hw.h"

static volatile ring_buffer_t uart_rx;
static volatile ring_buffer_t uart_tx;

void uart_init(void){
	uart_hw_init();
}

void USART1_IRQHandler(void){
	/* ERROR HANDLING */
	if (uart_hw_get_error()) {
		uart_hw_clear_error(); // clear error
		return;
	}

	if(uart_hw_rx_ready()){ // RXNE = 1
		uint16_t rx_next = (uart_rx.head + 1) % RX_BUF_SIZE;
		uint8_t rx_data = uart_hw_read();

		if (rx_next != uart_rx.tail) {
			uart_rx.buf[uart_rx.head] = rx_data;
			uart_rx.head = rx_next;
		}
	}

	if(uart_hw_tx_ready()){ // TXE = 1
		if(uart_tx.head == uart_tx.tail){
			uart_hw_disable_tx_irq();
		}
		else{
			uint8_t tx_data = uart_tx.buf[uart_tx.tail];
			uart_tx.tail = (uart_tx.tail + 1) % TX_BUF_SIZE;
			uart_hw_send(tx_data);
		}

	}
}

uart_status_t uart_send_byte(uint8_t data){
	uint16_t tx_next = (uart_tx.head + 1) % TX_BUF_SIZE;
	if (tx_next != uart_tx.tail) {
		uart_tx.buf[uart_tx.head] = data;
		uart_tx.head = tx_next;
		uart_hw_enable_tx_irq(); // enable TX interrupt
		return UART_OK;
	}
	return UART_BUSY;
}

void uart_send_string(const char *str)
{
    while(*str)
    {
        while(uart_send_byte(*str) == UART_BUSY);
        str++;
    }
}

uart_status_t uart_received(uint8_t *data)
{
    if(uart_rx.head != uart_rx.tail){
    	*data = uart_rx.buf[uart_rx.tail];
    	uart_rx.tail = (uart_rx.tail + 1) % RX_BUF_SIZE;
    	return UART_OK;
    }
    return UART_BUSY;
}
