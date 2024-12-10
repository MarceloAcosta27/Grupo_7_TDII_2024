/*
 * API_GPIO.h
 *
 *  Created on: Sep 24, 2024
 *      Author: Grupo 7
 */

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_

#include <stdint.h>
#include <stdbool.h>

typedef uint16_t led_t;
typedef bool buttonStatus_t;


void MX_GPIO_Init(void);
void writeLedOn_GPIO(led_t LDx);
void writeLedOff_GPIO(led_t LDx);
void toggleLed_GPIO(led_t LDx);
buttonStatus_t readButton_GPIO (void);



#endif /* API_INC_API_GPIO_H_ */
