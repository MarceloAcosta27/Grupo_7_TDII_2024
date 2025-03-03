Esta carpeta contiene las distintas versiones del proyecto final solicitado en el ciclo lectivo 2024 de la asignatura Tecnicas Digitales II. 
La version final es la version 2 (v2) correspondiente al directorio: ProyectoFinal_Grupo7_v2. Objetivos: 

La idea general del proyecto se basa en la lectura de la humedad y temperatura, los cuales se mostraràn en el display 16X2 I2C cuando exista la presencia de una persona u objeto, que detectará el sensor 
infrarrojo MZ80 y nos dará la información completa captada por el sensor DHT11. De la misma forma, bajo igual condicion de presencia se dará información a través de un modulo bluetooth HC-05 a un celular. 

En la carpeta Drivers se encuentran las librerias utilizadas para realizar el funcionamiento dentro del bucle infinito del main.c: 
API_Liquidcrystal_i2c: Este modulo proporciona una implementación completa para controlar un LCD I2C en una STM32F4, permitiendo escribir texto, manipular el cursor, configurar la pantalla y gestionar la retroiluminación de manera eficiente; 
API_DHT11_LIB: Este Modulo proporciona una implementación para leer la temperatura y la humedad desde un DHT11 en una STM32, asegurando una comunicación correcta y verificando la validez de los datos; 
API_puertos: Este puerto proporciona una interfaz optimizada para configurar y manejar pines GPIO en STM32, permitiendo: Configuración rápida y eficiente de los pines como entrada o salida. Compatibilidad con diferentes microcontroladores STM32, incluyendo modelos STM32F1 y otros. 
API-Delays.c: Manejo preciso de temporización con temporizadores y registros de ciclo de reloj. Dos enfoques para configurar los pines: uno optimizado mediante registros y otro más simple con HAL.

