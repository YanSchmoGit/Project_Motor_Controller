//
// Created by yan on 6/8/26.
//

#ifndef PROJECT_MOTOR_CONTROLLER_HALLSENSOR_H
#define PROJECT_MOTOR_CONTROLLER_HALLSENSOR_H
#include <cstdint>

class HallSensor
{
private:
    uint32_t last_cycle_count{};
    uint32_t actual_cycle_count{};
    uint32_t delta_count{}; // cycle counts between input signals



public:
    HallSensor();

    // Copy actual cycle value between to interrupts - functions gets called by interrupt
    void countSignals(); // interrupt function

    // Get / Set functions
    uint32_t getCount() const;



};


#endif //PROJECT_MOTOR_CONTROLLER_HALLSENSOR_H
