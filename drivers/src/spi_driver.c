//
// Created by Kok on 5/29/25.
//

#include "spi_driver.h"
#include "commons.h"

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

void SPI_Init(SPI_Handle_t *pSPIHandle) {
    // Enable Peripheral Clock
    SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

    // 1. SPI Mode
    pSPIHandle->pSPIx->CFG2 |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CFG2_MASTER_Pos;

    // 2. Bus config
    pSPIHandle->pSPIx->CFG2 |= pSPIHandle->SPIConfig.SPI_BusConfig << SPI_CFG2_COMM_Pos;

    // 3. Baud rate
    pSPIHandle->pSPIx->CFG1 |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CFG1_MBR_Pos;

    // 4. Data frame
    pSPIHandle->pSPIx->CFG1 |= pSPIHandle->SPIConfig.SPI_DF << SPI_CFG1_DSIZE_Pos;

    // 5. CPOL
    pSPIHandle->pSPIx->CFG2 |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CFG2_CPOL_Pos;

    // 6. CPHA
    pSPIHandle->pSPIx->CFG2 |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CFG2_CPHA_Pos;

    // 7. SS Output control
    pSPIHandle->pSPIx->CFG2 |= pSPIHandle->SPIConfig.SPI_SS_OutputEnabled << SPI_CFG2_SSOE_Pos;

    // 8. Select SS Hardware or Software control
    pSPIHandle->pSPIx->CFG2 |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CFG2_SSM_Pos;

    // 9. If SS is software controlled -> Pull up the SS pin
    if (pSPIHandle->SPIConfig.SPI_SSM & (1 << SPI_CFG2_SSM_Pos)) pSPIHandle->pSPIx->CR1 |= 1 << SPI_CR1_SSI_Pos;

    // 10. SS Active level
    pSPIHandle->pSPIx->CFG2 |= pSPIHandle->SPIConfig.SPI_SS_ActiveLevel << SPI_CFG2_SSIOP_Pos;
}

/**
 * @brief Sends data via the SPI peripheral
 * @note This method will block until all data is transmitted
 * @param pSPIx Pointer to SPI peripheral
 * @param pTXBuffer Buffer of the data to be transferred
 * @param len Number of bytes in the tx buffer
 */
int SPI_SendData(SPI_Handle_t *pSPIHandle, uint8_t *pTXBuffer, uint32_t len) {
    while (len > 0) {
        // Wait for empty tx queue
        while (!(pSPIHandle->pSPIx->SR & (1 << SPI_SR_TXP_Pos))) {}

        if (pSPIHandle->SPIConfig.SPI_DF & (1 << SPI_DF_8BITS)) {
            pSPIHandle->pSPIx->TXDR = *pTXBuffer;
            pTXBuffer++;
            len--;
        } else if (pSPIHandle->SPIConfig.SPI_DF & (1 << SPI_DF_16BITS)) {
            pSPIHandle->pSPIx->TXDR = *(uint16_t*)pTXBuffer;
            pTXBuffer += 2;
            len -= 2;
        } else {
            return 1;
        }
    }

    // Wait for tx completed
    while (!(pSPIHandle->pSPIx->SR & (1 << SPI_SR_TXC_Pos))) {}

    return 0;
}

/**
 * @brief Enables or disables the SPI Peripheral
 * @param pSPIx SPI Port
 * @param enabled If the SPI Peripheral should be enabled
 */
void SPI_PeripheralControl(SPI_TypeDef *pSPIx, uint8_t enabled) {
    if (enabled == ENABLE) pSPIx->CR1 |= (1 << SPI_CR1_CSTART_Pos);
    else pSPIx->CR1 &=~ (1 << SPI_CR1_CSTART_Pos);
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
