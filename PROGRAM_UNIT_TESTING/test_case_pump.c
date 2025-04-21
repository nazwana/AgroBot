/*
 * test_case_pump.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

 #include <stdio.h>
 #include <stdint.h>
 #include <stdbool.h>
 
 typedef enum {
     PUMP_OFF = 0U,  // MISRA 10.1 - Unsigned literal
     PUMP_ON = 1U    // MISRA 10.1 - Unsigned literal
 } PumpState;  // MISRA 8.1 - All declarations visible
 
 void setPump(PumpState state)  // MISRA 8.2 - Function declaration
 {
     // MISRA 14.3 - Single statement per branch
     if (state == PUMP_ON) {
         (void)printf("Pump: ON\n");  // MISRA 17.2 - Ignore return
     } else {
         (void)printf("Pump: OFF\n");  // MISRA 17.2 - Ignore return
     }
 }
 
 int main(void)  // MISRA 8.2
 {
     int input = 0;  // MISRA 8.1 - All declarations visible
     
     (void)printf("=== PUMP TEST PROGRAM ===\n");  // MISRA 17.2 - Ignore return
     (void)printf("1 - Turn Pump ON\n");  // MISRA 17.2 - Ignore return
     (void)printf("0 - Turn Pump OFF\n");  // MISRA 17.2 - Ignore return
     (void)printf("-1 - Exit\n");  // MISRA 17.2 - Ignore return
     
     while (true)  // MISRA 14.4 - Boolean controlled loop
     {
         (void)printf("\nEnter Command: ");  // MISRA 17.2 - Ignore return
         (void)scanf("%d", &input);  // MISRA 17.2 - Ignore return
         
         // MISRA 14.3 - Single statement per branch
         if (input == -1) {
             break;  // MISRA 15.4 - Single break statement
         }
         
         if (input == 0 || input == 1) {
             setPump((PumpState)input);  // MISRA 10.3 - Cast in range
         } else {
             (void)printf("Invalid input! Use 0 (OFF) or 1 (ON)\n");  // MISRA 17.2 - Ignore return
         }
     }
     
     (void)printf("Test program exited.\n");  // MISRA 17.2 - Ignore return
     return 0;
 }