/*
 * API_DelayNoBloqueante.c
 *
 *  Created on: Nov 10, 2024
 *      Author: Grupo 7
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_DelayNoBloqueante.h"

/**
  * @brief Initialization DelayUnblocking Function
  * @param delay_t pointer
  *        tick_t duration
  * @retval None
  */
void delayInit(delay_t *delay, tick_t duration)
{
	//delay->startTime = HAL_GetTick();
	delay->duration = duration;
	delay->running=false;
}
/**
  * @brief Read DelayUnblocking Function
  * @param delay_t pointer
  * @retval bool_t
  */
bool_t delayRead(delay_t* delay) {
    if (!delay->running) {                 // Si el retardo no estÃ¡ en ejecuciÃ³n
        delay->startTime = HAL_GetTick();  // Toma la marca de tiempo actual
        delay->running = true;             // Inicia el retardo
        return false;                      // Retorna que no se ha cumplido el tiempo
    }
    else {                                 // Si el retardo se cumplio en ejecucion
        tick_t currentTime = HAL_GetTick();
        if ((currentTime - delay->startTime) >= delay->duration) {
            delay->running = false;        // Finaliza el retardo
            return true;                   // Retorna que se ha cumplido el tiempo
        }
        return false;                      // Retorna que el tiempo no se ha cumplido
    }
}
/**
  * @brief Write DelayUnblocking Function
  * @param delay_t pointer
  *        tick_t duration
  * @retval bool_t
  */
void delayWrite(delay_t *delay, tick_t duration)
{
	delay->duration = duration;
}
