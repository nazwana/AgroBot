/*
 * soil_moisture.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#include "soil_moisture.h"

void initSoilMoisture(soil_moisture_t *sensor, ADC_HandleTypeDef *hadc)
{
    uint8_t i = 0U;  // MISRA 13.1 - Initialize counter
    
    sensor->hadc = (ADC_HandleTypeDef*)hadc;  // MISRA 11.3 - Explicit cast
    sensor->moisture = 0U;
    sensor->moistureADC = 0U;
    
    // MISRA 14.4 - Simple for loop with counter
    for (i = 0U; i < MOISTURE_BUFFER_SIZE; i++) 
    {
        sensor->moistureBuffer[i] = 0U;  // MISRA 10.1 - Unsigned literal
    }
    
    // MISRA 17.2 - Ignore return value
    (void)HAL_ADC_Start(sensor->hadc);
}

void readMoisture(soil_moisture_t *sensor)
{
    uint32_t sum = 0UL;  // MISRA 13.1 - Initialize variable
    uint8_t i = 0U;      // MISRA 13.1 - Initialize counter
    
    // MISRA 14.4 - Simple for loop with counter
    for (i = 0U; i < MOISTURE_BUFFER_SIZE; i++) 
    {
        // MISRA 17.2 - Ignore return value
        (void)HAL_ADC_PollForConversion(sensor->hadc, 10U);  // MISRA 10.1 - Unsigned literal
        
        sensor->moistureBuffer[i] = (uint16_t)HAL_ADC_GetValue(sensor->hadc);  // MISRA 10.3 - Cast in range
        sum += (uint32_t)sensor->moistureBuffer[i];  // MISRA 10.1 - Prevent overflow
    }
    
    sensor->moistureADC = (uint16_t)(sum / MOISTURE_BUFFER_SIZE);  // MISRA 10.3 - Cast in range
    
    // MISRA 10.1/10.4 - Ensure unsigned arithmetic with proper casting
    if (sensor->moistureADC > DRY_VALUE) 
    {
        uint32_t range = (uint32_t)(ADC_MAX_VALUE - DRY_VALUE);
        uint32_t adjusted = (uint32_t)(sensor->moistureADC - DRY_VALUE);
        sensor->moisture = (uint16_t)(100U - ((adjusted * 100U) / range));
    }
    else
    {
        sensor->moisture = 100U;  // MISRA 10.1 - Max moisture if below dry threshold
    }
}