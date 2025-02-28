/*
 * API_uart.h
 *
 *  Created on: Feb 25, 2025
 *      Author: seckl
 */

#ifndef LIBRERIAS_UART_H_
#define LIBRERIAS_UART_H_


#include "main.h"



void uartx_write(UART_HandleTypeDef *huart,uint8_t ch);
void uartx_write_text(UART_HandleTypeDef *huart, uint8_t *info);
uint8_t uartx_read(UART_HandleTypeDef *huart);
void uartx_read_text(UART_HandleTypeDef *huart,uint8_t  *info,const uint8_t final,uint8_t cuanto);





#endif /* LIBRERIAS_UART_H_ */
