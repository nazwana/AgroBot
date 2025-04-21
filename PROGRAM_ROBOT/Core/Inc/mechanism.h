/*
 * mechanism.h
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#ifndef MECHANISM_H_
#define MECHANISM_H_

#include "motor.h"

// MISRA 8.12 - External objects must be declared in headers
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;
extern TIM_HandleTypeDef htim12;

// MISRA 8.4 - External functions must be declared
void initAllMotors(void);
void moveForward(void);
void moveBackward(void);
void turnLeft(void);
void turnRight(void);
void stopMotors(void);

#endif // MECHANISM_H_