#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>
#include "my_I2C.h"

void MY_I2C2_SETUP(void)
{
    // PRESC
    I2C2->TIMINGR &= ~((0x1 << 28) | (0x1 << 29) | (0x1 << 30) | (0x1 << 31)); // Clear PRESC
    I2C2->TIMINGR |= (0x1 << 28); // Set PRESC to 1

    // SCLL
    I2C2->TIMINGR &= ~((0x1 << 0) | (0x1 << 1) | (0x1 << 2) | (0x1 << 3) | (0x1 << 4) | (0x1 << 5) | (0x1 << 6) | (0x1 << 7)); // Clear SCLL
    I2C2->TIMINGR |= ((0x1 << 4) | (0x1 << 1) | (0x1 << 0)); // Set SCLL to 0x13

    // SCLH
    I2C2->TIMINGR &= ~((0x1 << 8) | (0x1 << 9) | (0x1 << 10) | (0x1 << 11) | (0x1 << 12) | (0x1 << 13) | (0x1 << 14) | (0x1 << 15)); // Clear SCLH
    I2C2->TIMINGR |= ((0x1 << 8) | (0x1 << 9) | (0x1 << 10) | (0x1 << 11)); // Set SCLH to 0xF

    // SDADEL
    I2C2->TIMINGR &= ~((0x1 << 16) | (0x1 << 17) | (0x1 << 18) | (0x1 << 19)); // Clear SDADEL
    I2C2->TIMINGR |= (0x1 << 17); // Set SDADEL to 0x2

    // SCLDEL
    I2C2->TIMINGR &= ~((0x1 << 20) | (0x1 << 21) | (0x1 << 22) | (0x1 << 23)); // Clear SCLDEL
    I2C2->TIMINGR |= (0x1 << 22); // Set SCLDEL to 0x4

    I2C2->CR1 |= I2C_CR1_PE; // Set PE fir I2C2
}