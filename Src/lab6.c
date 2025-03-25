#include <stm32f0xx_hal.h>
#include <assert.h>
#include "my_ADC.h"
#include "main.h"

int lab6_main(void) 
{
    HAL_Init(); // Reset of all peripherals, init the Flash and Systick
    My__HAL_RCC_GPIOC_CLK_ENABLE(); // Enable the GPIOC clock in the RCC
    My__HAL_RCC_GPIOB_CLK_ENABLE(); // Enable the GPIOB clock in the RCC
    // Set up a configuration struct to pass to the initialization function
    My_HAL_GPIO_InitAll(); // Initialize pins PC6, PC7, PC8 & PC9
     My__HAL_RCC_ADC1_ENABLE();
    My_HAL_GPIO_PC0_ADC();
    My_ADC_CAL();
    while(1)
    {
        int16_t ADC_DATA = ADC1-> DR;
        if((ADC_DATA > 0) && (ADC_DATA <= 8))
        {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET); // if ADC is greater than or equal to 8 turn Red LED on
        }
        else
        {
           My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
        }

        if((ADC_DATA > 8) && (ADC_DATA <= 16))
        {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET); // if ADC is greater than or equal to 16 turn Orange LED on
        }
        else
        {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);

        }

        if((ADC_DATA > 16) && (ADC_DATA <= 32))
        {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET); // if ADC is greater than or equal to 32 turn Blue LED on
        }
        else
        {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);

        }

        if((ADC_DATA > 32))
        {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET); // if ADC is greater than or equal to 64 turn Green LED on
        }
        else
        {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
        }
    }
        
}