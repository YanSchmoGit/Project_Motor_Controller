//
// Created by yan on 6/1/26.
//

#include "../Inc/Application.h"
#include "stm32l476xx.h"

// Hier können Sie echten C++ Code nutzen (Klassen, Namespaces etc.)
class LedBlinker {
public:
    void toggle() {
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
        GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
        GPIOA->MODER |= GPIO_MODER_MODE5_0;

        GPIOA->BSRR |= GPIO_BSRR_BS5;
    }
};

void Application_Main(void) {
    LedBlinker blinker;

    // Bare-Metal Super-Loop
    while (1) {
        blinker.toggle();

    }
}