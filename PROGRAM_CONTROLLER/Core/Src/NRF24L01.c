#include "stm32f1xx_hal.h"               // MISRA C 2012 Rule 1.1: Include only necessary headers
#include "NRF24L01.h"                    // MISRA C 2012 Rule 1.1

extern SPI_HandleTypeDef hspi1;         // MISRA C 2012 Rule 8.4: external declaration is allowed
#define NRF24_SPI &hspi1                // MISRA C 2012 Rule 2.5: macro definition used

#define NRF24_CE_PORT   GPIOA           // MISRA C 2012 Rule 2.5
#define NRF24_CE_PIN    GPIO_PIN_9      // MISRA C 2012 Rule 2.5

#define NRF24_CSN_PORT  GPIOA           // MISRA C 2012 Rule 2.5
#define NRF24_CSN_PIN   GPIO_PIN_8      // MISRA C 2012 Rule 2.5

void CS_Select(void)
{
    HAL_GPIO_WritePin(NRF24_CSN_PORT, NRF24_CSN_PIN, GPIO_PIN_RESET); // MISRA C 2012 Rule 21.6: direct hardware access
}

void CS_UnSelect(void)
{
    HAL_GPIO_WritePin(NRF24_CSN_PORT, NRF24_CSN_PIN, GPIO_PIN_SET);   // MISRA C 2012 Rule 21.6
}
//CSN = Chip Select Not = Aktif Low//

void CE_Enable(void)
{
    HAL_GPIO_WritePin(NRF24_CE_PORT, NRF24_CE_PIN, GPIO_PIN_SET);     // MISRA C 2012 Rule 21.6
}

void CE_Disable(void)
{
    HAL_GPIO_WritePin(NRF24_CE_PORT, NRF24_CE_PIN, GPIO_PIN_RESET);   // MISRA C 2012 Rule 21.6
}

void nrf24_WriteReg(uint8_t Reg, uint8_t Data)
{
    uint8_t buf[2];
    buf[0] = (uint8_t)(Reg | 0x20U);   // MISRA C 2012 Rule 10.6: cast for bitwise operation
    buf[1] = Data;

    CS_Select();
    (void)HAL_SPI_Transmit(NRF24_SPI, buf, 2U, 1000U); // MISRA C 2012 Rule 21.2: explicit cast
    CS_UnSelect();
}

void nrf24_WriteRegMulti(uint8_t Reg, uint8_t *data, int size)
{
    uint8_t buf = (uint8_t)(Reg | 0x20U); // MISRA C 2012 Rule 10.6

    CS_Select();
    (void)HAL_SPI_Transmit(NRF24_SPI, &buf, 1U, 100U);
    (void)HAL_SPI_Transmit(NRF24_SPI, data, (uint16_t)size, 1000U); // MISRA C 2012 Rule 10.8
    CS_UnSelect();
}

uint8_t nrf24_ReadReg(uint8_t Reg)
{
    uint8_t data = 0U;

    CS_Select();
    (void)HAL_SPI_Transmit(NRF24_SPI, &Reg, 1U, 100U);
    (void)HAL_SPI_Receive(NRF24_SPI, &data, 1U, 100U);
    CS_UnSelect();

    return data;
}

void nrf24_ReadReg_Multi(uint8_t Reg, uint8_t *data, int size)
{
    CS_Select();
    (void)HAL_SPI_Transmit(NRF24_SPI, &Reg, 1U, 100U);
    (void)HAL_SPI_Receive(NRF24_SPI, data, (uint16_t)size, 1000U); // MISRA C 2012 Rule 10.8
    CS_UnSelect();
}

void nrfsendCmd(uint8_t cmd)
{
    CS_Select();
    (void)HAL_SPI_Transmit(NRF24_SPI, &cmd, 1U, 100U);
    CS_UnSelect();
}

void nrf24_reset(uint8_t REG)
{
    if (REG == STATUS)
    {
        nrf24_WriteReg(STATUS, 0x00U);
    }
    else if (REG == FIFO_STATUS)
    {
        nrf24_WriteReg(FIFO_STATUS, 0x11U);
    }
    else
    {
        nrf24_WriteReg(CONFIG, 0x08U);
        nrf24_WriteReg(EN_AA, 0x3FU);
        nrf24_WriteReg(EN_RXADDR, 0x03U);
        nrf24_WriteReg(SETUP_AW, 0x03U);
        nrf24_WriteReg(SETUP_RETR, 0x03U);
        nrf24_WriteReg(RF_CH, 0x02U);
        nrf24_WriteReg(RF_SETUP, 0x0EU);
        nrf24_WriteReg(STATUS, 0x00U);
        nrf24_WriteReg(OBSERVE_TX, 0x00U);
        nrf24_WriteReg(CD, 0x00U);
        uint8_t rx_addr_p0_def[5] = {0xE7U, 0xE7U, 0xE7U, 0xE7U, 0xE7U};
        nrf24_WriteRegMulti(RX_ADDR_P0, rx_addr_p0_def, 5);
        uint8_t rx_addr_p1_def[5] = {0xC2U, 0xC2U, 0xC2U, 0xC2U, 0xC2U};
        nrf24_WriteRegMulti(RX_ADDR_P1, rx_addr_p1_def, 5);
        nrf24_WriteReg(RX_ADDR_P2, 0xC3U);
        nrf24_WriteReg(RX_ADDR_P3, 0xC4U);
        nrf24_WriteReg(RX_ADDR_P4, 0xC5U);
        nrf24_WriteReg(RX_ADDR_P5, 0xC6U);
        uint8_t tx_addr_def[5] = {0xE7U, 0xE7U, 0xE7U, 0xE7U, 0xE7U};
        nrf24_WriteRegMulti(TX_ADDR, tx_addr_def, 5);
        nrf24_WriteReg(RX_PW_P0, 0U);
        nrf24_WriteReg(RX_PW_P1, 0U);
        nrf24_WriteReg(RX_PW_P2, 0U);
        nrf24_WriteReg(RX_PW_P3, 0U);
        nrf24_WriteReg(RX_PW_P4, 0U);
        nrf24_WriteReg(RX_PW_P5, 0U);
        nrf24_WriteReg(FIFO_STATUS, 0x11U);
        nrf24_WriteReg(DYNPD, 0U);
        nrf24_WriteReg(FEATURE, 0U);
    }
}

void NRF24_Init(void)
{
    CE_Disable();
    nrf24_reset(0U);
    nrf24_WriteReg(CONFIG, 0U);
    nrf24_WriteReg(EN_AA, 0U);
    nrf24_WriteReg(EN_RXADDR, 0U);
    nrf24_WriteReg(SETUP_AW, 0x03U);
    nrf24_WriteReg(SETUP_RETR, 0U);
    nrf24_WriteReg(RF_CH, 0U);
    nrf24_WriteReg(RF_SETUP, 0x0EU);
    CE_Enable();
}

void NRF24_TxMode(uint8_t *Address, uint8_t channel)
{
    CE_Disable();
    nrf24_WriteReg(RF_CH, channel);
    nrf24_WriteRegMulti(TX_ADDR, Address, 5);

    uint8_t config = nrf24_ReadReg(CONFIG);
    config = (uint8_t)((config & 0xF2U));
    nrf24_WriteReg(CONFIG, config);
    CE_Enable();
}

uint8_t NRF24_Transmit(uint8_t *data)
{
    uint8_t cmdtosend;

    CS_Select();
    cmdtosend = W_TX_PAYLOAD;
    (void)HAL_SPI_Transmit(NRF24_SPI, &cmdtosend, 1U, 100U);
    (void)HAL_SPI_Transmit(NRF24_SPI, data, 32U, 1000U);
    CS_UnSelect();

    HAL_Delay(1U); // MISRA C 2012 Rule 21.6

    uint8_t fifostatus = nrf24_ReadReg(FIFO_STATUS);

    if (((fifostatus & (1U << 4)) != 0U) && ((fifostatus & (1U << 3)) == 0U))
    {
        cmdtosend = FLUSH_TX;
        nrfsendCmd(cmdtosend);
        nrf24_reset(FIFO_STATUS);
        return 1U;
    }

    return 0U;
}

void NRF24_RxMode(uint8_t *Address, uint8_t channel)
{
    CE_Disable();
    nrf24_reset(STATUS);
    nrf24_WriteReg(RF_CH, channel);

    uint8_t en_rxaddr = nrf24_ReadReg(EN_RXADDR);
    en_rxaddr = (uint8_t)(en_rxaddr | (1U << 2));
    nrf24_WriteReg(EN_RXADDR, en_rxaddr);

    nrf24_WriteRegMulti(RX_ADDR_P1, Address, 5);
    nrf24_WriteReg(RX_ADDR_P2, 0xEEU);
    nrf24_WriteReg(RX_PW_P2, 32U);

    uint8_t config = nrf24_ReadReg(CONFIG);
    config = (uint8_t)(config | 0x03U);
    nrf24_WriteReg(CONFIG, config);

    CE_Enable();
}

uint8_t isDataAvailable(int pipenum)
{
    uint8_t status = nrf24_ReadReg(STATUS);
    if (((status & (1U << 6)) != 0U) && ((status & (uint8_t)(pipenum << 1)) != 0U))
    {
        nrf24_WriteReg(STATUS, (1U << 6));
        return 1U;
    }
    return 0U;
}

void NRF24_Receive(uint8_t *data)
{
    uint8_t cmdtosend;

    CS_Select();
    cmdtosend = R_RX_PAYLOAD;
    (void)HAL_SPI_Transmit(NRF24_SPI, &cmdtosend, 1U, 100U);
    (void)HAL_SPI_Receive(NRF24_SPI, data, 32U, 1000U);
    CS_UnSelect();

    HAL_Delay(1U);

    cmdtosend = FLUSH_RX;
    nrfsendCmd(cmdtosend);
}

void NRF24_ReadAll(uint8_t *data)
{
    for (int i = 0; i < 10; ++i)
    {
        data[i] = nrf24_ReadReg((uint8_t)i);
    }

    nrf24_ReadReg_Multi(RX_ADDR_P0, &data[10], 5);
    nrf24_ReadReg_Multi(RX_ADDR_P1, &data[15], 5);

    data[20] = nrf24_ReadReg(RX_ADDR_P2);
    data[21] = nrf24_ReadReg(RX_ADDR_P3);
    data[22] = nrf24_ReadReg(RX_ADDR_P4);
    data[23] = nrf24_ReadReg(RX_ADDR_P5);

    nrf24_ReadReg_Multi(RX_ADDR_P0, &data[24], 5);

    for (int i = 29; i < 38; ++i)
    {
        data[i] = nrf24_ReadReg((uint8_t)(i - 12));
    }
}
