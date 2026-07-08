//
// Created by yan on 6/8/26.
//

#include "../Inc/MotorDriver.h"


HallSensor* MotorDriver::instancePointer = nullptr;


MotorDriver::MotorDriver()
    :
      pi_controller(1.0f, 0.5f,10.0f,0.0f,1000.0f),
      actual_speed(0.0f),
      target_speed(0.0f),
      pwm_value(0)
{
    instancePointer = &hall_sensor;

    // Init PWM for motor driver
    initPWM();

    // Init PI-controller
    initPIController();


}

void MotorDriver::initPWM()
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

    // Calculate freuqncy for PWM Signal = f_pwm = f_tim / ((pcs + 1) * (arr + 1))

    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
    TIM2->PSC = 3;
    TIM2->ARR = 999;

    TIM2->CCMR1 &= ~(TIM_CCMR1_CC1S_Msk | TIM_CCMR1_OC1M_Msk);
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;

    TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
    TIM2->CCR1 = 0000;
    TIM2->CCER |= TIM_CCER_CC1E;

    TIM2->CNT = 0;
    TIM2->CR1 |= TIM_CR1_CEN;
}

void MotorDriver::initPIController()
{
    // Init TIM 3 for controller cycle interrupt

    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;

    // 10ms cycle
    TIM3->PSC = (SystemCoreClock / 1000000) - 1;
    TIM3->ARR = 10000 - 1;

    TIM3->EGR |= TIM_EGR_UG; // Generate an update
    TIM3->SR &= ~TIM_SR_UIF; // Reset the interrupt bit. Interrupt generated from update will be reset.

    TIM3->DIER |= TIM_DIER_UIE; // Enable interrupt
    NVIC_EnableIRQ(TIM3_IRQn);

    TIM3->CR1 |= TIM_CR1_CEN;

}

void MotorDriver::DriveMotor(const float speed, const int16_t direction)
{

    calcSpeed();

    target_speed = speed;

    if (direction == 0)
    {
        GPIOA->BSRR |= GPIO_BSRR_BS6;
        GPIOA->BSRR |= GPIO_BSRR_BR7;
        TIM2->CCR1 = pwm_value;
    }
    else
    {
        GPIOA->BSRR |= GPIO_BSRR_BR6;
        GPIOA->BSRR |= GPIO_BSRR_BS7;
        TIM2->CCR1 = pwm_value;
    }
}

void MotorDriver::controllerCycle10ms()
{
    if (TIM3->SR & TIM_SR_UIF)
    {
        pwm_value = pi_controller.update(this->target_speed, this->actual_speed);

        TIM3->SR &= ~TIM_SR_UIF;
    }
}


void MotorDriver::calcSpeed()
{
    const auto actual_count = static_cast<float>(hall_sensor.getCount());
    float actual_speed_linear = 0.0f;
    if (actual_count > 0.0000001f)
    {
        actual_speed_linear = (7.5f * static_cast<float>(SystemCoreClock)) / actual_count;
    }

    actual_speed = actual_speed_linear;
}

float MotorDriver::getActualSpeed() const
{
        return actual_speed;
}

float MotorDriver::getTargetSpeed() const
{
        return target_speed;
}

uint32_t MotorDriver::getPWMValue() const
{
    return pwm_value;
}

extern "C" void cpp_handle_interrupt_tim5(void)
{

    if (MotorDriver::instancePointer != nullptr)
    {
        MotorDriver::instancePointer->countSignals();
    }
}


