#include <stdio.h>

#include "stm32h7xx.h"
#include "gpio_driver.h"

#define LED_PIN		GPIO_PIN_NO_14
#define BTN_PIN		GPIO_PIN_NO_13

int main(void) {

    GPIO_Handle_t ledGPIOHandle = {
        .pGPIOx = GPIOB,
        .GPIO_PinConfig = {
            .GPIO_PinNumber = LED_PIN,
            .GPIO_PinMode = GPIO_MODE_OUTPUT,
            .GPIO_PinSpeed = GPIO_SPEED_LOW,
            .GPIO_PinOPType = GPIO_OP_TYPE_PP,
            .GPIO_PinPuPdControl = GPIO_NO_PUPD
        }
    };

    GPIO_Handle_t buttonGPIOHandle = {
        .pGPIOx = GPIOC,
        .GPIO_PinConfig = {
            .GPIO_PinNumber = BTN_PIN,
            .GPIO_PinMode = GPIO_MODE_INPUT_R_EDGE,
            .GPIO_PinSpeed = GPIO_SPEED_LOW,
            .GPIO_PinPuPdControl = GPIO_PD
        }
    };

    GPIO_PeriClockControl(GPIOB, ENABLE);
    GPIO_PeriClockControl(GPIOC, ENABLE);
    GPIO_Init(&ledGPIOHandle);
    GPIO_Init(&buttonGPIOHandle);

    GPIO_IRQConfig(BTN_PIN, 1, ENABLE);

    while (1);
}

void EXTI15_10_IRQHandler(void) {
    GPIO_IRQHandling(BTN_PIN);
    GPIO_ToggleOutputPin(GPIOB, LED_PIN);
}