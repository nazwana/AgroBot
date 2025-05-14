/*
 * soil_moisture.h
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#ifndef SOIL_MOISTURE_H_
#define SOIL_MOISTURE_H_

#include "main.h"

#define MOISTURE_BUFFER_SIZE 10U  // MISRA 10.1 - Unsigned constant
#define ADC_MAX_VALUE 4095U       // MISRA 10.1 - 12-bit ADC range
#define DRY_VALUE 1200U           // MISRA 10.1 - Calibration value

typedef struct {
    ADC_HandleTypeDef *hadc;      // MISRA 8.4 - External linkage
    uint16_t moisture;            // 0-100% moisture level
    uint16_t moistureADC;         // Raw ADC value
    uint16_t moistureBuffer[MOISTURE_BUFFER_SIZE];  // MISRA 8.12 - Array size as constant
} soil_moisture_t;

void initSoilMoisture(soil_moisture_t *sensor, ADC_HandleTypeDef *hadc);  // MISRA 8.4
void readMoisture(soil_moisture_t *sensor);  // MISRA 8.4

#endif /* SOIL_MOISTURE_H_ */