#ifndef PUMP_H_
#define PUMP_H_

#include "main.h"

#define ON  GPIO_PIN_SET
#define OFF GPIO_PIN_RESET

void setPump(GPIO_PinState state);

#endif /* PUMP_H_ */
