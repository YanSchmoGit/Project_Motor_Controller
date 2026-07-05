//
// Created by yan on 7/1/26.
//

#ifndef PROJECT_MOTOR_CONTROLLER_PICONTROLLER_H
#define PROJECT_MOTOR_CONTROLLER_PICONTROLLER_H
#include <cstdint>


class PIController
{
private:
    float kp_;
    float ki_;

    float sample_time_ms_;

    float min_output_;
    float max_output_;

    float integral_sum_ = 0.0f;

public:
    PIController(float kp, float ki, float sample_time_ms, float min_output, float max_output);

    // Update values
    int32_t update(float setpoint, float current_value);

    // Rest integration result
    void reset();


};


#endif //PROJECT_MOTOR_CONTROLLER_PICONTROLLER_H
