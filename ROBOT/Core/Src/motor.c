/*
 * motor.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#include "motor.h"

void initMotor(motor_t *motor, TIM_HandleTypeDef *htim, uint32_t channel) {
    motor->htim = htim;
    motor->channel = channel;
    motor->direction = FORWARD;
    motor->speed = 0;

    HAL_TIM_PWM_Start(motor->htim, motor->channel);
}

void setSpeedMotor(motor_t *motor, int speed, int direction) {
    if (speed < 0) speed = 0;
    if (speed > 999) speed = 999;

    if (direction == BACKWARD) {
        motor->direction = BACKWARD; 
    } else {
        motor->direction = FORWARD;  
    }

    motor->speed = speed;
		
    __HAL_TIM_SET_COMPARE(motor->htim, motor->channel, speed);
}
