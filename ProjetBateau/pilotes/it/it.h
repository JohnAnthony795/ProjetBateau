#ifndef IT_H
#define IT_H

#include "stm32f10x.h"
#include "clock/clock.h"
#include "gpio/gpio.h"
#include "timer/Timer_1234.h"

extern void (*pFnc) (void);

/** 
* Configure la routine d'interruption d'un Timer
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef ) du timer considéré
* @param Priority Niveau de priorité de l'interruption
* @param IT_function Pointeur sur la fonction qui sera exécutée dans le routine d'interruption
**/
void Timer_Active_IT( TIM_TypeDef *Timer, u8 Priority, void (*IT_function) (void));


#endif
