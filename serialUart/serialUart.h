#include <stdint.h>
#include "../incFiles/stm32f103x6.h"

#ifndef SERIAL_H_UART
#define SERIAL_H_UART

void inicializarUart(void);
void enviarCaracter(uint8_t caracter);
void nuevaLinea(void);
void enviarPalabra(uint8_t cadena[]);

//Pregunta 1
int existeCaracter(void);

//Pregunta 2
uint8_t leerCaracter(void);

#endif