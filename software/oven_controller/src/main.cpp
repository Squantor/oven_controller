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
    uint16_t pwm_value = 0;
    while (1) 
    {
        result readState = dsReadChar(&streamUart, &character);
        if(readState == noError)
        {
            dsWriteChar(&streamUart, character);
            SctMatchReloadH(SCT0, SCT_MATCH_1, pwm_value);
            pwm_value+=200;
            if(pwm_value > 5000)
                pwm_value = 0;
        }
    }
}
