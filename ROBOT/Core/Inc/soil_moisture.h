#ifndef SOIL_MOISTURE_H_
#define SOIL_MOISTURE_H_

#include "main.h"

typedef struct {
    ADC_HandleTypeDef *hadc;
    uint16_t moisture;
    uint16_t moistureADC;
    uint16_t moistureBuffer[10];
} soil_moisture_t;

void initSoilMoisture(soil_moisture_t *sensor, ADC_HandleTypeDef *hadc);
void readMoisture(soil_moisture_t *sensor);

#endif /* SOIL_MOISTURE_H_ */
