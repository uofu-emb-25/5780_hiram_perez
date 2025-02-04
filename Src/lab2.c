#include <stm32f0xx_hal.h>
#include <assert.h>
int lab2_main(void) 
{
    HAL_Init(); // Reset of all peripherals, init the Flash and Systick
    SystemClock_Config(); //Configure the system clock
    /* This example uses HAL library calls to control
    the GPIOC peripheral. You’ll be redoing this code
    with hardware register access. */
    My__HAL_RCC_GPIOC_CLK_ENABLE(); // Enable the GPIOC clock in the RCC
    My__HAL_RCC_GPIOA_CLK_ENABLE(); // Enable the GPIOA clock in the RCC
    // Set up a configuration struct to pass to the initialization function
    My_HAL_GPIO_InitAll(); // Initialize pins PC6, PC7, PC8 & PC9
    My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET); // Start PC9 high

    My_HAL_GPIO_Init_PA0();
    assert(EXTI->IMR == 0x7F840000);
    assert(SYSCFG->EXTICR[0] == 0x0);
    EXTI_SETUP();
    assert(EXTI->IMR == 0x7F840001);
    assert(SYSCFG->EXTICR[0] == 0x0);
    while(1) 
    {
        HAL_Delay(500); // Delay 500ms
        // Toggle the output state of PC6
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
    }
}