/*
 * servo.h
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "main.h"

typedef struct {
    TIM_HandleTypeDef *htim;  // MISRA 8.4 - External linkage
    uint32_t channel;
    int16_t angle;  // MISRA 6.2 - Appropriate sized type
} servo_t;

void initServo(servo_t *servo, TIM_HandleTypeDef *htim, uint32_t channel);  // MISRA 8.4
void setAngleServo(servo_t *servo, int16_t angle);  // Fixed typo in function name

#endif // SERVO_H_