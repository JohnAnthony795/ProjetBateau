#include "stm32f10x.h"

char Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Broche);
char Port_IO_Init_Input( GPIO_TypeDef * Port, u8  Broche);
void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche);
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche);
void Port_IO_SR(GPIO_TypeDef * Port, u8 Broche, char SetReset);
void Port_IO_Blink(GPIO_TypeDef * Port, u8 Broche);
unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche);

