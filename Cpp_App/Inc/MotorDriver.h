//
// Created by yan on 6/8/26.
//

#ifndef PROJECT_MOTOR_CONTROLLER_MOTORDRIVER_H
#define PROJECT_MOTOR_CONTROLLER_MOTORDRIVER_H

#include <cstdint>
#include "stm32l476xx.h"
#include "../Inc/HallSensor.h"
#include "../Inc/PIController.h"

class MotorDriver
{
private:
    // Hall sensor - speed measurement
    HallSensor hall_sensor;

    // PI motor controller
    PIController pi_controller;

    // Actual speed motor
    float actual_speed;

    // Target speed motor
    float target_speed;

    // PWM value
    uint32_t pwm_value;

public:
    MotorDriver();

    // Pointer for interrupt handling
    static HallSensor* instancePointer;

    // Init functions

    static void initPWM();
    static void initPIController();

    // Drive motor
    void DriveMotor(float speed, int16_t direction);
    void controllerCycle10ms();


    // Calculate actual motor speed, depending on values from hall sensor
    void calcSpeed();

    // Get / Set functions
    [[nodiscard]] float getSpeed() const ;
    [[nodiscard]] uint32_t getPWMValue() const;




};


#endif //PROJECT_MOTOR_CONTROLLER_MOTORDRIVER_H
