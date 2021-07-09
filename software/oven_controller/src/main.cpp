/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <board.hpp>
#include <stream_uart.hpp>
#include <print.h>

extern "C" 
{
    void SysTick_Handler(void)
    {
        __NOP();
    }
}

int main()
{
    char character;
    boardInit();
    dsPuts(&streamUart, "Hello World!\n");
    while (1) 
    {
        result readState = dsReadChar(&streamUart, &character);
        if(readState == noError)
            dsWriteChar(&streamUart, character);
    }
}
