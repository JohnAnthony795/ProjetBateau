
#include "stm32f10x.h"


/** 
* Configure les Timers 1, 2, 3 et 4
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef) du timer consid�r�
* @param Duree_us Intervalle de temps exprim� en �s entre deux d�bordements successifs
* @return Le dur�e v�ritable qui a �t� configur�e
**/
float Timer_1234_Init(TIM_TypeDef *Timer, float Duree_us );