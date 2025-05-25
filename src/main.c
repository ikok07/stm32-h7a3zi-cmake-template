#include <stdio.h>

#include "stm32h7xx.h"
#include "gpio_driver.h"

#define LED_PIN		GPIO_PIN_NO_14

int main(void) {

    GPIO_Handle_t gpioHandle = {
        .pGPIOx = GPIOB,
        .GPIO_PinConfig = {
            .GPIO_PinNumber = LED_PIN,
            .GPIO_PinMode = GPIO_MODE_OUTPUT,
            .GPIO_PinSpeed = GPIO_SPEED_LOW,
            .GPIO_PinOPType = GPIO_OP_TYPE_PP,
            .GPIO_PinPuPdControl = GPIO_NO_PUPD
        }
    };

    GPIO_PeriClockControl(GPIOB, ENABLE);
    GPIO_Init(&gpioHandle);

    while (1) {
        GPIO_ToggleOutputPin(GPIOB, LED_PIN);
        for (int i = 0; i < 1000000; i++) {}
    }
}