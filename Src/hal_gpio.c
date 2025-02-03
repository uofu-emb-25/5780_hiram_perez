#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    //GPIOx->MODER &= ~((1<<16) | (1<<17) | (1<<18) | (1<<19));
    //GPIOx->MODER |= ((1<<18) | (1<<16));

    GPIOx->MODER &= ~((1<<12) | (1<<13) | (1<<14) | (1<<15));
    GPIOx->MODER |= ((1<<12) | (1<<14));

    GPIOx->OTYPER &= ~(0x1 << 6);
    GPIOx->OTYPER &= ~(0x1 << 7);

    GPIOx->OSPEEDR &= ~(0x1 << 6);
    GPIOx->OSPEEDR &= ~(0x1 << 7);

    GPIOx->PUPDR &= ~(0x1 << 6);
    GPIOx->PUPDR &= ~(0x1 << 7);

    GPIOx->MODER &= ~((1<<0) | (1<<1) | (1<<2) | (1<<3));

    GPIOx->OSPEEDR &= ~(0x1 << 0);
    GPIOx->OSPEEDR &= ~(0x1 << 1);

    GPIOx->PUPDR &= ~(0x1 << 6);
    GPIOx->PUPDR &= ~(0x1 << 7);


    GPIOA->MODER &= ~(0x1 << 0);
    GPIOA->MODER &= ~(0x1 << 1);

    GPIOA->OSPEEDR &= ~(0x1 << 0);
    GPIOA->OSPEEDR &= ~(0x1 << 1);


    GPIOA->PUPDR &= ~(0x1 << 0);
    GPIOA->PUPDR &= ~(0x1 << 1);

    GPIOA->PUPDR |= (0x1 << 1);
}

/*
void My_HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
}
*/

GPIO_PinState My_HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    if(GPIOx->IDR & 1)
    {
        return GPIO_PIN_SET;
    }
    else
    {
        return GPIO_PIN_RESET;
    }
}

void My_HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    if(PinState == GPIO_PIN_SET)
    {
        GPIOx->ODR |= GPIO_Pin; // Set PIN
    }
    else
    {
        GPIOx->ODR &= ~GPIO_Pin; // Clear PIN

    }

}

void My_HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->ODR ^= GPIO_Pin; // Clear PIN 8
   
}
