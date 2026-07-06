//
// Created by yan on 6/1/26.
//

#include "../Inc/Application.h"
#include "stm32l476xx.h"
#include "../Inc/MotorDriver.h"
#include "../Inc/Init.h"
#include "../Inc/BridgeFunctions.h"
#include "../Inc/Terminal.h"


namespace global
{
    volatile MotorDriver* g_motor_ptr = nullptr;
}




void Application_Main(void)
{
    Init::initSystemClock();

    MotorDriver Motor;
    global::g_motor_ptr = &Motor;

    Terminal terminal;

    float targetSpeed = 500.0f;



    while (true)
    {

        Motor.DriveMotor(targetSpeed, 1);

        float actualSpeed = Motor.getActualSpeed();

        terminal.terminalSend(static_cast<uint32_t>(targetSpeed), static_cast<uint32_t>(actualSpeed));


    }
}
extern "C" void cpp_handle_interrupt_tim3(void)
{

    if (global::g_motor_ptr != nullptr)
    {
        const_cast<MotorDriver*>(global::g_motor_ptr)->controllerCycle10ms();
    }
}