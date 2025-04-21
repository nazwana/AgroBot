/*
 * test_case_mechanism.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

 #include <stdio.h>
 #include <stdint.h>
 #include <string.h>
 
 #define FORWARD  1U  // MISRA 10.1 - Unsigned literal
 #define BACKWARD 0U  // MISRA 10.1 - Unsigned literal
 
 typedef struct {
     uint8_t direction;  // MISRA 8.1 - All declarations visible
     uint16_t speed;     // MISRA 8.1 - All declarations visible
 } motor_t;
 
 // MISRA 8.9 - Objects with static storage duration should be defined
 motor_t motorFL;  // Front Left
 motor_t motorFR;  // Front Right
 motor_t motorBL;  // Back Left
 motor_t motorBR;  // Back Right
 
 void setSpeedMotor(motor_t *motor, int32_t speed, int32_t direction)  // MISRA 8.2 - Function declaration
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
 }
 
 void moveForward(void)  // MISRA 8.2
 {
     setSpeedMotor(&motorFL, 999, FORWARD);
     setSpeedMotor(&motorFR, 999, FORWARD);
     setSpeedMotor(&motorBL, 999, FORWARD);
     setSpeedMotor(&motorBR, 999, FORWARD);
 }
 
 void moveBackward(void)  // MISRA 8.2
 {
     setSpeedMotor(&motorFL, 999, BACKWARD);
     setSpeedMotor(&motorFR, 999, BACKWARD);
     setSpeedMotor(&motorBL, 999, BACKWARD);
     setSpeedMotor(&motorBR, 999, BACKWARD);
 }
 
 void turnLeft(void)  // MISRA 8.2
 {
     setSpeedMotor(&motorFL, 999, BACKWARD);
     setSpeedMotor(&motorFR, 999, FORWARD);
     setSpeedMotor(&motorBL, 999, BACKWARD);
     setSpeedMotor(&motorBR, 999, FORWARD);
 }
 
 void turnRight(void)  // MISRA 8.2
 {
     setSpeedMotor(&motorFL, 999, FORWARD);
     setSpeedMotor(&motorFR, 999, BACKWARD);
     setSpeedMotor(&motorBL, 999, FORWARD);
     setSpeedMotor(&motorBR, 999, BACKWARD);
 }
 
 void stopMotors(void)  // MISRA 8.2
 {
     setSpeedMotor(&motorFL, 0, FORWARD);
     setSpeedMotor(&motorFR, 0, FORWARD);
     setSpeedMotor(&motorBL, 0, FORWARD);
     setSpeedMotor(&motorBR, 0, FORWARD);
 }
 
 void printMotorState(const char* label, const motor_t* motor)  // MISRA 8.2
 {
     const char *dir_str = (motor->direction == FORWARD) ? "FORWARD" : "BACKWARD";  // MISRA 13.5 - Single assignment
     (void)printf("%s - Speed: %u | Direction: %s\n", label, motor->speed, dir_str);  // MISRA 17.2 - Ignore return
 }
 
 void printAllMotors(void)  // MISRA 8.2
 {
     printMotorState("MotorFL", &motorFL);
     printMotorState("MotorFR", &motorFR);
     printMotorState("MotorBL", &motorBL);
     printMotorState("MotorBR", &motorBR);
 }
 
 int main(void)  // MISRA 8.2
 {
     char command[16];  // MISRA 8.1 - All declarations visible
 
     (void)printf("=== TEST CASE MECHANISM ===\n");  // MISRA 17.2 - Ignore return
     (void)printf("Commands: Forward, Backward, Left, Right, Stop\n");  // MISRA 17.2 - Ignore return
 
     while (1) {
         (void)printf("\nInput Command: ");  // MISRA 17.2 - Ignore return
         (void)scanf("%15s", command);  // MISRA 17.2 - Ignore return
 
         // MISRA 14.3 - Single statement per branch
         if (strcmp(command, "Forward") == 0) {
             moveForward();
         } else if (strcmp(command, "Backward") == 0) {
             moveBackward();
         } else if (strcmp(command, "Left") == 0) {
             turnLeft();
         } else if (strcmp(command, "Right") == 0) {
             turnRight();
         } else if (strcmp(command, "Stop") == 0) {
             stopMotors();
         } else {
             (void)printf("Unknown command.\n");  // MISRA 17.2 - Ignore return
             continue;
         }
 
         printAllMotors();
     }
 
     return 0;
 }