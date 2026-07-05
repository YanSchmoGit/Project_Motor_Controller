//
// Created by yan on 7/1/26.
//

#include "../Inc/PIController.h"


PIController::PIController(const float kp, const float ki, const float sample_time_ms, const float min_output, const float max_output)
    : kp_(kp), ki_(ki), sample_time_ms_(sample_time_ms), min_output_(min_output), max_output_(max_output)
{

}

int32_t PIController::update(float setpoint, float current_value)
{
    // Calculate error value
    const float error = setpoint - current_value;

    // Calculate p-part
    const float p_term = this->kp_ * error;

    // Sum up integral - based in sample time in seconds
    const float dt_seconds = this->sample_time_ms_ / 1000.0f;
    integral_sum_ += error * dt_seconds;

    // Anti wind up for the integral part
    if (integral_sum_ > max_output_)
    {
        integral_sum_ = max_output_;
    }
    else if (integral_sum_ < min_output_)
    {
        integral_sum_ = min_output_;
    }

    // Calculate the i-part - with the already limited integral part
    const float i_term = this->ki_ * integral_sum_;

    // Calculate output value
    float output = p_term + i_term;

    // Anti wind up for the p-part
    if (output > max_output_)
    {
        output = max_output_;
    }
    else if (output < min_output_)
    {
        output = min_output_;
    }

    return static_cast<int32_t>(output);
}


void PIController::reset()
{
    integral_sum_ = 0.0f;
}
