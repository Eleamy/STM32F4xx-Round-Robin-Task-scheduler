

#include "my_rtos.h"

void (*systick_callback_ptr)(void) = OS_scheduler;

/* Task control block global variables */
OS_TCB *g_task_arr[20];
uint32 g_task_arr_index = 0;
uint32 g_number_of_tasks = 0;

OS_TCB *volatile g_OSCurrent;
OS_TCB *volatile g_OSNext;

uint32 idleTask_stack[40];
OS_TCB idleTask;

void OS_on_idle(void)
{
    mcu_sleep();
}

void idleTaskHandler(void)
{
    while (1)
    {
        OS_on_idle();
    }
}

void OS_init(void)
{
    /* set PendSV interrupt to lowest priority */
    SCB->SHPR[2] |= (0xFF << 16);
    /* create idle task */
    OS_task_create(&idleTask,
                   idleTaskHandler,
                   idleTask_stack,
                   sizeof(idleTask_stack));
}

void OS_task_create(OS_TCB *control_block,
                    TaskHandler handler,
                    uint32 *task_stack,
                    uint32 stack_size)
{

    uint32 *sp = (uint32 *)((((uint32)task_stack + stack_size) / 8) * 8); // align task stack by 8 bytes + set sp to top of task stack
    /* setup task stack (stack frame) */
    *(--sp) = (1 << 24);       // PSR
    *(--sp) = (uint32)handler; // PC
    *(--sp) = 0x0000000E;      // LR
    *(--sp) = 0x0000000C;      // r12
    *(--sp) = 0x00000003;      // r3
    *(--sp) = 0x00000002;      // r2
    *(--sp) = 0x00000001;      // r1
    *(--sp) = 0x00000000;      // r0

    /* fill r4-r11 with dummy data */
    *(--sp) = 0x0000000B; // r11
    *(--sp) = 0x0000000A; // r10
    *(--sp) = 0x00000009; // r9
    *(--sp) = 0x00000008; // r8
    *(--sp) = 0x00000007; // r7
    *(--sp) = 0x00000006; // r6
    *(--sp) = 0x00000005; // r5
    *(--sp) = 0x00000004; // r4

    /* set task sp pointer after stacking */
    control_block->sp = (void *)sp;

    /* align bottom of the stack to 8 bytes */
    uint32 *stackLimit = (uint32 *)(((((uint32)task_stack - 1U) / 8U) + 1U) * 8U);

    /* fill remaining task stack with 0xDEADBEAF */
    for (--sp; sp >= stackLimit; sp--)
    {
        *sp = 0xDEADBEEF;
    }

    /* queue task in task array */
    g_task_arr[g_number_of_tasks] = control_block;
    g_number_of_tasks++;
}

void OS_scheduler(void)
{
    /* switch to next task in task array */
    if (g_task_arr_index == g_number_of_tasks - 1) // if schedular reaches the end of task array
    {
        g_task_arr_index = 0; // loop back to task 1
    }
    else
    {
        g_task_arr_index++;
    }

    g_OSNext = g_task_arr[g_task_arr_index];

    /* signal PendSV interrupt */
    if (g_OSNext != g_OSCurrent)
    {
        SET_BIT(SCB->ICSR, SCB_ICSR_PENDSVSET);
    }
}

void OS_run(void)
{
    /* initialize systick timer to run every 100 cycles */
    systick_init(100000, SYS_CLK, systick_interrupt);

    /* start the scheduler */
    __DISABLE_INTERRUPTS();
    OS_scheduler();
    __ENABLE_INTERRUPTS(); // PendSV should start once interrupts are enabled

    /* code should never be reached */
    systick_deinit();
    return;
}

__attribute__((naked)) // compiler attribute naked: tells the compiler to leave stack management to user
void
PendSV_Handler(void)
{

    __asm volatile ( // __asm()  tells the compiler to execute assembly instructions passed as string argument

        /* disable interrupts*/
        "CPSID      I           \n"

        /* if (OSCurrent != NULL_PTR )  */
        "LDR    r1,=g_OSCurrent   \n"
        "LDR    r1,[r1,#0x00]   \n"
        "CMP    r1,#0           \n"
        "BEQ    PendSV_Restore  \n"

        /* { */
        /* push registers r4-r11 on current task stack */
        "PUSH   {r4-r11}        \n"
        /* } */

        "PendSV_Restore:        \n" // restore next task context
        /* OSCurrent->sp = sp */
        "LDR    r1,=g_OSCurrent \n"
        "LDR    r1,[r1,#0x00]   \n"
        "MOV    r0,sp           \n"
        "STR    r0,[r1,#0x00]   \n"

        /* sp = OSNext->sp */
        "LDR    r1,=g_OSNext    \n"
        "LDR    r1,[r1,#0x00]   \n"
        "LDR    r0,[r1,#0x00]   \n"
        "MOV    sp,r0           \n"

        /* OSCurrent = OSNext */
        "LDR    r1,=g_OSNext      \n"
        "LDR    r1,[r1,#0x00]   \n"
        "LDR    r2,=g_OSCurrent   \n"
        "STR    r1,[r2,#0x00]   \n"

        /* pop r4-r11 on next task stack */
        "POP    {r4-r11}        \n"

        /* re-enable interrupts */
        "CPSIE      I           \n"

        /* return to the next thread */
        "BX         lr          \n");
}