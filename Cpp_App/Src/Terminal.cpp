//
// Created by yan on 7/5/26.
//

#include "../Inc/Terminal.h"

#include <cstdio>

#include "stm32l476xx.h"


Terminal::Terminal()
{
    // Init terminal functions
    terminalInit();
}

void Terminal::terminalInit()
{
    // Init UART functions

    // Enable PA2 & PA3 for UART communication
    // Configure AF7 for UART

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    GPIOA->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);
    GPIOA->MODER |= GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1;

    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2_Msk | GPIO_AFRL_AFSEL3_Msk);
    GPIOA->AFR[0] |= GPIO_AFRL_AFSEL2_0 | GPIO_AFRL_AFSEL2_1 | GPIO_AFRL_AFSEL2_2; // AF 7 for PA2
    GPIOA->AFR[0] |= GPIO_AFRL_AFSEL3_0 | GPIO_AFRL_AFSEL3_1 | GPIO_AFRL_AFSEL3_2; // AF 7 for PA3

    // Configure UART

    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;

    USART2->BRR = 139; // Set Baudrate to 115200 -> Calculation: 16 000 000 / 115200 = 138.888 -> BRR = 139 (0x8B)

    USART2->CR3 |= USART_CR3_DMAT; // Enable DMA for USART 2
    USART2->CR1 &= ~(USART_CR1_M0_Msk | USART_CR1_M1_Msk); // Set word length -> 1 start bit, 8 data bits, n stop bits
    USART2->CR1 &= ~USART_CR1_PCE_Msk; // Configure parity bit -> no parity bit
    USART2->CR2 &= ~(USART_CR2_STOP_Msk); // Configure stop bit -> 1 stop bit

    USART2->CR1 |= USART_CR1_UE | USART_CR1_TE; // Start USART & enable transmitter


    // Configure DMA

    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

    DMA1_CSELR->CSELR &= ~DMA_CSELR_C7S_Msk; // Reset selection
    DMA1_CSELR->CSELR |= (2 << DMA_CSELR_C7S_Pos); // Map to USART2_TX -> see reference manual

    // Configure source, destination of data
    DMA1_Channel7->CPAR = reinterpret_cast<uint32_t>(&(USART2->TDR)); // destination
    DMA1_Channel7->CMAR = reinterpret_cast<uint32_t>(m_tx_ascii_buffer.data()); // source

    // Configure DMA mode
    DMA1_Channel7->CCR |= DMA_CCR_DIR | DMA_CCR_MINC;

    //DMA1_Channel7->CCR |= DMA_CCR_EN;
}

bool Terminal::is_ready()
{
    // Check if DMA is ready to transmit data
    if ((DMA1->ISR & DMA_ISR_TCIF7) || !(DMA1_Channel7->CCR & DMA_CCR_EN))
    {
        return true;
    }
    return false;
}


void Terminal::terminalSend(const uint32_t setpoint, const uint32_t process_value)
{
    if (is_ready())
    {
        DMA1_Channel7->CCR &= ~DMA_CCR_EN; // Disable DMA1
        DMA1->IFCR = DMA_IFCR_CTCIF7; // Delete transfer-complete-flag
/*
        // Write data to transmit buffer
        m_tx_buffer[0].process_value = process_value;
        m_tx_buffer[0].setpoint = setpoint;*/


        int text_length = snprintf(m_tx_ascii_buffer.data(), m_tx_ascii_buffer.size(),
                                   "%lu.%02lu,%lu.%02lu\r\n",
                                   setpoint , setpoint % 100,
                                   process_value , process_value % 100);

        // Check for buffer overflow
        if (text_length <= 0 || text_length >= static_cast<int>(m_tx_ascii_buffer.size())) {
            return;
        }

        // Set size of the char chain to DMA register
        DMA1_Channel7->CNDTR = text_length;


        //DMA1_Channel7->CNDTR = sizeof(Data); // Set size to DMA register

        DMA1_Channel7->CCR |= DMA_CCR_EN; // Enable DMA1

    } // else --> DMA is still busy
}
