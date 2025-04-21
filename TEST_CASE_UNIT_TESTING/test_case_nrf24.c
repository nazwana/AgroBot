#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* === MOCK HAL BEGIN === */
#define GPIO_PIN_SET   1U     // MISRA 5.1 - Unique identifier
#define GPIO_PIN_RESET 0U     // MISRA 5.1 - Unique identifier

typedef uint32_t GPIO_PinState;  // MISRA 6.1 - Typedef for primitive type

void HAL_GPIO_WritePin(void* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)  // MISRA 8.2 - Function declaration
{
    (void)GPIOx;  // MISRA 17.2 - Unused parameter
    printf("GPIO Pin %u -> %s\n", GPIO_Pin, (PinState == GPIO_PIN_SET) ? "SET" : "RESET");  // MISRA 17.2 - printf allowed in test code
}

void HAL_SPI_Transmit(void* hspi, uint8_t* pData, uint16_t Size, uint32_t Timeout)  // MISRA 8.2
{
    uint16_t i;  // MISRA 8.9 - Declare at block scope
    (void)hspi;  // MISRA 17.2
    (void)Timeout;  // MISRA 17.2
    printf("[SPI TX] %u bytes:", Size);  // MISRA 17.2
    for (i = 0U; i < Size; ++i) {  // MISRA 10.4 - Unsigned loop counter
        printf(" %02X", pData[i]);  // MISRA 17.2
    }
    printf("\n");  // MISRA 17.2
}

void HAL_SPI_Receive(void* hspi, uint8_t* pData, uint16_t Size, uint32_t Timeout)  // MISRA 8.2
{
    uint16_t i;  // MISRA 8.9
    (void)hspi;  // MISRA 17.2
    (void)Timeout;  // MISRA 17.2
    for (i = 0U; i < Size; ++i) {  // MISRA 10.4
        pData[i] = (uint8_t)(0xA0U + i);  // MISRA 10.1 - Explicit cast
    }
    printf("[SPI RX] %u bytes received\n", Size);  // MISRA 17.2
}

void HAL_Delay(uint32_t Delay)  // MISRA 8.2
{
    printf("Delay: %lu ms\n", Delay);  // MISRA 17.2
}
/* === MOCK HAL END === */

/* === NRF24 FUNCTION STUBS BEGIN === */
void NRF24_Init(void)  // MISRA 8.2
{
    printf("[NRF24] Init\n");  // MISRA 17.2
}

void NRF24_TxMode(uint8_t* addr, uint8_t channel)  // MISRA 8.2
{
    uint8_t i;  // MISRA 8.9
    printf("[NRF24] TxMode - Channel %u, Addr:", channel);  // MISRA 17.2
    for (i = 0U; i < 5U; ++i) {  // MISRA 10.4
        printf(" %02X", addr[i]);  // MISRA 17.2
    }
    printf("\n");  // MISRA 17.2
}

uint8_t NRF24_Transmit(uint8_t* data)  // MISRA 8.2
{
    uint8_t i;  // MISRA 8.9
    printf("[NRF24] Transmit:");  // MISRA 17.2
    for (i = 0U; i < 32U; ++i) {  // MISRA 10.4
        printf(" %02X", data[i]);  // MISRA 17.2
    }
    printf("\n");  // MISRA 17.2
    return 1U;  // MISRA 10.1 - Explicit unsigned return
}

void NRF24_RxMode(uint8_t* addr, uint8_t channel)  // MISRA 8.2
{
    uint8_t i;  // MISRA 8.9
    printf("[NRF24] RxMode - Channel %u, Addr:", channel);  // MISRA 17.2
    for (i = 0U; i < 5U; ++i) {  // MISRA 10.4
        printf(" %02X", addr[i]);  // MISRA 17.2
    }
    printf("\n");  // MISRA 17.2
}

uint8_t isDataAvailable(uint8_t pipe)  // MISRA 8.2
{
    printf("[NRF24] Data Available? Pipe %u\n", pipe);  // MISRA 17.2
    return 1U;  // MISRA 10.1
}

void NRF24_Receive(uint8_t* data)  // MISRA 8.2
{
    uint8_t i;  // MISRA 8.9
    printf("[NRF24] Receive:");  // MISRA 17.2
    for (i = 0U; i < 32U; ++i) {  // MISRA 10.4
        data[i] = (uint8_t)(0x55U + i);  // MISRA 10.1
        printf(" %02X", data[i]);  // MISRA 17.2
    }
    printf("\n");  // MISRA 17.2
}

void NRF24_ReadAll(uint8_t* output)  // MISRA 8.2
{
    uint8_t i;  // MISRA 8.9
    printf("[NRF24] ReadAll:\n");  // MISRA 17.2
    for (i = 0U; i < 38U; ++i) {  // MISRA 10.4
        output[i] = (uint8_t)(0x10U + i);  // MISRA 10.1
    }
}
/* === NRF24 FUNCTION STUBS END === */

int main(void)  // MISRA 8.2
{
    uint8_t i;  // MISRA 8.9
    uint8_t dummy_data[32U] = {0U};  // MISRA 9.2 - Initialize array
    uint8_t address[5U] = {0xE7U, 0xE7U, 0xE7U, 0xE7U, 0xE7U};  // MISRA 9.2
    uint8_t read_buf[38U] = {0U};  // MISRA 9.2

    printf("=== START NRF24 UNIT TEST ===\n");  // MISRA 17.2

    NRF24_Init();
    NRF24_TxMode(address, 76U);
    (void)NRF24_Transmit(dummy_data);  // MISRA 17.2 - Ignore return
    NRF24_RxMode(address, 76U);
    (void)isDataAvailable(2U);  // MISRA 17.2
    NRF24_Receive(dummy_data);
    NRF24_ReadAll(read_buf);

    for (i = 0U; i < 38U; ++i) {  // MISRA 10.4
        printf("Reg[%02u] = %02X\n", i, read_buf[i]);  // MISRA 17.2
    }

    printf("=== END NRF24 UNIT TEST ===\n");  // MISRA 17.2

    return 0;  // MISRA 15.1 - Exit point
}