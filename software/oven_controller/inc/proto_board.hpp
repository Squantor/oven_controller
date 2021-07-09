/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#ifndef PROTO_BOARD_HPP
#define PROTO_BOARD_HPP

#define CLOCK_XTAL          (12000000u)
#define CLOCK_EXT_IN        (0u)
#define CLOCK_CPU           (12000000u)
#define CLOCK_AHB           (12000000u)
#define CLOCK_MAIN          (12000000u)

#include <mcu_ll.h>

#define TICKS_PER_S         10

#define IOCON_XTAL_IN       IOCON_PIO0_8
#define IOCON_XTAL_OUT      IOCON_PIO0_9

#define IOCON_UART_TX       IOCON_PIO0_25
#define PORT_UART_TX        (0u)
#define PIN_UART_TX         (SWM_PORTPIN_P0_25)
#define IOCON_UART_RX       IOCON_PIO0_24
#define PORT_UART_RX        (0u)
#define PIN_UART_RX         (SWM_PORTPIN_P0_24)

#define UART_DEBUG          LPC_USART0
#define UART_BAUD_RATE      (115200u)

#endif