

#ifndef TERMINAL_H
#define TERMINAL_H

/*includes*/
#include "usart.h"

/*definitions*/
#define NEW_LINE 13
#define TERMINAL_CHANNEL USART1
/*types*/

/*prottype*/
void terminal_init(void);
void terminal_println(sint8 *str);
void terminal_newline(void);
void terminal_loopback_echo(void);
void terminal_loopback(void);
void terminal_clear(void);
void terminal_print_int(uint32 number);

#endif