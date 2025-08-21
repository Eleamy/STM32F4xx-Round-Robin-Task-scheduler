

#ifndef USART_H
#define USART_H

/*includes*/
#include "stm32f4xx.h"
#include "gpio.h"
#include "nvic.h"

#define FCLK (16000000)
/*RCC registers definitions*/

#define USART1_ENABLE_CLOCK 4U
#define USART2_ENABLE_CLOCK 17U
#define USART6_ENABLE_CLOCK 5U

#define USART1_RESET 4U
#define USART2_RESET 17U
#define USART6_RESET 5U

/* CR1 regsiter bit definitions*/

#define OVER8 15U
#define UE 13U
#define M 12U
#define WAKE 11U
#define PCE 10U
#define PS 9U
#define TE 3U
#define RE 2U
#define RWU 1U

/* CR2 regsiter bit definitions*/

#define STOP1 12U
#define STOP2 13U
#define CLKEN 11U
#define CPOL 10U
#define CPHA 9U
#define ADDR_POS 0U

/* CR3 regsiter bit definitions*/

#define ONEBIT 11U

/* GTPR regsiter bit definitions*/

#define PSC_POS 0U
#define GT_POS 8U

/* SR regsiter bit definitions*/

#define TXE 7U
#define RXNE 5U

/* key defintions*/

#define ENTER_KEY 13
/*macros*/
#define IS_USARTx(USARTx) ((USARTx == USART1) ? 1 : (USARTx == USART2) ? 2 \
                                                : (USARTx == USART6)   ? 6 \
                                                                       : 0)

/*types*/

/*prototypes*/
typedef enum
{
    usart_sample_16,
    usart_sample_8
} sampleRate;

typedef enum
{
    usart_3_sample,
    usart_1_sample
} sampleMode;

typedef enum
{
    no_parity,
    odd_parity,
    even_parity
} parity;

typedef enum
{
    usart_8_bit,
    usart_9_bit
} usartFrameLength;

typedef enum
{
    idle_line,
    address_mark
} usartWakeMethod;

typedef enum
{
    reciver_active,
    reciver_mute
} recieverWakeMode;

typedef enum
{
    usart_one_stop_bit,
    usart_half_stop_bit,
    usart_two_stop_bit,

} usartStopBits;

typedef enum
{
    clk_disable,
    clk_enable
} usartClock;

typedef enum
{
    usart_low_idle,
    usart_high_idle
} usartPolarity;

typedef enum
{
    first_edge,
    second_edge
} usartPhase;

typedef uint8 nodeAddress;

typedef struct
{
    sampleRate sampleRate;
    sampleMode sampleMode;
    parity parity;
    usartFrameLength length;
    usartWakeMethod wakeMethod;
    recieverWakeMode wakeMode;
    usartStopBits stopBits;
    usartClock clock;
    usartPolarity polarity;
    usartPhase phase;
    uint32 baudRate;

} USARTInitStruct;

/*prototypes*/

void usart_init(USART_TypeDef *USARTx, USARTInitStruct *initStruct);
void usart_send_byte(USART_TypeDef *USARTx, sint8 data);
void usart_send_string(USART_TypeDef *USARTx, const sint8 *str);
uint8 usart_receive_byte(USART_TypeDef *USARTx);
void usart_recieve_string_loopback(USART_TypeDef *USARTx, sint8 *buffer);

#endif