#ifndef TIMER_H
#define TIMER_H

/* includes */
#include "gpio.h"
#include "nvic.h"

/* definitions */

#define F_CLK 16000000U      /* 16 MHz clock frequency */
#define MAX_PRESCALER 65535U /* Maximum prescaler value for 16-bit timer */

/* timer_init() return values */
#define INIT_SUCCESS 0U
#define INIT_INVALID_PARAMETER 1U
#define INIT_TIMER_INITIALIZED 2U
#define INIT_INVALID_TIMER_INSTANCE 3U
#define INIT_INVALID_DIRECTION 4U
#define INIT_INVALID_CHANNEL 5U

/* timer_start() return values */
#define START_SUCCESS 0U
#define START_INVALID_PARAMETER 1U
#define START_TIMER_UNINITIALIZED 2U
#define START_INVALID_TIMER_INSTANCE 3U

/* timer_stop() return values */
#define STOP_SUCCESS 0U
#define STOP_INVALID_PARAMETER 1U
#define STOP_TIMER_UNINITIALIZED 2U
#define STOP_INVALID_TIMER_INSTANCE 3U
/* RCC bit definitions */
#define RCC_TIM1_RESET 0U
#define RCC_TIM2_RESET 0U
#define RCC_TIM3_RESET 1U
#define RCC_TIM4_RESET 2U
#define RCC_TIM5_RESET 3U

#define RCC_TIM1_CLOCK_ENABLE 0U
#define RCC_TIM2_CLOCK_ENABLE 0U
#define RCC_TIM3_CLOCK_ENABLE 1U
#define RCC_TIM4_CLOCK_ENABLE 2U
#define RCC_TIM5_CLOCK_ENABLE 3U

/* Timer CR1 bit definitoions*/
#define TIM_CR1_CEN 0U   /* Counter enable bit */
#define TIM_CR1_UDIS 1U  /* Update disable bit */
#define TIM_CR1_URS 2U   /* Update request source bit */
#define TIM_CR1_OPM 3U   /* One-pulse mode bit */
#define TIM_CR1_DIR 4U   /* Direction bit */
#define TIM_CR1_CMS_0 5U /* Center-aligned mode selection bit 0 */
#define TIM_CR1_CMS_1 6U /* Center-aligned mode selection bit */
#define TIM_CR1_CKD_0 8U /* Clock division bit 0 */
#define TIM_CR1_ARPE 7U  /* Auto-reload preload enable bit */
#define TIM_CR1_CKD_1 9U /* Clock division bit 1 */

/* timer CR2 bit definitions */
#define TIM_CR2_CCPC 0U   /* Capture/compare preloaded control */
#define TIM_CR2_CCUS 1U   /* Capture/compare control update selection */
#define TIM_CR2_CCDS 2U   /* Capture/compare DMA selection */
#define TIM_CR2_MMS_0 4U  /* Master mode selection bit 0 */
#define TIM_CR2_MMS_1 5U  /* Master mode selection bit 1 */
#define TIM_CR2_MMS_2 6U  /* Master mode selection bit 2 */
#define TIM_CR2_TI1S 7U   /* TI1 selection */
#define TIM_CR2_OIS1 8U   /* Output idle state 1 */
#define TIM_CR2_OIS1N 9U  /* Output idle state 1 complementary */
#define TIM_CR2_OIS2 10U  /* Output idle state 2 */
#define TIM_CR2_OIS2N 11U /* Output idle state 2 complementary */
#define TIM_CR2_OIS3 12U  /* Output idle state 3 */
#define TIM_CR2_OIS3N 13U /* Output idle state 3 complementary */
#define TIM_CR2_OIS4 14U  /* Output idle state 4 */

/* Timer SR bit defintions */
#define TIM_SR_UIF 0U    /* Update interrupt flag */
#define TIM_SR_CC1IF 1U  /* Capture/compare 1 interrupt flag */
#define TIM_SR_CC2IF 2U  /* Capture/compare 2 interrupt flag */
#define TIM_SR_CC3IF 3U  /* Capture/compare 3 interrupt flag */
#define TIM_SR_CC4IF 4U  /* Capture/compare 4 interrupt flag */
#define TIM_SR_TIF 5U    /* Trigger interrupt flag */
#define TIM_SR_COMIF 6U  /* Commutation interrupt flag */
#define TIM_SR_BIF 7U    /* Break interrupt flag */
#define TIM_SR_CC1OF 9U  /* Capture/compare 1 overcapture flag */
#define TIM_SR_CC2OF 10U /* Capture/compare 2 overcapture flag */
#define TIM_SR_CC3OF 11U /* Capture/compare 3 overcapture flag */
#define TIM_SR_CC4OF 12U /* Capture/compare 4 overcapture flag */

/* Timer EGR bit definitions */
#define TIM_EGR_UG 0U   /* Update generation */
#define TIM_EGR_CC1G 1U /* Capture/compare 1 generation */
#define TIM_EGR_CC2G 2U /* Capture/compare 2 generation */
#define TIM_EGR_CC3G 3U /* Capture/compare 3 generation */
#define TIM_EGR_CC4G 4U /* Capture/compare 4 generation */
#define TIM_EGR_TG 5U   /* Trigger generation */
#define TIM_EGR_COMG 6U /* Commutation generation */
#define TIM_EGR_BG 7U   /* Break generation */

/* Timer CCMR1 bit definitions */
#define TIM_CCMR1_CC1S_0 0U  /* Capture/compare 1 selection bit 0 */
#define TIM_CCMR1_CC1S_1 1U  /* Capture/compare 1 selection bit 1 */
#define TIM_CCMR1_OC1FE 2U   /* Output compare 1 fast enable bit */
#define TIM_CCMR1_OC1PE 3U   /* Output compare 1 preload enable bit */
#define TIM_CCMR1_OC1M_0 4U  /* Output compare 1 mode bit 0 */
#define TIM_CCMR1_OC1M_1 5U  /* Output compare 1 mode bit 1 */
#define TIM_CCMR1_OC1M_2 6U  /* Output compare 1 mode bit 2 */
#define TIM_CCMR1_OC1CE 7U   /* Output compare 1 clear enable bit */
#define TIM_CCMR1_CC2S_0 8U  /* Capture/compare 2 selection bit 0 */
#define TIM_CCMR1_CC2S_1 9U  /* Capture/compare 2 selection bit 1 */
#define TIM_CCMR1_OC2FE 10U  /* Output compare 2 fast enable bit */
#define TIM_CCMR1_OC2PE 11U  /* Output compare 2 preload enable bit */
#define TIM_CCMR1_OC2M_0 12U /* Output compare 2 mode bit 0 */
#define TIM_CCMR1_OC2M_1 13U /* Output compare 2 mode bit 1 */
#define TIM_CCMR1_OC2M_2 14U /* Output compare 2 mode bit 2 */
#define TIM_CCMR1_OC2CE 15U  /* Output compare 2 clear enable bit */

/* Timer CCMR2 bit definitions */
#define TIM_CCMR2_CC3S_0 0U  /* Capture/compare 3 selection bit 0 */
#define TIM_CCMR2_CC3S_1 1U  /* Capture/compare 3 selection bit 1 */
#define TIM_CCMR2_OC3FE 2U   /* Output compare 3 fast enable bit */
#define TIM_CCMR2_OC3PE 3U   /* Output compare 3 preload enable bit */
#define TIM_CCMR2_OC3M_0 4U  /* Output compare 3 mode bit 0 */
#define TIM_CCMR2_OC3M_1 5U  /* Output compare 3 mode bit 1 */
#define TIM_CCMR2_OC3M_2 6U  /* Output compare 3 mode bit 2 */
#define TIM_CCMR2_OC3CE 7U   /* Output compare 3 clear enable bit */
#define TIM_CCMR2_CC4S_0 8U  /* Capture/compare 4 selection bit 0 */
#define TIM_CCMR2_CC4S_1 9U  /* Capture/compare 4 selection bit 1 */
#define TIM_CCMR2_OC4FE 10U  /* Output compare 4 fast enable bit */
#define TIM_CCMR2_OC4PE 11U  /* Output compare 4 preload enable bit */
#define TIM_CCMR2_OC4M_0 12U /* Output compare 4 mode bit 0 */
#define TIM_CCMR2_OC4M_1 13U /* Output compare 4 mode bit 1 */
#define TIM_CCMR2_OC4M_2 14U /* Output compare 4 mode bit 2 */
#define TIM_CCMR2_OC4CE 15U  /* Output compare 4 clear enable bit */

/* Timer CCER bit definitions */
#define TIM_CCER_CC1E 0U   /* Capture/compare 1 output enable */
#define TIM_CCER_CC1P 1U   /* Capture/compare 1 output polarity */
#define TIM_CCER_CC1NE 2U  /* Capture/compare 1 complementary output enable */
#define TIM_CCER_CC1NP 3U  /* Capture/compare 1 complementary output polarity */
#define TIM_CCER_CC2E 4U   /* Capture/compare 2 output enable */
#define TIM_CCER_CC2P 5U   /* Capture/compare 2 output polarity */
#define TIM_CCER_CC2NE 6U  /* Capture/compare 2 complementary output enable */
#define TIM_CCER_CC2NP 7U  /* Capture/compare 2 complementary output polarity */
#define TIM_CCER_CC3E 8U   /* Capture/compare 3 output enable */
#define TIM_CCER_CC3P 9U   /* Capture/compare 3 output polarity */
#define TIM_CCER_CC3NE 10U /* Capture/compare 3 complementary output enable */
#define TIM_CCER_CC3NP 11U /* Capture/compare 3 complementary output polarity */
#define TIM_CCER_CC4E 12U  /* Capture/compare 4 output enable */
#define TIM_CCER_CC4P 13U  /* Capture/compare 4 output polarity */
#define TIM_CCER_CC4NP 14U /* Capture/compare 4 complementary output polarity */
#define TIM_CCER_CC4NE 15U /* Capture/compare 4 complementary output enable */

/* Timer DIER bit defintions */
#define TIM_DIER_UIE 0U    /* Update interrupt enable */
#define TIM_DIER_CC1IE 1U  /* Capture/compare 1 interrupt enable */
#define TIM_DIER_CC2IE 2U  /* Capture/compare 2 interrupt enable */
#define TIM_DIER_CC3IE 3U  /* Capture/compare 3 interrupt enable */
#define TIM_DIER_CC4IE 4U  /* Capture/compare 4 interrupt enable */
#define TIM_DIER_TIE 5U    /* Trigger interrupt enable */
#define TIM_DIER_COMIE 6U  /* Commutation interrupt enable */
#define TIM_DIER_BIE 7U    /* Break interrupt enable */
#define TIM_DIER_UDE 8U    /* Update DMA request enable */
#define TIM_DIER_CC1DE 9U  /* Capture/compare 1 DMA request enable */
#define TIM_DIER_CC2DE 10U /* Capture/compare 2 DMA request enable */
#define TIM_DIER_CC3DE 11U /* Capture/compare 3 DMA request enable */
#define TIM_DIER_CC4DE 12U /* Capture/compare 4 DMA request enable */
#define TIM_DIER_TDE 13U   /* Trigger DMA request enable */
#define TIM_DIER_COMDE 14U /* Commutation DMA request enable */
#define TIM_DIER_BDE 15U   /* Break DMA request enable */

/* macros */

#define IS_TIMx(TIMx) ((TIMx == TIM1) ? 1 : (TIMx == TIM2) ? 2 \
                                        : (TIMx == TIM3)   ? 3 \
                                        : (TIMx == TIM4)   ? 4 \
                                        : (TIMx == TIM5)   ? 5 \
                                                           : 0)

/* timer enums */

typedef enum
{
    tim_up_count,
    tim_down_count,
    tim_center_aligned_count
} timerCountDirection;

typedef enum
{
    tim_no_output,
    tim_channel_1,
    tim_channel_2,
    tim_channel_3,
    tim_channel_4
} timerOutputChannel;

/* PWM enums */
typedef enum
{
    PWM_channel_1 = 1,
    PWM_channel_2,
    PWM_channel_3,
    PWM_channel_4

} PWMChannel;

/* init structs */
typedef struct
{
    uint32 frequency;
    timerCountDirection direction;
    uint16 auto_reload_value;
    uint8 repetitions;
    timerOutputChannel channel; /* Output channel for PWM */
} TimerInitStruct;

typedef struct
{
    uint8 mode;         /* PWM mode */
    uint16 duty_cycle;  /* Duty cycle in percentage (0-100) */
    uint16 frequency;   /* Frequency in Hz */
    PWMChannel channel; /* Timer channel (1-4) */
} PWMInitStruct;

typedef struct
{
    uint8 mode;       /* Input capture mode */
    uint16 filter;    /* Input capture filter */
    uint8 channel;    /* Timer channel (1-4) */
    uint16 prescaler; /* Prescaler value */
} ICInitStruct;

/* prototypes */

/*
 * function: timer_init()
 * description: configure timers 1-5
 * param1: pointer to timer 1-5 periphral struct (members contain timer registers)
 * param2: pointer to timer init struct (members contain neccessary configurations)
 */
uint8 timer_init(TIM_TypeDef *TIMx, TimerInitStruct *initStruct);

/*
 * function: timer_start()
 * description: start counter
 * param1: pointer to timer 1-5 periphral struct (members contain timer registers)
 * return value: function execution status
 */
uint8 timer_start(TIM_TypeDef *TIMx);

/*
 * function: timer_stop()
 * description: stop counter
 * param1: pointer to timer 1-5 periphral struct (members contain timer registers)
 * return: function execution sta
 */
uint8 timer_stop(TIM_TypeDef *TIMx);
void timer_deinit(TIM_TypeDef *TIMx);
void timer_enable_interrupt(TIM_TypeDef *TIMx);
void timer_disable_interrupt(TIM_TypeDef *TIMx);
void IC_init(TIM_TypeDef *TIMx, ICInitStruct *initStruct);

void pwm_init(TIM_TypeDef *TIMx, PWMInitStruct *initStruct);

#endif