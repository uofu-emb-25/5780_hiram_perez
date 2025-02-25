#include <stm32f0xx_hal.h>
#include <assert.h>
#include "main.h"

int lab3_main(void) 
{
    HAL_Init(); // Reset of all peripherals, init the Flash and Systick
    //SystemClock_Config(); //Configure the system clock
    /* This example uses HAL library calls to control
    the GPIOC peripheral. You’ll be redoing this code
    with hardware register access. */
    My__HAL_RCC_GPIOC_CLK_ENABLE(); // Enable the GPIOC clock in the RCC
    My__HAL_RCC_GPIOB_CLK_ENABLE(); // Enable the GPIOA clock in the RCC
    // Set up a configuration struct to pass to the initialization function
    //My_HAL_GPIO_InitAll(); // Initialize pins PC6, PC7, PC8 & PC9
    My__HAL_RCC_I2C2_ENABLE(); // Enable I2C clock

}
