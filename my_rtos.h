

#ifndef MY_RTOS
#define MY_RTOS

/* includes */

/* helper includes */
#include "std_types.h"
#include "common_macros.h"

/* stm32 drivers */
#include "nvic.h"
#include "systick.h"
#include "stm32f4xx.h"
#include "pwr.h"
#include "gpio.h"
#include "terminal.h"
#include "usart.h"

/* definitions */
#define SCB_ICSR_PENDSVSET 28U

/* OS types */

typedef struct
{
    void *sp; // task stack pointer

    // and other members ..

} OS_TCB; // task control block

typedef void (*TaskHandler)(void);

/* prototypes */
void OS_task_create(OS_TCB *control_block,
                    TaskHandler handler,
                    uint32 *task_stack,
                    uint32 stack_size);
void OS_init(void);
void OS_scheduler(void);
void OS_run(void);


#endif