/*
 * Puertos.h
 *
 *  Created on: Feb 24, 2025
 *      Author: Grupo 7
 */

#ifndef API_INC_PUERTOS_H_
#define API_INC_PUERTOS_H_

#include "main.h"
#include "Delays.h"

void Output_Pin (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Input_Pin (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Output_Pin1 (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Input_Pin1 (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t waitforhigh(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,uint32_t tiem);
uint8_t waitforlow(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,uint32_t tiem);

#endif /* API_INC_PUERTOS_H_ */
