#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    GPIOx->MODER &= ~((1<<16) | (1<<17) | (1<<18) | (1<<19));
    GPIOx->MODER |= ((1<<18) | (1<<16));

    GPIOx->OTYPER &= ~(0x1 << 8);
    GPIOx->OTYPER &= ~(0x1 << 9);

    GPIOx->OSPEEDR &= ~(0x1 << 8);
    GPIOx->OSPEEDR &= ~(0x1 << 9);

    GPIOx->PUPDR &= ~(0x1 << 8);
    GPIOx->PUPDR &= ~(0x1 << 9);
}


/*
void My_HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
}
*/

/*
GPIO_PinState My_HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    return -1;
}
*/


void My_HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    GPIOx->ODR &= ~(0x1<< 8); // Clear PIN 8
    GPIOx->ODR |= (0x1<< 8); // Set PIN 8


    GPIOx->ODR &= ~(0x1<< 9); // Clear PIN 9

}



void My_HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->ODR ^= GPIO_Pin; // Clear PIN 8
   
}

