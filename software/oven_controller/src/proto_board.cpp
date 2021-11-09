/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <board.hpp>

void crudeDelay(uint32_t iterations)
{
    for(uint32_t i = iterations; i > 0; i--)
    {
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }
}

void setup50HzOutput(void)
{
    SctSetControl(SCT0, 
        SCT_CTRL_BIDIR_H | 
        // TODO: change prescalers to use more bits of the 16bit timer
        SCT_CTRL_PRE_H(30-1) | 
        SCT_CTRL_PRE_L(30-1) |
        SCT_CTRL_CLRCTR_H | 
        SCT_CTRL_CLRCTR_L );
    SctMatchH(SCT0, SCT_MATCH_0, 5000);
    SctMatchReloadH(SCT0, SCT_MATCH_0, 5000);
    SctMatchH(SCT0, SCT_MATCH_1, 4950);
    SctMatchReloadH(SCT0, SCT_MATCH_1, 4950);
    SctSetEventStateMask(SCT0, SCT_EVENT_0_VAL, SCT_STATE_ALL_BIT);
    SctSetEventControl(SCT0, SCT_EVENT_0_VAL, 
        SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH) | 
        SCT_EV_CTRL_H_EVENT |
        SCT_EV_CTRL_MATCHSEL(SCT_MATCH_1));
    SctOutputSet(SCT0, SCT_OUTPUT_0_VALUE, SCT_EVENT_0_BIT);
    SctOutputDirCtrl(SCT0, SCT_OUTPUTDIRCTRL(SCT_OUTPUT_0_VALUE, SCT_OUTPUTDIRCTRL_H));
}

void boardInit(void)
{
    sysconEnableClocks(SYSCON, 
        CLKCTRL0_UART0 | 
        CLKCTRL0_IOCON | 
        CLKCTRL0_SWM |
        CLKCTRL0_SCT , 
        CLKCTRL1_NONE);
    // setup GPIO pins
    ioconSetupPin(IOCON, IOCON_UART_RX, IOCON_MODE_PULLUP);
    ioconSetupPin(IOCON, IOCON_UART_TX, IOCON_MODE_INACTIVE);
    ioconSetupPin(IOCON, IOCON_TESTPIN0, IOCON_MODE_INACTIVE);
    ioconSetupPin(IOCON, IOCON_ZEROCROSS, IOCON_MODE_PULLDOWN);
    SwmMovablePinAssign(SWM, SWM_USART0_TXD, SWM_UART_TX);
    SwmMovablePinAssign(SWM, SWM_USART0_RXD, SWM_UART_RX);
    SwmMovablePinAssign(SWM, SWM_SCT_OUT0, SWM_TESTPIN0);
    SwmMovablePinAssign(SWM, SWM_SCT_PIN0, SWM_ZEROCROSS);
    // setup crystal oscillator to run core at 12MHz
    ioconSetupPin(IOCON, IOCON_XTAL_IN, IOCON_MODE_INACTIVE);
    ioconSetupPin(IOCON, IOCON_XTAL_OUT, IOCON_MODE_INACTIVE);
    swmEnableFixedPin(SWM, SWM_EN0_XTALIN | SWM_EN0_XTALOUT, SWM_EN1_NONE);
    sysconSysOscControl(SYSCON, SYSOSCCTRL_FREQ_1_20MHZ);
    sysconPowerEnable(SYSCON, PDRUNCFG_SYSOSC);
    // wait until crystal oscillator stabilizes
    crudeDelay(6000);
    sysconExternalClockSelect(SYSCON, EXTCLKSEL_SYSOSC);
    sysconSysPllClockSelect(SYSCON, SYSPLLCLKSEL_EXTCLK);
    FlashControlFlashClocks(FLASHTIM_2_CLOCKS);
    // setup PLL
    sysconPowerDisable(SYSCON, PDRUNCFG_SYSPLL);
    sysconPllControl(SYSCON, 4, SYSPLLCTRL_POSTDIV_4);
    sysconPowerEnable(SYSCON, PDRUNCFG_SYSPLL);
    while (sysconPllStatus(SYSCON) == 0)
        ;
    sysconMainClockDivider(SYSCON, 2);
    sysconMainClockPllSelect(SYSCON, MAINCLKPLLSEL_SYSPLL);
    // disable all unneeded clocks
    sysconDisableClocks(SYSCON, CLKCTRL0_IOCON | CLKCTRL0_SWM, CLKCTRL1_NONE);
    // setup systick
    SysTick_Config(CLOCK_AHB / TICKS_PER_S);
    // setup UART
    sysconPeripheralClockSelect(SYSCON, UART0CLKSEL, CLKSRC_MAIN);
    usartSetBaud(UART_DEBUG, CLOCK_MAIN, UART_BAUD_RATE);
    usartSetConfig(UART_DEBUG, DATALEN_8, PARITY_NONE, STOPLEN_1, 0);
    usartTXEnable(UART_DEBUG);
    // setup SCT
    SctConfig(SCT0, SCT_CONFIG_16BIT_COUNTER | SCT_CONFIG_AUTOLIMIT_H);

    // if match 2 is reached, disable output and stop and reset the timer
    SctMatchL(SCT0, SCT_MATCH_2, 6000);
    SctMatchReloadL(SCT0, SCT_MATCH_2, 6000);
    // assign event 2 to match 2
    SctSetEventControl(SCT0, SCT_EVENT_2_VAL, 
        SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH) | 
        SCT_EV_CTRL_L_EVENT |
        SCT_EV_CTRL_MATCHSEL(SCT_MATCH_2));
    SctSetEventStateMask(SCT0, SCT_EVENT_2_VAL, SCT_STATE_ALL_BIT);
    // TODO: Disable triac control output

    // if we get a negative edge on the input, start the timer
    // assign timer restart to event 3
    SctSetEventControl(SCT0, SCT_EVENT_3_VAL, 
        SCT_EV_CTRL_INSEL | 
        SCT_EV_CTRL_IOSEL(0) | 
        SCT_EV_CTRL_IOCOND(SCT_IOCOND_FALL) |
        SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_IO) );
    SctSetEventStateMask(SCT0, SCT_EVENT_3_VAL, SCT_STATE_ALL_BIT);
    // if we get a positive edge on the input, stop and clear the timer
    // assign timer stop to event 4
    SctSetEventControl(SCT0, SCT_EVENT_4_VAL, 
        SCT_EV_CTRL_INSEL | 
        SCT_EV_CTRL_IOSEL(0) | 
        SCT_EV_CTRL_IOCOND(SCT_IOCOND_RISE) |
        SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_IO) );
    SctSetEventStateMask(SCT0, SCT_EVENT_4_VAL, SCT_STATE_ALL_BIT);

    SctStartL(SCT0, SCT_EVENT_3_BIT);
    SctStopL(SCT0, SCT_EVENT_2_BIT | SCT_EVENT_4_BIT);
    SctLimitL(SCT0, SCT_EVENT_4_BIT);

    setup50HzOutput();
    SctClearControl(SCT0, SCT_CTRL_HALT_L | SCT_CTRL_HALT_H);
}
