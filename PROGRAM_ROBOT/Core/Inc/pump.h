/*
 * pump.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#ifndef PUMP_H_
#define PUMP_H_

#include "main.h"

#define ON  GPIO_PIN_SET    // MISRA 10.1 - Use of defined constants
#define OFF GPIO_PIN_RESET  // instead of magic numbers

void setPump(GPIO_PinState state);  // MISRA 8.4 - Function declaration

#endif /* PUMP_H_ */