#include <stdint.h>
#include "../incFiles/stm32f103x6.h"

#ifndef MOTOR_H_DRIVER
#define MOTOR_H_DRIVER

//Implementar el codigo fuente de las fuciones
void delay_ms(uint32_t milisegundos);
void CCRX_clear(void);
void iniciarModulo(void);
void avanzar(uint8_t vel);
void retroceder(uint8_t vel);
void girarDerecha(void);
void girarIzquierda(void);

#endif