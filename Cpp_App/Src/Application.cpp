//
// Created by yan on 6/1/26.
//

#include "../Inc/Application.h"
#include "stm32l476xx.h"
#include "../Inc/HallSensor.h"
#include "../Inc/MotorDriver.h"
#include "../Inc/BridgeFunctions.h"




uint32_t countValue;
HallSensor TestSensor;

void Application_Main(void)
{



    // Onboard LED...
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;

    //GPIOA->BSRR = GPIO_BSRR_BS5;
    //MotorDriver TestMotor;



    while (1)
    {
        countValue = TestSensor.getCount();

        //TestMotor.DriveMotor(0000, 1);
    }
}

extern "C" void cpp_handle_interrupt_exti9_5(void)
{
    if (TestSensor.getState() == 1)
    {
        GPIOA->BSRR = GPIO_BSRR_BR5;
    }
    else
    {
        GPIOA->BSRR = GPIO_BSRR_BS5;
    }

        TestSensor.countSignals();
}