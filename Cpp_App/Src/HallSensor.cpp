//
// Created by yan on 6/8/26.
//

#include "../Inc/HallSensor.h"
#include "stm32l476xx.h"


HallSensor::HallSensor()
{
    count = 0;

    // Test Hall Sensor PC8

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    GPIOC->MODER &= ~GPIO_MODER_MODE8_Msk;
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD8_Msk;

    // Activate interrupt

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // Activate SYSCFG - Needed for EXTI Mapping

    SYSCFG->EXTICR[2] &= ~SYSCFG_EXTICR3_EXTI8_Msk;
    SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI8_PC; // Map EXTI8 to port C

    EXTI->IMR1 |= EXTI_IMR1_IM8;
    EXTI->FTSR1 |= EXTI_FTSR1_FT8;
    EXTI->RTSR1 &= ~EXTI_RTSR1_RT8;

    NVIC_EnableIRQ(EXTI9_5_IRQn);

}

void HallSensor::countSignals()
{
    if (state != 1)
    {
        state = 1;
    }
    else
    {
        state = 0;
    }

    count++;
}

uint32_t HallSensor::getCount() const
{
    return count;
}

uint8_t HallSensor::getState() const
{
    return state;
}
