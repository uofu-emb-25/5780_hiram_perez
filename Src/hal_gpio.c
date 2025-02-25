#include <stdint.h> 
#include <stm32f0xx_hal.h> 
#include <stm32f0xx_hal_gpio.h> 
void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{ 
    GPIOx->MODER &= ~((1<<16) | (1<<17) | (1<<18) | (1<<19)); 
    GPIOx->MODER |= ((1<<18) | (1<<16));
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
void My_HAL_GPIO_PB11_PB13_PB_14_PC0_Init(void)
{
    GPIOB->MODER &= ~((0x1 << 22) | (0x1 << 23) | (0x1 << 26) | (0x1 << 27) | (0x1 << 28) | (0x1 << 29)); // Clear MODER bits for PB11, PB13, PB14
    GPIOC->MODER &= ~((0x1 << 0) | (0x1 << 1)); // CLear MODER bits for PC0
    GPIOB-> MODER |= ((0x1 << 23) | (0x1 << 27) | (0x1 << 28)); // PB11 -> Alternate, PB13-> Alternate, PB14->output
    GPIOC->MODER |= (0x1 << 0); // PC0-> Output

    GPIOB->OTYPER &= ~((0x1 << 11) | (0x1 << 13) | (0x1 << 14)); // Clear OTYPER bits for PB11, PB13, PB14
    GPIOB->OTYPER |= ((0x1 << 11)  | (0x1 << 13)); // PB11->Open-drain, PB13->Open-drain, PB14-> Push-pull
    GPIOC->OTYPER &= ~(0x1 << 0); // PC0->Push-pull

    GPIOB->AFR[1] &= ~((0x1 << 15) | (0x1 << 14) | (0x1 << 13)); // Clear PB11 AFR
    GPIOB->AFR[1] |= (0x1 << 12); // Set PB11 AFR to I2C_SDA

    GPIOB->AFR[1] &= ~((0x1 << 23) | (0x1 << 21));
    GPIOB->AFR[1] |= ((0x1 << 22) | (0x1 << 20)); // Set PB13 to I2C_SCL

    My_HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET); // Start PB14 high
    My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET); // Start PC0 high
}
void My_HAL_GPIO_InitAll(void)
{
    GPIOC->MODER &= ~((0x1 << 12) | (0x1 << 13) | (0x1 << 14) | (0x1 << 15) | (0x1 << 16) | (0x1 << 17) | (0x1 << 18) | (0x1 << 19)); // Clear PC6-9 
    GPIOC->MODER |= ((0x1 << 12) | (0x1 << 14) | (0x1 << 16)| (0x1 << 18)); // Set PC6-9 to output mode
    GPIOC->OTYPER &= ~((0x1 << 6) | (0x1 << 7) | (0x1 << 8) | (0x1 << 9)); // Set PC6-9 to Push-Pull 
    GPIOC->OSPEEDR &= ~((0x1 << 18) | (0x1 << 16) | (0x1 << 14) | (0x1 << 12));  // Set PC6-9 to Low-speed 
    GPIOC->PUPDR &= ~((0x1 << 6) | (0x1 << 7) | (0x1 << 8) | (0x1 << 9)); // Ser PC6-9's to no Pull-up, Pull-down 
    GPIOC->PUPDR |= ((0x1 << 13) | (0x1 << 15) | (0x1 << 17) | (0x1 << 19));
    
}

void My_HAL_GPIO_Init_PC4_PC5(void)
{
    GPIOC->MODER &= ~((0x1 << 8) | (0x1 << 9) | (0x1 << 10) | (0x1 << 11)); // Clear PC4 & PC5
    GPIOC->MODER |= ((0x1 << 11) | (0x1 << 9)); // Set PC4 & PC5 to Alternate function mode
    GPIOC->AFR[0] &= ~((0x1 << 19) | (0x1 << 18) | (0x1 << 15) | (0x1 << 16)); // Set PC4 to AF1
    GPIOC->AFR[0] |= (0x1 << 16); // Set PC4 to AF1
    GPIOC->AFR[0] &= ~((0x1 << 23) | (0x1 << 23) | (0x1 << 21) | (0x1 << 20)); // Set PC5 to AF1
    GPIOC->AFR[0] |= (0x1 << 20); // Set PC5 to AF1
}

void My_HAL_GPIO_Init_PA0(void)
{
    GPIOA->MODER &= ~((0x1 << 0) | (0x1 << 1));// Set to input mode 
    GPIOA->OSPEEDR &= ~(0x1 << 0); // Set to low-speed 
    GPIOA->PUPDR &= ~((0x1 << 0) | (0x1 << 1)); // Clear PA0 PUPDR 
    GPIOA->PUPDR |= (0x1 << 1); // Set pull down resistor
} 
 
/*void My_HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin) 
{ 
} */ 

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
    GPIOx->ODR ^= GPIO_Pin;
}