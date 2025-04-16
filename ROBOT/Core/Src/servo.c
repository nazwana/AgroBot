/*
 * servo.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#include "servo.h"

void initServo(servo_t *servo, TIM_HandleTypeDef *htim, uint32_t channel) {
    servo->htim = htim;
    servo->channel = channel;
    servo->angle = 0;

    HAL_TIM_PWM_Start(servo->htim, servo->channel);
}

void setAngleServo(servo_t *servo, int angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    servo->angle = angle;

    int ccr_value = 50 + ((angle * 200) / 180);
    __HAL_TIM_SET_COMPARE(servo->htim, servo->channel, ccr_value);
}