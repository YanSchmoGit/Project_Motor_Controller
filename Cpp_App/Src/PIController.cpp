//
// Created by yan on 7/1/26.
//

#include "../Inc/PIController.h"


PIController::PIController(float kp, float ki, float sample_time_ms, float min_output, float max_output)
{
    this->kp_ = kp;
    this->ki_ = ki;
    this->sample_time_ms_ = sample_time_ms;
    this->min_output_ = min_output;
    this->max_output_ = max_output;
}

uint32_t PIController::update(float setpoint, float current_value)
{
    // Calculate error
    float error = setpoint - current_value;

    // Calculate integral
    float delta_integral = error * this->sample_time_ms_;
    integral_sum_ += delta_integral;

    // Calculate i-part & p-part
    float p_term = this->kp_ * error;
    float i_term = this->ki_ * integral_sum_;

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
