#include "it.h"


void Timer_Active_IT( TIM_TypeDef *Timer, u8 Priority, void (*IT_function) (void)) {
	
	int var = 0;
	
	if (Timer == TIM2)
		var = TIM2_IRQn;
	else if (Timer == TIM3)
		var = TIM3_IRQn;
	else if (Timer == TIM4)
		var = TIM4_IRQn;
	else if (Timer == TIM1)
		var = TIM1_UP_IRQn;
	
	//configuration NVIC pour accepter l'IT
	NVIC->ISER[0] = 1 << var;
	
	//configuration priorité
	NVIC->IP[var] = Priority;
	
  pFnc = IT_function;
	
}


