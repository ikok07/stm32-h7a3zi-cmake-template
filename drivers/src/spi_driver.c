//
// Created by Kok on 5/29/25.
//

#include "spi_driver.h"

/**
 * @brief Enables or disables peripheral clock for the given SPI peripheral
 * @param pSPIx Base address of the SPI peripheral
 * @param Enabled If the peripheral is enabled or disabled (1 or 0)
 */
void SPI_PeriClockControl(SPI_TypeDef *pSPIx, uint8_t Enabled) {
    if (Enabled) {
        if (pSPIx == SPI1) SPI_PCLK_EN(1, RCC_APB2ENR_SPI1EN_Pos);
        if (pSPIx == SPI2) SPI_PCLK_EN(2, RCC_APB1LENR_SPI2EN_Pos);
        if (pSPIx == SPI3) SPI_PCLK_EN(3, RCC_APB1LENR_SPI3EN_Pos);
        if (pSPIx == SPI4) SPI_PCLK_EN(4, RCC_APB2ENR_SPI4EN_Pos);
        if (pSPIx == SPI5) SPI_PCLK_EN(5, RCC_APB2ENR_SPI5EN_Pos);
        if (pSPIx == SPI6) SPI_PCLK_EN(6, RCC_APB4ENR_SPI6EN_Pos);
    } else {
        if (pSPIx == SPI1) SPI_PCLK_DI(1, RCC_APB2ENR_SPI1EN_Pos);
        if (pSPIx == SPI2) SPI_PCLK_DI(2, RCC_APB1LENR_SPI2EN_Pos);
        if (pSPIx == SPI3) SPI_PCLK_DI(3, RCC_APB1LENR_SPI3EN_Pos);
        if (pSPIx == SPI4) SPI_PCLK_DI(4, RCC_APB2ENR_SPI4EN_Pos);
        if (pSPIx == SPI5) SPI_PCLK_DI(5, RCC_APB2ENR_SPI5EN_Pos);
        if (pSPIx == SPI6) SPI_PCLK_DI(6, RCC_APB4ENR_SPI6EN_Pos);
    }
}

/**
 * @brief De-Initializes the specified SPI Peripheral
 * @param pSPIx SPI Port
 */
void SPI_DeInit(SPI_TypeDef *pSPIx) {
    if (pSPIx == SPI1) SPI_REG_RESET(1, RCC_APB2RSTR_SPI1RST_Pos);
    if (pSPIx == SPI2) SPI_REG_RESET(2, RCC_APB1LRSTR_SPI2RST_Pos);
    if (pSPIx == SPI3) SPI_REG_RESET(3, RCC_APB1LRSTR_SPI3RST_Pos);
    if (pSPIx == SPI4) SPI_REG_RESET(4, RCC_APB2RSTR_SPI4RST_Pos);
    if (pSPIx == SPI5) SPI_REG_RESET(5, RCC_APB2RSTR_SPI5RST_Pos);
    if (pSPIx == SPI6) SPI_REG_RESET(6, RCC_APB4RSTR_SPI6RST_Pos);
}
