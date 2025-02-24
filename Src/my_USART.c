#include <stdint.h> 
#include <stm32f0xx_hal.h> 
#include "my_USART.h"

void My_USART3_SETUP(void)
{
  USART3->BRR = (HAL_RCC_GetHCLKFreq() / 115200); // Set baud rate
  USART3->CR1 |= USART_CR1_RE; // Enable Reciever hardware
  USART3->CR1 |= USART_CR1_TE; // Enable Transmitter hardware
  USART3->CR1 |= USART_CR1_RXNEIE; // Enable Transmiter recieve interrupt
  USART3->CR1 |= USART_CR1_UE; // Enable USART
}

void My_CHAR_TX(char character)
{
    while(!(USART3->ISR & (USART_ISR_TXE)))
    {
    }
    USART3->TDR = character;
}

void My_STRING_TX(char string[])
{
    for(int i =0; string[i] != '\0'; i++)
    {
        My_CHAR_TX(string[i]);
    }
    return;
}