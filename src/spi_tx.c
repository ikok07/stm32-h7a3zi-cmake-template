//
// Created by Kok on 6/1/25.
//

#include <gpio_driver.h>
#include <spi_driver.h>
#include <string.h>

/**
 * GPIO Ports (AF5):
 * MISO:    PB14
 * MOSI:    PB15
 * SCK:     PB10
 * SS:      PB12
 */
void spi_tx() {
    GPIO_Handle_t spi_pin_handle = {
        .pGPIOx = GPIOB,
        .GPIO_PinConfig = {
            .GPIO_PinMode = GPIO_MODE_ALTERNATE,
            .GPIO_PinOPType = GPIO_OP_TYPE_PP,
            .GPIO_PinAltFunMode = GPIO_AF5,
            .GPIO_PinPuPdControl = GPIO_NO_PUPD
        }
    };

    // // MISO Pin
    // spi_pin_handle.GPIO_PinConfig.GPIO_PinNumber = 14;
    // GPIO_Init(&spi_pin_handle);

    // MOSI Pin
    spi_pin_handle.GPIO_PinConfig.GPIO_PinNumber = 15;
    GPIO_Init(&spi_pin_handle);

    // SCK Pin
    spi_pin_handle.GPIO_PinConfig.GPIO_PinNumber = 10;
    GPIO_Init(&spi_pin_handle);

    // // SS Pin
    // spi_pin_handle.GPIO_PinConfig.GPIO_PinNumber = 12;
    // GPIO_Init(&spi_pin_handle);

    SPI_Handle_t spi_handle = {
        .pSPIx = SPI2,
        .SPIConfig = {
            .SPI_DeviceMode = SPI_DEVICE_MODE_MASTER,
            .SPI_BusConfig = SPI_BUS_CFG_FULL_DUPLEX,
            .SPI_DF = SPI_DF_8BITS,
            .SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2,
            .SPI_SSM = SPI_SSM_HW,
            .SPI_CPHA = SPI_CPHA_LOW,
            .SPI_CPOL = SPI_CPOL_LOW,
            .SPI_SS_OutputEnabled = SPI_SS_OUTPUT_ENABLED,
            .SPI_SS_ActiveLevel = SPI_SS_LOW,
        }
    };

    SPI_Init(&spi_handle);
    SPI_PeripheralControl(spi_handle.pSPIx, ENABLE);

    char buffer[] = "Hello World!";
    SPI_SendData(&spi_handle, (uint8_t*)buffer, 1);

    SPI_PeripheralControl(spi_handle.pSPIx, DISABLE);
}