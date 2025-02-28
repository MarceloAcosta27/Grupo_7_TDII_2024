/* USER CODE BEGIN Header */
/**
  **********
  * @file           : main.c
  * @brief          : Main program body
  **********
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "eth.h"
#include "i2c.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "API_DHT11_LIB.h"                 //agregado por Sensor de Temperatura y Humedad DHT11
#include "API_uart.h"
#include "stdio.h"                         //agregado por bluetooth HC-05
#include "string.h"                        //agregado por bluetooth HC-05
#include "API_liquidcrystal_i2c.h"         //agregados por lcd



#define DEVICE_ADDR    (0x27 << 1)  // Dirección del LCD (ajustar según tu módulo)

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char texto[100];
char texto2[16];
char texto3[16];
unsigned int DHT11_TEMP;    // Declarar en al main
unsigned int DHT11_HUM;     //declarar en el main

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void MX_USART3_UART_Init(void);
void MX_USB_OTG_FS_PCD_Init(void);
void encenderSoloUnLED(GPIO_TypeDef *port, uint16_t pin);   //FUNCION PARA ACTIVAR LED

uint8_t estadoErrorDHT11 = 0; // Bandera para indicar si hay error con el sensor
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

	//---------------------LCD--------------------------//
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();

    // Inicializar LCD
    HD44780_Init(2);
    HD44780_Clear();
    HD44780_SetCursor(0,0);
    HD44780_PrintStr("PROYECTO FINAL");
    HD44780_SetCursor(0,1);
    HD44780_PrintStr("GRUPO N7");

    // Enciende LED Verde (PC7) y apaga los demás
        encenderSoloUnLED(GPIOC, GPIO_PIN_7);

        HAL_Delay(3000);

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_ETH_Init();
  MX_I2C2_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  /* USER CODE BEGIN 2 */
  delay_us_dwt_init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  // Función para encender solo un LED y apagar los demás

  int error_DHT11 = 0; // Variable para indicar si hay error en el DHT11

  // Bucle principal
  while (1)
     {
         if (error_DHT11) {
             HD44780_Clear();
             HD44780_SetCursor(0, 0);
             HD44780_PrintStr("Error DHT11");

             //Enciende todos los LEDs
             encenderSoloUnLED(GPIOB, GPIO_PIN_3);  // LED AMARILLO ON
             encenderSoloUnLED(GPIOB, GPIO_PIN_4);  // LED VERDE ON
             encenderSoloUnLED(GPIOC, GPIO_PIN_7);  // LED ROJO ON

             //Envia mensaje por Bluetooth
             HAL_UART_Transmit(&huart3, (uint8_t*)"Error DHT11", strlen("Error DHT11"), HAL_MAX_DELAY);
             HAL_UART_Transmit(&huart3, (uint8_t*)"\r\n", 2, HAL_MAX_DELAY);

             HAL_Delay(1000);
             continue;
         }

         if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) != GPIO_PIN_RESET) {
             HD44780_Clear();
             HD44780_SetCursor(0, 0);
             HD44780_PrintStr("Esperando...");

             //Enciende LED Verde
             encenderSoloUnLED(GPIOB, GPIO_PIN_4);

             //Envia mensaje por Bluetooth
             HAL_UART_Transmit(&huart3, (uint8_t*)"Esperando...", strlen("Esperando..."), HAL_MAX_DELAY);
             HAL_UART_Transmit(&huart3, (uint8_t*)"\r\n", 2, HAL_MAX_DELAY);

         } else {
             if (DHT11_ok() == 1) {
                 error_DHT11 = 0;
                 DHT11_Read();

                 sprintf(texto3, "Temp=%uC", (unsigned int)DHT11_TEMP);
                 sprintf(texto2, "Hum=%u%%", (unsigned int)DHT11_HUM);

                 // Combina temperatura y humedad en una sola línea
                            char mensaje_combinado[32];
                            snprintf(mensaje_combinado, sizeof(mensaje_combinado), "%s %s", texto3, texto2);

                 // Mostrar en LCD
                 HD44780_Clear();
                 HD44780_SetCursor(0, 0);
                 HD44780_PrintStr(texto3);
                 HD44780_SetCursor(0, 1);
                 HD44780_PrintStr(texto2);

                 // Enviar datos combinados por Bluetooth utilizando USART3
                         HAL_UART_Transmit(&huart3, (uint8_t*)mensaje_combinado, strlen(mensaje_combinado), HAL_MAX_DELAY);
                         HAL_UART_Transmit(&huart3, (uint8_t*)"\r\n", 2, HAL_MAX_DELAY);

                 encenderSoloUnLED(GPIOB, GPIO_PIN_3);  // Enciende LED Amarillo
             } else {
                 HD44780_Clear();
                 HD44780_SetCursor(0, 0);
                 HD44780_PrintStr("Error DHT11");

                 //Enciende todos los LEDs
                 encenderSoloUnLED(GPIOB, GPIO_PIN_3);  // LED Amarillo
                 encenderSoloUnLED(GPIOB, GPIO_PIN_4);  // LED VERDE ON
                 encenderSoloUnLED(GPIOC, GPIO_PIN_7);  // LED ROJO ON

                 //Enviar mensaje por Bluetooth
                 HAL_UART_Transmit(&huart3, (uint8_t*)"Error DHT11", strlen("Error DHT11"), HAL_MAX_DELAY);
                 HAL_UART_Transmit(&huart3, (uint8_t*)"\r\n", 2, HAL_MAX_DELAY);

                 error_DHT11 = 1;
             }
         }
         HAL_Delay(1000);  // Esperar antes de la siguiente lectura
     }
}

  void encenderSoloUnLED(GPIO_TypeDef *port, uint16_t pin) {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);  // LED ROJO OFF
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);  // LED VERDE OFF
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);  // LED Amarillo OFF
      HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);  // Enciende el LED seleccionado
  }

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;                     //4
  RCC_OscInitStruct.PLL.PLLN = 192;                    //72
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;                      //3
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
