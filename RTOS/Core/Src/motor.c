/*
 * motor.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#include "motor.h"

void initMotor(motor_t *motor, TIM_HandleTypeDef *htim, uint32_t channel) 
{
    motor->htim = htim;  // MISRA 11.3 - Pointer assignment
    motor->channel = channel;
    motor->direction = FORWARD;  // MISRA 10.3 - Value in range
    motor->speed = 0U;  // MISRA 10.1 - Unsigned literal
    
    (void)HAL_TIM_PWM_Start(motor->htim, motor->channel);  // MISRA 17.2 - Ignore return
}

void setSpeedMotor(motor_t *motor, int32_t speed, int32_t direction) 
{
    uint16_t actual_speed = 0U;  // MISRA 13.1 - Initialized
    
    // MISRA 14.3 - Single statement per branch
    if (speed < 0) {
        actual_speed = 0U;
    } 
    else if (speed > 999) {
        actual_speed = 999U;  // MISRA 10.1 - Unsigned literal
    } 
    else {
        actual_speed = (uint16_t)speed;  // MISRA 10.3 - Cast in range
    }

    motor->direction = (direction == BACKWARD) ? BACKWARD : FORWARD;  // MISRA 13.5 - Single assignment
    motor->speed = actual_speed;
    
    __HAL_TIM_SET_COMPARE(motor->htim, motor->channel, actual_speed);  // MISRA 17.2 - Void return
}