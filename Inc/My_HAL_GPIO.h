#include "hal_gpio.h"

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void My_HAL_GPIO_PB11_PB13_PB_14_PC0_Init(void);
void My_HAL_GPIO_InitAll(void);
void My_HAL_GPIO_Init_PC4_PC5(void);
void My_HAL_GPIO_Init_PA0(void);
GPIO_PinState My_HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void My_HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void My_HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void My_HAL_GPIO_PC0_ADC (void);
void My_HAL_GPIO_PA4_DAC (void);