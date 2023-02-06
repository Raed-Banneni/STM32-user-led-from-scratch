//we must locate port and pin number
// Port A
// pin  5
#include <stdint.h>
#define periph_base 			(0x40000000UL)

#define ahb2_offset				(0x08000000UL)
#define ahb2_base  				(periph_base + ahb2_offset)

#define ahb1_offset				(0x20000UL)
#define ahb1_base				(periph_base + ahb1_offset)

#define gpioa_offset 			(0x000000UL)
#define gpioa_base				(ahb2_base + gpioa_offset)

#define rcc_offset				(0X1000UL)
#define rcc_base				(ahb1_base + rcc_offset)

#define rcc_ahb2enr_offset 		(0x4CUL)
#define rcc_ahb2enr				(*(volatile unsigned int *)(rcc_base + rcc_ahb2enr_offset))

#define gpioa_moder_offset		(0x00UL)
#define gpioa_moder 			(*(volatile unsigned int*)(gpioa_base +gpioa_moder_offset))

#define odr_offset 				(0X14UL)
#define odr 					(*(volatile unsigned int*)(gpioa_base + odr_offset))

#define gpioa_en				(1U<<0)

#define pin5					(1U<<5)
#define led_pin					pin5


typedef struct
{	//REGISTERS SHOULD BE IN THE SAME ORDER AS IN THE RM EACH ONE OCCUPIES 4 BYTES
	volatile uint32_t MODER;
//	volatile uint32_t OTYPER;
//	volatile uint32_t OSPEEDR;
//	volatile uint32_t PUPDR;
//	volatile uint32_t IDR;
	volatile uint32_t DUMMY[4]; //we added this dummy array to keep the same offset between the only two registers that we need.
	volatile uint32_t ODR;
//	volatile uint32_t BSRR;
//	volatile uint32_t LCKR;
//	volatile uint32_t AFR[2];
//	volatile uint32_t PBRR;
//	volatile uint32_t PASCR;
//
}gpio_Typedef;

typedef struct
{
	volatile uint32_t DUMMY[19];
	volatile uint32_t AHB2ENR;
}rcc_Typedef;


#define RCC 		((rcc_Typedef*) rcc_base)
#define GPIOA 		((gpio_Typedef*) gpioa_base)

int main(void)
{
	//	rcc_ahb2enr |= gpioa_en;
	RCC->AHB2ENR    |= gpioa_en;

//	gpioa_moder 	|= (1U<<10);
//	gpioa_moder 	&=~(1U<<11);

	GPIOA->MODER 	|= (1U<<10);
	GPIOA->MODER 	&=~ (1U<<11);

	while(1)
	{
		//odr |=led_pin;
		GPIOA->ODR  ^= led_pin;
		for(volatile long int i =0; i<100000;i++){}
	}
}

