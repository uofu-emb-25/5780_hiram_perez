#include <stdint.h> 
#include <stm32f0xx_hal.h> 
#include "my_time.h"

void My_TIM2_SETUP(void)
{
    RCC->APB1ENR |= 0x1;
    TIM2->PSC = 7999; //1999
    TIM2->ARR = 250; // 999
    TIM2->DIER = TIM_DIER_UIE;
    TIM2->CR1 = TIM_CR1_CEN;
}





