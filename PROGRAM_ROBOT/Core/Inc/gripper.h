/*
 * gripper.h
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#ifndef GRIPPER_H_
#define GRIPPER_H_

#include "servo.h"

typedef struct {
    servo_t servo;  // MISRA 8.4 - Properly declared type
} gripper_t;

void initGripper(gripper_t *gripper, TIM_HandleTypeDef *htim, uint32_t channel);  // MISRA 8.4
void grip(gripper_t *gripper);  // MISRA 8.4
void release(gripper_t *gripper);  // MISRA 8.4

#endif /* GRIPPER_H_ */