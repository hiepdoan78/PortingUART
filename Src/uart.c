/*
 * uart.c
 *
 *  Created on: Feb 2, 2026
 *      Author: Hiepm
 */

#include "uart.h"
#include "uart_cfg.h"
#include "stm32f103xb.h"

void uart_init(void){
	// Enable CLOCK for GPIOA & USART1
	RCC->APB2ENR |= (1 << 2); // GPIOA
	RCC->APB2ENR |= (1 << 14); // USART1

	// Config PA9 - TX: push-pull ouput
	GPIOA->CRH &= ~(0xF << 4); // Clear 4 bits of PA9
	GPIOA->CRH |=  (0xB << 4); // Set Alternate Function, Push-Pull mode

	// Config PA10 - RX: Floating intput
	GPIOA->CRH &= ~(0xF << 8); // Clear 4 bits of PA10
	GPIOA->CRH |=  (0x4 << 8); // Set Floating input mode

	//Baudrate
	USART1->BRR = UART_CLK_FREQ / UART_BAUDRATE;

	 //Enable TX, RX, USART
	USART1->CR1 |= (1 << 3);   // TE
	USART1->CR1 |= (1 << 2);   // RE
	USART1->CR1 |= (1 << 13);  // UE
}

void uart_send_byte(uint8_t data){
	while (!(USART1->SR & (1 << 7)));  // Wait for TXE = 1
	USART1->DR = data; // Write to Data Register
}

void uart_send_string(const char *str){
	while(*str){
		uart_send_byte(*str++);
	}
}

uint8_t uart_receive_byte(void)
{
    while (!(USART1->SR & (1 << 5)));  // Wait until RXNE = 1
    return USART1->DR;
}
