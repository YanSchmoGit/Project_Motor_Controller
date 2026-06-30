//
// Created by yan on 6/8/26.
//

#include "../Inc/HallSensor.h"
#include "stm32l476xx.h"


HallSensor::HallSensor()
{
    // Init TIM5 & GPIOA for input capture modus

    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM5EN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;


    // Configure AF 2 for GPIOA PA0

    GPIOA->MODER &= ~GPIO_MODER_MODE0_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE0_1;

    GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL0_Msk;
    GPIOA->AFR[0] |= GPIO_AFRL_AFSEL0_1;


    // Configure timer 5

    TIM5->PSC = 0;
    TIM5->ARR = 0xFFFFFFFF;


    // Configure channel 1 as input
    TIM5->CCMR1 &= ~TIM_CCMR1_CC1S;
    TIM5->CCMR1 |= TIM_CCMR1_CC1S_0;

    // Configure edge detection (rising edge, CC1P = 0, CC1NP = 0)
    TIM5->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);

    // Activate capture for channel 1
    TIM5->CCER |= TIM_CCER_CC1E;

    // Activate interrupts
    TIM5->DIER |= TIM_DIER_CC1IE;
    NVIC_EnableIRQ(TIM5_IRQn);

    // Start timer
    TIM5->CR1 |= TIM_CR1_CEN;
}

void HallSensor::countSignals()
{
    actual_cycle_count = TIM5->CCR1;
    delta_count = actual_cycle_count - last_cycle_count;
    last_cycle_count = actual_cycle_count;

}


uint32_t HallSensor::getCount() const
{
    return delta_count;
}




