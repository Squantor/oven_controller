/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#ifndef PROTO_BOARD_HPP
#define PROTO_BOARD_HPP

#define CLOCK_MAIN_SOURCE   SYSCTL_MAINCLKSRC_PLLOUT

#define CLOCK_XTAL          (12000000u)
#define CLOCK_EXT_IN        (0u)
#define CLOCK_CPU           (30000000u)
#define CLOCK_AHB           (30000000u)
#define CLOCK_MAIN          (60000000u)

#include <mcu_ll.h>

#define TICKS_PER_S         10

#define IOCON_XTAL_IN       IOCON_PIO0_8
#define IOCON_XTAL_OUT      IOCON_PIO0_9

#define IOCON_UART_TX       IOCON_PIO0_25
#define PORT_UART_TX        (0u)
#define SWM_UART_TX         SWM_PORTPIN_P0_25
#define IOCON_UART_RX       IOCON_PIO0_24
#define PORT_UART_RX        (0u)
#define SWM_UART_RX         SWM_PORTPIN_P0_24

#define UART_DEBUG          USART0
#define UART_BAUD_RATE      (115200u)

// Bunch of test pins
#define IOCON_TESTPIN0      (IOCON_PIO1_10)
#define PORT_TESTPIN0       (GPIO_PORT1)
#define PIN_TESTPIN0        (10u)
#define SWM_TESTPIN0        (SWM_PORTPIN_P1_10)

#define IOCON_TESTPIN1      (IOCON_PIO1_10)
#define PORT_TESTPIN1       (GPIO_PORT1)
#define PIN_TESTPIN1        (11u)
#define SWM_TESTPIN1        (SWM_PORTPIN_P1_11)

#define IOCON_TESTPIN2      (IOCON_PIO0_18)
#define PORT_TESTPIN2       (GPIO_PORT0)
#define PIN_TESTPIN2        (18u)
#define SWM_TESTPIN2        (SWM_PORTPIN_P0_18)

#define IOCON_TESTPIN3      (IOCON_PIO1_21)
#define PORT_TESTPIN3       (GPIO_PORT1)
#define PIN_TESTPIN3        (21u)
#define SWM_TESTPIN3        (SWM_PORTPIN_P1_21)

#define IOCON_TESTPIN4      (IOCON_PIO1_20)
#define PORT_TESTPIN4       (GPIO_PORT1)
#define PIN_TESTPIN4        (20u)
#define SWM_TESTPIN4        (SWM_PORTPIN_P1_20)

// Zero cross detector input pin
#define IOCON_ZEROCROSS     (IOCON_PIO0_1)
#define PORT_ZEROCROSS      (GPIO_PORT0)
#define PIN_ZEROCROSS       (1u)
#define SWM_ZEROCROSS       (SWM_PORTPIN_P0_1)

// Triac control output pin
#define IOCON_TRIAC         (IOCON_PIO1_4)
#define PORT_TRIAC          (GPIO_PORT1)
#define PIN_TRIAC           (4u)
#define SWM_TRIAC           (SWM_PORTPIN_P1_4)

// User Interface I2C interface
#define IOCON_UI_SDA        (IOCON_PIO0_11)
#define PORT_UI_SDA         (GPIO_PORT0)
#define PIN_UI_SDA          (11u)
#define SWM_UI_SDA          (SWM_PORTPIN_P0_11)
#define IOCON_UI_SCL        (IOCON_PIO0_10)
#define PORT_UI_SCL         (GPIO_PORT0)
#define PIN_UI_SCL          (10u)
#define SWM_UI_SCL          (SWM_PORTPIN_P0_10)

// User interface interrupt pin
#define IOCON_UI_INT        (IOCON_PIO1_1)
#define PORT_UI_INT         (GPIO_PORT1)
#define PIN_UI_INT          (1u)
#define SWM_UI_INT          (SWM_PORTPIN_P1_1)




#endif