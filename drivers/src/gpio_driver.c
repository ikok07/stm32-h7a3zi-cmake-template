//
// Created by Kok on 5/25/25.
//

#include "gpio_driver.h"

/**
 * @brief Enables or disables peripheral clock for the given GPIO port
 * @param pGPIOx Base address of the GPIO peripheral
 * @param Enabled If the peripheral is enabled or disabled (1 or 0)
 */
void GPIO_PeriClockControl(GPIO_TypeDef *pGPIOx, uint8_t Enabled) {
    if (Enabled) {
        if (pGPIOx == GPIOA)       { GPIO_PCLK_EN(RCC_AHB4ENR_GPIOAEN_Pos); }
        else if (pGPIOx == GPIOB)  { GPIO_PCLK_EN(RCC_AHB4ENR_GPIOBEN_Pos); }
        else if (pGPIOx == GPIOC)  { GPIO_PCLK_EN(RCC_AHB4ENR_GPIOCEN_Pos); }
        else if (pGPIOx == GPIOD)  { GPIO_PCLK_EN(RCC_AHB4ENR_GPIODEN_Pos); }
        else if (pGPIOx == GPIOE)  { GPIO_PCLK_EN(RCC_AHB4ENR_GPIOEEN_Pos); }
        else if (pGPIOx == GPIOF)  { GPIO_PCLK_EN(RCC_AHB4ENR_GPIOFEN_Pos); }
        else if (pGPIOx == GPIOG)  { GPIO_PCLK_EN(RCC_AHB4ENR_GPIOGEN_Pos); }
        else if (pGPIOx == GPIOH)  { GPIO_PCLK_EN(RCC_AHB4ENR_GPIOHEN_Pos); }
        else if (pGPIOx == GPIOI)  { GPIO_PCLK_EN(RCC_AHB4ENR_GPIOIEN_Pos); }
        else if (pGPIOx == GPIOJ)  { GPIO_PCLK_EN(RCC_AHB4ENR_GPIOJEN_Pos); }
        else if (pGPIOx == GPIOK)  { GPIO_PCLK_EN(RCC_AHB4ENR_GPIOKEN_Pos); }
    } else {
        if (pGPIOx == GPIOA)       { GPIO_PCLK_DI(RCC_AHB4ENR_GPIOAEN_Pos); }
        else if (pGPIOx == GPIOB)  { GPIO_PCLK_DI(RCC_AHB4ENR_GPIOBEN_Pos); }
        else if (pGPIOx == GPIOC)  { GPIO_PCLK_DI(RCC_AHB4ENR_GPIOCEN_Pos); }
        else if (pGPIOx == GPIOD)  { GPIO_PCLK_DI(RCC_AHB4ENR_GPIODEN_Pos); }
        else if (pGPIOx == GPIOE)  { GPIO_PCLK_DI(RCC_AHB4ENR_GPIOEEN_Pos); }
        else if (pGPIOx == GPIOF)  { GPIO_PCLK_DI(RCC_AHB4ENR_GPIOFEN_Pos); }
        else if (pGPIOx == GPIOG)  { GPIO_PCLK_DI(RCC_AHB4ENR_GPIOGEN_Pos); }
        else if (pGPIOx == GPIOH)  { GPIO_PCLK_DI(RCC_AHB4ENR_GPIOHEN_Pos); }
        else if (pGPIOx == GPIOI)  { GPIO_PCLK_DI(RCC_AHB4ENR_GPIOIEN_Pos); }
        else if (pGPIOx == GPIOJ)  { GPIO_PCLK_DI(RCC_AHB4ENR_GPIOJEN_Pos); }
        else if (pGPIOx == GPIOK)  { GPIO_PCLK_DI(RCC_AHB4ENR_GPIOKEN_Pos); }
    }
}

/**
 * @brief Initializes the GPIO.
 * @param pGPIOHandle GPIO Handle
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle) {
    uint8_t pinNumber = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
    uint32_t temp = 0;

    // GPIO Mode Configuration
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG) {
        temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pinNumber);
        pGPIOHandle->pGPIOx->MODER &=~ (0b11 << (2 * pinNumber));
        pGPIOHandle->pGPIOx->MODER |= temp;
    } else {
        // Todo...
    }

    // GPIO Speed Configuration
    temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pinNumber);
    pGPIOHandle->pGPIOx->OSPEEDR &=~ (0b11 << (2 * pinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;

    // GPIO Pull Up & Pull Down Configuration
    temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pinNumber);
    pGPIOHandle->pGPIOx->PUPDR &=~ (0b11 << (2 * pinNumber));
    pGPIOHandle->pGPIOx->PUPDR |= temp;

    // GPIO Output Type Configuration
    temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pinNumber;
    pGPIOHandle->pGPIOx->OTYPER &=~ (0b01 << pinNumber);
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    // GPI Alternate Function Configuration
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTERNATE) {
        int offset = 4 * (pinNumber % 8);
        temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << offset;
        pGPIOHandle->pGPIOx->AFR[pinNumber / 8] &=~ (0b1111 << offset);
        pGPIOHandle->pGPIOx->AFR[pinNumber / 8] |= temp;
    }
}

/**
 * @brief De-Initializes the specified GPIO Port
 * @param pGPIOx GPIO Port
 */
void GPIO_DeInit(GPIO_TypeDef *pGPIOx) {
    if (pGPIOx == GPIOA)       { GPIO_REG_RESET(RCC_AHB4ENR_GPIOAEN_Pos); }
    else if (pGPIOx == GPIOB)  { GPIO_REG_RESET(RCC_AHB4ENR_GPIOBEN_Pos); }
    else if (pGPIOx == GPIOC)  { GPIO_REG_RESET(RCC_AHB4ENR_GPIOCEN_Pos); }
    else if (pGPIOx == GPIOD)  { GPIO_REG_RESET(RCC_AHB4ENR_GPIODEN_Pos); }
    else if (pGPIOx == GPIOE)  { GPIO_REG_RESET(RCC_AHB4ENR_GPIOEEN_Pos); }
    else if (pGPIOx == GPIOF)  { GPIO_REG_RESET(RCC_AHB4ENR_GPIOFEN_Pos); }
    else if (pGPIOx == GPIOG)  { GPIO_REG_RESET(RCC_AHB4ENR_GPIOGEN_Pos); }
    else if (pGPIOx == GPIOH)  { GPIO_REG_RESET(RCC_AHB4ENR_GPIOHEN_Pos); }
    else if (pGPIOx == GPIOI)  { GPIO_REG_RESET(RCC_AHB4ENR_GPIOIEN_Pos); }
    else if (pGPIOx == GPIOJ)  { GPIO_REG_RESET(RCC_AHB4ENR_GPIOJEN_Pos); }
    else if (pGPIOx == GPIOK)  { GPIO_REG_RESET(RCC_AHB4ENR_GPIOKEN_Pos); }
}

/**
 * @brief Reads data from specified GPIO Port and Pin
 * @param pGPIOx GPIO Port
 * @param PinNumber GPIO Pin
 * @return Data read from the GPIO Pin
 */
uint8_t GPIO_ReadFromInputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber) {
    return (pGPIOx->IDR >> PinNumber) & 1;
}

/**
 * @brief Reads data from specified GPIO Port
 * @param pGPIOx GPIO Port
 * @return Data read from the GPIO Port
 */
uint32_t GPIO_ReadFromInputPort(GPIO_TypeDef *pGPIOx) {
    return pGPIOx->IDR;
}

/**
 * @brief Writes data to specified GPIO Port and Pin
 * @param pGPIOx GPIO Port
 * @param PinNumber GPIO Pin
 * @param Value Value to write
 */
void GPIO_WriteToOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber, uint8_t Value) {
    if (Value == 1) pGPIOx->ODR |= (1 << PinNumber);
    else pGPIOx->ODR &=~ (1 << PinNumber);
}

/**
 * @brief Writes data to specified GPIO Port
 * @param pGPIOx GPIO Port
 * @param Value Value to write
 */
void GPIO_WriteToOutputPort(GPIO_TypeDef *pGPIOx, uint32_t Value) {
    pGPIOx->ODR = Value;
}

void GPIO_ToggleOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber) {
    pGPIOx->ODR ^= (1 << PinNumber);
}
