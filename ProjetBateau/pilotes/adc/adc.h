#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"
#include "clock/clock.h"
#include "gpio/gpio.h"
#include "timer/Timer_1234.h"


float Init_ADC_Single_Conv(ADC_TypeDef * ADC,u16 Duree_Acq_us, u16 ADC_input_channel);
void Init_Sample_Time (ADC_TypeDef * ADC, float cyclesAcq, u16 ADC_input_channel);
void Enable_ADC_Clock (ADC_TypeDef * ADC);

#endif
