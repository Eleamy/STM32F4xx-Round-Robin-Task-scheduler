#include "timer.h"
#include "nvic.h"
#include "systick.h"
#include "my_rtos.h"
#include "terminal.h"
#include "gpio.h"


void software_delay_ms(uint32 delay)
{
    while (delay--)
    {
        // loop for 1ms
        for (uint32 i = 0; i < (F_CLK/10000); i++)
        {
            __NOP();    // do nothing
        }
    }
}


uint32 task1_stack[40];     //8 byte alignment preferred (40 / 8 = 5)
OS_TCB task1_TCB;
void task1(void)
{
    while (1)
    {
        gpio_toggle_pin(portA, pin_1);
        software_delay_ms(1000);
    }
}

uint32 task2_stack[40];
OS_TCB  task2_TCB;
void task2(void){
    while(1){
        gpio_toggle_pin(portA, pin_2);
        software_delay_ms(1000);
    }
}

uint32 task3_stack[40];
OS_TCB task3_TCB;
void task3(void){
    while(1){
        gpio_toggle_pin(portA, pin_3);
        software_delay_ms(100);
    }
}

uint32 task4_stack[40];
OS_TCB task4_TCB;
void task4(void){

    while(1){
    terminal_loopback_echo();
    }
}



void main()
{

    /* gpio initialization */
    gpio_setup_pin(GPIOA, pin_1, high_speed, output, push_pull, no_pull);
    gpio_setup_pin(GPIOA, pin_2, high_speed, output, push_pull, no_pull);
    gpio_setup_pin(GPIOA, pin_3, high_speed, output, push_pull, no_pull);

    /* setup terminal pins */
    gpio_setup_pin(GPIOA, pin_9, high_speed, alternate_function, push_pull, no_pull);
    gpio_setup_pin(GPIOA, pin_10, high_speed, alternate_function, push_pull, no_pull);

    gpio_setup_AF(GPIOA, pin_9, AF7); // Alterate function 7 for USART 1 TX
    gpio_setup_AF(GPIOA, pin_10, AF7); // Alterate function 7 for USART 1 RX

    terminal_init();

    OS_init();

    OS_task_create(&task1_TCB, task1, task1_stack, sizeof(task1_stack));
    OS_task_create(&task2_TCB, task2, task2_stack, sizeof(task2_stack));
    OS_task_create(&task3_TCB, task3, task3_stack, sizeof(task3_stack));
    OS_task_create(&task4_TCB, task4, task4_stack, sizeof(task4_stack));

    OS_run();

    /* unreachable code section */

}