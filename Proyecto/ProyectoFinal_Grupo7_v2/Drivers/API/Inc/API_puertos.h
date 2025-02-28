/*
 * API_puertos.h
 *
 *  Created on: Feb 25, 2025
 *      Author: seckl
 */
#include "main.h"
#include "API_delays.h"

void Output_Pin (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Input_Pin (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Output_Pin1 (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Input_Pin1 (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t waitforhigh(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,uint32_t tiem);
uint8_t waitforlow(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,uint32_t tiem);
