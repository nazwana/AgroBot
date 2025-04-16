/*
 * mechanism.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */
 
#include "mechanism.h"

motor_t motorFL; // Front Left
motor_t motorFR; // Front Right
motor_t motorBL; // Back Left
motor_t motorBR; // Back Right


void initAllMotors() {
    initMotor(&motorFL, &htim10, TIM_CHANNEL_1);
    initMotor(&motorFR, &htim11, TIM_CHANNEL_1);
    initMotor(&motorBL, &htim12, TIM_CHANNEL_1);
    initMotor(&motorBR, &htim12, TIM_CHANNEL_2);
}

void moveForward() {
    setSpeedMotor(&motorFL, 999, FORWARD);
    setSpeedMotor(&motorFR, 999, FORWARD);
    setSpeedMotor(&motorBL, 999, FORWARD);
    setSpeedMotor(&motorBR, 999, FORWARD);
}

void moveBackward() {
    setSpeedMotor(&motorFL, 999, BACKWARD);
    setSpeedMotor(&motorFR, 999, BACKWARD);
    setSpeedMotor(&motorBL, 999, BACKWARD);
    setSpeedMotor(&motorBR, 999, BACKWARD);
}

void turnLeft() {
    setSpeedMotor(&motorFL, 999, BACKWARD);
    setSpeedMotor(&motorFR, 999, FORWARD);
    setSpeedMotor(&motorBL, 999, BACKWARD);
    setSpeedMotor(&motorBR, 999, FORWARD);
}

void turnRight() {
    setSpeedMotor(&motorFL, 999, FORWARD);
    setSpeedMotor(&motorFR, 999, BACKWARD);
    setSpeedMotor(&motorBL, 999, FORWARD);
    setSpeedMotor(&motorBR, 999, BACKWARD);
}

void stopMotors() {
    setSpeedMotor(&motorFL, 0, FORWARD);
    setSpeedMotor(&motorFR, 0, FORWARD);
    setSpeedMotor(&motorBL, 0, FORWARD);
    setSpeedMotor(&motorBR, 0, FORWARD);
}
