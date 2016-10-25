#ifndef GIROUETTE
#define GIROUETTE

#include "gpio/gpio.h"
#include "clock/clock.h"
#include "it/it.h"
#include "stm32f10x.h"
#include <math.h>

#endif

void EXTI_ClearITPendingBit(unsigned int LineNumber) {
	EXTI->PR &= (1 << LineNumber);
}

void Port_IO_Init_Input_pull (GPIO_TypeDef * Port, u8 Broche) {
	if (Broche <= 7)
		Port->CRL = ((Port->CRL) & (~(0xf << (Broche*4)))) | (1 << (Broche*4+3));
	else
		Port->CRH = ((Port->CRH) & (~(0xf << ((Broche-8)*4)))) | (1 << ((Broche-8)*4+3));				
}

void Timer_Init (TIM_TypeDef *Timer) {
	if (Timer == TIM1)
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	else if (Timer == TIM2)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	else if (Timer == TIM3)
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
}

void IT_Configure_EXTI (unsigned int Line, unsigned int Priority, void (*IT_function) (void)) {
	EXTI->IMR |= 1 << Line; //on autorise le déclenchement d'une IT depuis Line x (broches PA.x, PB.x etc)
	EXTI->RTSR |= 1 << Line;//on déclenche l'IT sur front montant, pas sur front descendant
	EXTI->FTSR &= ~(1 << Line);
	
	int IRQn = 0;
	
	if (Line == 0) //on détermine le num d'interruption
		IRQn = EXTI0_IRQn;
	else if (Line == 1)
		IRQn = EXTI1_IRQn;
	else if (Line == 2)
		IRQn = EXTI2_IRQn;
	else if (Line == 3)
		IRQn = EXTI3_IRQn;
	else if (Line == 4)
		IRQn = EXTI4_IRQn;
	else if (Line >=5 && Line <=9)
		IRQn = EXTI9_5_IRQn;
	else if (Line >=10 && Line <=15)
		IRQn = EXTI15_10_IRQn;
	
	if (IRQn != 0) {
	//réglages NVIC : on autorise l'IT extérieure depuis les Lines 5-9 et on règle la priorité
	NVIC->ISER[0] = 1 << IRQn;
	NVIC->IP[IRQn] = Priority;
		
	//on définit la fonction à utiliser
	//il faut pour cela définir "void (*pFnc) (void)" en var globale et l'appeler ("(*pFnc) ()") dans le TIMx_IRQHandler()
	pFnc = IT_function;
	}
}

void Set_TIM3_To_Zero () {
	TIM3->CNT &= 0;
}

void Timer_Configure_Girouette (TIM_TypeDef *Timer) {
	Timer->CCER &= ~(1); //on désactive le timer pour la configuration
	
	Timer->DIER = 1; //autoriser interruptions
	Timer->PSC = 0; //pas de prescaler : on compte simplement les degrés
	Timer->ARR = 360;
	
	//on configure le canal en input, IC1->TI1 et IC2->TI2
	Timer->CCMR1 = ((Timer->CCMR1) & (~(1 << 1))) | 1;
	Timer->CCMR2 = ((Timer->CCMR2) & (~(1 << 9))) | (1 << 8);
	
	//on met les bits CC1P et CC2P à 0 pour ne pas inverser la polarité sur le compteur
	Timer->CCER &= ~(0b100010);
	
	//on règle le timer pour qu'il prenne en compte les deux entrées
	Timer->SMCR = ((Timer->SMCR) & (~(1 << 2))) | 0b11;
	
	//on réactive le Timer
	Timer->CCER |= 1;
}

void Timer_Enable (TIM_TypeDef *Timer) {
	Timer->CR1 |= 1;
}

void Config_Girouette () {
	//on configure les ports PA5 PA6 et PA7 pour recupérer les infos en input pull-up
	Port_IO_Init_Input_pull (GPIOA, 5);
	Port_IO_Init_Input_pull (GPIOA, 6);
	Port_IO_Init_Input_pull (GPIOA, 7);
	
	//on configure le timer 3, qu'on utilisera ici
	Timer_Init (TIM3); //RCC
	Timer_Configure_Girouette (TIM3); //configuration complète pour un fonctionnement avec l'encodeur
	
	//on permet au timer de lever une IT quand INDEX=1
	//càd quand l'angle est à 0
	IT_Configure_EXTI (5, 3, Set_TIM3_To_Zero);

	Timer_Enable (TIM3);
}

int Get_Angle () {
	return floor(TIM2->CNT / 4);
}



