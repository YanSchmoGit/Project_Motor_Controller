//
// Created by yan on 6/13/26.
//

#ifndef PROJECT_MOTOR_CONTROLLER_BRIDGEFUNCTIONS_H
#define PROJECT_MOTOR_CONTROLLER_BRIDGEFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

// Bridge function interrupts

// TIM5


void cpp_handle_interrupt_tim5(void);

void cpp_handle_interrupt_tim3(void);


#ifdef __cplusplus
}
#endif


#endif //PROJECT_MOTOR_CONTROLLER_BRIDGEFUNCTIONS_H
