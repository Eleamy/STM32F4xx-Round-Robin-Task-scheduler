#include "interrupts.h"
#include "nvic.h"
#include "usart.h"
#include "timer.h"

extern void (*systick_callback_ptr)(void);

void TIM1_UP_TIM10_IRQHandler(void)
{
}

void TIM2_IRQHandler(void)
{
}

void TIM3_IRQHandler(void)
{
}

void SysTick_Handler(void)
{
    __DISABLE_INTERRUPTS();
    systick_callback_ptr();
    __ENABLE_INTERRUPTS();
}