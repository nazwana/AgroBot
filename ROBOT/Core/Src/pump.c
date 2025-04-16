/*
 * pump.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#include "pump.h"

void setPump(GPIO_PinState state) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, state);
}
