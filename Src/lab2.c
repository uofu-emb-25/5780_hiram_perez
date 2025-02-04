#include <stm32f0xx_hal.h>
#include <assert.h>
int lab1_main(void) 
{
    HAL_Init(); // Reset of all peripherals, init the Flash and Systick
    SystemClock_Config(); //Configure the system clock
    /* This example uses HAL library calls to control
    the GPIOC peripheral. You’ll be redoing this code
    with hardware register access. */
    My__HAL_RCC_GPIOC_CLK_ENABLE(); // Enable the GPIOC clock in the RCC
    My__HAL_RCC_GPIOA_CLK_ENABLE(); // Enable the GPIOA clock in the RCC
    // Set up a configuration struct to pass to the initialization function
    GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_7,
    GPIO_MODE_OUTPUT_PP,
    GPIO_SPEED_FREQ_LOW,
    GPIO_NOPULL};
    My_HAL_GPIO_Init(GPIOC, &initStr); // Initialize pins PC8 & PC9
    //assert(GPIOC->MODER == 0x50000); // check if GPIOC->MODER is set to 0
    //assert(GPIOC->OTYPER == 0x0); // check value for OTYPER
    //assert(GPIOC->OSPEEDR == 0x00); // Check value for OSPEEDR 
    //assert(GPIOC->PUPDR == 0x00); // Check value for PUPDR
    //assert(GPIOC->ODR == 0x00); // Check value for ODR
    My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET); // Start PC8 high

    uint32_t debouncer = 0;
    while(1) 
    {
        debouncer = (debouncer << 1); // Always shift every loop iteration
        GPIO_PinState Pressed = My_HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
        if(Pressed == GPIO_PIN_SET)
        { // If input signal is set/high
            debouncer |= 0x01; // Set lowest bit of bit-vector
        }
        if (debouncer == 0x7FFFFFFF) 
        {
            My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6 | GPIO_PIN_7);
        }
        // When button is bouncing the bit-vector value is random since bits are set when the button is high and not when it bounces low.
    }
}