#include <stm32f0xx_hal.h>
#include <assert.h>
#include "main.h"
#include "my_time.h"

void TIM2_IRQHandler(void)
{
    My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8 | GPIO_PIN_9);
    TIM2->SR &=  ~(0x1);
}

void TIM3_IRQHandler(void)
{
    My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6 | GPIO_PIN_7);
    TIM3->SR &=  ~(0x1);
}


int lab3_main(void) 
{
    HAL_Init(); // Reset of all peripherals, init the Flash and Systick
    //SystemClock_Config(); //Configure the system clock
    /* This example uses HAL library calls to control
    the GPIOC peripheral. You’ll be redoing this code
    with hardware register access. */
    My__HAL_RCC_GPIOC_CLK_ENABLE(); // Enable the GPIOC clock in the RCC
    My__HAL_RCC_GPIOA_CLK_ENABLE(); // Enable the GPIOA clock in the RCC
    // Set up a configuration struct to pass to the initialization function
    My_HAL_GPIO_InitAll(); // Initialize pins PC6, PC7, PC8 & PC9
    My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET); // Start PC9 high

    GPIOC->MODER &= ~((0x1 << 13) | (0x1 << 12) | (0x1 << 14) | (0x1 << 15)); // Clear PC6 & PC7
    GPIOC->MODER |= ((0x1 << 15) | (0x1 << 13)); // Set PC6 & PC7 to Alternate function mode
    GPIOC->AFR[0] &= ~((0x1 << 27) | (0x1 << 26) | (0x1 << 25) | (0x1 << 24)); // Set PC6 to AFO
    GPIOC->AFR[0] &= ~((0x1 << 31) | (0x1 << 30) | (0x1 << 29) | (0x1 << 28)); // Set PC7 to AFO
    My_TIM2_SETUP();
    My_TIM3_SETUP();
    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_SetPriority(TIM2_IRQn, 1);
    NVIC_EnableIRQ(TIM3_IRQn);   
    NVIC_SetPriority(TIM3_IRQn, 1);   

}
