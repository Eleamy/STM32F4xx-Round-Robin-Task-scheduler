#include "timer.h"

uint8 g_tim_init_flag = 0;

static uint16 calculate_prescaler(uint32 frequency)
{
    if (((F_CLK / frequency) - 1) > MAX_PRESCALER)
    {
        return MAX_PRESCALER;
    }
    /* Calculate the prescaler value based on the desired frequency */
    return (uint16)((F_CLK / frequency) - 1); // Subtract 1 because prescaler is zero-based
}

uint8 timer_init(TIM_TypeDef *TIMx, TimerInitStruct *initStruct)
{
    uint32 temp; // set to perform registers dummy reads 

    if (TIMx == NULL_PTR || initStruct == NULL_PTR)
    {
        return INIT_INVALID_PARAMETER; // Invalid parameters
    }

    /* check timer number (timers 1-5 supprted) */
    uint16 timer_instance = IS_TIMx(TIMx);

    /* check if timer is already initialized */
    if (BIT_IS_SET(g_tim_init_flag, timer_instance))
    {
        return INIT_TIMER_INITIALIZED;
    }
    else
    {
        SET_BIT(g_tim_init_flag, timer_instance); // mark timer as initialized
    }

    switch (timer_instance)
    {
    case 0:
        CLEAR_BIT(g_tim_init_flag, timer_instance); // remove initialization mark
        return INIT_INVALID_TIMER_INSTANCE;

    case 1:
        /* reset timer */
        SET_BIT(RCC->APB2RSTR, RCC_TIM1_RESET);
        CLEAR_BIT(RCC->APB2RSTR, RCC_TIM1_RESET);
        /* enable clock */
        SET_BIT(RCC->APB2ENR, RCC_TIM1_CLOCK_ENABLE);
        temp = RCC->APB2ENR; // dummy read to ensure clock is enabled (STM32 specific)
        break;
    default:
        /* reset timer */
        SET_BIT(RCC->APB1RSTR, (timer_instance - 2));
        CLEAR_BIT(RCC->APB1RSTR, (timer_instance - 2));

        /* enable clock */
        SET_BIT(RCC->APB1ENR, (timer_instance - 2));
        temp = RCC->APB1ENR; // dummy read to ensure clock is enabled (STM32 specific)
    }

    /* clear timer registers */
    TIMx->CR1 = 0;
    TIMx->SR = 0;
    TIMx->DIER = 0;

    /* setup counter prescaler */
    TIMx->PSC = calculate_prescaler(initStruct->frequency);

    /* setup auto-reload value */
    TIMx->ARR = initStruct->auto_reload_value;

    /* setup direction */
    switch (initStruct->direction)
    {
    case tim_up_count:
        CLEAR_BIT(TIMx->CR1, TIM_CR1_DIR);
        TIMx->CNT = 0; // Set counter to 0 for up counting
        break;
    case tim_down_count:
        SET_BIT(TIMx->CR1, TIM_CR1_DIR);
        TIMx->CNT = initStruct->auto_reload_value; // Set counter to auto-reload value for down counting
        break;
    case tim_center_aligned_count:
        SET_BIT(TIMx->CR1, TIM_CR1_CMS_0); // Center-aligned mode
        SET_BIT(TIMx->CR1, TIM_CR1_CMS_1);
        CLEAR_BIT(TIMx->CR1, TIM_CR1_DIR); // Direction is not applicable in center-aligned mode
        break;
    default:

        return INIT_INVALID_DIRECTION; // Invalid direction
    }
    /* setup timer output channel */
    switch (initStruct->channel)
    {
    case tim_no_output:
        CLEAR_BIT(TIMx->CCER, TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E);
        break;
    case tim_channel_1:
        SET_BIT(TIMx->CCER, TIM_CCER_CC1E);
        CLEAR_BIT(TIMx->CCER, TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E);
        break;
    case tim_channel_2:
        SET_BIT(TIMx->CCER, TIM_CCER_CC2E);
        CLEAR_BIT(TIMx->CCER, TIM_CCER_CC1E | TIM_CCER_CC3E | TIM_CCER_CC4E);
        break;
    case tim_channel_3:
        SET_BIT(TIMx->CCER, TIM_CCER_CC3E);
        CLEAR_BIT(TIMx->CCER, TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC4E);
        break;
    case tim_channel_4:
        SET_BIT(TIMx->CCER, TIM_CCER_CC4E);
        CLEAR_BIT(TIMx->CCER, TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E);
        break;
    default:
        return INIT_INVALID_CHANNEL; // Invalid channel
    }

    /* setup repetitions (works only in one pulse mode) */
    TIMx->RCR = initStruct->repetitions;

    /* force an update event for PSC and ARR vlaues to take effect */
    SET_BIT(TIMx->EGR, TIM_EGR_UG);

    return INIT_SUCCESS;
}

uint8 timer_start(TIM_TypeDef *TIMx)
{
    if (TIMx == NULL_PTR)
    {
        return START_INVALID_PARAMETER; // Invalid parameter
    }

    TIMx->SR = 0; // Clear any pending update flag

    /* check timer instance (timers 1-5 are supported)*/
    uint8 timer_instance = IS_TIMx(TIMx);
    if ((0 == timer_instance) || (5 < timer_instance))
    {
        return START_INVALID_TIMER_INSTANCE;
    }

    /* check if timer uninitialized */
    if (BIT_IS_CLEAR(g_tim_init_flag, timer_instance))
    {
        return START_TIMER_UNINITIALIZED;
    }

    /* enable timer */
    SET_BIT(TIMx->CR1, TIM_CR1_CEN);

    return START_SUCCESS;
}

uint8 timer_stop(TIM_TypeDef *TIMx)
{
    if (TIMx == NULL_PTR)
    {
        return STOP_INVALID_PARAMETER; // Invalid parameter
    }

    /* check timer instance */
    uint8 timer_instance = IS_TIMx(TIMx);
    if (0 == timer_instance || 5 > timer_instance)
    {
        return STOP_INVALID_PARAMETER;
    }

    /* check if timer uninitialized*/
    if (BIT_IS_CLEAR(g_tim_init_flag, timer_instance))
    {
        return STOP_TIMER_UNINITIALIZED;
    }
    /* disable timer */
    CLEAR_BIT(TIMx->CR1, TIM_CR1_CEN);
    return STOP_SUCCESS;
}
void pwm_init(TIM_TypeDef *TIMx, PWMInitStruct *initStruct) // under construction
{
    if (TIMx == NULL_PTR || initStruct == NULL_PTR)
    {
        return; // Invalid parameters
    }

    /* check if timer is valid */
    if (IS_TIMx(TIMx) == 0)
    {
        return; // Invalid timer
    }

    /* enable timer clock */
    uint8 timer_instance = IS_TIMx(TIMx);
    switch (timer_instance)
    {
    case 0:
        return;
    case 1:
        /* reset timer */
        SET_BIT(RCC->APB2RSTR, RCC_TIM1_RESET);
        CLEAR_BIT(RCC->APB2RSTR, RCC_TIM1_RESET);
        /* enable clock */
        SET_BIT(RCC->APB2ENR, RCC_TIM1_CLOCK_ENABLE);
        break;
    default:
        /* reset timer */
        SET_BIT(RCC->APB1RSTR, (timer_instance - 2));
        CLEAR_BIT(RCC->APB1RSTR, (timer_instance - 2));

        /* enable clock */
        SET_BIT(RCC->APB1ENR, (timer_instance - 2));
    }

    /* setup PWM mode and duty cycle */
    TIMx->CCMR1 |= (initStruct->mode << TIM_CCMR1_OC1M_0); // Set PWM mode
    TIMx->CCR1 = initStruct->duty_cycle;                   // Set duty cycle

    /* setup PWM channel */
    switch (initStruct->channel)
    {
    case PWM_channel_1:
        TIMx->CCER |= TIM_CCER_CC1E; // Enable channel 1
        break;
    case PWM_channel_2:
        TIMx->CCER |= TIM_CCER_CC2E; // Enable channel 2
        break;
    case PWM_channel_3:
        TIMx->CCER |= TIM_CCER_CC3E; // Enable channel 3
        break;
    case PWM_channel_4:
        TIMx->CCER |= TIM_CCER_CC4E; // Enable channel 4
        break;
    default:
        return; // Invalid channel
    }

    /* enable timer */
    SET_BIT(TIMx->CR1, TIM_CR1_CEN);
}

void IC_init(TIM_TypeDef *TIMx, ICInitStruct *initStruct) // under construction
{
    if (TIMx == NULL_PTR || initStruct == NULL_PTR)
    {
        return; // Invalid parameters
    }

    /* check if timer is valid */
    if (IS_TIMx(TIMx) == 0)
    {
        return; // Invalid timer
    }

    /* enable timer clock */
    uint8 timer_channel = IS_TIMx(TIMx);
    switch (timer_channel)
    {
    case 0:
        return;
    case 1:
        /* reset timer */
        SET_BIT(RCC->APB2RSTR, RCC_TIM1_RESET);
        CLEAR_BIT(RCC->APB2RSTR, RCC_TIM1_RESET);
        /* enable clock */
        SET_BIT(RCC->APB2ENR, RCC_TIM1_CLOCK_ENABLE);
        break;
    default:
        /* reset timer */
        SET_BIT(RCC->APB1RSTR, (timer_channel - 2));
        CLEAR_BIT(RCC->APB1RSTR, (timer_channel - 2));

        /* enable clock */
        SET_BIT(RCC->APB1ENR, (timer_channel - 2));
    }

    /* setup input capture mode and parameters */
}

void timer_deinit(TIM_TypeDef *TIMx)
{
    if (TIMx == NULL_PTR)
    {
        return; // Invalid parameter
    }

    /* disable timer */
    CLEAR_BIT(TIMx->CR1, TIM_CR1_CEN);

    /* disable clock */
    uint8 timer_instance = IS_TIMx(TIMx);
    switch (timer_instance)
    {
    case 0:
        return;
    case 1:
        /* disable clock */
        CLEAR_BIT(RCC->APB2ENR, RCC_TIM1_CLOCK_ENABLE);
        break;
    default:
        /* disable clock */
        CLEAR_BIT(RCC->APB1ENR, (timer_instance - 2));
        break;
    }
}

void timer_enable_interrupt(TIM_TypeDef *TIMx)
{
    if (TIMx == NULL_PTR)
    {
        return; // Invalid parameter
    }

    TIMx->SR = 0; // Clear any pending update flag
    /* enable update interrupt */
    SET_BIT(TIMx->DIER, TIM_DIER_UIE);

    /* enable timer interrupt in NVIC */
    switch (IS_TIMx(TIMx))
    {
    case 1:
        nvic_enable_interrupt(INT_TIM1_UP_TIM10);
        break;
    case 2:
        nvic_enable_interrupt(INT_TIM2);
        break;
    case 3:
        nvic_enable_interrupt(INT_TIM3);
        break;
    case 4:
        nvic_enable_interrupt(INT_TIM4);
        break;
    case 5:
        nvic_enable_interrupt(INT_TIM5);
        break;
    }
}

void timer_disable_interrupt(TIM_TypeDef *TIMx)
{
    if (TIMx == NULL_PTR)
    {
        return; // Invalid parameter
    }

    /* disable update interrupt */
    CLEAR_BIT(TIMx->DIER, TIM_DIER_UIE);

    /* disable timer interrupt in NVIC */
    switch (IS_TIMx(TIMx))
    {
    case 1:
        nvic_disable_interrupt(INT_TIM1_UP_TIM10);
        break;
    case 2:
        nvic_disable_interrupt(INT_TIM2);
        break;
    case 3:
        nvic_disable_interrupt(INT_TIM3);
        break;
    case 4:
        nvic_disable_interrupt(INT_TIM4);
        break;
    case 5:
        nvic_disable_interrupt(INT_TIM5);
        break;
    }
}