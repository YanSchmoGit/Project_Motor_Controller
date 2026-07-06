//
// Created by yan on 7/5/26.
//

#ifndef PROJECT_MOTOR_CONTROLLER_TERMINAL_H
#define PROJECT_MOTOR_CONTROLLER_TERMINAL_H
#include <array>
#include <cstdint>


class Terminal
{


public:

    // Structure for the controller data
    struct Data {
        uint32_t setpoint;
        uint32_t process_value;
    };

    Terminal();

    void terminalInit();

    void terminalSend(uint32_t setpoint, uint32_t process_value);

    static bool is_ready() ;


private:
    std::array<Data, 1> m_tx_buffer{};
    std::array<char, 64> m_tx_ascii_buffer{};


};


#endif //PROJECT_MOTOR_CONTROLLER_TERMINAL_H
