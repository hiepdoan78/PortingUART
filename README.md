## 📌 Overview

This project provides a lightweight UART driver written in Embedded C with interrupt-based TX/RX buffering. It is designed to be portable across different STM32 microcontrollers using a hardware abstraction layer (HAL-like separation).

The driver supports:

* Interrupt-based transmit and receive
* Ring buffer TX/RX
* Error detection (ORE, FE, NE)
* Easy porting to different STM32 families

---

## 🏗 Project Structure

```
uart/
 ├── uart.c              # Generic UART driver logic
 ├── uart.h              # Public API
 ├── uart_hw_stm32f1.c   # STM32F1 hardware implementation
 ├── uart_hw.h           # Hardware abstraction interface
```

---

## 🚀 Features

### 1. Interrupt-driven communication

* Non-blocking TX/RX
* Circular buffer implementation

### 2. Error handling

Handles common UART errors:

* Overrun error (ORE)
* Framing error (FE)
* Noise error (NE)

### 3. Hardware abstraction

Hardware-specific code separated from generic driver.

➡ Allows easy migration between STM32 series.

---

## ⚙️ Usage

### Initialization

Hardware initialization should be implemented in:

```
uart_hw_xxx.c
```

Example:

```c
uart_init();
```

---

### Send Data

Single byte:

```c
uart_send_byte('A');
```

String:

```c
uart_send_string("HELLO\r\n");
```

---

### Receive Data

```c
uint8_t data;
if(uart_received(&data) == UART_OK)
{
    uart_send_byte(data);
}
```

---

## 🧩 Porting Guide

To port this driver to another STM32 family:

1. Create new hardware file:

```
uart_hw_stm32f4.c
```

2. Implement required hardware functions:

* UART register configuration
* Interrupt enable/disable
* ISR handler

No modification required in `uart.c`.

---

## 🔧 Requirements

* ARM Cortex-M MCU (STM32 recommended)
* CMSIS headers
* Basic interrupt configuration

---

## 📚 Future Improvements

* DMA support
* RTOS compatibility
* Power optimization
* Multi-UART support
* Timeout support using SysTick

---

## 👨‍💻 Author

Doan Minh Hiep

Embedded Software Developer passionate about automotive, robotics, and low-level system programming.

---
