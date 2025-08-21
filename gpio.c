#include "gpio.h"



void gpio_setup_pin(GPIO_TypeDef *GPIOx, pin pin, gpioSpeed speed, gpioMode mode, gpioType type, gpioPullDir direction)
{
    uint8 temp = IS_GPIOx(GPIOx);
    switch (temp)
    {

    case (1):
        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
        break;

    case (2):
        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
        break;
    default:
    }

    gpio_set_mode(GPIOx, mode, pin);
    gpio_set_output_type(GPIOx, type, pin);
    gpio_set_output_speed(GPIOx, speed, pin);
    gpio_set_pull_direction(GPIOx, direction, pin);
}

void gpio_set_mode(GPIO_TypeDef *GPIOx, gpioMode mode, pin pin)
{
    switch (mode)
    {

    case input:
        CLEAR_2_BITS(GPIOx->MODER, (2 * pin));
        break;

    case output:
        SET_BIT(GPIOx->MODER, (2 * pin));
        CLEAR_BIT(GPIOx->MODER, ((2 * pin) + 1));
        break;

    case alternate_function:
        CLEAR_BIT(GPIOx->MODER, (2 * pin));
        SET_BIT(GPIOx->MODER, ((2 * pin) + 1));
        break;

    case Analogue:
        SET_2_BITS(GPIOx->MODER, (2 * pin));
        break;
    }
}

void gpio_set_output_type(GPIO_TypeDef *GPIOx, gpioType type, pin pin)
{

    switch (type)
    {

    case push_pull:
        CLEAR_BIT(GPIOx->OTYPER, pin);
        break;

    case open_drain:
        SET_BIT(GPIOx->OTYPER, pin);
        break;
    }
}

void gpio_set_output_speed(GPIO_TypeDef *GPIOx, gpioSpeed speed, pin pin)
{

    switch (speed)
    {
    case low_speed:
        CLEAR_2_BITS(GPIOx->OSPEEDR, 2 * pin);
        break;

    case mediuem_speed:
        SET_BIT(GPIOx->OSPEEDR, 2 * pin);
        CLEAR_BIT(GPIOx->OSPEEDR, ((2 * pin) + 1));
        break;

    case high_speed:
        CLEAR_BIT(GPIOx->OSPEEDR, 2 * pin);
        SET_BIT(GPIOx->OSPEEDR, ((2 * pin) + 1));
        break;

    case very_high_speed:
        SET_2_BITS(GPIOx->OSPEEDR, 2 * pin);
        break;
    }
}

void gpio_set_pull_direction(GPIO_TypeDef *GPIOx, gpioPullDir pullDir, pin pin)
{

    switch (pullDir)
    {
    case no_pull:
        CLEAR_2_BITS(GPIOx->PUPDR, 2 * pin);
        break;

    case pull_up:
        SET_BIT(GPIOx->PUPDR, 2 * pin);
        CLEAR_BIT(GPIOx->PUPDR, (2 * pin + 1));
        break;

    case pull_down:
        CLEAR_BIT(GPIOx->PUPDR, 2 * pin);
        SET_BIT(GPIOx->PUPDR, (2 * pin + 1));
        break;
    }
}

void gpio_write_pin(port port, pin pin, pinState state)
{
    if (port == portA)
    {
        switch (state)
        {

        case low:
            SET_BIT(GPIOA->BSRR, (pin + 16));
            break;

        case high:
            SET_BIT(GPIOA->BSRR, pin);
            break;
        }
    }

    else
    {
        switch (state)
        {

        case low:
            CLEAR_BIT(GPIOB->ODR, pin);
            break;

        case high:
            SET_BIT(GPIOB->ODR, pin);
            break;
        }
    }
}
pinState gpio_read_pin(port port, pin pin)
{
    if (pin > 15)
        return low; // Invalid pin

    switch (port)
    {
    case portA:
        return (GPIOA->IDR & (1 << pin)) ? high : low;

    case portB:
        return (GPIOB->IDR & (1 << pin)) ? high : low;

    default:
        return low;
    }
}

void gpio_toggle_pin(port port, pin pin)
{
    if (port == portA)
    {
        TOGGLE_BIT(GPIOA->ODR, pin);
    }

    else
    {
        TOGGLE_BIT(GPIOB->ODR, pin);
    }
}
void gpio_deinit(gpioInitStruct *gpioInitStruct_1)
{
    switch (gpioInitStruct_1->port)
    {

    case (portA):
        CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
        break;

    case (portB):
        CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
        break;
    }
}

void gpio_setup_AF(GPIO_TypeDef *GPIOx, pin pin, AFType af)
{
    /* basic argument checks */
    if (!IS_GPIOx(GPIOx) || pin > 15 || af > 15)
        return;

    /* select the AF number (AFRL/AFRH) */
    uint32 reg_index = pin >> 3;       /* 0 = AFRL, 1 = AFRH  */
    uint32 bit_pos = (pin & 0x7U) * 4; /* 4 bits per pin      */

    GPIOx->AFR[reg_index] &= ~(0xFU << bit_pos);      /* clear old AF   */
    GPIOx->AFR[reg_index] |= ((uint32)af << bit_pos); /* set new AF */
}

uint8 gpio_is_input_set(port port, pin pin)
{
    return (GPIOA->IDR & (1 << pin));
}