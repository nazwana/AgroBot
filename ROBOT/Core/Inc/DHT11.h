#ifndef DHT11_H_
#define DHT11_H_

#include "main.h"

#define OUTPUT 1
#define INPUT 0

struct _dht11_t {
    GPIO_TypeDef* port;
    uint16_t pin;
    TIM_HandleTypeDef *htim;
    uint8_t temperature;
    uint8_t humidty;
};
typedef struct _dht11_t dht11_t;

void initDHT(dht11_t *dht, TIM_HandleTypeDef *htim, GPIO_TypeDef* port, uint16_t pin);
void setGPIOMode(dht11_t *dht, uint8_t pMode);
uint8_t readDHT(dht11_t *dht);

#endif /* DHT11_H_ */
