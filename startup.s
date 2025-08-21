.syntax unified
.cpu cortex-m4
.thumb

.global _estack
_estack = 0x20010000     // Top of RAM (64KB for STM32F401CB)

/* ---------------------------
 * Vector Table
 * --------------------------- */
.section .isr_vector, "a", %progbits
.type _vector_table, %object
.global _vector_table
_vector_table:
    .word _estack              // Initial stack pointer
    .word Reset_Handler        // Reset handler
    .word NMI_Handler          // NMI
    .word HardFault_Handler    // Hard fault
    .word MemManage_Handler    // MemManage
    .word BusFault_Handler     // BusFault
    .word UsageFault_Handler   // UsageFault
    .word 0                    // Reserved
    .word 0                    // Reserved
    .word 0                    // Reserved
    .word 0                    // Reserved
    .word SVC_Handler          // SVCall
    .word DebugMon_Handler     // Debug monitor
    .word 0                    // Reserved
    .word PendSV_Handler       // PendSV
    .word SysTick_Handler      // SysTick

    /* IRQ handlers (add more if needed) */
    .word Default_Handler      // WWDG
    .word Default_Handler      // PVD
    .word Default_Handler      // TAMP_STAMP
    .word Default_Handler      // RTC_WKUP
    .word Default_Handler      // FLASH
    .word Default_Handler      // RCC
    .word Default_Handler      // EXTI0
    .word Default_Handler      // EXTI1
    .word Default_Handler      // EXTI3
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI9_5
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word TIM1_UP_TIM10_IRQHandler // timer 1 update interrupt handler and TIM10 global interrupt
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word TIM2_IRQHandler      // Timer 2 global interrupt
    .word TIM3_IRQHandler      // Timer 3 global interrupt
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler      // EXTI4
    .word Default_Handler     // EXTI4

    /* ... add more as needed for your app */

/* ---------------------------
 * Reset Handler
 * --------------------------- */
.section .text.Reset_Handler
.global Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    /* Copy .data section from flash to RAM */
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata

copy_data:
    cmp r0, r1
    ittt lt
    ldrlt r3, [r2], #4
    strlt r3, [r0], #4
    blt copy_data

    /* Zero initialize .bss section */
    ldr r0, =_sbss
    ldr r1, =_ebss

zero_bss:
    cmp r0, r1
    itt lt
    movlt r2, #0
    strlt r2, [r0], #4
    blt zero_bss

    bl main
    b .

/* ---------------------------
 * Weak Default Handlers
 * --------------------------- */
.weak NMI_Handler
.weak HardFault_Handler
.weak MemManage_Handler
.weak BusFault_Handler
.weak UsageFault_Handler
.weak SVC_Handler
.weak DebugMon_Handler
.weak PendSV_Handler
.weak SysTick_Handler
.weak Default_Handler


.thumb_func
NMI_Handler:          b .
HardFault_Handler:    b .
MemManage_Handler:    b .
BusFault_Handler:     b .
UsageFault_Handler:   b .
SVC_Handler:          b .
DebugMon_Handler:     b .
PendSV_Handler:       b .
SysTick_Handler:      b .

.global Default_Handler
Default_Handler:      b .
