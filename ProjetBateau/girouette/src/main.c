//__________________________________________________________
// BINOME :
// ETAT : 
//__________________________________________________________

//____ registres de périphériques du stm_32
#include "stm32f10x.h"
#include "girouette.c"

void (*pFnc) (void);

void EXTI9_5_IRQHandler (void) {
	
	if (pFnc != 0)
		(*pFnc) ();
	
	EXTI_ClearITPendingBit(5);
}  

int main (void)
{
	Config_Girouette();
	int i = 0;
	while (1) {
		i = 3;
	}
	return 0;
}

