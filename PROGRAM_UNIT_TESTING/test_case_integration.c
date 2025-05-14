/*
 * test_case_integration.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

 #include <stdio.h>
 #include <stdint.h>
 #include <stdbool.h>
 
 // Fungsi aksi sederhana
 void moveForward(void)  { (void)printf("ACTION: MOVING FORWARD\n"); }  // MISRA 17.2 - Ignore return
 void moveBackward(void) { (void)printf("ACTION: MOVING BACKWARD\n"); }  // MISRA 17.2 - Ignore return
 void turnLeft(void)     { (void)printf("ACTION: TURNING LEFT\n"); }     // MISRA 17.2 - Ignore return
 void turnRight(void)    { (void)printf("ACTION: TURNING RIGHT\n"); }    // MISRA 17.2 - Ignore return
 void stopMotors(void)   { (void)printf("ACTION: MOTORS STOPPED\n"); }   // MISRA 17.2 - Ignore return
 
 void grip(void)         { (void)printf("ACTION: GRIPPER CLOSED\n"); }    // MISRA 17.2 - Ignore return
 void release(void)      { (void)printf("ACTION: GRIPPER OPENED\n"); }    // MISRA 17.2 - Ignore return
 
 void pumpOn(void)       { (void)printf("ACTION: PUMP ACTIVATED\n"); }    // MISRA 17.2 - Ignore return
 void pumpOff(void)      { (void)printf("ACTION: PUMP DEACTIVATED\n"); } // MISRA 17.2 - Ignore return
 
 void processJoystick(uint8_t data[10]) {  // MISRA 8.2 - Function declaration
     uint16_t LY = (data[2] << 8) | data[3];  // Sumbu Y kiri
     uint16_t RX = (data[4] << 8) | data[5];  // Sumbu X kanan
 
     (void)printf("\n[DEBUG] LY (Forward/Backward): %u\n", LY);  // MISRA 17.2 - Ignore return
     (void)printf("[DEBUG] RX (Left/Right):        %u\n", RX);      // MISRA 17.2 - Ignore return
 
     bool isMoving = false;
 
     // Deteksi gerakan maju/mundur
     if (LY > 3000U) {  // MISRA 10.1 - Unsigned literal
         moveForward();
         isMoving = true;
     } else if (LY < 1000U) {  // MISRA 10.1 - Unsigned literal
         moveBackward();
         isMoving = true;
     }
 
     // Deteksi belok kiri/kanan
     if (RX > 3000U) {  // MISRA 10.1 - Unsigned literal
         turnRight();
         isMoving = true;
     } else if (RX < 1000U) {  // MISRA 10.1 - Unsigned literal
         turnLeft();
         isMoving = true;
     }
 
     // Jika tidak bergerak dan tidak belok, berhenti
     if (!isMoving) {
         stopMotors();
     }
 
     // Aksi tombol
     if (data[8]) {
         grip();
     }
     if (data[9]) {
         release();
     }
 }
 
 void checkSoilMoisture(uint8_t moisture) {  // MISRA 8.2 - Function declaration
     (void)printf("[DEBUG] Moisture value: %u\n", moisture);  // MISRA 17.2 - Ignore return
     if (moisture < 40U) {  // MISRA 14.4
         pumpOn();
     } else {
         pumpOff();
     }
 }
 
 void printInstructions(void) {  // MISRA 8.2 - Function declaration
     (void)printf("\n=== Joystick Data Format ===\n");  // MISRA 17.2 - Ignore return
     (void)printf("Masukkan 10 nilai heksadesimal (2 digit tiap nilai):\n");  // MISRA 17.2 - Ignore return
     (void)printf("[0-1] = LX (Left X-axis, tidak digunakan)\n");  // MISRA 17.2 - Ignore return
     (void)printf("[2-3] = LY (Left Y-axis, maju/mundur)\n");  // MISRA 17.2 - Ignore return
     (void)printf("[4-5] = RX (Right X-axis, belok kiri/kanan)\n");  // MISRA 17.2 - Ignore return
     (void)printf("[6-7] = RY (Right Y-axis, tidak digunakan)\n");  // MISRA 17.2 - Ignore return
     (void)printf("[8]   = RB (Tombol kanan untuk GRIP)\n");  // MISRA 17.2 - Ignore return
     (void)printf("[9]   = LB (Tombol kiri untuk RELEASE)\n");  // MISRA 17.2 - Ignore return
     (void)printf("Contoh input: 00 00 0F A0 03 E8 00 00 00 00\n");  // MISRA 17.2 - Ignore return
     (void)printf("=============================\n");  // MISRA 17.2 - Ignore return
 }
 
 int main(void) {  // MISRA 8.2 - Function declaration
     (void)printf("=== Joystick Control Test Program ===\n");  // MISRA 17.2 - Ignore return
 
     while (1) {
         int choice;  // MISRA 8.1 - All declarations visible
         (void)printf("\nMenu:\n1. Test Joystick\n2. Set Moisture\n0. Exit\nChoice: ");  // MISRA 17.2 - Ignore return
         (void)scanf("%d", &choice);  // MISRA 17.2 - Ignore return
 
         if (choice == 0) {
             break;
         }
 
         if (choice == 1) {
             printInstructions();
             uint8_t data[10];  // MISRA 8.1 - All declarations visible
             (void)printf("Enter 10 bytes (in hex, separated by space): ");  // MISRA 17.2 - Ignore return
             for (int i = 0; i < 10; i++) {
                 unsigned int temp;  // MISRA 8.1 - All declarations visible
                 (void)scanf("%x", &temp);  // MISRA 17.2 - Ignore return
                 data[i] = (uint8_t)temp;  // MISRA 10.3 - Cast in range
             }
             processJoystick(data);
         } else if (choice == 2) {
             uint8_t moisture;  // MISRA 8.1 - All declarations visible
             (void)printf("Enter moisture value (0–100): ");  // MISRA 17.2 - Ignore return
             (void)scanf("%hhu", &moisture);  // MISRA 17.2 - Ignore return
             checkSoilMoisture(moisture);
         } else {
             (void)printf("Invalid choice.\n");  // MISRA 17.2 - Ignore return
         }
     }
 
     (void)printf("Program exited.\n");  // MISRA 17.2 - Ignore return
     return 0;
 }
 
// 00 00 0F A0 03 E8 00 00 00 00 → MOVING FORWARD + TURNING LEFT
// 00 00 03 E8 0F A0 00 00 00 00 → MOVING BACKWARD + TURNING RIGHT
// 00 00 08 00 08 00 00 00 00 00 → MOTORS STOPPED
// 00 00 0F A0 08 00 00 00 01 00 → MOVING FORWARD + GRIPPER CLOSED
// 00 00 03 E8 03 E8 00 00 00 01 → MOVING BACKWARD + TURNING LEFT + GRIPPER OPENED