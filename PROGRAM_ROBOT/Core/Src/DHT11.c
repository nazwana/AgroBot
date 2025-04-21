#include "DHT11.h"
#include <string.h>  // For memset

// MISRA 10.1 - Timing constants as unsigned
#define DHT_START_DELAY_MS      18U
#define DHT_TIMEOUT_TICKS       500U
#define DHT_START_MIN_TICKS     75U
#define DHT_START_MAX_TICKS     85U
#define DHT_BIT0_MAX_TICKS      30U
#define DHT_BIT1_MIN_TICKS      60U
#define DHT_BIT1_MAX_TICKS      80U

static void safeDelay(uint32_t ms)  // MISRA 8.2 - Static for internal use
{
    uint32_t start = HAL_GetTick();
    while((HAL_GetTick() - start) < ms) { /* Wait */ }
}

void initDHT(dht11_t *dht, TIM_HandleTypeDef *htim, GPIO_TypeDef* port, uint16_t pin)
{
    // MISRA 11.3 - No implicit pointer conversion
    dht->htim = (TIM_HandleTypeDef*)htim;
    dht->port = (GPIO_TypeDef*)port;
    dht->pin = pin;
    dht->temperature = 0U;
    dht->humidity = 0U;
}

void setGPIOMode(dht11_t *dht, uint8_t pMode)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};  // MISRA 9.3 - Full initialization
    
    GPIO_InitStruct.Pin = dht->pin;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    
    // MISRA 14.3 - Single statement per branch
    if (pMode == OUTPUT) {
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    } 
    else {  // Default to input if not output
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    }
    
    // MISRA 17.2 - Ignore return value
    (void)HAL_GPIO_Init(dht->port, &GPIO_InitStruct);
}

uint8_t readDHT(dht11_t *dht)
{
    uint16_t mTime1 = 0U, mTime2 = 0U;  // MISRA 13.1 - Initialize
    uint8_t mData[40] = {0};            // MISRA 9.3 - Initialize array
    uint8_t humVal = 0U, tempVal = 0U, parityVal = 0U, genParity = 0U;
    uint8_t result = 0U;  // Return value
    uint8_t i = 0U;       // Loop counter
    
    // 1. Start signal
    setGPIOMode(dht, OUTPUT);
    HAL_GPIO_WritePin(dht->port, dht->pin, GPIO_PIN_RESET);
    safeDelay(DHT_START_DELAY_MS);
    
    // 2. Prepare for reading
    __disable_irq();
    (void)HAL_TIM_Base_Start(dht->htim);  // MISRA 17.2
    setGPIOMode(dht, INPUT);
    
    // 3. Wait for response low
    __HAL_TIM_SET_COUNTER(dht->htim, 0U);
    while (HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_SET) 
    {
        if ((uint16_t)__HAL_TIM_GET_COUNTER(dht->htim) > DHT_TIMEOUT_TICKS) 
        {
            goto cleanup;  // MISRA 15.5 - Single point of exit
        }
    }
    
    // 4. Wait for response high
    __HAL_TIM_SET_COUNTER(dht->htim, 0U);
    while (HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_RESET) 
    {
        if ((uint16_t)__HAL_TIM_GET_COUNTER(dht->htim) > DHT_TIMEOUT_TICKS) 
        {
            goto cleanup;
        }
    }
    
    // 5. Measure start pulses
    mTime1 = (uint16_t)__HAL_TIM_GET_COUNTER(dht->htim);
    __HAL_TIM_SET_COUNTER(dht->htim, 0U);
    while (HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_SET) 
    {
        if ((uint16_t)__HAL_TIM_GET_COUNTER(dht->htim) > DHT_TIMEOUT_TICKS) 
        {
            goto cleanup;
        }
    }
    mTime2 = (uint16_t)__HAL_TIM_GET_COUNTER(dht->htim);
    
    // 6. Validate start pulses
    if ((mTime1 < DHT_START_MIN_TICKS) || (mTime1 > DHT_START_MAX_TICKS) ||
        (mTime2 < DHT_START_MIN_TICKS) || (mTime2 > DHT_START_MAX_TICKS)) 
    {
        goto cleanup;
    }
    
    // 7. Read 40 bits of data
    for (i = 0U; i < 40U; i++) 
    {
        __HAL_TIM_SET_COUNTER(dht->htim, 0U);
        while (HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_RESET) 
        {
            if ((uint16_t)__HAL_TIM_GET_COUNTER(dht->htim) > DHT_TIMEOUT_TICKS) 
            {
                goto cleanup;
            }
        }
        
        __HAL_TIM_SET_COUNTER(dht->htim, 0U);
        while (HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_SET) 
        {
            if ((uint16_t)__HAL_TIM_GET_COUNTER(dht->htim) > DHT_TIMEOUT_TICKS) 
            {
                goto cleanup;
            }
        }
        
        mTime1 = (uint16_t)__HAL_TIM_GET_COUNTER(dht->htim);
        mData[i] = ((mTime1 > DHT_BIT1_MIN_TICKS) && (mTime1 < DHT_BIT1_MAX_TICKS)) ? 1U : 0U;
    }
    
    // 8. Process data
    for (i = 0U; i < 8U; i++) 
    {
        humVal = (humVal << 1U) | mData[i];
    }
    
    for (i = 16U; i < 24U; i++) 
    {
        tempVal = (tempVal << 1U) | mData[i];
    }
    
    for (i = 32U; i < 40U; i++) 
    {
        parityVal = (parityVal << 1U) | mData[i];
    }
    
    // 9. Validate checksum
    genParity = humVal + tempVal;
    if (parityVal == genParity) 
    {
        dht->temperature = tempVal;
        dht->humidity = humVal;
        result = 1U;
    }
    
cleanup:
    (void)HAL_TIM_Base_Stop(dht->htim);  // MISRA 17.2
    __enable_irq();
    return result;
}