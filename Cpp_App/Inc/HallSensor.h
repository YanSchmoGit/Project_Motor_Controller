//
// Created by yan on 6/8/26.
//

#ifndef PROJECT_MOTOR_CONTROLLER_HALLSENSOR_H
#define PROJECT_MOTOR_CONTROLLER_HALLSENSOR_H
#include <cstdint>


class HallSensor
{
private:
    uint32_t count;

    uint8_t state;

public:
    HallSensor();
    void countSignals();
    uint32_t getCount() const;
    uint8_t getState() const;


};


#endif //PROJECT_MOTOR_CONTROLLER_HALLSENSOR_H
