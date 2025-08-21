
#include "nvic.h"


void nvic_enable_interrupt(IRQN_Type irq)
{
    NVIC->ISER[irq >> 5] = 1 << (irq & 0x1F);
}
void nvic_disable_interrupt(IRQN_Type irq)
{
    NVIC->ICER[irq >> 5] = 1 << (irq & 0x1F);
}
void nvic_set_priority(IRQN_Type irq, uint32 priority)
{
    NVIC->IPR[(uint32)(irq)] = (uint8)((priority << (4 - __NVIC_PRIO_BITS)) & 0xFF);
}
uint32 nvic_get_priority(IRQN_Type irq)
{
    return NVIC->IPR[(uint32)(irq)] >> (8 - __NVIC_PRIO_BITS);
}
void nvic_set_pending(IRQN_Type irq)
{
    NVIC->ISPR[irq >> 5] = 1 << (irq & 0x1F);
}
void nvic_clear_pending(IRQN_Type irq)
{
    NVIC->ICPR[irq >> 5] = 1 << (irq & 0x1F);
}

void NVIC_SystemReset(void)
{
    /* set the SYSRESETREQ bit high in AIRCR (interrupt and reset control register) */
    SCB->AIRCR = VECTKEY_MSK | SYSRESETREQ_MSK;
    // do nothing untill software reset completes
    while (TRUE){
        __NOP();       // perform "nop" arm assembly instruction (no_operation instruction)
    }
}
