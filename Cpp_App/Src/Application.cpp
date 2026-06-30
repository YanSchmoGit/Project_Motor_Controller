//
// Created by yan on 6/1/26.
//

#include "../Inc/Application.h"
#include "stm32l476xx.h"
#include "../Inc/MotorDriver.h"
#include "../Inc/BridgeFunctions.h"



float actualSpeed;

void Application_Main(void)
{

    SystemCoreClockUpdate();

    MotorDriver Motor;

    while (1)
    {

        Motor.DriveMotor(210, 1);

        actualSpeed = Motor.getSpeed();

    }
}


