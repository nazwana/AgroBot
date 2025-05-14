/*
 * mechanism.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#include "mechanism.h"

// MISRA 8.9 - Objects with static storage duration should be defined
motor_t motorFL; // Front Left  
motor_t motorFR; // Front Right
motor_t motorBL; // Back Left
motor_t motorBR; // Back Right

void initAllMotors(void)  // MISRA 8.2 - Function declaration
{
    // MISRA 11.3 - No implicit pointer conversion
    initMotor(&motorFL, (TIM_HandleTypeDef*)&htim10, TIM_CHANNEL_1);
    initMotor(&motorFR, (TIM_HandleTypeDef*)&htim11, TIM_CHANNEL_1);
    initMotor(&motorBL, (TIM_HandleTypeDef*)&htim12, TIM_CHANNEL_1);
    initMotor(&motorBR, (TIM_HandleTypeDef*)&htim12, TIM_CHANNEL_2);
}

void moveForward(void)  // MISRA 8.2
{
    // MISRA 10.1 - Use unsigned literal for unsigned parameter
    setSpeedMotor(&motorFL, 999U, FORWARD);
    setSpeedMotor(&motorFR, 999U, FORWARD);
    setSpeedMotor(&motorBL, 999U, FORWARD);
    setSpeedMotor(&motorBR, 999U, FORWARD);
}

void moveBackward(void)  // MISRA 8.2
{
    setSpeedMotor(&motorFL, 999U, BACKWARD);
    setSpeedMotor(&motorFR, 999U, BACKWARD);
    setSpeedMotor(&motorBL, 999U, BACKWARD);
    setSpeedMotor(&motorBR, 999U, BACKWARD);
}

void turnLeft(void)  // MISRA 8.2
{
    setSpeedMotor(&motorFL, 999U, BACKWARD);
    setSpeedMotor(&motorFR, 999U, FORWARD);
    setSpeedMotor(&motorBL, 999U, BACKWARD);
    setSpeedMotor(&motorBR, 999U, FORWARD);
}

void turnRight(void)  // MISRA 8.2
{
    setSpeedMotor(&motorFL, 999U, FORWARD);
    setSpeedMotor(&motorFR, 999U, BACKWARD);
    setSpeedMotor(&motorBL, 999U, FORWARD);
    setSpeedMotor(&motorBR, 999U, BACKWARD);
}

void stopMotors(void)  // MISRA 8.2
{
    setSpeedMotor(&motorFL, 0U, FORWARD);
    setSpeedMotor(&motorFR, 0U, FORWARD);
    setSpeedMotor(&motorBL, 0U, FORWARD);
    setSpeedMotor(&motorBR, 0U, FORWARD);
}