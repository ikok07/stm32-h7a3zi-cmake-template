#include <stdio.h>

#include "stm32h7xx.h"

#define GPIOBEN		(1U<<1)
#define PIN14		(1U<<14)
#define LED_PIN		PIN14

int main(void)
{
    RCC->AHB4ENR |= GPIOBEN;

    GPIOB->MODER |= (1U<<28);
    GPIOB->MODER &=~ (1U<<29);

    while (1) {
        GPIOB->ODR ^= LED_PIN;
        for (int i = 0; i < 1000000; i++) {}
    }
}
