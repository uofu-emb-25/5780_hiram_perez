#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>
#include "my_I2C.h"

void MY_I2C2_SETUP(void)
{
    // PRESC
    //I2C2->TIMINGR &= ~((0x1 << 28) | (0x1 << 29) | (0x1 << 30) | (0x1 << 31)); // Clear PRESC
    I2C2->TIMINGR |= (0x1 << 28); // Set PRESC to 1

    // SCLL
    I2C2->TIMINGR |= (0x13 << 0); // Set SCLL 0x13

    // SCLH
    I2C2->TIMINGR |= (0xF << 8); // Set SCLH to 0xF

    // SDADEL
    I2C2->TIMINGR |= (0x2 << 16); // Set SDADEL to 0x2

    // SCLDEL
    I2C2->TIMINGR |= (0x4 << 20); // Set SCLDEL to 0x4

    // TXIE enable
    //I2C2->CR1 |= I2C_CR1_TXIE;

    I2C2->CR1 |= I2C_CR1_PE; // Set PE fir I2C2
}

void MY_I2C2_READ_REG(void)
{
    // SADD
    I2C2->CR2 &= ~((0x1 << 1) | (0x1 << 2) | (0x1 << 3) | (0x1 << 4) | (0x1 << 5) | (0x1 << 6) | (0x1 << 7)); // Clear SADD register
    I2C2->CR2 |= ((0x1 << 7) | (0x1 << 6) | (0x1 << 4) | (0x1 << 1)); // Set SADD to 0x69

    // NBYTES
    I2C2->CR2 &= ~ ((0x1 << 16) | (0x1 << 17) | (0x1 << 18) | (0x1 << 19) | (0x1 << 20) | (0x1 << 21) | (0x1 << 22) | (0x1 << 23)); // Clear NBYTES register
    I2C2->CR2 |= (0x1 << 16); // Set NBYTES to 0x1

    // RD_WDR
    I2C2->CR2 &= ~(0x1 << 10);  // Set RD_WDR to write

    // START
    I2C2->CR2 |= (0x1 << 13); // Set start bit
}