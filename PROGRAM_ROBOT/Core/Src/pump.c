/*
 * pump.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Andik Putra Nazwana
 */

#include "pump.h"

void setPump(GPIO_PinState state)
{
    // MISRA 17.2 - Ignore return value (HAL_GPIO_WritePin returns void but rule applies generally)
    (void)HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, state);  // MISRA 11.3 - All parameters match expected types
    
    // MISRA 15.7 - All switch statements have default case (not applicable here)
    // MISRA 16.1 - All switch statements have at least one case (not applicable here)
}