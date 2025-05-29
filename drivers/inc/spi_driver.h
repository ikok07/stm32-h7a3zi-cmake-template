//
// Created by Kok on 5/29/25.
//

#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <stdint.h>
#include <stm32h7a3xx.h>

/**
 * @brief Enables the SPI peripheral clock
 * @param perIndex The index of the specific SPI perifpheral (SPI1, SPI2, SPI3, etc.)
 * @param offset The offset of the enable register specific to each SPI
 */
#define SPI_PCLK_EN(perIndex, offset)        (\
                                                perIndex > 1 && perIndex < 4 ? RCC->APB1LENR |= (1U << offset) :\
                                                perIndex == 1 || (perIndex > 3 && perIndex < 6) ? RCC->APB2ENR |= (1U << offset) :\
                                                perIndex == 6 ? RCC->APB4ENR |= (1U << offset) : (void)0\
                                             )

/**
 * @brief Disables the SPI peripheral clock
 * @param perIndex The index of the specific SPI perifpheral (SPI1, SPI2, SPI3, etc.)
 * @param offset The offset of the enable register specific to each SPI
 */
#define SPI_PCLK_DI(perIndex, offset)        (\
                                                perIndex > 1 && perIndex < 4 ? RCC->APB1LENR &=~ (1U << offset) :\
                                                perIndex == 1 || (perIndex > 3 && perIndex < 6) ? RCC->APB2ENR &=~ (1U << offset) :\
                                                perIndex == 6 ? RCC->APB4ENR &=~ (1U << offset) : (void)0\
                                             )

/**
 * @brief Resets the SPI peripheral
 * @param perIndex The index of the specific SPI perifpheral (SPI1, SPI2, SPI3, etc.)
 * @param offset The offset of the reset register specific to each SPI peripheral
 */
#define SPI_REG_RESET(perIndex, offset)      do {\
                                                if (perIndex > 1 && perIndex < 4) {\
                                                    (RCC->APB1LRSTR |= (1U << offset));\
                                                    (RCC->APB1LRSTR &=~ (1U << offset));\
                                                }\
                                                else if (perIndex == 1 || (perIndex > 3 && perIndex < 6)) {\
                                                    (RCC->AHB4RSTR |= (1U << offset));\
                                                    (RCC->AHB4RSTR &=~ (1U << offset));\
                                                }\
                                                else if (perIndex == 6) {\
                                                    (RCC->APB4RSTR |= (1U << offset));\
                                                    (RCC->APB4RSTR &=~ (1U << offset));\
                                                }\
                                                (void)0;\
                                             } while (0)

typedef struct {
    uint8_t SPI_DeviceMode;
    uint8_t SPI_BusConfig;
    uint8_t SPI_SclkSpeed;
    uint8_t SPI_DFF;
    uint8_t SPI_CPOL;
    uint8_t SPI_CPHA;
    uint8_t SPI_SSM;
} SPI_Config_t;

typedef struct {
    SPI_TypeDef *pSPIx;
    SPI_Config_t SPIConfig;
} SPI_Handle_t;

/*
 * Peripheral Clock Setup
 */
void SPI_PeriClockControl(SPI_TypeDef *pSPIx, uint8_t Enabled);

/*
 * Init and De-Init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_TypeDef *pSPIx);

/*
 * Data send and receive
 */
void SPI_SendData(SPI_TypeDef *pSPIx, uint8_t *pTXBuffer, uint32_t len);
void SPI_ReceiveData(SPI_TypeDef *pSPIx, uint8_t *pRXBuffer, uint32_t len);

/*
 * IRQ Configuration
 */
void SPI_IRQConfig(uint8_t PinNumber, uint8_t IRQPriority, uint8_t Enabled);
void SPI_IRQHandling(uint8_t PinNumber);

#endif //SPI_DRIVER_H
