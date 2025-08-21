
#include "terminal.h"

USARTInitStruct USARTInitStruct1 = {
    usart_sample_16,
    usart_1_sample,
    no_parity,
    usart_8_bit,
    idle_line,
    reciver_active,
    usart_one_stop_bit,
    clk_disable,
    usart_low_idle,
    first_edge,
    38400,
};

 sint8 terminal_buffer[50];

static uint32 my_strlen(const sint8 *str)
{

    uint32 i;
    for (i = 1; str[i] != '\0'; i++)
        ;
    return i;
}
static uint8 my_strcmp(const sint8 *str1, const sint8 *str2)
{

    if (my_strlen(str1) != my_strlen(str2))
    {
        return FALSE;
    }

    for (uint32 i = 0; ((str1[i] != '\0') && (str2[i] != '\0')); i++)
    {
        if (str1[i] != str2[i])
            return FALSE;
    }
    return TRUE;
}

void terminal_init(void)
{
    usart_init(TERMINAL_CHANNEL, &USARTInitStruct1);
    usart_send_string(TERMINAL_CHANNEL, ">> Terminal started successfully \r");
}
void terminal_println(sint8 *str)
{
    usart_send_string(TERMINAL_CHANNEL, str);
}

void terminal_newline(void)
{
    usart_send_byte(TERMINAL_CHANNEL, NEW_LINE);
}

void terminal_loopback_echo(void)
{
    usart_recieve_string_loopback(TERMINAL_CHANNEL, terminal_buffer);
    usart_send_string(TERMINAL_CHANNEL, terminal_buffer); // echo string 
    if (my_strcmp(terminal_buffer, "clear\r"))
        terminal_clear();
}

void terminal_loopback(void)
{
    usart_recieve_string_loopback(TERMINAL_CHANNEL, terminal_buffer);
    if (my_strcmp(terminal_buffer, "clear\r"))
        terminal_clear();
}

void terminal_clear(void)
{
    usart_send_byte(TERMINAL_CHANNEL, '\f');
}

void terminal_print_int(uint32 number)
{
    sint32 i, k = 0;
    uint32 divisor;

    if (number >= 10)
    {
        divisor = 10;
        for (i = 1; number / divisor > 9; i++)
            divisor *= 10;
    }
    else
    {
        divisor = 1;
        i = 0;
    }
    terminal_buffer[i + 1] = '\0';

    while (k <= i)
    {
        terminal_buffer[k] = (number / divisor) + 48;
        number -= (number / divisor) * divisor;
        divisor /= 10;
        k++;
    }
    usart_send_string(TERMINAL_CHANNEL, terminal_buffer);
}
