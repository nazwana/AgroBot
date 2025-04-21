/*
 * servo.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#include "servo.h"

void initServo(servo_t *servo, TIM_HandleTypeDef *htim, uint32_t channel)
{
    // MISRA 11.3 - No implicit pointer conversion
    servo->htim = (TIM_HandleTypeDef*)htim;
    
    servo->channel = channel;
    servo->angle = 0;  // MISRA 10.1 - Implicit conversion allowed (0 is universal)
    
    // MISRA 17.2 - Ignore return value
    (void)HAL_TIM_PWM_Start(servo->htim, servo->channel);
}

void setAngleServo(servo_t *servo, int16_t angle)
{
    int16_t boundedAngle = angle;  // MISRA 13.1 - Initialize variable
    
    // MISRA 14.3 - Single statement per branch
    if (angle < 0) {
        boundedAngle = 0;
    }
    else if (angle > 180) {
        boundedAngle = 180;
    }
    
    servo->angle = boundedAngle;
    
    // MISRA 10.1 - Explicit conversion in calculation
    uint32_t ccr_value = 50U + ((uint32_t)boundedAngle * 200U) / 180U;
    
    // MISRA 17.2 - Void return from macro
    __HAL_TIM_SET_COMPARE(servo->htim, servo->channel, (uint32_t)ccr_value);
}