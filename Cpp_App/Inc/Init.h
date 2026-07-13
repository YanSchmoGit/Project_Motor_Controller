//
// Created by yan on 6/30/26.
//

#ifndef PROJECT_MOTOR_CONTROLLER_INIT_H
#define PROJECT_MOTOR_CONTROLLER_INIT_H

#pragma once
#include <stm32l4xx.h>
namespace Init
{
    inline volatile uint32_t ticks = 0;

    void initSystemClock();

    void delay(uint32_t ms);


}



#endif //PROJECT_MOTOR_CONTROLLER_INIT_H
