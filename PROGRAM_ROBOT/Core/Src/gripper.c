/*
 * gripper.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#include "gripper.h"

void initGripper(gripper_t *gripper, TIM_HandleTypeDef *htim, uint32_t channel)
{
    // MISRA 11.3 - No implicit pointer conversion
    initServo(&gripper->servo, (TIM_HandleTypeDef*)htim, channel);
    
    // MISRA 17.2 - Ignore return value (release returns void but rule applies generally)
    (void)release(gripper);  // Initialize to released position
}

void grip(gripper_t *gripper)
{
    // MISRA 10.1 - Literal matches parameter type (setAngleServo expects int16_t)
    setAngleServo(&gripper->servo, (int16_t)180);  // MISRA 11.3 - Proper parameter passing
}

void release(gripper_t *gripper)
{
    setAngleServo(&gripper->servo, (int16_t)0);  // MISRA 10.1/11.3 - Type safety
}