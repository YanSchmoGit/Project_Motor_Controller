//
// Created by yan on 6/30/26.
//

#include "../Inc/Init.h"


namespace Init
{
    void initSystemClock()
    {
        // Set Clock HSI - 16 MHz

        RCC->CR |= RCC_CR_HSION;

        while (!(RCC->CR & RCC_CR_HSIRDY)) {}

        // Configure waite states
        FLASH->ACR &= ~FLASH_ACR_LATENCY;
        FLASH->ACR |= FLASH_ACR_LATENCY_0WS;

        // Select HSI as system clock
        RCC->CFGR &= ~RCC_CFGR_SW;
        RCC->CFGR |= RCC_CFGR_SW_HSI;

        // Wait until clock is selected
        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);

        SystemCoreClockUpdate();

        // Config SysTick
        SysTick_Config(SystemCoreClock / 1000);
    }

    void delay(const uint32_t ms)
    {
        const uint32_t start = ticks;
        while (ticks - start < ms);
    }

    extern "C" void cpp_handle_systick(void)
    {
        ++ticks;
    }

}
