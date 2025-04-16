/*
 * soil_moisture.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */


#include "soil_moisture.h"

void initSoilMoisture(soil_moisture_t *sensor, ADC_HandleTypeDef *hadc) {
    sensor->hadc = hadc;
    sensor->moisture = 0;
    sensor->moistureADC = 0;
    for (int i = 0; i < 10; i++) {
        sensor->moistureBuffer[i] = 0;
    }
    HAL_ADC_Start(sensor->hadc);
}

void readMoisture(soil_moisture_t *sensor) {
    uint32_t sum = 0;
    for (int i = 0; i < 10; i++) {
    	HAL_ADC_PollForConversion(sensor->hadc, 10);
        sensor->moistureBuffer[i] = HAL_ADC_GetValue(sensor->hadc);
        sum += sensor->moistureBuffer[i];
    }
    sensor->moistureADC = (uint16_t)(sum / 10);
    sensor->moisture = 100 - ((sensor->moistureADC - 1200) * 100) / (4096 - 1200);
}
