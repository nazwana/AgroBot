#ifndef DHT11_H_
#define DHT11_H_

#include "main.h"

#define OUTPUT 1U  // MISRA 10.1 - Unsigned constants
#define INPUT  0U

typedef struct {
    GPIO_TypeDef* port;        // MISRA 8.4 - External linkage
    uint16_t pin;
    TIM_HandleTypeDef *htim;   // MISRA 8.4
    uint8_t temperature;
    uint8_t humidity;          // Fixed typo in member name
} dht11_t;

void initDHT(dht11_t *dht, TIM_HandleTypeDef *htim, GPIO_TypeDef* port, uint16_t pin);  // MISRA 8.4
void setGPIOMode(dht11_t *dht, uint8_t pMode);  // MISRA 8.4
uint8_t readDHT(dht11_t *dht);  // MISRA 8.4

#endif /* DHT11_H_ */