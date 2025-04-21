/*
 * test_case_motor.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

 #include <stdio.h>
 #include <stdint.h>
 
 #define FORWARD  1U  // MISRA 10.1 - Unsigned literal
 #define BACKWARD 0U  // MISRA 10.1 - Unsigned literal
 
 typedef struct {
     uint8_t direction;  // MISRA 8.1 - All declarations visible
     uint16_t speed;     // MISRA 8.1 - All declarations visible
 } motor_t;
 
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
 }
 
 void printMotor(const motor_t *motor) 
 {
     const char *dir_str = (motor->direction == FORWARD) ? "FORWARD" : "BACKWARD";  // MISRA 13.5 - Single assignment
     (void)printf("Motor - Speed: %u | Direction: %s\n", motor->speed, dir_str);  // MISRA 17.2 - Ignore return
 }
 
 int main(void) 
 {
     motor_t motor = { FORWARD, 0U };  // MISRA 10.3 - Value in range
     int32_t speed = 0;
     int32_t direction = FORWARD;
 
     (void)printf("=== TEST CASE MOTOR ===\n");  // MISRA 17.2 - Ignore return
 
     while (1) 
     {
         (void)printf("\nInput speed (0-999): ");  // MISRA 17.2 - Ignore return
         (void)scanf("%d", &speed);  // MISRA 17.2 - Ignore return
 
         (void)printf("Input direction (1 = FORWARD, 0 = BACKWARD): ");  // MISRA 17.2 - Ignore return
         (void)scanf("%d", &direction);  // MISRA 17.2 - Ignore return
 
         setSpeedMotor(&motor, speed, direction);
         printMotor(&motor);
     }
 
     return 0;
 }