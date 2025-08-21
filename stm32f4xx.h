#ifndef STM32F4XX_H
#define STM32F4XX_H

#include "std_types.h"

/* bus bases */
#define PERIPH_BASE (0x40000000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define AHB2PERIPH_BASE (PERIPH_BASE + 0x10000000UL)
#define APB2PERIPH_BASE (PERIPH_BASE + 0x00010000UL)
#define APB1PERIPH_BASE (PERIPH_BASE + 0x00000000UL)

/* AHB1 periphrals*/
#define RCC_BASE (AHB1PERIPH_BASE + 0x3800)
#define FLASH_BASE (AHB1PERIPH_BASE + 0x3C00)
#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASE (AHB1PERIPH_BASE + 0x0400)

/*APB1 peripherials*/
#define USART2_BASE (APB1PERIPH_BASE + 0x4400)
#define SPI3_BASE (APB1PERIPH_BASE + 0x3C00)
#define SPI2_BASE (APB1PERIPH_BASE + 0x3800)
#define TIMER5_BASE (APB1PERIPH_BASE + 0x0C00)
#define TIMER4_BASE (APB1PERIPH_BASE + 0x0800)
#define TIMER3_BASE (APB1PERIPH_BASE + 0x0400)
#define TIMER2_BASE (APB1PERIPH_BASE + 0x0000)
#define PWR_BASE (APB1PERIPH_BASE + 0x7000)

/*APB2 peripherials*/
#define EXTI_BASE (APB2PERIPH_BASE + 0x3C00)
#define SYSCFG_BASE (APB2PERIPH_BASE + 0x3800)
#define SPI1_BASE (APB2PERIPH_BASE + 0x3000)
#define SPI4_BASE (APB2PERIPH_BASE + 0x3400)
#define USART1_BASE (APB2PERIPH_BASE + 0x1000)
#define USART6_BASE (APB2PERIPH_BASE + 0x1400)
#define TIMER11_BASE (APB2PERIPH_BASE + 0x4800)
#define TIMER10_BASE (APB2PERIPH_BASE + 0x4400)
#define TIMER9_BASE (APB2PERIPH_BASE + 0x4000)
#define TIMER1_BASE (APB2PERIPH_BASE + 0x0000)

/* system peripheral bases */
#define NVIC_BASE (0xE000E100U)
#define SCB_BASE (0xE000E008U)
#define SYSTICK_BASE (0xE000E010U)

/* periphirals type definitions */
typedef struct
{
    volatile uint32 MODER;   // 0x00
    volatile uint32 OTYPER;  // 0x04
    volatile uint32 OSPEEDR; // 0x08
    volatile uint32 PUPDR;   // 0x0C
    volatile uint32 IDR;     // 0x10
    volatile uint32 ODR;     // 0x14
    volatile uint32 BSRR;    // 0x18
    volatile uint32 LCKR;    // 0x1C
    volatile uint32 AFR[2];  // 0x20, 0x24
} GPIO_TypeDef;

typedef struct
{
    volatile uint32 CR;       // 0x00
    volatile uint32 PLLCFGR;  // 0x04
    volatile uint32 CFGR;     // 0x08
    volatile uint32 CIR;      // 0x0C
    volatile uint32 AHB1RSTR; // 0x10
    volatile uint32 AHB2RSTR;
    volatile uint32 AHB3RSTR;
    uint32 RESERVED0;
    volatile uint32 APB1RSTR;
    volatile uint32 APB2RSTR;
    uint32 RESERVED1[2];
    volatile uint32 AHB1ENR; // 0x30
    volatile uint32 AHB2ENR;
    volatile uint32 AHB3ENR;
    uint32 RESERVED2;
    volatile uint32 APB1ENR;
    volatile uint32 APB2ENR;
    // ... more if needed
} RCC_TypeDef;

typedef struct
{
    volatile uint32 CR1;   /*!< TIM control register 1,              Address offset: 0x00 */
    volatile uint32 CR2;   /*!< TIM control register 2,              Address offset: 0x04 */
    volatile uint32 SMCR;  /*!< TIM slave mode control register,     Address offset: 0x08 */
    volatile uint32 DIER;  /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
    volatile uint32 SR;    /*!< TIM status register,                 Address offset: 0x10 */
    volatile uint32 EGR;   /*!< TIM event generation register,       Address offset: 0x14 */
    volatile uint32 CCMR1; /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
    volatile uint32 CCMR2; /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
    volatile uint32 CCER;  /*!< TIM capture/compare enable register, Address offset: 0x20 */
    volatile uint32 CNT;   /*!< TIM counter register,                Address offset: 0x24 */
    volatile uint32 PSC;   /*!< TIM prescaler,                       Address offset: 0x28 */
    volatile uint32 ARR;   /*!< TIM auto-reload register,            Address offset: 0x2C */
    volatile uint32 RCR;   /*!< TIM repetition counter register,     Address offset: 0x30 */
    volatile uint32 CCR1;  /*!< TIM capture/compare register 1,      Address offset: 0x34 */
    volatile uint32 CCR2;  /*!< TIM capture/compare register 2,      Address offset: 0x38 */
    volatile uint32 CCR3;  /*!< TIM capture/compare register 3,      Address offset: 0x3C */
    volatile uint32 CCR4;  /*!< TIM capture/compare register 4,      Address offset: 0x40 */
    volatile uint32 BDTR;  /*!< TIM break and dead-time register,    Address offset: 0x44 */
    volatile uint32 DCR;   /*!< TIM DMA control register,            Address offset: 0x48 */
    volatile uint32 DMAR;  /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
    volatile uint32 OR;    /*!< TIM option register,                 Address offset: 0x50 */
} TIM_TypeDef;

typedef struct
{
    volatile uint32 IMR;   // 0x00
    volatile uint32 EMR;   // 0x04
    volatile uint32 RTSR;  // 0x08
    volatile uint32 FTSR;  // 0x0C
    volatile uint32 SWIER; // 0x10
    volatile uint32 PR;    // 0x14
} EXTI_TypeDef;

typedef struct
{
    volatile uint32 SR;   // 0x00
    volatile uint32 DR;   // 0x04
    volatile uint32 BRR;  // 0x08
    volatile uint32 CR1;  // 0x0C
    volatile uint32 CR2;  // 0x10
    volatile uint32 CR3;  // 0x14
    volatile uint32 GTPR; // 0x14
} USART_TypeDef;

typedef struct
{
    volatile uint32 MEMRMP;       // 0x00
    volatile uint32 PMC;          // 0x04
    volatile uint32 EXTICR[3U];   // 0x08 to 0x14
    volatile uint32 RESERVED[2U]; // 0x18, 0x1C
    volatile uint32 CMPCR;        // 0x20
} SYSCFG_TypeDef;

typedef struct
{
    volatile uint32 ISER[16U]; /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
    volatile uint32 RESERVED0[16U];
    volatile uint32 ICER[16U]; /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
    volatile uint32 RSERVED1[16U];
    volatile uint32 ISPR[16U]; /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
    volatile uint32 RESERVED2[16U];
    volatile uint32 ICPR[16U]; /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
    volatile uint32 RESERVED3[16U];
    volatile uint32 IABR[16U]; /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
    volatile uint32 RESERVED4[16U];
    volatile uint32 ITNS[16U]; /*!< Offset: 0x280 (R/W)  Interrupt Non-Secure State Register */
    volatile uint32 RESERVED5[16U];
    volatile uint32 IPR[124U]; /*!< Offset: 0x300 (R/W)  Interrupt Priority Register */
} NVIC_TypeDef;

typedef struct
{
    volatile uint32 ACTLR;
    volatile uint32 reserved0[829];
    volatile uint32 CPUID; /*!< Offset: 0x000 (R/ )  CPUID Base Register */
    volatile uint32 ICSR;  /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
    volatile uint32 VTOR;  /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
    volatile uint32 AIRCR; /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
    volatile uint32 SCR;   /*!< Offset: 0x010 (R/W)  System Control Register */
    volatile uint32 CCR;   /*!< Offset: 0x014 (R/W)  Configuration Control Register */
    volatile uint32 RESERVED1;
    volatile uint32 SHPR[2U]; /*!< Offset: 0x01C (R/W)  System Handlers Priority Registers. [0] is RESERVED */
    volatile uint32 SHCSR;    /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
} SCB_TypeDef;

typedef struct {
    volatile uint32 CTRL;
    volatile uint32 LOAD;
    volatile uint32 VAL;
    volatile uint32 CAL;
}SYSTICK_TypeDef;

typedef struct
{
    volatile uint32 SPI_CR1;
    volatile uint32 SPI_CR2;
    volatile uint32 SPI_SR;
    volatile uint32 SPI_DR;
    volatile uint32 SPI_CRCPR;
    volatile uint32 SPI_RXCRCR;
    volatile uint32 SPI_TXCRCR;
    volatile uint32 SPI_I2SCFGR;
    volatile uint32 SPI_I2SPR;
} SPI_TypeDef;

typedef struct
{
    volatile uint32 FLASH_ACR;
    volatile uint32 FLASH_KEYR;
    volatile uint32 FLASH_OPTKEYR;
    volatile uint32 FLASH_SR;
    volatile uint32 FLASH_CR;
    volatile uint32 FLASH_OPTCR;
} FLASH_TypeDef;

typedef struct
{
    volatile uint32 CR;
    volatile uint32 CSR;
} PWR_TypeDef;

/* periphirals definitions */
#define PWR ((PWR_TypeDef *)PWR_BASE)
#define RCC ((RCC_TypeDef *)RCC_BASE)
#define FLASH ((FLASH_TypeDef *)FLASH_BASE)
#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE)
#define EXTI ((EXTI_TypeDef *)EXTI_BASE)
#define SYSCFG ((SYSCFG_TypeDef *)SYSCFG_BASE)
#define NVIC ((NVIC_TypeDef *)NVIC_BASE)
#define SCB ((SCB_TypeDef *)SCB_BASE)
#define SYSTICK ((SYSTICK_TypeDef *) SYSTICK_BASE) 
#define SPI1 ((SPI_TypeDef *)SPI1_BASE)
#define SPI2 ((SPI_TypeDef *)SPI2_BASE)
#define SPI3 ((SPI_TypeDef *)SPI3_BASE)
#define SPI4 ((SPI_TypeDef *)SPI4_BASE)
#define USART1 ((USART_TypeDef *)USART1_BASE)
#define USART2 ((USART_TypeDef *)USART2_BASE)
#define USART6 ((USART_TypeDef *)USART6_BASE)
#define TIM1 ((TIM_TypeDef *)TIMER1_BASE)
#define TIM2 ((TIM_TypeDef *)TIMER2_BASE)
#define TIM3 ((TIM_TypeDef *)TIMER3_BASE)
#define TIM4 ((TIM_TypeDef *)TIMER4_BASE)
#define TIM5 ((TIM_TypeDef *)TIMER5_BASE)
#define TIM9 ((TIM_TypeDef *)TIMER9_BASE)
#define TIM10 ((TIM_TypeDef *)TIMER10_BASE)
#define TIM11 ((TIM_TypeDef *)TIMER11_BASE)

/* RCC perphirals clock bit definitions */
#define RCC_AHB1ENR_GPIOAEN (uint32)(0)
#define RCC_AHB1ENR_GPIOBEN (uint32)(1)
#define RCC_CR_HSEON (uint32)(16)
#define RCC_CR_HSERDY (uint32)(17)
#define RCC_CR_HSION (uint32)(0)
#define RCC_CR_HSIRDY (uint32)(1)
#define RCC_APB2ENR_SYSCFGEN (uint32)(14)



#endif
