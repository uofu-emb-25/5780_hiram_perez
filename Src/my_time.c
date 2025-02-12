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

void My_TIM3_SETUP(void)
{
    RCC->APB1ENR |= (0x1 << 1); // Enable in RCC
    TIM3->PSC = 20;
    TIM3->ARR = 525; // SET frequency to 800 Hz
    TIM3->CCMR1 &= ~((0x1 << 0) | (0x1 << 1)); // Set TIM3 CC1S to output mode
    TIM3->CCMR1 &= ~((0x1 << 9) | (0x1 << 8)); // Set TIM3 CC2S to output mode
    TIM3->CCMR2 &= ~((0x1 << 0) | (0x1 << 1)); // Set TIM3 CC3S to output mode
    TIM3->CCMR2 &= ~((0x1 << 9) | (0x1 << 8)); // Set TIM3 CC4S to output mode
    TIM3->CCMR1 |= ((0x1 << 6) | (0x1 << 5) | (0x1 << 4)); // SET TIM3 Channel 1 to PWM mode 2
    TIM3->CCMR1 &= ~(0x1 << 12); // Clear bit 12 of TIM3 CCMR1 (this is to set Channel 2 to PWM 1)
    TIM3->CCMR1 |= ((0x1 << 14) | (0x1 << 13)); // Set TIM3 Channel 2 to PWM mode 1
    TIM3->CCMR1 |= (0x1 << 11); // Set TIM3 Channel 1 preload enable
    TIM3->CCMR2 |= (0x1 << 11); // Set TIM3 Channel 1 preload enable
    TIM3->CCER |= (0x1 << 0); // Set TIM3 Channel 1 output enable bit
    TIM3->CCER |= (0x1 << 4); // Set TIM3 Channel 2 output enable bit
    TIM3->CCR1 = 500;
    TIM3->CCR2 = 20;
    TIM3->CR1 = TIM_CR1_CEN;
}




