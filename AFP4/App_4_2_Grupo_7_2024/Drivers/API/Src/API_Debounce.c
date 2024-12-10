/*
 * API_debounce.c
 *
 *  Created on: Dec 4, 2024
 *      Author: Grupo 7
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_DelayNoBloqueante.h"
#include "API_GPIO.h"
#include "API_Debounce.h"


/*Declaracion de variables */

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING
    }debounceState_t;

static debounceState_t debounceState;		// Representa el estado del boton (BUTTON_UP,BUTTON_FALLING, BUTTON_DOWN, BUTTON_RISING)
static bool_t keyPressing = false;			// fue presionado el boton? Inicializacion en falso
static bool_t fallingEdge = false;			// Hubo flanco descendente? Inicializacion en falso
//bool_t buttonState;
delay_t debounceDelay;



/**
  * @brief Read Key Function
  * @param none
  * @retval bool_t
  */
bool_t readKey (void){
	bool_t keyPress = false;
	fallingEdge = false;
	if (keyPressing == true){
		keyPress = true;
		keyPressing = false;
	}
	return (keyPress);
}


/**
  * @brief Initialization Debounce
  * @param None
  * @retval None
  */
void debounceFSM_init(){
	debounceState = BUTTON_UP;     // Estado inicial de la MEF
	delayInit(&debounceDelay, 40); // Retardo de 40 ms
	writeLedOff_GPIO(LEDS[0]);     // LEDs apagados
	writeLedOff_GPIO(LEDS[1]);
	writeLedOff_GPIO(LEDS[2]);
	//buttonState = false;          // Estado inicial del boton
}

/**
  * @brief Debounce Update
  * @param None
  * @retval None
  */
void debounceFSM_update() {
    switch (debounceState) {
        case BUTTON_UP:
            if (readButton_GPIO() == GPIO_PIN_RESET) { // Botón presionado
                debounceState = BUTTON_FALLING;
                delayRead(&debounceDelay);             // Iniciar el retardo
            }
            break;
        case BUTTON_FALLING:
            if (delayRead(&debounceDelay)) {               // Verificar si se cumplió el retardo
                if (readButton_GPIO() == GPIO_PIN_RESET) { // Confirmar boton presionado
                    debounceState = BUTTON_DOWN;
                    keyPressing=true;
                    fallingEdge=true;
                } else {
                    debounceState = BUTTON_UP;
                }
            }
            break;
        case BUTTON_DOWN:
            if (readButton_GPIO() == GPIO_PIN_SET) { // Boton liberado
                debounceState = BUTTON_RISING;
                delayRead(&debounceDelay);           // Iniciar retardo
            }
            break;
        case BUTTON_RISING:
            if (delayRead(&debounceDelay)) {              // Verificar si se cumplio el retardo
                if (readButton_GPIO() == GPIO_PIN_SET) {  // Confirmar boton liberado
                    debounceState = BUTTON_UP;
                    keyPressing=false;
                } else {
                    debounceState = BUTTON_DOWN;
                }
            }
            break;
        default:
        	debounceState = BUTTON_UP;
        break;
    }
}
