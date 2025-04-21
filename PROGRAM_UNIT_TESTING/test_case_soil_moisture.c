/*
 * test_soil_moisture.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

 #include <stdio.h>
 #include <stdint.h>
 #include <stdlib.h>
 #include <time.h>
 #include <stdbool.h>  // Added for bool type
 
 #define MOISTURE_BUFFER_SIZE 10U  // MISRA 10.1 - Unsigned literal
 #define DRY_VALUE 1200U           // MISRA 10.1 - Unsigned literal
 #define WET_VALUE 4095U           // MISRA 10.1 - Unsigned literal
 
 typedef struct {
     void* hadc;                   // MISRA 8.1 - All declarations visible
     uint16_t moisture;            // MISRA 8.1
     uint16_t moistureADC;         // MISRA 8.1
     uint16_t moistureBuffer[MOISTURE_BUFFER_SIZE];  // MISRA 8.1
 } soil_moisture_t;
 
 uint32_t mock_ADC_value = 0U;     // MISRA 13.1 - Initialize variable
 
 uint32_t HAL_ADC_GetValue(void* hadc)  // MISRA 8.2 - Function declaration
 {
     // MISRA 10.1 - Ensure unsigned arithmetic
     return mock_ADC_value + (uint32_t)(rand() % 200U) - 100U;
 }
 
 void HAL_ADC_Start(void* hadc)    // MISRA 8.2
 {
     // MISRA 17.2 - Ignore return value
     (void)printf("ADC Initialized\n");
 }
 
 void HAL_ADC_PollForConversion(void* hadc, uint32_t timeout)  // MISRA 8.2
 {
     // MISRA 17.2 - Ignore return value
     (void)printf("Reading ADC...\n");
 }
 
 void initSoilMoisture(soil_moisture_t *sensor, void *hadc)  // MISRA 8.2
 {
     uint8_t i = 0U;  // MISRA 13.1 - Initialize counter
     
     sensor->hadc = hadc;  // MISRA 11.3 - No implicit pointer conversion
     sensor->moisture = 0U;
     sensor->moistureADC = 0U;
     
     // MISRA 14.4 - Simple for loop with counter
     for (i = 0U; i < MOISTURE_BUFFER_SIZE; i++) 
     {
         sensor->moistureBuffer[i] = 0U;  // MISRA 10.1 - Unsigned literal
     }
     
     HAL_ADC_Start(sensor->hadc);
 }
 
 void readMoisture(soil_moisture_t *sensor)  // MISRA 8.2
 {
     uint32_t sum = 0UL;  // MISRA 13.1 - Initialize variable
     uint8_t i = 0U;      // MISRA 13.1 - Initialize counter
     
     // MISRA 14.4 - Simple for loop with counter
     for (i = 0U; i < MOISTURE_BUFFER_SIZE; i++) 
     {
         // MISRA 17.2 - Ignore return value
         (void)HAL_ADC_PollForConversion(sensor->hadc, 10U);
         
         sensor->moistureBuffer[i] = (uint16_t)HAL_ADC_GetValue(sensor->hadc);  // MISRA 10.3 - Cast in range
         sum += (uint32_t)sensor->moistureBuffer[i];  // MISRA 10.1 - Prevent overflow
     }
     
     sensor->moistureADC = (uint16_t)(sum / MOISTURE_BUFFER_SIZE);  // MISRA 10.3 - Cast in range
     
     // MISRA 14.3 - Single statement per branch
     if (sensor->moistureADC < DRY_VALUE) 
     {
         sensor->moisture = 0U;  // MISRA 10.1 - Unsigned literal
     } 
     else if (sensor->moistureADC > WET_VALUE) 
     {
         sensor->moisture = 100U;  // MISRA 10.1 - Unsigned literal
     }
     else 
     {
         uint32_t range = WET_VALUE - DRY_VALUE;  // MISRA 10.1 - Unsigned arithmetic
         uint32_t adjusted = sensor->moistureADC - DRY_VALUE;  // MISRA 10.1
         sensor->moisture = (uint16_t)((adjusted * 100U) / range);  // MISRA 10.3 - Cast in range
     }
 }
 
 int main(void)  // MISRA 8.2
 {
     soil_moisture_t sensor;  // MISRA 8.1 - All declarations visible
     int input_adc = 0;       // MISRA 8.1
     
     // MISRA 17.2 - Ignore return value
     (void)srand((unsigned int)time(NULL));  // MISRA 10.3 - Cast in range
     
     // MISRA 17.2 - Ignore return value
     (void)printf("SOIL MOISTURE TEST (1200 = DRY, 4095 = WET)\n");
     initSoilMoisture(&sensor, NULL);
     
     for (;;)  // MISRA 14.4 - Alternative to while(true) that's valid in C
     {
         // MISRA 17.2 - Ignore return value
         (void)printf("\nEnter ADC Value (1200-4095, 0 = EXIT): ");
         (void)scanf("%d", &input_adc);
         
         if (input_adc == 0) 
         {
             break;  // MISRA 15.4 - Single break statement
         }
         
         if (input_adc < 1200 || input_adc > 4095) 
         {
             // MISRA 17.2 - Ignore return value
             (void)printf("Invalid input\n");
             continue;
         }
         
         mock_ADC_value = (uint32_t)input_adc;  // MISRA 10.3 - Cast in range
         readMoisture(&sensor);
         
         // MISRA 17.2 - Ignore return values
         (void)printf("ADC: %u\n", sensor.moistureADC);
         (void)printf("Moisture: %u%%\n", sensor.moisture);
         (void)printf("Readings: ");
         
         uint8_t i = 0U;  // MISRA 13.1 - Initialize counter
         for (i = 0U; i < MOISTURE_BUFFER_SIZE; i++)  // MISRA 14.4
         {
             (void)printf("%u ", sensor.moistureBuffer[i]);  // MISRA 17.2
         }
         (void)printf("\n");  // MISRA 17.2
     }
     
     // MISRA 17.2 - Ignore return value
     (void)printf("Test ended\n");
     return 0;
 }