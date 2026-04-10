#include <stdint.h>
#include "registers.h"

void TIM2_IRQHandler(void)
{
    if ((TIM2->SR & TIM_SR_UIF_Msk) != 0U)
    {
        GPIOA->ODR ^= GPIO_ODR_OD5_Msk;
        /* SR bits are rc_w0 on this timer; write 0 to clear pending flags. */
        TIM2->SR = 0U;
    }
}

int main(void)
{
    /* Enable peripheral clocks for GPIOA and TIM2 */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN_Msk;

    /* Configure PA5 as general-purpose push-pull output */
    GPIOA->MODER &= ~GPIO_MODER_MODER5_Msk;
    GPIOA->MODER |= (GPIO_MODER_OUTPUT << GPIO_MODER_MODER5_Pos);

    /*
     * TIM2 configuration for 1 Hz update event at reset clocking.
     * Default SYSCLK after reset is 16 MHz (HSI), APB1 prescaler = 1,
     * so TIM2 clock is 16 MHz.
     * PSC = 15999 -> 1 kHz counter clock
     * ARR = 999   -> update every 1.0 s
     */
    TIM2->PSC = 15999U;
    TIM2->ARR = 999U;
    TIM2->CNT = 0U;

    /* Load prescaler immediately and reset counter */
    TIM2->EGR = TIM_EGR_UG_Msk;

    /* Clear pending update flag before enabling interrupt */
    TIM2->SR = 0U;
    TIM2->DIER |= TIM_DIER_UIE_Msk;

    /* Clear pending state then enable TIM2 interrupt in NVIC. */
    NVIC_ICPR0 = (1UL << TIM2_IRQn);
    NVIC_ISER0 |= (1UL << TIM2_IRQn);

    /* Start timer */
    TIM2->CR1 |= TIM_CR1_CEN_Msk;

    while (1)
    {
    }
}
