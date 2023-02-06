//WHERE THE LED IS CONNECTED
//PORT: A
//PIN: 5
#define PERIPH_BASE 		(0x40000000UL)

#define AHB2_PERIPH_OFFSET	(0x08000000UL)
#define AHB2_PERIPH_BASE 	(PERIPH_BASE + AHB2_PERIPH_OFFSET)

#define GPIOA_OFFSET		(0x0000UL) // OFFSETfrom AHB2bus
#define GPIOA_BASE 			(AHB2_PERIPH_BASE + GPIOA_OFFSET)

#define AHB1_PERIPH_OFFSET	(0x00020000UL)
#define AHB1_PERIPH_BASE	(PERIPH_BASE + AHB1_PERIPH_OFFSET)

#define RCC_OFFSET			(0x1000UL) // OFFSETfrom AHB2 bus
#define RCC_BASE 			(AHB1_PERIPH_BASE + RCC_OFFSET)


#define AHB2EN_R_OFFSET		(0x4CUL)	//REGISTER OFFSET
#define RCC_AHB2EN_R			(*(volatile unsigned int *)( RCC_BASE + AHB2EN_R_OFFSET)) //THE REGISTER

#define MODE_R_OFFSET			(0x00)
#define GPIOA_MODE_R			(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET			(0x14)
#define GPIO_OD_R 				(*(volatile unsigned int *)(GPIOA_BASE +OD_R_OFFSET))


#define GPIOAEN					(1U<<0)	//SHIFT 1 POSITION 0
										// 0B 0000 0000 0000 0000 0000 0000 0000 0001
#define PIN5				    (1U<<5)
#define LED_PIN					PIN5

/*MODE REGISTER BITS 10 AND 11 ARE PIN 5 MODE BITS
 * FOR OUTPUT IT MUST BE 01
 * (1U<<10) // sets only bit 10 to 1
 * &=~(1U<<11)0 sets only bit 11 to 0
 */

int main (void)
{
	//1. enable clock access to GPIOA
	RCC_AHB2EN_R |= GPIOAEN;
	//2.SET pA5 to output
	 GPIOA_MODE_R |= (1U<<10);
	 GPIOA_MODE_R &=~(1U<<11);
	while(1)
	{
		// 3 . set pa5 high
		GPIO_OD_R |=LED_PIN ;
	}
}
