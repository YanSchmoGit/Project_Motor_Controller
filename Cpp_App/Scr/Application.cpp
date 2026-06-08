//
// Created by yan on 6/1/26.
//

#include "../Inc/Application.h"
#include "stm32l476xx.h"
#include "../Inc/MotorDriver.h"


void Application_Main(void)
{

    // Test Hall Sensor PC8

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    GPIOC->MODER &= ~GPIO_MODER_MODE8_Msk;
    GPIOC->PUPDR |= GPIO_MODER_MODE8_1;

    // Onboard LED...
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;


    MotorDriver TestMotor;

    while (1)
    {
        TestMotor.DriveMotor(2000, 1);

    }
}
