
#include "pwr.h"

uint8 g_pwr_clk_flag = 0;

void mcu_sleep(void)
{

    /* enable PWR perophiral clock */
    if (!g_pwr_clk_flag)
    {
        SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWR_EN);
        g_pwr_clk_flag = 1;
    }

    /* clear DEEPSLEEP bit in system control register */
    CLEAR_BIT(SCB->SCR, SCB_CR_DEEPSLEEP);

    /* enable wakeup pin */
    PWR->CSR = 0;
    SET_BIT(PWR->CSR, PWR_CSR_EWUP);
    /* enable wakeup flag */
    SET_BIT(PWR->CSR, PWR_CSR_EWUP);

    /* wait for 2 clock cycles */
    __NOP();
    __NOP();
    /* execute wait for interrupts WFI assembly instruction */
    __WFI();
}

void mcu_stop(void)
{
    /* enable PWR clock */
    if (!g_pwr_clk_flag)
    {
        SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWR_EN);
        g_pwr_clk_flag = 1;
    }

    /* set SLEEPDEEP bit in system control register */
    SET_BIT(SCB->SCR, SCB_CR_DEEPSLEEP);

    /* clear PDDS bit in pwr_cr register */
    CLEAR_BIT(PWR->CR, PWR_CR_PDDS);
    SET_BIT(PWR->CR, PWR_CR_LPDS);

    /* clear wakeup flag */
    SET_BIT(PWR->CR, PWR_CSR_WUF);

    /* enable wakeup pin */
    SET_BIT(PWR->CSR, PWR_CSR_EWUP);

    /* wait for two clock cycles for PDDS bit to take effect */
    __NOP();
    __NOP();

    /* execute WFI assembly instruction */
    __WFI();
}

void mcu_standby(void)
{

    /* enable PWR clock */
    if (!g_pwr_clk_flag)
    {
        SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWR_EN);
        g_pwr_clk_flag = 1;
    }

    /* set DEEPSLEEP bit in system control register */
    SET_BIT(SCB->SCR, SCB_CR_DEEPSLEEP);
    /* SET PDDS bit in PWR_CR register */
    SET_BIT(PWR->CR, PWR_CR_PDDS);

    /* enable wakeup pin */
    SET_BIT(PWR->CSR, PWR_CSR_EWUP);

    /* clear wakeup flag */
    SET_BIT(PWR->CR, PWR_CR_CWUF);

    /* wait for 2 clock cycles */
    __NOP();
    __NOP();

    /* execute WFI (wait for interrup) assembly instruction */
    __WFI();
}

void mcu_software_reset(void)
{
    /* set the SYSRESETREQ bit high in AIRCR (interrupt and reset control register) */
    SCB->AIRCR = SCB_AIRCR_VECTKEY_MSK | SCB_AIRCR_SYSRESETREQ_MSK;
    // do nothing untill software reset completes
    while (TRUE)
    {
        __NOP(); // perform "nop" arm assembly instruction (no_operation instruction)
    }
}