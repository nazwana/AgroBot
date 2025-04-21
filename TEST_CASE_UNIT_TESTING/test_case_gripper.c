/*
 * test_case_gripper.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

 #include <stdio.h>
 #include <stdint.h>
 #include <stdbool.h>
 
 typedef struct {
     bool is_gripped;  // MISRA 8.1 - All declarations visible
 } gripper_t;
 
 void initGripper(gripper_t *gripper)
 {
     // MISRA 10.1 - Boolean initialization
     gripper->is_gripped = false;
     
     // MISRA 17.2 - Ignore return value
     (void)printf("Gripper initialized in released state\n");
 }
 
 void grip(gripper_t *gripper)
 {
     // MISRA 10.1 - Boolean assignment
     gripper->is_gripped = true;
     
     // MISRA 17.2 - Ignore return value
     (void)printf("Gripper CLOSED (gripping)\n");
 }
 
 void release(gripper_t *gripper)
 {
     // MISRA 10.1 - Boolean assignment
     gripper->is_gripped = false;
     
     // MISRA 17.2 - Ignore return value
     (void)printf("Gripper OPEN (released)\n");
 }
 
 void printGripperState(const gripper_t *gripper)
 {
     // MISRA 13.5 - Single assignment per statement
     const char *state = gripper->is_gripped ? "GRIPPING" : "RELEASED";
     
     // MISRA 17.2 - Ignore return value
     (void)printf("Current state: %s\n", state);
 }
 
 int main(void)
 {
     gripper_t my_gripper;  // MISRA 8.1 - All declarations visible
     int choice = 0;        // MISRA 8.1 - All declarations visible
     
     // MISRA 17.2 - Ignore return value
     (void)printf("=== GRIPPER TEST PROGRAM ===\n");
     initGripper(&my_gripper);
     
     while (true)  // MISRA 14.4 - Boolean controlled loop
     {
         // MISRA 17.2 - Ignore return values
         (void)printf("\nOptions:\n");
         (void)printf("1 - Grip\n");
         (void)printf("2 - Release\n");
         (void)printf("3 - Check State\n");
         (void)printf("0 - Exit\n");
         (void)printf("Select: ");
         (void)scanf("%d", &choice);
         
         if (choice == 0) {
             break;  // MISRA 15.4 - Single break statement
         }
         
         // MISRA 16.1 - Switch with at least one case
         switch(choice) {
             case 1:
                 grip(&my_gripper);
                 break;  // MISRA 15.2 - One break per case
             case 2:
                 release(&my_gripper);
                 break;
             case 3:
                 printGripperState(&my_gripper);
                 break;
             default:
                 // MISRA 17.2 - Ignore return value
                 (void)printf("Invalid input! Use 0-3\n");
                 break;  // MISRA 16.3 - Default case has break
         }
     }
     
     // MISRA 17.2 - Ignore return value
     (void)printf("Test completed.\n");
     return 0;
 }