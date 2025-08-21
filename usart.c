

#include "usart.h"

uint32 get_pclk2_freq(void)
{
    uint32 sysclk, hclk, pclk2;
    uint32 sw = (RCC->CFGR >> 2) & 0x3;

    switch (sw)
    {
    case 0:
        sysclk = 16000000;
        break; // HSI
    case 1:
        sysclk = 8000000;
        break; // HSE (adjust if using external)
    default:
        sysclk = 16000000;
    }

    uint32 hpre = (RCC->CFGR >> 4) & 0xF;
    uint32 ahb_div = (hpre < 8) ? 1 : (1 << ((hpre - 7)));

    uint32 ppre2 = (RCC->CFGR >> 13) & 0x7;
    uint32 apb2_div = (ppre2 < 4) ? 1 : (1 << (ppre2 - 3));

    hclk = sysclk / ahb_div;
    pclk2 = hclk / apb2_div;

    return pclk2;
}

static uint16 usart_BRR_calculator(uint32 BR, sampleRate sampleRate)
{
    uint32 multiplier = (sampleRate == usart_sample_16) ? 16 : 8;
    uint32 usartdiv_times_100 = (FCLK * 100) / (multiplier * BR);

    uint32 mantissa = usartdiv_times_100 / 100;
    uint32 fraction = ((usartdiv_times_100 % 100) * multiplier + 50) / 100;

    // Clamp fraction to valid size
    if (sampleRate == usart_sample_16 && fraction > 15)
    {
        mantissa++;
        fraction = 0;
    }
    else if (sampleRate == usart_sample_8 && fraction > 7)
    {
        mantissa++;
        fraction = 0;
    }

    return (mantissa << 4) | (fraction & ((sampleRate == usart_sample_16) ? 0x0F : 0x07));
}

void usart_init(USART_TypeDef *USARTx, USARTInitStruct *initStruct)
{
    /*enable usartx clock*/

    switch (IS_USARTx(USARTx))
    {
    case 1:
        /*reset usart1*/
        SET_BIT(RCC->APB2RSTR, USART1_RESET);
        CLEAR_BIT(RCC->APB2RSTR, USART1_RESET);
        /*enable USART1 clock*/
        SET_BIT(RCC->APB2ENR, USART1_ENABLE_CLOCK);
        break;

    case 2:
        /*reset usart2*/
        SET_BIT(RCC->APB1RSTR, USART2_RESET);
        CLEAR_BIT(RCC->APB1RSTR, USART2_RESET);
        /*enable USART2 clock*/
        SET_BIT(RCC->APB1ENR, USART2_ENABLE_CLOCK);
        break;

    case 6:
        /*reset usart6*/
        SET_BIT(RCC->APB2RSTR, USART6_RESET);
        CLEAR_BIT(RCC->APB2RSTR, USART6_RESET);
        /*enable USART6 clock*/
        SET_BIT(RCC->APB2ENR, USART6_ENABLE_CLOCK);
        break;

    default:
        return;
    }

    /*setup oversample rate*/
    switch (initStruct->sampleRate)
    {
    case (usart_sample_16):
        CLEAR_BIT(USARTx->CR1, OVER8);
        break;
    case (usart_sample_8):
        SET_BIT(USARTx->CR1, OVER8);
        break;
    }

    /*setup bit sample mode*/
    switch (initStruct->sampleMode)
    {
    case (usart_3_sample):
        CLEAR_BIT(USARTx->CR3, ONEBIT);
        break;
    case (usart_1_sample):
        SET_BIT(USARTx->CR3, ONEBIT);
        break;
    }

    /*setup parity*/
    switch (initStruct->parity)
    {
    case (even_parity):
        SET_BIT(USARTx->CR1, PCE);
        CLEAR_BIT(USARTx->CR1, PS);
        break;
    case (odd_parity):
        SET_BIT(USARTx->CR1, PCE);
        SET_BIT(USARTx->CR1, PS);
        break;
    case (no_parity):
        CLEAR_BIT(USARTx->CR1, PCE);
        break;
    }

    /*setup frame length*/
    switch (initStruct->length)
    {
    case (usart_8_bit):
        CLEAR_BIT(USARTx->CR1, M);
        break;
    case (usart_9_bit):
        SET_BIT(USARTx->CR1, M);
        break;
    }

    /*setup wake method*/

    switch (initStruct->wakeMethod)
    {
    case (idle_line):
        CLEAR_BIT(USARTx->CR1, WAKE);
        break;
    case (address_mark):
        SET_BIT(USARTx->CR1, WAKE);
        break;
    }

    /*setup reciver wake mode*/
    switch (initStruct->wakeMode)
    {
    case (reciver_active):
        CLEAR_BIT(USARTx->CR1, RWU);
        break;
    case (reciver_mute):
        SET_BIT(USARTx->CR1, RWU);
        break;
    }

    /*setup stop bits*/
    switch (initStruct->stopBits)
    {
    case (usart_one_stop_bit):
        CLEAR_2_BITS(USARTx->CR2, STOP1);
        break;
    case (usart_half_stop_bit):
        CLEAR_BIT(USARTx->CR2, STOP1);
        SET_BIT(USARTx->CR2, STOP2);
        break;
    case (usart_two_stop_bit):
        SET_2_BITS(USARTx->CR2, STOP1);
        break;
    }

    /*setup usart clock*/
    switch (initStruct->clock)
    {
    case (clk_disable):
        CLEAR_BIT(USARTx->CR2, CLKEN);
        break;
    case (clk_enable):
        SET_BIT(USARTx->CR2, CLKEN);
        break;
    }

    /*setup clk polarity*/
    switch (initStruct->polarity)
    {
    case (usart_low_idle):
        CLEAR_BIT(USARTx->CR2, CPOL);
        break;
    case (usart_high_idle):
        SET_BIT(USARTx->CR2, CPOL);
        break;
    }

    /*setup clk phase*/

    switch (initStruct->phase)
    {
    case (first_edge):
        CLEAR_BIT(USARTx->CR2, CPHA);
        break;
    case (second_edge):
        SET_BIT(USARTx->CR2, CPHA);
        break;
    }

    /*setup bauderate*/
    USARTx->BRR = usart_BRR_calculator(initStruct->baudRate, initStruct->sampleRate);
    // USART1->BRR = 0b01101000001011;

    /*enable USART*/
    USARTx->CR1 |= (1 << UE);

    /* enable usart transmit buffer*/
    USARTx->CR1 |= (1 << TE);
    /* enable usart recieve buffer*/
    USARTx->CR1 |= (1 << RE);
}

void usart_send_byte(USART_TypeDef *USARTx, sint8 data)
{
    while (!(USARTx->SR & (1 << TXE)))
        ;
    USARTx->DR = data;
}

void usart_send_string(USART_TypeDef *USARTx, const sint8 *str)
{

    for (uint8 i = 0; str[i] != '\0'; i++)
    {
        usart_send_byte(USARTx, str[i]);
    }
}

uint8 usart_receive_byte(USART_TypeDef *USARTx)
{
    while (!(USARTx->SR & (1 << RXNE)))
        ;
    return USARTx->DR;
}

void usart_recieve_string_loopback(USART_TypeDef *USARTx, sint8 *buffer)
{

    uint8 i = 0;
    uint8 recived_data;

    while (i < 50)
    {
        recived_data = usart_receive_byte(USARTx);
        usart_send_byte(USARTx, recived_data);
        if ((recived_data == ENTER_KEY) && i == 0){
            break;
        }

        buffer[i] = recived_data;
        i++;
        if (recived_data == ENTER_KEY)
        {
            break;
        }
    }

    buffer[i] = '\0';
}

void usart_enable_interrupt(USART_TypeDef *USARTx)
{
    switch (IS_USARTx(USARTx))
    {
    case 1:
        nvic_enable_interrupt(INT_USART1);
        break;
    case 2:
        nvic_enable_interrupt(INT_USART2);
        break;
    case 6:
        nvic_enable_interrupt(INT_USART6);
        break;
    }
}

void usart_disable_interrupt(USART_TypeDef *USARTx)
{
    switch (IS_USARTx(USARTx))
    {
    case 1:
        nvic_disable_interrupt(INT_USART1);
        break;
    case 2:
        nvic_disable_interrupt(INT_USART2);
        break;
    case 6:
        nvic_disable_interrupt(INT_USART6);
        break;
    }
}

void usart_deinit(USART_TypeDef *USARTx)
{
}