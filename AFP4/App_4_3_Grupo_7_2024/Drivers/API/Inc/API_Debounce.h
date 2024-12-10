/*
 * API_Debounce.h
 *
 *  Created on: Dec 5, 2024
 *      Author: marcelo
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdbool.h>

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING
    }debounceState_t;
typedef bool bool_t;
void debounceFSM_init();
void debounceFSM_update();
bool_t readKey (void);

#endif /* API_INC_API_DEBOUNCE_H_ */