

#ifndef NVIC_H
#define NVIC_H

/*includes*/

#include "stm32f4xx.h"
#include "common_macros.h"
#include "std_types.h"

/*definitions*/

#define VECTKEY_MSK (0x5FAU << 16)
#define SYSRESETREQ_MSK (1 << 2)
#define __NOP() __asm("nop")
#define __NVIC_PRIO_BITS 4
#ifndef __STATIC_FORCEINLINE
#define __STATIC_FORCEINLINE __attribute__((always_inline)) static inline
#endif

/* assembly instructions definitions */
#define __ENABLE_INTERRUPTS() __asm("CPSIE I")
#define __DISABLE_INTERRUPTS() __asm("CPSID I")
#define __ENABLE_FAULTS() __asm("CPSIE F")
#define __DISABLE_FAULTS() __asm("CPSID F")

/*types*/
typedef enum
{
    INT_WWDG,
    INT_EXTI16_PVD,
    INT_EXTI21_TAMP_STAMP,
    INT_EXTI22_RTC_WKUP,
    INT_FLASH,
    INT_RCC_I,
    INT_EXTI0,
    INT_EXTI1,
    INT_EXTI2,
    INT_EXTI3,
    INT_EXTI4,
    INT_DMA1_Stream0,
    INT_DMA1_Stream1,
    INT_DMA1_Stream2,
    INT_DMA1_Stream3,
    INT_DMA1_Stream4,
    INT_DMA1_Stream5,
    INT_DMA1_Stream6,
    INT_ADC,
    INT_EXTI9_5 = 23U,
    INT_TIM1_BRK_TIM9,
    INT_TIM1_UP_TIM10,
    INT_TIM1_TRG_COM_TIM11,
    INT_TIM1_CC,
    INT_TIM2,
    INT_TIM3,
    INT_TIM4,
    INT_I2C1_EV,
    INT_I2C1_ER,
    INT_I2C2_EV,
    INT_I2C2_ER,
    INT_SPI1,
    INT_SPI2,
    INT_USART1,
    INT_USART2,
    INT_EXTI15_10 = 40U,
    INT_EXTI17_RTC_Alarm,
    INT_EXTI18_OTG_FS_WKUP,
    INT_DMA1_Stream7 = 47U,
    INT_SDIO = 49U,
    INT_TIM5,
    INT_SPI3,
    INT_DMA2_Stream0 = 56U,
    INT_DMA2_Stream1,
    INT_DMA2_Stream2,
    INT_DMA2_Stream3,
    INT_DMA2_Stream4,
    INT_OTG_FS = 67U,
    INT_DMA2_Stream5,
    INT_DMA2_Stream6,
    INT_DMA2_Stream7,
    INT_USART6,
    INT_I2C3_EV,
    INT_FPU = 81U,
    INT_SPI4 = 84U,
} IRQN_Type;

/*prototypes*/
void nvic_enable_interrupt(IRQN_Type irq);
void nvic_disable_interrupt(IRQN_Type irq);
void nvic_set_priority(IRQN_Type irq, uint32 priority);
uint32 nvic_get_priority(IRQN_Type irq);
void nvic_set_pending(IRQN_Type irq);
void nvic_clear_pending(IRQN_Type irq);
void NVIC_SystemReset(void);

#endif