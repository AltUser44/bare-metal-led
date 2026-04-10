.syntax unified
.cpu cortex-m4
.thumb

.global _estack
.global Reset_Handler
.global Default_Handler
.global main
.global TIM2_IRQHandler

.extern _sidata
.extern _sdata
.extern _edata
.extern _sbss
.extern _ebss

.section .isr_vector, "a", %progbits
.type g_pfnVectors, %object
g_pfnVectors:
    .word _estack                 /* Initial stack pointer */
    .word Reset_Handler           /* Reset Handler */
    .word NMI_Handler             /* NMI Handler */
    .word HardFault_Handler       /* Hard Fault Handler */
    .word MemManage_Handler       /* MPU Fault Handler */
    .word BusFault_Handler        /* Bus Fault Handler */
    .word UsageFault_Handler      /* Usage Fault Handler */
    .word 0                       /* Reserved */
    .word 0                       /* Reserved */
    .word 0                       /* Reserved */
    .word 0                       /* Reserved */
    .word SVC_Handler             /* SVCall Handler */
    .word DebugMon_Handler        /* Debug Monitor Handler */
    .word 0                       /* Reserved */
    .word PendSV_Handler          /* PendSV Handler */
    .word SysTick_Handler         /* SysTick Handler */

    /* External interrupts (IRQ0..IRQ27) */
    .rept 28
    .word Default_Handler
    .endr

    /* IRQ28: TIM2 global interrupt */
    .word TIM2_IRQHandler

    /* Remaining vectors (to 84 external IRQs on STM32F401) */
    .rept 55
    .word Default_Handler
    .endr
.size g_pfnVectors, . - g_pfnVectors

.section .text.Reset_Handler, "ax", %progbits
.type Reset_Handler, %function
Reset_Handler:
    /* Copy initialized data from FLASH to RAM */
    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata
1:
    cmp r1, r2
    bcc 2f
    b 3f
2:
    ldr r3, [r0], #4
    str r3, [r1], #4
    b 1b

    /* Zero-fill .bss */
3:
    ldr r0, =_sbss
    ldr r1, =_ebss
    movs r2, #0
4:
    cmp r0, r1
    bcc 5f
    b 6f
5:
    str r2, [r0], #4
    b 4b

    /* Enter application */
6:
    bl main
7:
    b 7b
.size Reset_Handler, . - Reset_Handler

.section .text.Default_Handler, "ax", %progbits
.type Default_Handler, %function
Default_Handler:
1:
    b 1b
.size Default_Handler, . - Default_Handler

.weak NMI_Handler
.thumb_set NMI_Handler, Default_Handler
.weak HardFault_Handler
.thumb_set HardFault_Handler, Default_Handler
.weak MemManage_Handler
.thumb_set MemManage_Handler, Default_Handler
.weak BusFault_Handler
.thumb_set BusFault_Handler, Default_Handler
.weak UsageFault_Handler
.thumb_set UsageFault_Handler, Default_Handler
.weak SVC_Handler
.thumb_set SVC_Handler, Default_Handler
.weak DebugMon_Handler
.thumb_set DebugMon_Handler, Default_Handler
.weak PendSV_Handler
.thumb_set PendSV_Handler, Default_Handler
.weak SysTick_Handler
.thumb_set SysTick_Handler, Default_Handler
.weak TIM2_IRQHandler
.thumb_set TIM2_IRQHandler, Default_Handler
