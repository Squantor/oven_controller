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
            SctMatchReloadL(SCT0, SCT_MATCH_0, pwm_value);
            pwm_value+=1000;
            if(pwm_value > 10000)
            {
                pwm_value = 0;
            }
            i2cSetMasterData(I2C0, 0x43);
            i2cSetMasterControl(I2C0, I2C_MSCTL_MSTSTART);
            uint32_t i2cStatus;
            do {
                __NOP();
                i2cStatus = i2cGetStatus(I2C0);
            } while (I2C_STAT_MSTSTATE(i2cStatus) != I2C_STAT_MSSTATE_RECEIVE_READY);
            volatile uint8_t data = i2cGetMasterData(I2C0);
            i2cSetMasterControl(I2C0, I2C_MSCTL_MSTSTOP);
                do {
                __NOP();
                i2cStatus = i2cGetStatus(I2C0);
            } while (I2C_STAT_MSTSTATE(i2cStatus) != I2C_STAT_MSSTATE_IDLE);
        }
    }
}
