#include <stm32f0xx_hal.h>
#include <assert.h>
#include "main.h"

void who_am_i_check_off(void);
void I2C_TX(uint8_t slave_add, uint8_t reg_add, uint8_t data);
uint8_t I2C_RX(uint8_t slave_add, uint8_t reg_add);
void gryo_check_off(void);
int16_t X_axis = 0, Y_axis = 0, x_temp = 0, y_temp = 0, old_x =0 , old_y = 0;

int lab5_main(void) 
{
    HAL_Init(); // Reset of all peripherals, init the Flash and Systick
    //SystemClock_Config(); //Configure the system clock
    /* This example uses HAL library calls to control
    the GPIOC peripheral. You’ll be redoing this code
    with hardware register access. */
    My__HAL_RCC_GPIOC_CLK_ENABLE(); // Enable the GPIOC clock in the RCC
    My__HAL_RCC_GPIOB_CLK_ENABLE(); // Enable the GPIOB clock in the RCC
    // Set up a configuration struct to pass to the initialization function
    My_HAL_GPIO_InitAll(); // Initialize pins PC6, PC7, PC8 & PC9
    My_HAL_GPIO_PB11_PB13_PB_14_PC0_Init();
    My__HAL_RCC_I2C2_ENABLE(); // Enable I2C clock
    MY_I2C2_SETUP();
    //who_am_i_check_off();
    // if(I2C_RX(0x69, 0x0F) == 0xD3)
    // {
    //     My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
    // }
    
    // I2C_TX(0x69, 0x20, 0xB);
    // if(I2C_RX(0x69, 0x20) == 0xB)
    // {
    //     My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
    // }
    gryo_check_off();

}

void gryo_check_off(void)
{
    I2C_TX(0x69, 0x20, 0xB); // enable x, y and enter sleep mode
    while(1)
    {
        HAL_Delay(100); // wait 100 ms

        // RESET LEDS

        My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
        My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
        My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
        My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);

        y_temp = (I2C_RX(0x69, 0x2B) << 8) | I2C_RX(0x69, 0x2A); 
        x_temp = (I2C_RX(0x69, 0x29) << 8) | I2C_RX(0x69, 0x28);

        old_x = X_axis;
        old_y = Y_axis;
        if(x_temp > 5000 || x_temp < -5000)
        {
            X_axis += x_temp; // add value to x axis
        }
        if(y_temp > 5000 || y_temp < -5000)
        {
            Y_axis += y_temp; // add value to y axis
        }

        if(X_axis < old_x) // Green LED for Negative X direction
        {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
        }  

        else if(X_axis > old_x) // Orange LED for Postive X direction
        {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
        } 

        else if(Y_axis > old_y) // Red LED for Postivie Y direction
        {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
        } 

        else if(Y_axis < old_y) // Blue LED for Negative Y direction
        {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
        }  
    }
}

void who_am_i_check_off(void)
{
    I2C2->CR2 &= ~((0x7F << 16) | (0x3FF << 0)); // Clear SADD register
    I2C2->CR2 |= (0x69 << 1); // Set SADD to 0x69

    // NBYTES
    I2C2->CR2 &= ~ (0xFF << 16); // Clear NBYTES register
    I2C2->CR2 |= (0x1 << 16); // Set NBYTES to 0x1

    // RD_WDR
    I2C2->CR2 &= ~(0x1 << 10);  // Set RD_WDR to write

    // START
    I2C2->CR2 |= (0x1 << 13); // Set start bit

    
    while(!(I2C2->ISR & ( (I2C_ISR_NACKF) | (I2C_ISR_TXIS) ) ) )
    {
    }
   
    I2C2->TXDR = 0x0F;
        

    // RESET I2C2 CR values, except change to read //

    // SADD
    // I2C2->CR2 &= ~((0x7F << 16) | (0x3FF << 0)); // Clear SADD register
    I2C2->CR2 |= (0x69 << 1); // Set SADD to 0x69

    // // NBYTES
    // I2C2->CR2 &= ~ ((0x1 << 16) | (0x1 << 17) | (0x1 << 18) | (0x1 << 19) | (0x1 << 20) | (0x1 << 21) | (0x1 << 22) | (0x1 << 23)); // Clear NBYTES register
    I2C2->CR2 |= (0x1 << 16); // Set NBYTES to 0x1

    // RD_WDR
    I2C2->CR2 |= (0x1 << 10);  // Set RD_WDR to read

    // START
    I2C2->CR2 |= (0x1 << 13); // Set start bit

    while(!(I2C2->ISR & ( (I2C_ISR_NACKF)  | (I2C_ISR_RXNE) ) ) )
    {
    }

    //read_register = I2C2->RXDR;
    
    while(!(I2C2->ISR & (I2C_ISR_TC) ) )
    {
    }

    if((I2C2->RXDR) == 0xD3)
    {
        My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
    }

    I2C2->CR2 |= I2C_CR2_STOP; //Send Stop bit
}

void I2C_TX(uint8_t slave_add, uint8_t reg_add, uint8_t data)
{
    I2C2->CR2 = (slave_add << 1); // Set SADD to slave address

    // NBYTES
    I2C2->CR2 |= (0x2 << 16); // Set NBYTES to 0x1

    // RD_WDR
    I2C2->CR2 &= ~(0x1 << 10);  // Set RD_WDR to write

    // START
    I2C2->CR2 |= (0x1 << 13); // Set start bit

    
    while(!(I2C2->ISR & ( (I2C_ISR_NACKF) | (I2C_ISR_TXIS) ) ) )
    {
    }
   
    I2C2->TXDR = reg_add;

    while(!(I2C2->ISR & ( (I2C_ISR_NACKF) | (I2C_ISR_TXIS) ) ) )
    {
    }
   
    I2C2->TXDR = data;  

    while(!(I2C2->ISR & (I2C_ISR_TC)))
    {
    }

    I2C2->CR2 |= I2C_CR2_STOP;
}

uint8_t I2C_RX(uint8_t slave_add, uint8_t reg_add)
{
    uint8_t data;
    I2C2->CR2 = (slave_add << 1); // Set SADD to 0x69

    // NBYTES
    I2C2->CR2 |= (0x1 << 16); // Set NBYTES to 0x1

    // RD_WDR
    I2C2->CR2 &= ~(0x1 << 10);  // Set RD_WDR to write

    // START
    I2C2->CR2 |= (0x1 << 13); // Set start bit

    while(!(I2C2->ISR & ( (I2C_ISR_NACKF)  | (I2C_ISR_TXIS) ) ) )
    {
    }

    I2C2->TXDR = reg_add;
    
    while(!(I2C2->ISR & (I2C_ISR_TC) ) )
    {
    }

    I2C2->CR2 |= I2C_CR2_RD_WRN;  // Set RD_WDR to read

    // START
    I2C2->CR2 |= (0x1 << 13); // Set start bit

    while(!(I2C2->ISR & ( (I2C_ISR_NACKF)  | (I2C_ISR_RXNE) ) ) )
    {
    }
    
    data = I2C2->RXDR;

    I2C2->CR2 |= I2C_CR2_STOP; //Send Stop bit

    return data;
}
