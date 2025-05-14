/*
 * motor.h
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "main.h"

#define FORWARD  1U  // MISRA 10.1 - Unsigned literal
#define BACKWARD 0U

typedef struct {
    TIM_HandleTypeDef *htim;  // MISRA 8.4 - External linkage
    uint32_t channel;
    uint8_t direction;
    uint16_t speed;
} motor_t;

void initMotor(motor_t *motor, TIM_HandleTypeDef *htim, uint32_t channel);  // MISRA 8.4
void setSpeedMotor(motor_t *motor, int32_t speed, int32_t direction);  // MISRA 8.4

#endif // MOTOR_H_