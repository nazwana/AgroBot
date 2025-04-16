#include "DHT11.h"

void initDHT(dht11_t *dht, TIM_HandleTypeDef *htim, GPIO_TypeDef* port, uint16_t pin) {
    dht->htim = htim;
    dht->port = port;
    dht->pin = pin;
}

void setGPIOMode(dht11_t *dht, uint8_t pMode) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = dht->pin;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    if (pMode == OUTPUT) {
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    } else if (pMode == INPUT) {
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    }

    HAL_GPIO_Init(dht->port, &GPIO_InitStruct);
}

uint8_t readDHT(dht11_t *dht) {
    uint16_t mTime1 = 0, mTime2 = 0, mBit = 0;
    uint8_t humVal = 0, tempVal = 0, parityVal = 0, genParity = 0;
    uint8_t mData[40];

    setGPIOMode(dht, OUTPUT);
    HAL_GPIO_WritePin(dht->port, dht->pin, GPIO_PIN_RESET);
    HAL_Delay(18);

    __disable_irq();
    HAL_TIM_Base_Start(dht->htim);
    setGPIOMode(dht, INPUT);

    __HAL_TIM_SET_COUNTER(dht->htim, 0);
    while (HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_SET) {
        if ((uint16_t)__HAL_TIM_GET_COUNTER(dht->htim) > 500) {
            __enable_irq();
            return 0;
        }
    }

    __HAL_TIM_SET_COUNTER(dht->htim, 0);
    while (HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_RESET) {
        if ((uint16_t)__HAL_TIM_GET_COUNTER(dht->htim) > 500) {
            __enable_irq();
            return 0;
        }
    }

    mTime1 = (uint16_t)__HAL_TIM_GET_COUNTER(dht->htim);
    __HAL_TIM_SET_COUNTER(dht->htim, 0);
    while (HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_SET) {
        if ((uint16_t)__HAL_TIM_GET_COUNTER(dht->htim) > 500) {
            __enable_irq();
            return 0;
        }
    }
    mTime2 = (uint16_t)__HAL_TIM_GET_COUNTER(dht->htim);

    if (mTime1 < 75 && mTime1 > 85 && mTime2 < 75 && mTime2 > 85) {
        __enable_irq();
        return 0;
    }

    for (int j = 0; j < 40; j++) {
        __HAL_TIM_SET_COUNTER(dht->htim, 0);
        while (HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_RESET) {
            if ((uint16_t)__HAL_TIM_GET_COUNTER(dht->htim) > 500) {
                __enable_irq();
                return 0;
            }
        }

        __HAL_TIM_SET_COUNTER(dht->htim, 0);
        while (HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_SET) {
            if ((uint16_t)__HAL_TIM_GET_COUNTER(dht->htim) > 500) {
                __enable_irq();
                return 0;
            }
        }

        mTime1 = (uint16_t)__HAL_TIM_GET_COUNTER(dht->htim);
        mBit = (mTime1 > 20 && mTime1 < 30) ? 0 : (mTime1 > 60 && mTime1 < 80) ? 1 : 0;
        mData[j] = mBit;
    }

    HAL_TIM_Base_Stop(dht->htim);
    __enable_irq();

    for (int i = 0; i < 8; i++) {
        humVal += mData[i];
        humVal = humVal << 1;
    }

    for (int i = 16; i < 24; i++) {
        tempVal += mData[i];
        tempVal = tempVal << 1;
    }

    for (int i = 32; i < 40; i++) {
        parityVal += mData[i];
        parityVal = parityVal << 1;
    }

    parityVal = parityVal >> 1;
    humVal = humVal >> 1;
    tempVal = tempVal >> 1;
    genParity = humVal + tempVal;

    dht->temperature = tempVal;
    dht->humidty = humVal;

    return 1;
}
