/*
 * Delays.h
 *
 *  Created on: Feb 24, 2025
 *      Author: Grupo 7
 */

#ifndef API_INC_DELAYS_H_
#define API_INC_DELAYS_H_



#include "main.h"

//DEFINE CUAL SERA USADO COMO DELAY_US
#define Delay_us delay_us_dwt


#define delay_us Delay_us //para aceptar en mayuscula o minuscula
#define delay_ms Delay_ms



void delay_us_C (uint32_t reta);
void delay_us_ASM(uint32_t us);
void delay_us_ASM_IT(uint32_t us);
void delay_us_tim_init();
void delay_us_tim (uint32_t us);
void delay_us_dwt_init();
void delay_us_dwt(uint32_t reta);
void Delay_ms(uint32_t ms);


#endif /* API_INC_DELAYS_H_ */
