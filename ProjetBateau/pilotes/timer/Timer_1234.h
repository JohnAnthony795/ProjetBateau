
#include "stm32f10x.h"


/** 
* Configure les Timers 1, 2, 3 et 4
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef) du timer considéré
* @param Duree_us Intervalle de temps exprimé en µs entre deux débordements successifs
* @return Le durée véritable qui a été configurée
**/
float Timer_1234_Init(TIM_TypeDef *Timer, float Duree_us );