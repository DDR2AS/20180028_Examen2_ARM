#include "motorDriver.h"

#define FREQ_PWM 80000
#define PWM_50 40000
#define PWM_0 0
#define PWM_100 80000

volatile uint32_t tiempoMilis = 0;

void delay_ms(uint32_t milisegundos)
{
    tiempoMilis = 0;
    uint32_t inicioTiempo = tiempoMilis;
    while((tiempoMilis - inicioTiempo) < milisegundos);
    tiempoMilis = 0;
}

void CCRX_clear(void){
    TIM4->CCR4 = PWM_0;
    TIM4->CCR3  = PWM_0;
}

void iniciarModulo(void)
{
    //Habilitamos el clk 
    RCC->APB2ENR |= (1<<2)| (1<<4);
    RCC->APB1ENR |= (1<<2);
    //Configuro como salidas PA4,5,6,7 ; 2MHz
    GPIOA->CRL &= ~(0xFFFF << 16);
    GPIOA->CRL |= (0x2<<16)|(0x2<<20)|(0x2<<24)|(0x2<<28);
    //Inicializamos a 0 las salidas
    GPIOA->ODR &= ~(0xF<<4);
    //
    GPIOC->CRH &= ~(0XF<<20);
    GPIOC->CRH |= (0x2<<20);
    GPIOC->ODR &= ~(1<<13);

    /*CONFIGURAR PB8 y PB9*/
    RCC->APB2ENR |= (1<<3);
    GPIOB->CRH &= ~(0xFF<<0);
    GPIOB->CRH |= (1<<1)|(1<<3)|(1<<5)|(1<<7);

    /*CONFIGURAR EL TIMER4*/
    TIM4->CCMR2 &= ~((0xFF << 8) & (0x68 <<0));// i.
    TIM4->CCMR2 |= (0x68 << 8)|(0x68<<0);// i. Registro de configuración de modo (canal 4 y 3)
    TIM4->BDTR |= (1 << 15);//ii.
    TIM4->CCER |= (1 << 12)|(1<<8);//iii.

    TIM4->PSC = 7;//iv. prescalador 
    TIM4->ARR &= ~(0xFF);
    TIM4->ARR = FREQ_PWM;// inicio de la cuenta preescalador
    TIM4->CCR4 = 0;//vi. ciclo de reloj 0% canal 4
    TIM4->CCR3 = 0;//ciclo de reloj canal 3
    
    
    //vii.Habilitar el temporizador
    TIM4->CR1 |= (1<<7)|(1<<0);//bit 7 -> habilitar recarga , bit 0-> habilitar el timer
}

void avanzar(uint8_t vel)
{
    GPIOA->ODR |= (1<<5)|(1<<6);
    GPIOA->ODR &= ~((1<<4)&(1<<7));
    //Indicar ciclo de trabajo
    CCRX_clear();//
    if (vel == 1){
        TIM4->CCR4 = PWM_50;
        TIM4->CCR3  = PWM_50;
    } else {
        if(vel == 2){
            TIM4->CCR4 = PWM_100;
            TIM4->CCR3  = PWM_100;    
        }
    }
    delay_ms(1000);
    CCRX_clear();//
}

void retroceder(uint8_t vel)
{
    GPIOA->ODR &= ~((1<<5)&(1<<6));
    GPIOA->ODR |= (1<<4)|(1<<7);
    CCRX_clear();//
    if (vel == 1){
        // 50% de PWM
        TIM4->CCR4 = PWM_50;
        TIM4->CCR3  = PWM_50;
    }else{
        //PWM 100%
        TIM4->CCR4 = PWM_100;
        TIM4->CCR3  = PWM_100;  

    }
    delay_ms(1000);
    CCRX_clear();//
}

void girarDerecha(void)
{
    GPIOA->ODR &= ~((1<<5)&(1<<7));
    GPIOA->ODR |= (1<<4)|(1<<6);
    CCRX_clear();
    // 50% de PWM
    TIM4->CCR4 = PWM_50;
    TIM4->CCR3  = PWM_50;
    delay_ms(1000);
    CCRX_clear();

}

void girarIzquierda(void)
{
    GPIOA->ODR &= ~((1<<4)&(1<<6));
    GPIOA->ODR |= (1<<5)|(1<<7);
    CCRX_clear();
    // 50% de PWM
    TIM4->CCR4 = PWM_50;
    TIM4->CCR3  = PWM_50;
    delay_ms(1000);
    CCRX_clear();
}

/*
Desarrollar los prototipos de
iniciarModulo(),
avanzar(),
retroceder(),
girarDerecha(),
girarIzquierda()

*/