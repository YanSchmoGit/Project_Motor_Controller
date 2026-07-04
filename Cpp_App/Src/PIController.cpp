//
// Created by yan on 7/1/26.
//

#include "../Inc/PIController.h"


PIController::PIController(const float kp, const float ki, const float sample_time_ms, const float min_output, const float max_output)
    : kp_(kp), ki_(ki), sample_time_ms_(sample_time_ms), min_output_(min_output), max_output_(max_output)
{

}

uint32_t PIController::update(float setpoint, float current_value)
{
    // Calculate error
    const float error = setpoint - current_value;

    // Calculate integral
    float const delta_integral = error * this->sample_time_ms_;
    integral_sum_ += delta_integral;

    // Calculate i-part & p-part
    float const  p_term = this->kp_ * error;
    float const  i_term = this->ki_ * integral_sum_;

    // output
    float output = p_term + i_term;


    //Anti-Windup & setpoint limitation

    if (output > max_output_)
    {
        output = max_output_;
        integral_sum_ -= delta_integral;
    }
    else if (output < min_output_)
    {
        output = min_output_;
        integral_sum_ -= delta_integral;
    }

    return static_cast<uint32_t>(output);
}


void PIController::reset()
{
    integral_sum_ = 0.0f;
}
