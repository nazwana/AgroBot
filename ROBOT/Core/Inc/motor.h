/*
 * motor.h
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define FORWARD  1
#define BACKWARD 0

#include "main.h"

typedef struct {
	TIM_HandleTypeDef *htim;
    uint32_t channel;
    uint8_t direction;
    uint16_t speed;
} motor_t;

void initMotor(motor_t *motor, TIM_HandleTypeDef *htim, uint32_t channel);
void setSpeedMotor(motor_t *motor, int speed, int direction);

#endif /* MOTOR_H_ */
