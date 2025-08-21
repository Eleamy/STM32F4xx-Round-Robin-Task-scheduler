

#ifndef SYSTICK_H
#define SYSTICK_H

/* includes */

#include "common_macros.h"
#include "std_types.h"
#include "stm32f4xx.h"
#include "nvic.h"

/* definitions */

/* CTRL registrer definitions */

#define SYSTICK_CTRL_COUNTFLAG  16
#define SYSTICK_CTRL_CLKSOURCE  2 
#define SYSTICK_CTRL_TICKINT    1
#define SYSTICK_CTRL_ENABLE     0


/*  systick_init return types */


/* systick types */

typedef enum {
    SYS_CLK,
    SYS_CLK_8
}systickClkSource;

typedef enum {
    systick_poll,
    systick_interrupt
}systickOpType;

/* function prototypes */
void systick_init(uint32 reloadValue, systickClkSource tickSource, systickOpType opType);
uint32 systick_read_count_flag(void);
void systick_deinit(void);
#endif /* end if header file */