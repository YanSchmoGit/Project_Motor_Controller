//
// Created by yan on 6/8/26.
//

#ifndef PROJECT_MOTOR_CONTROLLER_MOTORDRIVER_H
#define PROJECT_MOTOR_CONTROLLER_MOTORDRIVER_H

#include <cstdint>
#include "stm32l476xx.h"
#include "../Inc/HallSensor.h"

class MotorDriver
{
private:
    // Hall sensor - speed measurement
    HallSensor hall_sensor;

    // Actual speed motor
    float speed;
public:
    MotorDriver();

    // Pointer for interrupt handling
    static HallSensor* instancePointer;

    // Drive motor
    void DriveMotor(std::uint32_t speed, std::int16_t direction);

    uint32_t SetMotorSpeed(std::uint32_t speed);

    // Calculate actual motor speed, depending on values from hall sensor
    void calcSpeed();

    // Get / Set functions
    float getSpeed();




};


#endif //PROJECT_MOTOR_CONTROLLER_MOTORDRIVER_H
