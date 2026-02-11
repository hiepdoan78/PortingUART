/*
 * uart_hw_stm32f1.c
 *
 *  Created on: Feb 11, 2026
 *      Author: Hiepm
 */

#include "uart_hw.h"
#include "uart_cfg.h"
#include "stm32f103xb.h"

void uart_hw_init(void)
{
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

		 //Enable TX, RX, USART, RXNEIE
		USART1->CR1 |= (1 << 2);   // RE
		USART1->CR1 |= (1 << 3);   // TE
		USART1->CR1 |= (1 << 5);   // RXNEIE
		USART1->CR1 |= (1 << 13);  // UE

		NVIC_EnableIRQ(USART1_IRQn);
}

void uart_hw_send(uint8_t data)
{
    USART1->DR = data;
}

uint8_t uart_hw_read(void)
{
    return USART1->DR;
}

uint8_t uart_hw_tx_ready(void)
{
    return (USART1->SR & (1<<7));
}

uint8_t uart_hw_rx_ready(void)
{
    return (USART1->SR & (1<<5));
}

void uart_hw_enable_tx_irq(void)
{
    USART1->CR1 |= (1<<7);
}

void uart_hw_disable_tx_irq(void)
{
    USART1->CR1 &= ~(1<<7);
}

uint32_t uart_hw_get_error(void)
{
    return ((USART1->SR) &(USART_SR_ORE | USART_SR_FE | USART_SR_NE));
}

void uart_hw_clear_error(void)
{
    volatile uint8_t tmp = USART1->DR;
    (void)tmp;
}

