//
// Created by yan on 6/8/26.
//

#ifndef PROJECT_MOTOR_CONTROLLER_MOTORDRIVER_H
#define PROJECT_MOTOR_CONTROLLER_MOTORDRIVER_H

#include <cstdint>
#include "stm32l476xx.h"

class MotorDriver
{
public:
    MotorDriver();

    void DriveMotor(std::uint32_t speed, std::int16_t direction);


};


#endif //PROJECT_MOTOR_CONTROLLER_MOTORDRIVER_H
