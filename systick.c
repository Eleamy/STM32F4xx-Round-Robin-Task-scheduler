#include "systick.h"

void systick_init(uint32 reloadValue, systickClkSource tickSource, systickOpType opType)
{

    /* setup reload value */
    SYSTICK->LOAD = (reloadValue & (0x00FFFFFFU)) - 1;

    /* clear current systick value */
    SYSTICK->VAL = 0;

    /* clear update flag by a dummy read*/
    systick_read_count_flag();
    /* choose systick clock source */
    switch (tickSource)
    {
    case (SYS_CLK):
        SET_BIT(SYSTICK->CTRL, SYSTICK_CTRL_CLKSOURCE); // MCU clk is selected
        break;
    case (SYS_CLK_8):
        CLEAR_BIT(SYSTICK->CTRL, SYSTICK_CTRL_CLKSOURCE); // MCU CLK/8 is selected
        break;
    default:
        return;
    }

    /* handle systick operation type */
    switch (opType)
    {
    case (systick_poll):
        break;
    case (systick_interrupt):
        SET_BIT(SYSTICK->CTRL, SYSTICK_CTRL_TICKINT);
        break;
    default:
        return;
    }

    /* enable systick timer */
    SET_BIT(SYSTICK->CTRL, SYSTICK_CTRL_ENABLE);
}

uint32 systick_read_count_flag(void){

    /* clear systick count flag if set */
    if (BIT_IS_SET(SYSTICK->CTRL, SYSTICK_CTRL_COUNTFLAG)){
        CLEAR_BIT(SYSTICK->CTRL, SYSTICK_CTRL_COUNTFLAG);
        return TRUE;
    }
    
    return FALSE;
}

void systick_deinit(void)
{

    /* disable systick timer */
    CLEAR_BIT(SYSTICK->CTRL, SYSTICK_CTRL_ENABLE);

    /* disable systick timer interrupts */
    CLEAR_BIT(SYSTICK->CTRL, SYSTICK_CTRL_TICKINT);
}