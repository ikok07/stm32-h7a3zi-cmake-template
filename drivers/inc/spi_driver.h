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

/**
 * @SPI_MODES
 */
#define SPI_DEVICE_MODE_MASTER              1
#define SPI_DEVICE_MODE_SLAVE               0

/**
 * @SPI_BUS_CONFIGURATIONS
 */
#define SPI_BUS_CFG_FULL_DUPLEX             0
#define SPI_BUS_CFG_SIMPLEX_RXONLY          2
#define SPI_BUS_CFG_HALF_DUPLEX             3

/**
 * @SPI_SPEEDs
 */
#define SPI_SCLK_SPEED_DIV2                 0
#define SPI_SCLK_SPEED_DIV4                 1
#define SPI_SCLK_SPEED_DIV8                 2
#define SPI_SCLK_SPEED_DIV16                3
#define SPI_SCLK_SPEED_DIV32                4
#define SPI_SCLK_SPEED_DIV64                5
#define SPI_SCLK_SPEED_DIV128               6
#define SPI_SCLK_SPEED_DIV256               7

/**
 * @SPI_DATA_FRAMES
 */
#define SPI_DF_8BITS                       7
#define SPI_DF_16BITS                      15

/**
 * @CLOCK_POLARITIES
 */
#define SPI_CPOL_HIGH                       1
#define SPI_CPOL_LOW                        0

/**
 * @CLOCK_PHASE
 */
#define SPI_CPHA_HIGH                       1
#define SPI_CPHA_LOW                        0

/**
 * @SPI_SLAVE_SELECT_MANAGEMENT
 */
#define SPI_SSM_HW                          0
#define SPI_SSM_SW                          1

/**
 * @SPI_SSOE
 */
#define SPI_SS_OUTPUT_DISABLED              0
#define SPI_SS_OUTPUT_ENABLED               1

/**
 * @SPI_SS_ACTIVE_LEVEL
 */
#define SPI_SS_LOW                          0
#define SPI_SS_HIGH                         1

typedef struct {
    uint8_t SPI_DeviceMode;                 /** Possible values from @SPI_MODES */
    uint8_t SPI_BusConfig;                  /** Possible values from @SPI_BUS_CONFIGURATIONS */
    uint8_t SPI_SclkSpeed;                  /** Possible values from @SPI_SPEEDs */
    uint8_t SPI_DF;                         /** Possible values from @SPI_DATA_FRAMES */
    uint8_t SPI_CPOL;                       /** Possible values from @CLOCK_POLARITIES */
    uint8_t SPI_CPHA;                       /** Possible values from @CLOCK_PHASE */
    uint8_t SPI_SSM;                        /** Possible values from @SPI_SLAVE_SELECT_MANAGEMENT */
    uint8_t SPI_SS_OutputEnabled;           /** Possible values from @SPI_SSOE */
    uint8_t SPI_SS_ActiveLevel;             /** Possible values from @SPI_SS_ACTIVE_LEVEL */
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
int SPI_SendData(SPI_Handle_t *pSPIHandle, uint8_t *pTXBuffer, uint32_t len);
void SPI_ReceiveData(SPI_Handle_t *pSPIHandle, uint8_t *pRXBuffer, uint32_t len);

/*
 * IRQ Configuration
 */
void SPI_IRQConfig(uint8_t PinNumber, uint8_t IRQPriority, uint8_t Enabled);
void SPI_IRQHandling(uint8_t PinNumber);

/*
 * Other controls
 */
void SPI_PeripheralControl(SPI_TypeDef *pSPIx, uint8_t enabled);

#endif //SPI_DRIVER_H
