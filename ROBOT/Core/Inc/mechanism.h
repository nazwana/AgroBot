/*
 * mechanism.h
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#ifndef MECHANISM_H_
#define MECHANISM_H_

#include "motor.h"

extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;
extern TIM_HandleTypeDef htim12;

void initAllMotors();
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stopMotors();

#endif /* MECHANISM_H_ */
