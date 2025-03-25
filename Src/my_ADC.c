#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>
#include "my_ADC.h"

    /* (1) Ensure that ADEN = 0 */
    /* (2) Clear ADEN by setting ADDIS*/
    /* (3) Clear DMAEN */
    /* (4) Launch the calibration by setting ADCAL */
    /* (5) Wait until ADCAL=0 */
void My_ADC_CAL(void)
{
    if ((ADC1->CR & ADC_CR_ADEN) != 0) /* (1) */
    {
        ADC1->CR |= ADC_CR_ADDIS; /* (2) */
    }
    
    while ((ADC1->CR & ADC_CR_ADEN) != 0)
    {
        /* For robust implementation, add here time-out management */
    }
    ADC1->CFGR1 &= ~ADC_CFGR1_DMAEN; /* (3) */
    ADC1->CR |= ADC_CR_ADCAL; /* (4) */
    while ((ADC1->CR & ADC_CR_ADCAL) != 0) /* (5) */
    {
        /* For robust implementation, add here time-out management */
    }
    if((ADC1->ISR & ADC_ISR_ADRDY) != 0)
    {
        ADC1->ISR |= ADC_ISR_ADRDY;
    }
    ADC1->CR |= ADC_CR_ADEN;
    while((ADC1->ISR & ADC_ISR_ADRDY) == 0)
    {}
    ADC1->CR |= ADC_CR_ADSTART;
}