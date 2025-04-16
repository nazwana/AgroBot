#ifndef SERVO_H_
#define SERVO_H_

#include "main.h"

typedef struct {
    TIM_HandleTypeDef *htim;
    uint32_t channel;
    int angle;
} servo_t;

void initServo(servo_t *servo, TIM_HandleTypeDef *htim, uint32_t channel);
void setAngleServo(servo_t *servo, int angle);

#endif /* SERVO_H_ */
