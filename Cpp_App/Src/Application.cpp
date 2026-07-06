//
// Created by yan on 6/1/26.
//

#include "../Inc/Application.h"
#include "stm32l476xx.h"
#include "../Inc/MotorDriver.h"
#include "../Inc/Init.h"
#include "../Inc/BridgeFunctions.h"


float actualSpeed;
uint32_t systemClock;
uint32_t pwm_value;
MotorDriver Motor;

int32_t counter_zeros;

void Application_Main(void)
{

    Init::initSystemClock();



    while (true)
    {
        pwm_value = Motor.getPWMValue();

        Motor.DriveMotor(000.0f, 1);

        actualSpeed = Motor.getSpeed();
    }
}
extern "C" void cpp_handle_interrupt_tim3(void)
{
    Motor.controllerCycle10ms();
}