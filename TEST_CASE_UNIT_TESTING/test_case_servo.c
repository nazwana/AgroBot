/*
 * test_case_servo.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

 #include <stdio.h>
 #include <stdint.h>
 #include <stdbool.h>
 
 typedef struct {
     int16_t angle;  // MISRA 8.1 - All declarations visible
 } servo_t;
 
 void setAngleServo(servo_t *servo, int16_t angle)  // MISRA 8.2 - Function declaration
 {
     int16_t boundedAngle = angle;  // MISRA 13.1 - Initialize variable
     
     // MISRA 14.3 - Single statement per branch
     if (angle < 0) {
         boundedAngle = 0;
     }
     else if (angle > 180) {
         boundedAngle = 180;
     }
     else {
         boundedAngle = angle;
     }
 
     servo->angle = boundedAngle;  // MISRA 13.5 - Single assignment
 
     // MISRA 10.1 - Explicit conversion in calculation
     uint32_t ccr_value = 50U + ((uint32_t)boundedAngle * 200U) / 180U;
     
     (void)printf("Calculated PWM value: %lu\n", ccr_value);  // MISRA 17.2 - Ignore return
 }
 
 void printServoState(const servo_t *servo)  // MISRA 8.2
 {
     (void)printf("Current Angle: %d°\n", servo->angle);  // MISRA 17.2 - Ignore return
     
     // MISRA 14.3 - Single statement per branch
     if (servo->angle == 0) {
         (void)printf("Position: Fully Closed\n");  // MISRA 17.2 - Ignore return
     }
     else if (servo->angle == 180) {
         (void)printf("Position: Fully Open\n");  // MISRA 17.2 - Ignore return
     }
     else {
         // MISRA 10.1 - Unsigned calculation
         uint8_t percent = (uint8_t)((servo->angle * 100U) / 180U);
         (void)printf("Position: %u%% Open\n", percent);  // MISRA 17.2 - Ignore return
     }
 }
 
 int main(void)  // MISRA 8.2
 {
     servo_t my_servo = {0};  // MISRA 10.1 - Implicit conversion allowed (0 is universal)
     int input_angle = 0;  // MISRA 8.1 - All declarations visible
     
     (void)printf("=== Servo Angle Tester ===\n");  // MISRA 17.2 - Ignore return
     (void)printf("Enter Angles (0-180), or -1 to quit:\n");  // MISRA 17.2 - Ignore return
     
     while (true)  // MISRA 14.4 - Boolean controlled loop
     {
         (void)printf("\nEnter Angle: ");  // MISRA 17.2 - Ignore return
         (void)scanf("%d", &input_angle);  // MISRA 17.2 - Ignore return
         
         // MISRA 14.3 - Single statement per branch
         if (input_angle == -1) {
             break;  // MISRA 15.4 - Single break statement
         }
         
         setAngleServo(&my_servo, input_angle);
         printServoState(&my_servo);
     }
     
     (void)printf("Testing complete.\n");  // MISRA 17.2 - Ignore return
     return 0;
 }