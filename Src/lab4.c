#include <stm32f0xx_hal.h>
#include <assert.h>
#include "main.h"
#include "my_USART.h"

char volatile flag;
char volatile buffer [2];
uint16_t volatile counter = 0;

// USART handler loads chars into buffer, sets flag when full
void USART3_4_IRQHandler(void)
{
    buffer[counter] = USART3->RDR;
    My_CHAR_TX(buffer[counter]);
    if(counter == 1)
    {
        flag = 1;
    }
    counter++;
}
int lab4_main(void) 
{
    HAL_Init(); // Reset of all peripherals, init the Flash and Systick
    //SystemClock_Config(); //Configure the system clock
    /* This example uses HAL library calls to control
    the GPIOC peripheral. You’ll be redoing this code
    with hardware register access. */
    My__HAL_RCC_GPIOC_CLK_ENABLE(); // Enable the GPIOC clock in the RCC
    //My__HAL_RCC_GPIOA_CLK_ENABLE(); // Enable the GPIOA clock in the RCC
    My__HAL_RCC_USART3_CLK_ENABLE(); // Enable the USART3 clock in RCC
    // Set up a configuration struct to pass to the initialization function
    My_HAL_GPIO_InitAll(); // Initialize pins PC6, PC7, PC8 & PC9
    //My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET); // Start PC9 high
    My_HAL_GPIO_Init_PC4_PC5(); // helper function to initalize PC4 and PC5 with correct alt function
    // SET UP USART3 and USART NVIC 
    My_USART3_SETUP();
    NVIC_EnableIRQ(USART3_4_IRQn);
    NVIC_SetPriority(USART3_4_IRQn, 1);
    while(1)
    {
        // Check RXNE 
        while(!(USART3->ISR & (0x1 << 5)))
        {
        }
        if(flag) // check if buffer is full
        {               
            // tansmitt new line and reset flag and counter
            My_STRING_TX("\n\r");
            flag = 0;
            counter = 0;
            // Ask user for CMD
            My_STRING_TX("CMD?\n\r");
            switch(buffer[0])
            {
                // Switch case for different LED combos
                case 'b': // blue LED
                    switch(buffer[1])
                    {
                        case '0':
                            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET); // Start PC7 high
                            My_STRING_TX("b0 recognized\n\r");
                            break;
                        case '1':
                            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET); // Start PC7 high
                            My_STRING_TX("b1 recognized\n\r");
                            break;
                        case '2':
                            My_HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_7); // Toggle PC7
                            My_STRING_TX("b2 recognized\n\r");
                            break;
                    }
                    break;
                case 'g': // green LED
                    switch(buffer[1])
                    {
                        case '0':
                            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET); // Start PC9 high
                            My_STRING_TX("g0 recognized\n\r");
                            break;
                        case '1':
                            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET); // Start PC9 high
                            My_STRING_TX("g1 recognized\n\r");
                            break;
                        case '2':
                            My_HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_9); // Toggle PC9
                            My_STRING_TX("g2 recognized\n\r");
                            break;
                    }
                    break;
                case 'o': // orange LED
                     switch(buffer[1])
                    {
                        case '0':
                            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET); // Start PC8 high
                            My_STRING_TX("o0 recognized\n\r");
                            break;
                        case '1':
                            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET); // Start PC8 high
                            My_STRING_TX("o1 recognized\n\r");
                            break;
                        case '2':
                            My_HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_8); // Toggle PC8
                            My_STRING_TX("o2 recognized\n\r");
                            break;
                    }
                    break;
                case 'r': // red LED
                    switch(buffer[1])
                    {
                        case '0':
                            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET); // Start PC6 high
                            My_STRING_TX("r0 recognized\n\r");
                            break;
                        case '1':
                            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET); // Start PC6 high
                            My_STRING_TX("r1 recognized\n\r");
                            break;
                        case '2':
                            My_HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_6); // Toggle PC6
                            My_STRING_TX("r2 recognized\n\r");
                            break;
                    }
                    break;
                default:
                    My_STRING_TX("ERROR!\n\r");
                    break;            
            }
        }
    }
}