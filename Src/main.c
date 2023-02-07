#include "stm32l476xx.h"

#define GPIOCEN	(1U<<2)
#define PIN13 	(1U<<13)
#define BTN     PIN13
#define GPIOAEN (1U<<0)
#define PIN5 	(1U<<5)
#define LED_PIN PIN5



int main (void )
{
	RCC->AHB2ENR |= GPIOAEN;
	RCC->AHB2ENR |= GPIOCEN;

	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);
	/* SET PC13 AS INPUT */
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	while (1)
	{
		if (GPIOC->IDR && PIN13)

		GPIOA->ODR &=~LED_PIN;

		else
		GPIOC->BSRR |=(1U<<21);

	}
}
