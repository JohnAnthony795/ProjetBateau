#include "adc.h"

void Enable_ADC_Clock (ADC_TypeDef * ADC){
	if (ADC==ADC1)
		RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;
	else if(ADC==ADC2)
		RCC->APB2ENR|=RCC_APB2ENR_ADC2EN;
	else if (ADC==ADC3)
		RCC->APB2ENR|=0x1<<15;
}

void Init_Sample_Time (ADC_TypeDef * ADC, float cyclesAcq, u16 ADC_input_channel) {
		int sampleTimeBin = 0;
				
		if (cyclesAcq < 4.5f)
			sampleTimeBin = 0b0;
		else if (cyclesAcq < 10.5)
			sampleTimeBin = 0b1;
		else if (cyclesAcq < 21)
			sampleTimeBin = 0b10;
		else if (cyclesAcq < 35)
			sampleTimeBin = 0b11;
		else if (cyclesAcq < 48.5)
			sampleTimeBin = 0b100;
		else if (cyclesAcq < 63.5)
			sampleTimeBin = 0b101;
		else if (cyclesAcq < 155.5)
			sampleTimeBin = 0b110;
		else
			sampleTimeBin = 0b111;
		if (ADC_input_channel <= 9)
			ADC->SMPR2 |= (sampleTimeBin << (ADC_input_channel * 3));
		else
			ADC->SMPR1 |= (sampleTimeBin << ((ADC_input_channel - 10) * 3));
}

//On initialise la channel 0 de l'ADC passé en paramètre
float Init_ADC_Single_Conv(ADC_TypeDef * ADC,u16 Duree_Acq_us, u16 ADC_input_channel)
{
		//on active le RCC
    Enable_ADC_Clock(ADC);
		ADC->CR2&=~0x1;
		int i=0;
		while(i<=10000){i++;}

		//calibrer 
		ADC->CR2|=0x5;
		while((ADC->CR2&0x4)==1){}
		
		//en supposant ADCCLK = 12MHz, on règle la durée d'acq
		Init_Sample_Time(ADC, Duree_Acq_us/(1.0f/12.0f), ADC_input_channel);
			
		//on initialise le NVIC pour récupérer l'interruption de l'ADC
		//on initialise l'ADC pour lever une IT en cas de EOC
			
		//on lance la conversion
		return  1.0;

}


