#include "gpio.h"


char Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Broche)
{
	char resultat;
	if(Broche <=7){
		Port->CRL=(Port->CRL | (0x1<<(Broche*4)))&(~(0x7<<(Broche*4+1)));
		resultat=((Port->CRL>>Broche*4)==0x1);
	}else{
		Port->CRH=(Port->CRH | (0x1<<((Broche-8)*4)))&(~(0x7<<((Broche-8)*4+1)));
		resultat=((Port->CRH>>(Broche-8)*4)==0x1);
	}
	return resultat;
}
	
char Port_IO_Init_Input( GPIO_TypeDef * Port, u8  Broche)
{
	char resultat;
	if(Broche <=7){
		Port->CRL=(Port->CRL | (0x1<<(Broche*4+2)))&(~(0x11<<(Broche*4)));
		resultat=((Port->CRL>>Broche*4)==0x4);
	}else{
		Port->CRH=(Port->CRH | (0x1<<((Broche-8)*4+2)))&(~(0x11<<((Broche-8)*4)));
		resultat=((Port->CRH>>(Broche-8)*4)==0x4);
	}
	return resultat;
}
	
void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche)
{
	if(Broche<=15){
		Port->BSRR=Port->BSRR|(0x1<<Broche);
	}
	//& si Broche >15 erreur;
}
	
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche)
{
	if(Broche<=15){
		Port->BSRR=Port->BSRR|(0x1<<(Broche+16));
		Port->BSRR=Port->BSRR&(~(0x1<<(Broche)));
	}
	//& si Broche >15 erreur;
}

void Port_IO_SR(GPIO_TypeDef * Port, u8 Broche, char SetReset)
{
	if (SetReset)
		Port_IO_Reset(Port,Broche);
	else
		Port_IO_Set(Port,Broche);
}
	
void Port_IO_Blink(GPIO_TypeDef * Port, u8 Broche)
{
	if ((Port->ODR>>Broche)&(0x0001)){
		Port_IO_Reset(Port,Broche);
	}else{
		Port_IO_Set(Port,Broche);
	}
}
	
unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche)
{
	if(Broche<=15){
		return ((Port->IDR>>Broche)&(0x0001));
	}else{
		return 2;
	}
}
	
