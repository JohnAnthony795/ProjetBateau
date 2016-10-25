#include "Timer_1234.h"
#include <math.h>
#include "clock.h"

float Timer_1234_Init(TIM_TypeDef *Timer, float Duree_us ) {

	//config RCC : on active tous les timers
		RCC->APB2ENR |= 0x0400;
		RCC->APB1ENR |= 0x1;
		RCC->APB1ENR |= 0x2;
		RCC->APB1ENR |= 0x4;
		
	//autoriser interruptions
	Timer->DIER = 1;

	//config prescaler et autoreload pour avoir une période de Duree_us
	int i = ceil((CLOCK_GetHCLK()*(Duree_us/1000000))/65535);
	Timer->PSC = i;
	Timer->ARR = ceil((CLOCK_GetHCLK()*(Duree_us/1000000))/i);
	
	//configuration des registres pour enable le compteur et laisser DIR = up
	Timer->CR1 = 0x0001;

	return 0;
}



