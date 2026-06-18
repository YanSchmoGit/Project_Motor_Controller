//
// Created by yan on 6/8/26.
//

#include "../Inc/MotorDriver.h"

MotorDriver::MotorDriver()
{
    // Test Motor driver L298N

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    GPIOA->MODER &= ~GPIO_MODER_MODE6_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE6_0;

    GPIOA->MODER &= ~GPIO_MODER_MODE7_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE7_0;

    // Configure timer

    GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE5_1; // Activate AF mode

    GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL5_Msk;
    GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_0;

    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
    TIM2->PSC = 10 ;
    TIM2->ARR = 10000;

    TIM2->CCMR1 &= ~(TIM_CCMR1_CC1S_Msk | TIM_CCMR1_OC1M_Msk);
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;

    TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
    TIM2->CCR1 = 0000;
    TIM2->CCER |= TIM_CCER_CC1E;

    TIM2->CNT = 0;
    TIM2->CR1 |= TIM_CR1_CEN;
}

void MotorDriver::DriveMotor(std::uint32_t speed, std::int16_t direction)
{
    if (direction == 0)
    {
        GPIOA->BSRR |= GPIO_BSRR_BS6;
        GPIOA->BSRR |= GPIO_BSRR_BR7;
        TIM2->CCR1 = speed;
    }
    else
    {
        GPIOA->BSRR |= GPIO_BSRR_BR6;
        GPIOA->BSRR |= GPIO_BSRR_BS7;
        TIM2->CCR1 = speed;
    }
}
