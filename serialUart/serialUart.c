#include "serialUart.h"

void inicializarUart(void)
{
    RCC->APB2ENR |= (1<<0)|(1<<2)|(1<<14);

    //Configuracion del modo de operacion en PA9 y PA10
    GPIOA->CRH &= ~(0xFF << 4);
    GPIOA->CRH |= (1<<10)|(1<<5)|(1<<7);

    USART1->BRR |= (0x34<<4);
    USART1->BRR |= (1<<0);
    USART1->CR1 |= (1<<2)|(1<<3)|(1<<13);
}

void enviarCaracter(uint8_t caracter)
{
    while(!(USART1->SR & (1<<7)));
    USART1->DR &= ~(0xF);
    USART1->DR |= caracter;
    while(!(USART1->SR & (1<<6)));
}

void nuevaLinea()
{
    while(!(USART1->SR & (1<<7)));
    USART1->DR &= ~(0xF);
    USART1->DR |= '\n';
    while(!(USART1->SR & (1<<6)));
}

void enviarPalabra(uint8_t cadena[])
{
    uint8_t i = 0;
    for(i=0;cadena[i] != '\0'; i++)
    {
        enviarCaracter(cadena[i]);
    }
    nuevaLinea();
}


//Implementar las funciones: 
int existeCaracter(void){
    if (USART1->SR & (1<<5)){
        //Si es 1 los datos recibidos están listos para su lectura
        return 1;
    }else{
        return 0;
    }
    
}


uint8_t leerCaracter(void){
    //Bucle para el bit RXNE sea 1 
    while ((USART1->SR & (1<<5)) == 0);
    uint8_t caracter = USART1->DR & 0xFF;
    return caracter;
    
}
